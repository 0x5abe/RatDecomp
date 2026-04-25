#include "StreamManager_Z.h"
#include "KSys_Z.h"
#include "Math_Z.h"
#include "Memory_Z.h"

S16 StreamManager_Z::readId = 0;
U32 LastError;

StreamManager_Z::StreamManager_Z() {
    m_Finished = FALSE;
    m_Retrying = FALSE;
    m_SuccessfulRetry = FALSE;
    m_LastError = STR_ERROR_NONE;
}

Bool StreamManager_Z::Open(const Char* i_FilePath, BaseStream_Z* i_Stream, void* i_UnkPtr_0x160, S32 i_UnkS32_0x164, S32 i_UserDefined) {
    SharedResourceGuard_Z l_StreamLock(m_StreamMutex);

    String_Z<ARRAY_CHAR_MAX> l_UpperCasePath;
    l_UpperCasePath.StrCpy(i_FilePath);
    l_UpperCasePath.Upr();

    S32 i;
    for (i = 0; i < m_OpenOps.GetSize(); i++) {
        if (m_OpenOps[i].m_Status == OpenOp::Finished) {
            break;
        }
        if (m_OpenOps[i].m_FilePath.StrCmp(l_UpperCasePath) == FALSE) {
            return FALSE;
        }
    }

    if (i == m_OpenOps.GetSize()) {
        if (m_OpenOps.IsFull()) {
            return FALSE;
        }
        i = m_OpenOps.Add();
    }

    OpenOp& l_OpenOp = m_OpenOps[i];
    l_OpenOp.m_Status = OpenOp::Start;
    builtin_memcpy(l_OpenOp.m_FilePath, l_UpperCasePath, ARRAY_CHAR_MAX);
    l_OpenOp.m_UserDefined = i_UserDefined;
    l_OpenOp.m_UnkPtr_0x160 = i_UnkPtr_0x160;
    l_OpenOp.m_UnkS32_0x164 = i_UnkS32_0x164;
    l_OpenOp.m_UserDefined = i_UserDefined;
    l_OpenOp.m_OpenStreamInterface = i_Stream;
    l_OpenOp.m_CloseStreamInterface = i_Stream;
    ASSERTLE_Z(l_OpenOp.m_OpenStreamInterface, "", 51, "Op.openStreamInterface");
    l_OpenOp.m_OpenStreamInterface->SetStreamId(i);
    l_OpenOp.m_OpenStreamInterface->SetReadId(-1);

    return TRUE;
}

BaseStream_Z& BaseStream_Z::operator=(const BaseStream_Z& i_Other) {
    ASSERTLE_Z(GetID().Ref.m_StreamId == -1 && GetID().Ref.m_ReadId == -1, "", 61, "GetID().Ref.m_StreamId==-1&&GetID().Ref.m_ReadId==-1");
    SetStreamId(i_Other.GetID().Ref.m_StreamId);
    SetReadId(-1);
    return *this;
}

Bool StreamManager_Z::Read(void* i_Buffer, S32 i_StartOffset, S32 i_BytesToRead, BaseStream_Z* i_Stream, S32 i_UserDefined) {
    SharedResourceGuard_Z l_StreamLock(m_StreamMutex);

    if (i_Stream->GetID().Ref.m_ReadId == -1) {
        if (++readId == -1) {
            readId++;
        }
        i_Stream->SetReadId(readId);
    }

    S16 l_ReadId;
    S16 l_OpenId;
    l_OpenId = i_Stream->GetID().Ref.m_StreamId;
    l_ReadId = i_Stream->GetID().Ref.m_ReadId;
    ASSERTLE_Z(l_OpenId >= 0, "", 88, "openId>=0L");
    ASSERTLE_Z(l_OpenId < m_OpenOps.GetSize(), "", 89, "openId<OpenOps.GetSize()");
    OpenOp& l_RefOp = m_OpenOps[l_OpenId];
    ASSERTLE_Z(l_RefOp.m_Status == OpenOp::Open, "", 91, "RefOp.status==OpenOp::Opened");

    S32 l_Size = m_ReadOps.GetSize();
    S32 i = 0;
    while (i < l_Size) {
        if (m_ReadOps[i].m_Status == ReadOp::Finished) {
            break;
        }
        i++;
    }

    if (i == l_Size) {
        if (m_ReadOps.IsFull()) {
            return FALSE;
        }
        i = m_ReadOps.Add();
    }

    ReadOp& l_ReadOp = m_ReadOps[i];
    l_ReadOp.m_Status = ReadOp::Start;
    l_ReadOp.m_StreamID.Ref.m_StreamId = l_OpenId;
    l_ReadOp.m_StreamID.Ref.m_ReadId = l_ReadId;
    l_ReadOp.m_Buffer = (Char*)i_Buffer;
    l_ReadOp.m_StartOffset = (Char*)i_StartOffset;
    l_ReadOp.m_BytesToRead = i_BytesToRead;
    l_ReadOp.m_UserDefined = i_UserDefined;
    l_ReadOp.m_BytesRead = 0;
    l_ReadOp.m_Stream = i_Stream;

    return TRUE;
}

