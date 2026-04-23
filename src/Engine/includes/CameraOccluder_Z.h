#ifndef _CAMERAOCCLUDER_Z_H_
#define _CAMERAOCCLUDER_Z_H_
#include "Manipulator_Z.h"

class CameraOccluder_Z : public Manipulator_Z {
public:
    virtual ~CameraOccluder_Z() { }

    virtual void Init();
    virtual void Update(Float i_DeltaTime);

    static BaseObject_Z* NewObject() { return NewL_Z(22) CameraOccluder_Z; }

    void SetViewportId(const S32 i_ViewportId) {
        m_ViewportId = i_ViewportId;
    }

    S32 m_ViewportId;
};

#endif // _CAMERAOCCLUDER_Z_H_
