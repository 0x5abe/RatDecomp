#include "CameraOccluder_Z.h"
#include "Renderer_Z.h"
#include "World_Z.h"
#include "Camera_Z.h"

void CameraOccluder_Z::Init() {
    Manipulator_Z::Init();
    SetGroup(ag_camera_occlusion);
    m_ViewportId = -1;
}

void CameraOccluder_Z::Update(Float i_DeltaTime) {
    if (gData.MainRdr->GetNbViewport() <= m_ViewportId) {
        return;
    }

    Viewport_Z& l_Vp = gData.MainRdr->GetViewport(m_ViewportId);
    l_Vp.UpdateFrustrum();

    World_Z* l_World = (World_Z*)GETPTR(l_Vp.GetWorld());
    Node_Z* l_CamNode = (Node_Z*)GETPTR(l_Vp.GetCamera());
    if (!l_World || !l_CamNode) {
        return;
    }

    Camera_Z* l_Camera = (Camera_Z*)l_CamNode->GetObjectA();
    if (!l_World->GetNbOccluder()) {
        l_Camera->NoOcclusion();
    }
    else {
        l_Camera->DoOcclusion(l_World->GetOccluder(0));
    }
}
