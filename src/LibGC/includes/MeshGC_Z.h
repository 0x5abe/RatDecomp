#ifndef _MESHGC_Z_H_
#define _MESHGC_Z_H_
#include "Mesh_Z.h"

class MeshGC_Z : public Mesh_Z {
public:
    virtual ~MeshGC_Z();
    virtual void Load(void** i_Data);
    virtual void AfterEndLoad();
    virtual void Clean();
    virtual void Draw(DrawInfo_Z& i_DrawInfo, ObjectDatas_Z* i_Data);
    virtual void DrawReceiveShadow(DrawInfo_Z& i_DrawInfo, ObjectDatas_Z* i_Data, S32 i_ObjID);
    virtual void DrawCastingShadow(DrawInfo_Z& i_DrawInfo, ObjectDatas_Z* i_Data);

    static BaseObject_Z* NewObject() {
        return NewL_Z(97) MeshGC_Z;
    }

private:
    U8 m_Pad_0x110[64];
};

class MeshDataGC_Z : public MeshData_Z {
public:
    virtual ~MeshDataGC_Z();
    virtual void AfterEndLoad();

    static BaseObject_Z* NewObject() {
        return NewL_Z(118) MeshDataGC_Z;
    }

private:
    U8 m_Pad_0x48[48];
};

#endif // _MESHGC_Z_H_
