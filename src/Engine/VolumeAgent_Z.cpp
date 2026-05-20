#include "VolumeAgent_Z.h"
#include "Node_Z.h"
#include "CollisionVol_Z.h"

// clang-format off

BEGIN_INIT_AGENT_CLASS(VolumeAgent_Z, Agent_Z)
    ADD_BEHAVIOR(VolumeAnimReset)
END_INIT_AGENT_CLASS

BEHAVIOR(VolumeAgent_Z,VolumeAnimReset)
    CATEGORY(cat_default)
BEGIN_BEHAVIOR
    CONDITION
        Message(msg_volume_anim_reset)
    ACTION
        ResetAnims();
END_BEHAVIOR

// clang-format on

void VolumeAgent_Z::UseNode(Node_ZHdl& i_NodeHdl) {
    Agent_Z::UseNode(i_NodeHdl);
}

Float VolumeAgent_Z::GetFloatParam(S32 i_Index) {
    CollisionVol_Z* l_ColVol = (CollisionVol_Z*)m_NodeHdl->GetObjectA();
    return l_ColVol->GetFloatParam(i_Index);
}

Node_ZHdl& VolumeAgent_Z::GetNodeParam(S32 i_Index) const {
    CollisionVol_Z* l_ColVol = (CollisionVol_Z*)m_NodeHdl->GetObjectA();
    return l_ColVol->GetNodeParam(i_Index);
}

S32 VolumeAgent_Z::GetNbNodeAnim() const {
    CollisionVol_Z* l_ColVol = (CollisionVol_Z*)m_NodeHdl->GetObjectA();
    return l_ColVol->GetNodeAnimsCount();
}

AnimFrame_ZHdl& VolumeAgent_Z::GetNodeAnim(S32 i_Index) const {
    CollisionVol_Z* l_ColVol = (CollisionVol_Z*)m_NodeHdl->GetObjectA();
    return l_ColVol->GetNodeAnim(i_Index);
}

void VolumeAgent_Z::StartAnims() {
    CollisionVol_Z* l_ColVol = (CollisionVol_Z*)m_NodeHdl->GetObjectA();
    l_ColVol->StartNodeAnims();
    l_ColVol->StartMatAnims();
}

void VolumeAgent_Z::ResetAnims() {
    CollisionVol_Z* l_ColVol = (CollisionVol_Z*)m_NodeHdl->GetObjectA();
    l_ColVol->ResetNodeAnims();
    l_ColVol->ResetMatAnims();
}

void VolumeAgent_Z::Entering(const Agent_ZHdl& i_AgentHdl) {
    StartAnims();
}