Bool StreamManager_Z::Close(BaseStream_Z* i_Stream, Bool i_CloseAllReadsForFile) {
    S16 l_ReadId;
    S16 l_OpenId;
    l_OpenId = i_Stream->GetID().Ref.m_StreamId;
    l_ReadId = i_Stream->GetID().Ref.m_ReadId;
    if (l_OpenId == -1 && l_ReadId == -1) {
        return TRUE;
    }

    m_ReadyToCloseEvent.Wait(-1);

    SharedResourceGuard_Z l_StreamLock(m_StreamMutex);

    SharedResourceGuard_Z l_ReadLock(m_ReadMutex);

    if (i_CloseAllReadsForFile && l_OpenId >= 0) {
        OpenOp& l_OpenOp = m_OpenOps[l_OpenId];
        ASSERTBOOL_Z(l_OpenOp.m_CloseStreamInterface ? TRUE : FALSE, "Op.closeStreamInterface (%d) %s", l_OpenId, l_OpenOp.m_FilePath.CStr());
        ASSERTBOOL_Z((S16)l_OpenId == l_OpenOp.m_CloseStreamInterface->GetID().Ref.m_StreamId, "openId==Op.closeStreamInterface->GetID().Ref.m_StreamId (%d==%d) %s", l_OpenId, l_OpenOp.m_CloseStreamInterface->GetID().Ref.m_StreamId, l_OpenOp.m_FilePath.CStr());

        l_OpenOp.m_FilePath.Empty();
        l_OpenOp.m_Status = OpenOp::CloseRequested;
        l_OpenOp.m_CloseStreamInterface->SetReadId(-1);
        l_OpenOp.m_CloseStreamInterface->SetStreamId(-1);
    }

    for (S32 i = 0; i < m_ReadOps.GetSize(); i++) {
        ReadOp& l_ReadOp = m_ReadOps[i];
        if (l_ReadOp.m_StreamID.Ref.m_StreamId != l_OpenId) {
            continue;
        }
        S32 l_Status = l_ReadOp.m_Status;
        if (l_Status == ReadOp::Finished) {
            continue;
        }
        if (!i_CloseAllReadsForFile && l_ReadOp.m_StreamID.Ref.m_ReadId != l_ReadId) {
            continue;
        }
        if (l_Status == ReadOp::Start) {
            l_ReadOp.m_Status = ReadOp::CloseRequested;
        }
        else {
            l_ReadOp.m_Status = ReadOp::Finished;
        }
        l_ReadOp.m_StreamID.Ref.m_StreamId = -1;
        l_ReadOp.m_StreamID.Ref.m_ReadId = -1;
        l_ReadOp.m_Stream->SetReadId(-1);
        l_ReadOp.m_Stream->SetStreamId(-1);
        l_ReadOp.m_Stream = NULL;
    }

    i_Stream->SetReadId(-1);
    i_Stream->SetStreamId(-1);

    return TRUE;
}

Bool StreamManager_Z::Heartbeat(Float i_DeltaTime) {
    SharedResourceGuard_Z l_StreamLock(m_StreamMutex);

    if (m_LastError != STR_ERROR_NONE && (!m_Retrying || (m_SuccessfulRetry == TRUE))) {
        return FALSE;
    }

    for (S16 i = 0; i < m_ReadOps.GetSize(); i++) {
        ReadOp& l_ReadOp = m_ReadOps[i];
        if (l_ReadOp.m_Status == ReadOp::Readed) {
            l_ReadOp.m_Status = ReadOp::Finished;
            l_ReadOp.m_Stream->StreamReaded(l_ReadOp.m_BytesToRead, l_ReadOp.m_UserDefined);
        }
        else if (l_ReadOp.m_Status == ReadOp::Failed) {
            l_ReadOp.m_Status = ReadOp::Start;
            m_OpenOps[l_ReadOp.m_StreamID.Ref.m_StreamId].m_Status = OpenOp::Failed;
        }
        else if (l_ReadOp.m_Status == ReadOp::CloseRequested) {
            l_ReadOp.m_Status = ReadOp::Finished;
        }
    }

    for (S16 i = 0; i < m_OpenOps.GetSize(); i++) {
        OpenOp& l_OpenOp = m_OpenOps[i];
        if (l_OpenOp.m_Status == OpenOp::Retry) {
            l_OpenOp.m_Status = OpenOp::Start;
        }
        else if (l_OpenOp.m_Status == OpenOp::Opened) {
            BaseStream_Z* l_OpenStream = l_OpenOp.m_OpenStreamInterface;
            l_OpenOp.m_Status = OpenOp::Open;
            l_OpenOp.m_OpenStreamInterface = NULL;
            if (l_OpenStream) {
                l_OpenStream->StreamOpened(l_OpenOp.m_FileSize, l_OpenOp.m_UserDefined);
            }
        }
        else if (l_OpenOp.m_Status == OpenOp::Closed) {
            l_OpenOp.m_Status = OpenOp::Finished;
        }
    }

    if (m_Retrying) {
        m_SuccessfulRetry = TRUE;
    }
    m_Retrying = FALSE;

    return TRUE;
}

