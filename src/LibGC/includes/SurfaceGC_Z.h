#ifndef _SURFACEGC_Z_H_
#define _SURFACEGC_Z_H_
#include "Surface_Z.h"
#include "StreamList_Z.h"
#include "ObjectCache_Z.h"
#include "Renderer_Z.h"

class SurfaceGC_Z : public Surface_Z {
public:
    virtual ~SurfaceGC_Z();
    virtual void Load(void** i_Data);
    virtual void Draw(DrawInfo_Z& i_DrawInfo, ObjectDatas_Z* i_Data);

    static BaseObject_Z* NewObject() {
        return NewL_Z(25) SurfaceGC_Z;
    }

private:
    U8 m_Pad_0xf0[16];
};

struct SurfaceGCVertex_Z {
    U8 m_Unk_0x0[32];
};

typedef DynArray_Z<SurfaceGCVertex_Z, 8, FALSE, FALSE, 32> SurfaceGCVertex_ZDA;

class SurfaceCacheGCEntry_Z : public StreamList_Z {
public:
    void FreeEntry(const CacheStateFrame_Z& i_CacheState);

private:
    S32 m_Lod;
    DynArray_Z<SurfaceGCVertex_Z, 8, FALSE, FALSE, 32> m_Vertices;
};

typedef CacheEntryFrame_Z<SurfaceCacheGCEntry_Z, TRUE, 32> SurfaceCacheGCEntryFrame_Z;
typedef BnkCacheEntryFrame_Z<SurfaceCacheGCEntry_Z, 128, TRUE, TRUE, 32> SurfaceCacheBnk_Z;
typedef BnkCacheEntryFrame_Z<SurfaceCacheGCEntry_Z, 128, TRUE, TRUE, 32>::BnkCacheEntryFrameEle_Z SurfaceCacheBnkEle_Z;

class SurfaceCache_Z {
    friend class GCRenderer_Z;

public:
    SurfaceCache_Z() {
        Reset();
    }

    ~SurfaceCache_Z();

    void Update() {
        m_BnkCache.Update();
    }

    void GetState(CacheState_Z& o_State) {
        o_State.Reset();
        m_BnkCache.GetState(o_State);
    }

    void Reset();

private:
    SurfaceCacheBnk_Z m_BnkCache;
};

#endif // _SURFACEGC_Z_H_
