#ifndef _INPUTACTION_Z_H_
#define _INPUTACTION_Z_H_

#include "DynArray_Z.h"
#include "Main_Z.h"
#include "Math_Z.h"
#include "HoleArray_Z.h"

struct InputDevice_Z {
    U8 m_Pad_0x0[0x316];
    Bool m_AnyDPadPressed;
    U8 m_Pad_0x317[0x3];
    Bool m_DPadUpPressed;
    Bool m_DPadDownPressed;
    Bool m_DPadLeftPressed;
    Bool m_DPadRightPressed;
    U8 m_Pad_0x31e[0x36];

    inline Bool IsAnyDPadPressed() const {
        return m_AnyDPadPressed;
    }
};

struct InputAction_Z {
    Bool m_UnkBool_0x0;
    Bool m_UnkBool_0x1;
    Bool m_UnkBool_0x2;
    Float m_UnkFloat_0x4;
    Bool m_UnkBool_0x8;
    Bool m_UnkBool_0x9;
    Bool m_UnkBool_0xa;
    Float m_UnkFloat_0xc;
    Float m_UnkFloat_0x10;
    Float m_UnkFloat_0x14;
    Float m_BaseValue;
    Float m_MinValue;
    Float m_MaxValue;
    Float m_UnkFloat_0x24;
    S32 m_UnkS32_0x28;
    Float m_UnkFloat_0x2c;
    Bool m_Pressed;
    Bool m_UnkBool_0x31;
    Bool m_UnkBool_0x32;
    Float m_PressedTimer;
    Float m_SomeTimer_0x38;
    Float m_SomeOtherTimer_0x3c;
    S32 m_DeviceIdx;
    S32 m_ActionId;

    InputAction_Z() {
        m_UnkBool_0x0 = FALSE;
        m_Pressed = FALSE;
        m_UnkBool_0x31 = FALSE;
        m_UnkBool_0x32 = FALSE;
        m_PressedTimer = 0.0f;
        m_SomeTimer_0x38 = 0.0f;
        m_SomeOtherTimer_0x3c = 0.0f;
        m_UnkBool_0x1 = FALSE;
        m_DeviceIdx = -1;
        m_ActionId = -1;
        m_UnkBool_0x8 = FALSE;
        m_UnkBool_0x9 = FALSE;
        m_UnkFloat_0xc = 0.0f;
        m_UnkFloat_0x10 = 0.4f;
        m_UnkFloat_0x14 = 0.08f;
        m_UnkBool_0xa = FALSE;
        m_UnkFloat_0x4 = 0.0f;
        m_BaseValue = 0.5f;
        m_MinValue = 0.2f;
        m_MaxValue = 0.9f;
        m_UnkFloat_0x24 = 1.1f;
        m_UnkS32_0x28 = -1;
        m_UnkBool_0x2 = TRUE;
        m_UnkFloat_0x2c = 0.0f;
    }
};

struct InputActionContext_Z {
    S32 m_DeviceIdx;
    Bool m_AlwaysActive;
    DynArray_Z<InputAction_Z, 4> m_Actions;
    S32 m_UnkS32_0x10;
    S32 m_FirstActionIdx;

    S32 AddAction(S32 i_ActionId);
    InputAction_Z& GetAction(S32 i_ActionId);
    void Update(Float i_DeltaTime);
};

#endif // _INPUTACTION_Z_H_
