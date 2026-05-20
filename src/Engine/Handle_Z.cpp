#include "Handle_Z.h"
#include "Main_Z.h"
#include "Program_Z.h"
#include "XRamManager_Z.h"

#define HANDLEREC_GRANULARITY 16384

HandleManager_Z::HandleManager_Z() {
    m_NbFree = 0;
    m_HandleRecDASize = 0;
    ExpandSize(HANDLEREC_GRANULARITY);
    m_UnkS32_0x44 = 0;
    m_UnkBool_SetsDeltaTimeTo30fps_0x34 = FALSE;
    m_DoAsynchCheckHandles = FALSE;
    m_LastDeleteFrameNb = -1;
    m_CheckHandlesQueued = FALSE;
    m_ForbidCheckHandles = FALSE;
}

const BaseObject_ZHdl& HandleManager_Z::CreateNewHandle(BaseObject_Z* i_ObjPtr, const Name_Z& i_Name, S16 i_ClassID, U8 i_Flag) {
    if (!m_NbFree) {
        ExpandSize();
    }

    int l_FreeRecID = m_FreeRecDA[--m_NbFree];

    HandleRec_Z& l_Rec = m_HandleRecDA[l_FreeRecID];
    l_Rec.m_ObjPtr = i_ObjPtr;
    l_Rec.m_Name = i_Name;
    l_Rec.m_xRamBlock = -1;
    l_Rec.m_ClassID = i_ClassID;
    l_Rec.m_Flag = i_Flag;
    l_Rec.m_Marked = HANDLE_MARKED_UNK;

    i_ObjPtr->SetHandle(l_FreeRecID, l_Rec.m_Key);
    i_ObjPtr->SetName(i_Name);

    i_ObjPtr->Init();
    AddResourceRef(l_Rec, l_FreeRecID);

    return i_ObjPtr->GetHandle();
}

void HandleManager_Z::DeleteHandle(const BaseObject_ZHdl& i_Hdl) {
    U32 l_ID = i_Hdl.GetID();
    HandleRec_Z& l_Rec = m_HandleRecDA[l_ID];

    if (l_Rec.m_xRamBlock != -1) {
        gData.XRamMgr->FreeBlock(l_Rec.m_xRamBlock);
    }
    l_Rec.m_xRamBlock = -1;

    RemoveResourceRef(l_Rec);

    l_Rec.m_Marked = HANDLE_MARKED_FALSE;
    l_Rec.m_ClassID = -1;

    Delete_Z l_Rec.m_ObjPtr;

    l_Rec.m_Name = m_NullName;
    l_Rec.m_Key++;
    if (l_Rec.m_Key == 0) {
        l_Rec.m_Key++;
    }

    l_Rec.m_AsyncRelated = FALSE;
    l_Rec.m_Flag = l_Rec.m_Flag & 0xfe;
    l_Rec.m_ObjPtr = NULL;

    m_FreeRecDA[m_NbFree++] = l_ID;
}

void HandleManager_Z::RemoveResourceRef(const HandleRec_Z& i_HandleRec) {
    if (i_HandleRec.m_Flag & 0x8) {
        S32Hash_Z l_HashElt(i_HandleRec.m_Name.GetID());
        Bool l_Result = m_HandleIdHT.Suppress(l_HashElt);
        ASSERTLE_Z(l_Result, "", 121, "bResult");
    }
}

void HandleManager_Z::AddResourceRef(const HandleRec_Z& i_HandleRec, S32 i_Index) {
    if (i_HandleRec.m_Flag & 0x8) {
        S32Hash_Z l_HashElt(i_HandleRec.m_Name.GetID(), i_Index);
        Bool l_Result = m_HandleIdHT.Insert(l_HashElt);
        ASSERTLE_Z(gData.m_UpdatingResource || l_Result, "", 131, "gData.UpdatingResource || bResult");
    }
}

S32 HandleManager_Z::IsResourceRef(S32 i_Hdl) {
    S32Hash_Z l_HashElt(i_Hdl);
    const S32Hash_Z* l_Result = m_HandleIdHT.Search(l_HashElt);
    if (l_Result) {
        return l_Result->m_Ref;
    }
    return -1;
}

S32 HandleManager_Z::ChangeHandleName(const BaseObject_ZHdl& i_Hdl, const Name_Z& i_Name) {
    S32 l_ID = i_Hdl.GetID();
    if (CheckKey(l_ID, i_Hdl.GetKey())) {
        HandleRec_Z& l_HandleRec = m_HandleRecDA[l_ID];
        ASSERTLE_Z(!(l_HandleRec.m_Flag & HandleRec_Z::RSC), "", 157, "!(HdlRec.Flag&HandleRec_Z::RSC)");
        l_HandleRec.m_Name = i_Name;
        return TRUE;
    }
    return FALSE;
}

void HandleManager_Z::Draw(DrawInfo_Z& i_DrawInfo) {
    HandleStream.Draw(i_DrawInfo);
}

void HandleManager_Z::ForbidCheckHandles(Bool i_ForbidCheckHandles) {
    if (i_ForbidCheckHandles) {
        if (m_ForbidCheckHandles) {
            return;
        }
        m_CheckHandlesQueued = FALSE;
    }
    m_ForbidCheckHandles = i_ForbidCheckHandles;
    if (m_CheckHandlesQueued) {
        m_ForbidCheckHandles = FALSE;
        CheckHandles();
    }
}

void HandleManager_Z::Update(Float i_DeltaTime) {
    HandleStream.Update(i_DeltaTime);
}

void HandleManager_Z::MarkU32Handle(U32 i_Hdl) {
    BaseObject_ZHdl l_Hdl = U32ToHandle(i_Hdl);
    S32 l_ID = l_Hdl.GetID();
    if (CheckKey(i_Hdl, l_Hdl.GetKey())) {
        m_HandleRecDA[l_ID].m_ObjPtr->MarkHandles();
    }
}

void HandleManager_Z::ExpandSize(S32 i_NewSize) {
    S32 l_NewSize = m_HandleRecDASize + i_NewSize;

    m_HandleRecDA.SetSize(l_NewSize);
    m_FreeRecDA.SetSize(l_NewSize);

    m_NbFree = i_NewSize;
    m_HandleRecDASize = l_NewSize;

    S32 i = 0;
    while (i_NewSize-- > 0) {
        m_FreeRecDA[i] = --l_NewSize;
        i++;
    }
}

S32 HandleManager_Z::HandleToU32(const BaseObject_ZHdl& i_Hdl) {
    return i_Hdl.m_RealID.GblID;
}

BaseObject_ZHdl HandleManager_Z::U32ToHandle(S32 i_Hdl) {
    BaseObject_ZHdl l_Hdl;
    l_Hdl.m_RealID.GblID = i_Hdl;
    return l_Hdl;
}

void HandleStream_Z::Draw(DrawInfo_Z& i_DrawInfo) {
}

void HandleStream_Z::Update(Float i_DeltaTime) {
}
