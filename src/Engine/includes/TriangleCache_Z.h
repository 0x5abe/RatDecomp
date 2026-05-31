#ifndef _TRIANGLECACHE_Z_H_
#define _TRIANGLECACHE_Z_H_
#include "DynArray_Z.h"
#include "BaseObject_Z.h"
#include "SystemObject_Z.h"

#define COL_TRI_OWNER_COUNT 256
#define COL_TRI_CACHE_SIZE 1024
#define COL_TRI_OWNER_LOOKUP_SIZE 8192

class Patch;

struct TriInfos {
    CollisionFastTriangle_Z m_Tri;
    S32 m_NextIdx;
};

typedef DynArray_Z<TriInfos, 32, FALSE, FALSE> TriInfosDA;

struct OwnerTInfos {
    U32 m_NodeNameId;
    Patch* m_DataPtr;
    U32 m_TriIdx;
};

typedef DynArray_Z<OwnerTInfos, 32, FALSE, FALSE> OwnerTInfosDA;

class ColTriangleCache_Z {
    S32 m_FreeTriangleCount;
    S32 m_FreeTriangleListHead;
    TriInfosDA m_TriPool;
    U16DA m_OwnerLookup;
    S32 m_EvictionScanIndex;
    S32 m_NextInsertOwnerIndex;
    OwnerTInfosDA m_Owners;
    S32 m_OwnerHashMask;
    S32 m_OwnerIndexMask;

public:
    ColTriangleCache_Z() {
        Flush();
    }

    void Flush();
};

#endif // _TRIANGLECACHE_Z_H_
