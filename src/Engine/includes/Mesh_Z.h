#ifndef _MESH_Z_H_
#define _MESH_Z_H_
#include "Points_Z.h"
#include "Camera_Z.h"

class MeshData_Z : public PointsDatas_Z {
public:
    virtual ~MeshData_Z();
    virtual void Load(void* a1);
    virtual void Clone(ObjectDatas_ZHdl& o_ObjectDatasHdl, Object_ZHdl& o_ObjectHdl);
    virtual void IsBSphere(Node_Z* i_Node, Frustrum_Z& i_Frust, DrawInfo_Z& i_DrawInfo);

protected:
    U8 m_Pad_0x28[32];
};

class Mesh_Z : public Points_Z {
public:
    Mesh_Z();
    virtual ~Mesh_Z();
    virtual void Load(void** i_Data);
    virtual void EndLoad();
    virtual void AfterEndLoad();
    virtual void EndLoadLinks();
    virtual void Clean();
    virtual Bool MarkHandles();
    virtual void Draw(DrawInfo_Z& a1, ObjectDatas_Z* a2);
    virtual Bool GetCollisionLines(Node_Z* i_Node, ObjectDatas_Z* i_Data, const Segment_Z& i_Seg, ColLineResult_Z& o_Result, U64 i_Flag, U64 i_NoFlag);
    virtual Bool GetCollisionMovingSphere(Node_Z* i_Node, ObjectDatas_Z* i_Data, const Capsule_Z& i_Cap, ColLineResult_Z& o_Result, U64 i_Flag, U64 i_NoFlag);
    virtual U32 GetNbNormals() const;

protected:
    U8 m_Pad_0xa0[112];
};

#endif
