#ifndef _GCINPUT_Z_H_
#define _GCINPUT_Z_H_
#include "InputEngine_Z.h"
#include <pad.h>

class GCInput_Z : public InputPlatForm_Z {
public:
    GCInput_Z();
    virtual ~GCInput_Z();
    virtual Bool Init();
    virtual void Shut();
    virtual void AddDevice();
    virtual void ResetPads();
    virtual void RemoveDevice(S32 a1);
    virtual void UpdateInput(Float a1);
    virtual void IsButtonPressed(U8 a1);
    virtual void Vibration(S32 a1, U8 a2, U8 a3);
    virtual void GetDeviceStatus(S32 a1, S32 a2);
    virtual void GetControl(InputDevice_Z* a1, S32 a2, void* a3, bool a4);
    virtual void ResetPad(S16 a1);

private:
    PADStatus m_PadStatus[4];
    U8 m_Unk_0x9c[32];
};

#endif // _GCINPUT_Z_H_
