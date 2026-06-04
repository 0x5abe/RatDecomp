#ifndef _SURFACEGC_Z_H_
#define _SURFACEGC_Z_H_
#include "DynArray_Z.h"
#include "StreamList_Z.h"
#include "ObjectCache_Z.h"

struct SurfaceGCVertex_Z {
    U8 m_Unk_0x0[32];
};

class SurfaceCacheGCEntry_Z : public StreamList_Z {
public:
    S32 m_Lod; // 0x04

    DynArray_Z<SurfaceGCVertex_Z, 8, FALSE, FALSE, 32> m_Vertices; // 0x08
};

typedef CacheEntryFrame_Z<SurfaceCacheGCEntry_Z, TRUE, 32> SurfaceCacheGCEntryFrame_Z;
typedef BnkCacheEntryFrame_Z<SurfaceCacheGCEntry_Z, 128, TRUE, TRUE, 32> SurfaceCacheFrame_Z;

class SurfaceCache_Z {
public:
    SurfaceCacheFrame_Z* GetFirstFrame() const {
        return m_First;
    }

    S32 GetMaxInUseNb() const {
        return m_MaxInUseNb;
    }

    void SetMaxInUseNb(S32 i_MaxInUseNb) {
        m_MaxInUseNb = i_MaxInUseNb;
    }

    U16 GetTotalNb() const {
        return m_TotalNb;
    }

private:
    SurfaceCacheFrame_Z* m_First; // 0x00
    U16 m_TotalNb;                // 0x04
    S32 m_MaxInUseNb;             // 0x08
};

#endif // _SURFACEGC_Z_H_