void StreamManager_Z::Thread() {
    if (m_LastError != STR_ERROR_NONE && !m_SuccessfulRetry) {
        return;
    }

    LastError = STR_ERROR_NONE;
    S32 i = 0;
    OpenOp* l_OpenOp = NULL;
    while (LastError == STR_ERROR_NONE) {

        {
            SharedResourceGuard_Z l_StreamLock(m_StreamMutex);

            if (i >= m_OpenOps.GetSize()) {
                break;
            }

            l_OpenOp = &m_OpenOps[i];
            if (!l_OpenOp->NeedsProcessing()) {
                i++;
                continue;
            }
        }

        if (l_OpenOp && l_OpenOp->NeedsProcessing()) {
            if (l_OpenOp->m_Status == OpenOp::Failed) {
                Bool l_Result = m_OpenOps[i].m_FileHdl.Close();

                SharedResourceGuard_Z l_Lock(m_StreamMutex);

                U32 l_Error = STR_ERROR_NONE;
                if (l_Result) {
                    l_OpenOp->m_Status = OpenOp::Start;
                }
                else {
                    LastError = STR_ERROR_UNKNOWN;
                }
            }
            if (l_OpenOp->m_Status == OpenOp::CloseRequested) {
                m_OpenOps[i].m_FileHdl.Close();

                SharedResourceGuard_Z l_Lock(m_StreamMutex);

                l_OpenOp->m_Status = OpenOp::Closed;
            }
            if (l_OpenOp->m_Status == OpenOp::Start) {
                String_Z<248> l_SysFilePath;
                PathKDBToSys(m_OpenOps[i].m_FilePath, l_SysFilePath);
                m_OpenOps[i].m_FileHdl.Open(l_SysFilePath, STR_READ_ONLY);
                LastError = m_OpenOps[i].m_FileHdl.GetLastError();

                SharedResourceGuard_Z l_Lock(m_StreamMutex);

                if (l_OpenOp->m_Status == OpenOp::Start) {
                    if (LastError == STR_ERROR_NONE) {
                        m_OpenOps[i].m_FileSize = l_OpenOp->m_FileHdl.GetSize();
                        l_OpenOp->m_Status = OpenOp::Opened;
                    }
                    else {
                        l_OpenOp->m_Status = OpenOp::Retry;
                    }
                }
            }
        }
    }

    i = 0;
    ReadOp* l_ReadOp = NULL;
    while (LastError == STR_ERROR_NONE) {
        SharedResourceGuard_Z l_StreamLock(m_StreamMutex);

        if (i >= m_ReadOps.GetSize()) {
            break;
        }
        if (m_ReadOps[i].m_Status != ReadOp::Start) {
            i++;
            continue;
        }

        l_ReadOp = &m_ReadOps[i];
        break;
    }
    if (l_ReadOp && l_ReadOp->NeedsProcessing()) {
        S16 l_OpenId = l_ReadOp->GetStreamID().Ref.m_StreamId;
        OpenOp* l_Open = &m_OpenOps[l_OpenId];

        S32 l_ReadSize = Min((S32)STR_MAX_READ_SIZE, l_ReadOp->m_BytesToRead - l_ReadOp->m_BytesRead);

        {
            SharedResourceGuard_Z l_ReadLock(m_ReadMutex);

            S32 l_SeekPos = (S32)l_ReadOp->m_StartOffset + l_ReadOp->m_BytesRead;

            if ((S32)l_Open->m_FileHdl.Seek(l_SeekPos, FILE_SEEK_START) == (S32)l_ReadOp->m_StartOffset + l_ReadOp->m_BytesRead) {
                l_Open->m_FileHdl.Read(l_ReadOp->m_Buffer + l_ReadOp->m_BytesRead, l_ReadSize);
            }

            LastError = l_Open->m_FileHdl.GetLastError();
        }

        SharedResourceGuard_Z l_StreamLock(m_StreamMutex);

        if (l_ReadOp->m_Status == ReadOp::Start) {
            if (LastError == STR_ERROR_NONE) {
                l_ReadOp->m_BytesRead = l_ReadOp->m_BytesRead + l_ReadSize;
                if (l_ReadOp->m_BytesRead == l_ReadOp->m_BytesToRead) {
                    l_ReadOp->m_Status = ReadOp::Readed;
                }
            }
            else {
                l_ReadOp->m_Status = ReadOp::Failed;
            }
        }
    }

    m_SuccessfulRetry = FALSE;
    m_LastError = LastError;
}
