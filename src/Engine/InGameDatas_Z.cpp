#include "InGameDatas_Z.h"
#include "Program_Z.h"

InGameDatas_Z::~InGameDatas_Z() {
    if (!gData.MainRdr || !IsActive()) {
        return;
    }
    DeactivateDatas();
}

void InGameDatas_Z::SetViewport(S32 i_VpId) {
    m_ViewportId = i_VpId;
    RecalcPositions();
}

void InGameDatas_Z::RecalcPositions() { }

void InGameDatas_Z::ActivateDatas(S32 i_VpId) {
    if (IsActive()) {
        return;
    }
    SetViewport(i_VpId);
    VpRegister();
    Activate();
}

void InGameDatas_Z::DeactivateDatas() {
    if (!IsActive()) {
        return;
    }
    VpUnRegister();
    Deactivate();
}
