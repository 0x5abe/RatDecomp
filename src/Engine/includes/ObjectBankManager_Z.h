#ifndef _OBJECTBANKMANAGER_Z_H_
#define _OBJECTBANKMANAGER_Z_H_
#include "HoleArray_Z.h"
#include "Object_ZHdl.h"
#include "Node_ZHdl.h"

#define BANKMGR_MAX_NODE 128

struct BankData {
    Name_Z m_Name;
    S32 m_UnkS32_0x4;
    BitArray_Z m_UnkBA_0x8;
    ObjectDatas_ZHdlDA m_ObjectDatasHdls;
};

class ObjectBankManager_Z {
private:
    HoleArray_Z<BankData, 16> m_Banks;
    Node_ZHdlDA m_NodeHdls;
    BitArray_Z m_NodeStatus; // If a given node index in m_NodeHdls is free or not

public:
    ObjectBankManager_Z();
    virtual ~ObjectBankManager_Z();

    S32 FreeBank(S32 i_Idx);
    void FreeNode(Node_ZHdl& i_NodeHdl);
    void FreeObject(S32 i_Unk, ObjectDatas_ZHdl& i_ObjectDataHdl);
    void MarkHandles();
    Bool Minimize();
};

#endif
