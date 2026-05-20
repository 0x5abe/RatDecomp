#ifndef _NETMANAGER_Z_H_
#define _NETMANAGER_Z_H_
#include "Types_Z.h"

struct NetObjectDescriptor {
    U16 m_Unk_0x00;
    U16 m_Pad_0x02;
    U32 m_Unk_0x04;
    U32 m_Unk_0x08;
    void* m_Ptr;
    U8 m_Pad_0x10[0x18 - 0x10];
};

struct NetObjectDescriptors {
    NetObjectDescriptor m_Descriptors[64];

    NetObjectDescriptors();
    ~NetObjectDescriptors();
    void KillDescriptor(U32 i_Idx);
};

class NetManager_Z {
protected:
    S32 m_State;
    Float m_Time1;
    Float m_Time2;

    static NetObjectDescriptors* Descriptors;

public:
    NetManager_Z();
    ~NetManager_Z();

    virtual U32 Init() = 0;
    virtual void Kill() = 0;
    virtual void FixNetTime() = 0;
    virtual U32 EnterSession(Char* a1) = 0;
    virtual U32 QuitSession() = 0;

    virtual Bool IsInSession() {
        return m_State == 2;
    }

    virtual U32 IsMasterSession() = 0;
    virtual U32 GetMyUserHandle() = 0;
    virtual U32 WaitSynchronisation(U16 a1, Float a2) = 0;
    virtual void AbortSynchronisation() = 0;
    virtual U32 New_NetObjet(U32 a1, U8* a2) = 0;
    virtual U32 NewLink_NetObjet(U32 a1, U8* a2, U32 a3) = 0;
    virtual void AbortLink_NetObjet(U32 a1) = 0;
    virtual void SetDataSegment_NetObjet(U32 a1, U8* a2) = 0;
    virtual void Release_NetObjet(U32 a1) = 0;
    virtual void Update_NetObjet(U32 a1) = 0;
    virtual void Update_NetObjet(U32 a1, U32 a2) = 0;
    virtual U32 Migrate_NetObjet(U32 a1, U32 a2) = 0;
    virtual U32 IsMaster_NetObjet(U32 a1) = 0;
    virtual U32 CanMigrate_NetObjet(U32 a1) = 0;
    virtual U32 Exist_NetObjet(U32 a1) = 0;
    virtual U32 GetUserHandle_NetObjet(U32 a1) = 0;
    virtual void InitScanForNewSlave_NetObjet() = 0;
    virtual void ScanForNewSlave_NetObjet(U32& a1, U32& a2) = 0;

    inline Float GetDeltaTime() {
        return m_Time2;
    }
};

#endif // _NETMANAGER_Z_H_
