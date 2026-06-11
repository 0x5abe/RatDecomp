#ifndef _ARAMMANAGER_Z_H_
#include "XRamManager_Z.h"
#include "AramXAllocator_Z.h"

class AramManager_Z : public XRamManager_Z {
public:
    virtual Bool Init();
    virtual void Shut();
    virtual void Update(Float a1);
    virtual void Flush();
    virtual void Minimize();
    virtual void AllocBlock(S32 a1, S32 a2, S32 a3);
    virtual void GetBlockPtr(S16 a1);
    virtual void GetBlockSize(S16 a1);
    virtual void FreeBlock(S16 a1);
    virtual void LockBlockAt(S16 a1, S32 a2);
    virtual void Get(S16 a1, S32 a2);
    virtual void Read(U8* a1, S32 a2, U32 a3, bool a4);
    virtual void Write(U8* a1, S32 a2, U32 a3, bool a4);

private:
    U8 m_Unk_0x4[4096];
    ARamXAllocator_Z<1024, 32, 0> m_ARamAllocator;
};

#endif
