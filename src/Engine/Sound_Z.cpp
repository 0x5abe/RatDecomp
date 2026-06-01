#include "Sound_Z.h"
#include "Program_Z.h"
#include "SoundManager_Z.h"

Sound_Z::Sound_Z() {
    Init();
}

Sound_Z::~Sound_Z() {
    Reset();
}

void Sound_Z::Init() {
    m_Data = NULL;
    m_Flag = 0;
    m_XRamBlock = -1;
    m_Frequency = 0;
    m_Unk0x1D = 0;
    m_SoundSize = 0;
}

void Sound_Z::Reset() {
    if (gData.SoundMgr && m_XRamBlock != -1) {
        gData.SoundMgr->FreeSound((void*)m_XRamBlock);
    }
    if (m_Data) {
        Free_Z(m_Data);
    }
    Init();
}
