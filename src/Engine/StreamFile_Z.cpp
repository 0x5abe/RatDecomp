#include "StreamFile_Z.h"
#include "Handle_Z.h"
#include "Renderer_Z.h"
#include "Timer_Z.h"

U8 StreamFile_Z::gBigFileHeader[sizeof(BigFileHeader_Z)];
Float StartLoadingTime;

void StreamFile_Z::Init() {
    Manipulator_Z::Init();
    SetGroup(ag_notpaused_last);
    m_LoadStage = STR_FILE_LOAD_STAGE_INIT;
}

void StreamFile_Z::Start(const Char* i_FilePath, const StreamAgent_ZHdl& i_AgentHdl) {
    m_AgentHdl = i_AgentHdl;
    StartLoadingTime = GetAbsoluteTime();
    m_BfPath.StrCpy(i_FilePath);
    gData.ClassMgr->SetBigFileOpened(TRUE);
    gData.Cons->EnableFlag(FL_CONSOLE_PAUSED);
    m_RestoreVSync = gData.MainRdr->IsEffectFlag(FL_EFFECT_VSYNC);
    gData.MainRdr->DisableEffectFlag(FL_EFFECT_VSYNC);
    g_BigFileHeader.m_VersionString[0] = '\0';
    m_LoadStage = 0;
    m_LoadStageBeforeResume = 0;
    m_CurBlockIdx = 0;
    Activate();
    m_Str.m_LoadStage = STR_FILE_LOAD_STAGE_INIT;
    m_Str.m_ErrorCode = STR_FILE_ERROR_NONE;
}

void StreamFile_Z::Update(Float i_DeltaTime) {
    if (!m_IsActive) {
        return;
    }

    m_Str.Update();
}
