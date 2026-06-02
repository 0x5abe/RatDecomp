#include "SoundManager_Z.h"
#include "Console_Z.h"
#include "ABC_ScriptManager.h"
#include "DebugTools_Z.h"
#include "Occluder_Z.h"

static Char SndMgrStatusString[ARRAY_CHAR_MAX];

ExternC_Z int rand();

SoundManager_Z::SoundManager_Z() {
    REGISTERCOMMANDC("PlayMUsic", Cmd_PlayMusic, " MusicName");
    REGISTERCOMMANDC("PlayDIalog", Cmd_PlayDialog, " Id");
    REGISTERCOMMANDC("StopMUsic", Cmd_StopMusic, " MusicName");
    REGISTERCOMMANDC("OpenSBF", Cmd_OpenSBF, " BigFileName");
    REGISTERCOMMAND("CloseSBF", Cmd_CloseSBF);

    for (S32 i = 0; i < SND_MGR_MAX_TRACKS; i++) {
        FreeTrack(i);
        m_Tracks[i].m_RandValues = Vec4f(rand() / 65536.0f, rand() / 65536.0f, rand() / 65536.0f, 1.0f);
    }

    m_NbFreeTracks = 0;
    m_MuteStateFlag = 0;
    m_RandomFreqScaleLow = 0.05f;
    m_RandomFreqScaleHigh = 0.0f;
    m_MusicVolume = 1.0f;
    m_MusicVolumeSecondary = 1.0f;
    m_SfxVolume = 1.0f;
    m_SfxVolumeSecondary = 1.0f;
    m_DialogVolume = 1.0f;
    m_DialogVolumeSecondary = 1.0f;
    m_SoundMode = 2;
    m_NbTracksFailedToPlay = 0;
}

Bool SoundManager_Z::Init() {
    return TRUE;
}

void SoundManager_Z::FreeTrack(S32 i_TrackIdx) {
    if (i_TrackIdx < 0) {
        return;
    }

    m_Tracks[i_TrackIdx].Release();
}

Bool Track_Z::Release() {
    Bool l_Used = m_Used;

    if (m_AgentHdl.IsValid()) {
        gData.ScriptMgr->Send(m_MsgToSend, m_AgentHdl);
    }

    m_Flags = FL_TRACK_NONE;
    m_BoneNode = NULL;
    m_Used = FALSE;
    m_LifeTime = 0.0f;
    m_DistanceCamToSound = 0.0f;
    m_SoundHdl = HANDLE_NULL;
    m_NodeHdl = HANDLE_NULL;
    m_AgentHdl = HANDLE_NULL;
    m_FrameRequestedNb = gData.m_FrameCount;
    m_UnkZoneId = -1;
    m_CamOccluderZoneId = -1;
    m_SoundOccluderZoneId = -1;
    m_OcclusionFactor = 1.0f;

    return l_Used;
}

void SoundManager_Z::Update(Float i_DeltaTime) {
    if (m_Music.UpdateFade(i_DeltaTime)) {
        StopMusic(0.0f);
        if (m_Music.m_FilePath.StrLen()) {
            PlayMusic(m_Music.m_FilePath, m_Music.m_Flag, 0.0f, 0.0f);
        }
    }

    S32 l_VpNb = gData.MainRdr->GetNbViewport();
    S32 i;
    for (i = 0; i < l_VpNb; i++) {
        Occluder_Z* l_Occluder = gData.MainRdr->GetViewport(i).GetOccluder();
        if (l_Occluder) {
            l_Occluder->GetZone(gData.MainRdr->GetViewport(i).GetCameraPos(), m_VpOccluderZoneIds[i]);
        }
        else {
            m_VpOccluderZoneIds[i] = -1;
        }
    }
    while (i < SND_MGR_MAX_OCCLUDER_ZONE_IDS) {
        m_VpOccluderZoneIds[i] = -1;
        i++;
    }
}

void SoundManager_Z::Draw(DrawInfo_Z& i_DrawInfo) {
    if (!(gData.m_EngineFlag & FL_DEBUG_SOUND)) {
        return;
    }

    // TODO: Implement debug draw
}

Bool Cmd_PlayMusic() {
    return TRUE;
}

Bool Cmd_StopMusic() {
    return TRUE;
}

Bool Cmd_OpenSBF() {
    return TRUE;
}

Bool Cmd_CloseSBF() {
    return TRUE;
}

Bool Cmd_PlayDialog() {
    return TRUE;
}
