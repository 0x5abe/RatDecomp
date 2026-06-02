#include "FileHdl_Z.h"
#include "StreamManager_Z.h"
#include "Assert_Z.h"
// $VIOLET: TODO: Actually implement these in file_io.c
ExternC_Z FILE* fopen(const Char* i_FilePath, const Char* i_Mode);

Bool FileHdl_Z::Open(const Char* i_FilePath, U32 i_Flags) {
    ASSERTL_Z(!IsOpened(), "", 6);

    Char l_FileName[128];
    Bool l_Result = GetRealFileName(i_FilePath, l_FileName);
    m_LastError = STR_ERROR_NONE;

    if (i_Flags & STR_READ_ONLY) {
        if (l_Result) {
            m_EntryNum = DVDConvertPathToEntrynum(l_FileName);
            if (m_EntryNum >= 0 && DVDFastOpen(m_EntryNum, &m_DvdFileInfo) == FALSE) {
                Close();
            }
            SetError(!IsOpened() ? STR_ERROR_UNKNOWN : STR_ERROR_NONE);
        }
        else {
            m_File = fopen(l_FileName, "rb");
        }
    }
    else if (i_Flags & STR_WRITE_ONLY) {
        m_File = fopen(l_FileName, "wb");
    }

    m_LastError = !IsOpened() ? STR_ERROR_UNKNOWN : STR_ERROR_NONE;
    return m_LastError == STR_ERROR_NONE;
}

void FileHdl_Z::SetError(U32 i_Error) {
    if (i_Error == STR_ERROR_NONE) {
        return;
    }
    if (i_Error != STR_ERROR_UNKNOWN) {
        m_LastError = i_Error;
        return;
    }

    m_LastError = STR_ERROR_UNKNOWN;

    S32 l_BlockStatus;
    for (;;) {
        l_BlockStatus = DVDGetCommandBlockStatus(&m_DvdFileInfo.cb);
        if (l_BlockStatus != DVD_STATE_BUSY && l_BlockStatus != DVD_STATE_WAITING) break;
    }

    switch (l_BlockStatus) {
        case DVD_STATE_NO_DISK:
            m_LastError = STR_ERROR_NO_DISK;
            break;
        case DVD_STATE_COVER_OPEN:
            m_LastError = STR_ERROR_COVER_OPEN;
            break;
        case DVD_STATE_WRONG_DISK:
            m_LastError = STR_ERROR_WRONG_DISK;
            break;
        case DVD_STATE_RETRY:
            m_LastError = STR_ERROR_RETRY;
            break;
        case DVD_STATE_FATAL_ERROR:
            m_LastError = STR_ERROR_FATAL;
    }
}
