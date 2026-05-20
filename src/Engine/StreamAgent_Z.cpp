#include "StreamAgent_Z.h"
#include "ABC_Message_Engine.h"
#include "StreamFile_Z.h"
#include "KSys_Z.h"
#include "StreamFile_Z.h"

// clang-format off

BEGIN_INIT_AGENT_CLASS(StreamAgent_Z, ABC_Agent)
    ADD_BEHAVIOR(StreamEnd)
    ADD_BEHAVIOR(StreamAborted)
    ADD_BEHAVIOR(StreamError)
    ADD_BEHAVIOR(StreamResumed)
END_INIT_AGENT_CLASS

BEHAVIOR(StreamAgent_Z,StreamEnd)
    CATEGORY(cat_running_stream)
BEGIN_BEHAVIOR
    CONDITION
        Message(msg_stream_end)
    ACTION
        End();
END_BEHAVIOR

BEHAVIOR(StreamAgent_Z,StreamError)
    CATEGORY(cat_running_stream)
BEGIN_BEHAVIOR
    CONDITION
        Message(msg_stream_error)
    ACTION
        Resume(m_StreamHdl->GetStream().GetErrorCode());
END_BEHAVIOR

BEHAVIOR(StreamAgent_Z,StreamResumed)
    CATEGORY(cat_running_stream)
BEGIN_BEHAVIOR
    CONDITION
        Message(msg_stream_resumed)
    ACTION
        Resumed();
END_BEHAVIOR

BEHAVIOR(StreamAgent_Z,StreamAborted)
    CATEGORY(cat_running_stream)
BEGIN_BEHAVIOR
    CONDITION
        Message(msg_stream_aborted)
    ACTION
        Aborted();
END_BEHAVIOR

// clang-format on

Bool StreamAgent_Z::MarkHandles() {
    if (!ABC_Agent::MarkHandles()) {
        return FALSE;
    }

    if (m_StreamHdl) {
        m_StreamHdl->MarkHandles();
    }

    return TRUE;
}

void StreamAgent_Z::OpenBigFile(const Char* i_BfName) {
    Name_Z l_BfName(i_BfName);
    Name_Z l_ClassName = Name_Z::GetID("StreamFile_Z");
    m_StreamHdl = gData.ClassMgr->NewObject(l_ClassName, l_BfName);

    String_Z<ARRAY_CHAR_MAX> l_SysPath;
    PathKDBToSys(i_BfName, l_SysPath);

    m_StreamHdl->Start(l_SysPath, GetHandle());
    Start();
    ActivateCategory(cat_running_stream);
}

void StreamAgent_Z::End() {
    DeactivateCategory(cat_running_stream);
}

void StreamAgent_Z::Abort() {
    m_StreamHdl->SetLoadStage(STR_FILE_LOAD_STAGE_ABORT);
}

void StreamAgent_Z::Aborted() {
    DeactivateCategory(cat_running_stream);
}

void StreamAgent_Z::Resume(S32 i_Cause) {
    m_StreamHdl->Resume();
}
