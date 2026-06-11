#ifndef _ROTSHAPEGC_Z_H_
#define _ROTSHAPEGC_Z_H_
#include "RotShape_Z.h"

class RotShapeGC_Z : public RotShape_Z {
public:
    virtual ~RotShapeGC_Z();
    virtual void Draw(DrawInfo_Z& i_DrawInfo, ObjectDatas_Z* i_Data);

    static BaseObject_Z* NewObject() {
        return NewL_Z(50) RotShapeGC_Z;
    }

private:
    U8 m_Pad_0xd0[16];
};

class RotShapeGCData_Z : public RotShapeData_Z {
public:
    virtual ~RotShapeGCData_Z();
    virtual void Load(void** i_Data);
    virtual void UpdatePointers(Object_Z* i_Obj, S32 i_Param = -1);
    virtual void Clone(ObjectDatas_ZHdl& o_ObjectDatasHdl, Object_ZHdl& o_ObjectHdl);

    static BaseObject_Z* NewObject() {
        return NewL_Z(77) RotShapeGCData_Z;
    }

private:
    U8 m_Pad_0x38[40];
};

#endif // _ROTSHAPEGC_Z_H_
