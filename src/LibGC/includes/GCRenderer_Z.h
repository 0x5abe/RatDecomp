#ifndef _GCRENDERER_Z_H_
#define _GCRENDERER_Z_H_
#include "Renderer_Z.h"
#include "BnkDynArray_Z.h"
#include "ARamXAllocator_Z.h"
#include "DisplayList_Z.h"
#include <gx.h>
#include <mtx.h>

// $SABE: Taken from MonopolyX360SUB.xdb and adapted, could be wrong (For more values see the file)
enum DrawingOrder {
    do_null = 0,
    do_none = 1,
    do_opaque = 2,
    do_unk_3 = 3,
    do_unk_4 = 4,
    do_unk_5 = 5,
    do_unk_6 = 6,
    do_unk_7 = 7,
    do_unk_8 = 8,
    do_shadow_cast = 9,
    do_scene_draw = 10,
    do_transp_first = 11,
    do_transp = 12,
    do_unk_13 = 13,
    do_unk_14 = 14,
    do_flare = 15,
    do_unk_16 = 16,
    do_unk_17 = 17,
    do_unk_18 = 18,
    do_last = 19,
    do_count = 20
};

// $SABE: Taken from MonopolyX360SUB.xdb and adapted, could be wrong (For more values see the file)
enum DrawingState {
    ds_ztest = 0x1,
    ds_zwrite = 0x2,
    ds_cwritergb = 0x4,
    ds_cwritea = 0x8,
    ds_ablend = 0x10,
    ds_noatest = 0x20,
    ds_aref128 = 0x40,
    ds_cw = 0x80,
    ds_ccw = 0x100,
    ds_unk_0x200 = 0x200,
    ds_unk_0x400 = 0x400,
    ds_disable_forced_dstalpha = 0x800,
    ds_zonly = ds_ztest | ds_zwrite | ds_cw,             // 0x0083
    ds_cwrite = ds_cwritergb | ds_cwritea,               // 0x000c
    ds_opaque = ds_ztest | ds_zwrite | ds_cwrite | ds_cw // 0x008f
};

// TODO: Move this to its own file

class StreamList_Z {
    virtual void SetStream();
    virtual void SetVtxDesc();
};

// END TODO

// TODO: Move these to their own files
#define DRAW2D_VTXBUFFER_NB 32
#define DRAW2D_VERTEX_LIST_ALIGN 32

class Draw2D_Z {
public:
    struct GCVertex2DStream {
        Vec3f m_Pos;
        GXColor m_Color;
        Vec2f m_UV;
    };

    class GCListVertex2D {
    public:
        U8 m_PrimType;
        U8 m_VertexCountHigh;
        U8 m_VertexCountLow;
        U8 m_VertexData[DRAW2D_VTXBUFFER_NB * sizeof(GCVertex2DStream)];
    } Aligned_Z(32);

    class Primitive2DList_Z {
    public:
        Material_Z* m_Material;
        S32 m_DisplayListIdx;
        U16 m_DrawState;
        U32 m_RenderFlags;
    };

    U8* m_CurWritePtr;
    U8* m_CurWriteEnd;
    U8* m_PreviousWritePtr;
    Material_Z* m_CurMaterial;
    U16 m_CurDrawState;
    U32 m_CurRenderFlags;
    S32 m_CurDisplayListIdx;
    S32 m_RemainingVertexCount;
    BnkDynArray_Z<GCListVertex2D, 16, FALSE, FALSE, DRAW2D_VERTEX_LIST_ALIGN> m_Vtx2DBufferDA;
    DynArray_Z<Primitive2DList_Z, 8, TRUE, TRUE, 4> m_PrimitiveLists;
};

// END TODO

// TODO: Move these to their own files
#define DRAW3D_VTXBUFFER_NB 128
#define DRAW3D_VERTEX_LIST_ALIGN 32

class Draw3D_Z {
public:
    struct GCVertex3DStream {
        Vec3f m_Pos;
        GXColor m_Color;
        Vec2f m_UV;
    };

    class GCDisplayListVertex3D : public BaseDisplayList_Z {
    public:
        U8 m_Unk_0x04[0x1c];
        U8 m_PrimType;
        U8 m_VertexCountHigh;
        U8 m_VertexCountLow;
        U8 m_VertexData[DRAW3D_VTXBUFFER_NB * sizeof(GCVertex3DStream)];
    } Aligned_Z(32);

    S32 m_CurBankIdx;
    BaseDisplayList_Z* m_CurDisplayList;
    BnkDynArray_Z<GCDisplayListVertex3D, 16, FALSE, TRUE, DRAW3D_VERTEX_LIST_ALIGN> m_Vtx3DBufferDA[2];
};

// END TODO

// TODO: Move these to their own files
struct ScanCode_Z {
    Float m_U1;
    Float m_V1;
    Float m_U2;
    Float m_V2;
    Float m_SizeX;
    Float m_SizeY;
    Bool m_Valid;
};

struct FontString_Z {
    Material_ZHdl m_MaterialHdl;
    ScanCode_Z m_Characters[256];
};

// END TODO

#define EXT_PRIM_INFO_ALIGN 32

struct ExtPrimitiveInfo_Z {
    Mtx m_Local2Cam Aligned_Z(32);
    U32 m_MtxId;
    U32 m_MtxKey;
    U32 m_RenderContextFlag;
    U32 m_BlendFlag;
    Mtx m_InvTransposed Aligned_Z(32);
    U32 m_Order;
    U8 m_DrawOrderGroup;
    U16 m_DrawState;
    U8 m_UnusedSortKeyInsideGroup_0x78;
    StreamList_Z* m_StreamList;
    BaseDisplayList_Z* m_DisplayList;
    Material_Z* m_Material;
    GXLightObj m_MainLight;
    GXColor m_AmbientColor;
    Vec3f m_ObjDatasColor;
    Float m_FadeValue;
    U32 m_ExtraLightCount;
    GXLightObj m_ExtraLights[3];
    U32 m_UnkU32_0x1a0;
    HFogData_Z* m_MainFog;
    HFogData_Z* m_EnabledFog;
    Float m_FogNear;
    Float m_FogFar;
    Float m_FogStartZ;
    Float m_FogEndZ;
    Bitmap_Z* m_ActiveBitmaps[BITMAP_NB_TYPES];
    S32 m_PrevDrawCallIdx;
    S32 m_NextDrawCallIdx;
};

typedef DynArray_Z<ExtPrimitiveInfo_Z, 256, FALSE, FALSE, EXT_PRIM_INFO_ALIGN> ExtPrimitiveInfo_ZDA;

#define INVALID_SORT_ELEM_IDX 0xFFFF

// Radix sort element
struct SortElem_Z {
    U32 m_Key; // Radix sorted by (high to low priority) (m_DrawOrderGroup << 24) | (m_UnusedSortKeyInsideGroup_0x78 << 16) | (((U8)m_Order >> 8) << 8) | (U8)m_OrderLowByte;
    U16 m_NextElemIdx;
};

class GCRenderer_Z : public Renderer_Z {
public:
    GCRenderer_Z();
    virtual ~GCRenderer_Z();
    virtual Bool Init(S32 i_SizeX, S32 i_SizeY);
    virtual void Shut();
    virtual void Reset();
    virtual void BeginRender();
    virtual void EndRender(Float a1);
    virtual void Minimize();
    virtual void Draw(S32 a1, Float a2);
    virtual void DrawTransparent(DrawInfo_Z& a1);
    virtual void ClearZBuffer(S32 a1, S32 a2, S32 a3, S32 a4);
    virtual void ClearFrameBuffer(S32 a1, S32 a2, S32 a3, S32 a4);
    virtual void PushOrder(Float a1);
    virtual void PushDo(U8 a1);
    virtual void PushDs(U16 a1);
    virtual void SetActiveMaterial(Material_Z* a1);
    virtual void SetActiveTexture(Bitmap_Z* a1, S32 a2);
    virtual void FreeTexture(S16 a1);
    virtual void GetTextureSize();
    virtual void MarkHandles();
    virtual void DrawFace(Vertex3D& a1, Vertex3D& a2, Vertex3D& a3);
    virtual void DrawStrip(Vertex3D* a1, U32 a2, Bool a3);
    virtual void DrawStripAfterScene(Vertex3D* a1, U32 a2, Bool a3);
    virtual void DrawLine(const Vec3f& a1, const Vec3f& a2, const Color& a3, Bool a4, Bool a5);
    virtual void DrawLine(const Vec2f& a1, const Vec2f& a2, const Color& a3, Float a4);
    virtual void DrawImage(Bitmap_ZHdl& a1);
    virtual void DrawCross(const Vec3f& a1, const Color& a2, Float a3);
    virtual void Draw2DQuad(const Vec2f& a1, const Vec2f& a2, const Vec2f& a3, const Vec2f& a4, const Color& a5, const Color& a6, Float a7);
    virtual void DrawQuad(Vec2f& a1, Vec2f& a2, Color& a3, Color& a4, Float a5);
    virtual void DrawQuad(Vec2f& a1, Vec2f& a2, Color& a3, Float a4);
    virtual void DrawQuad(Vec2f& a1, Vec2f& a2, Vec2f& a3, Vec2f& a4, Vec3f& a5, Float a6);
    virtual void Draw2DQuad(Vec2f* a1, Vec3f* a2, Vec2f* a3, Float a4, Float a5);
    virtual void DrawStrip(Vec2f* a1, S32 a2, const Color& a3, Float a4);
    virtual void DrawFan(Vec2f* a1, S32 a2, const Color& a3, Float a4);
    virtual void DrawString(const Vec2f& a1, const Char* a2, const Color& a3, Float a4, Float a5);
    virtual void DrawString(const Vec3f& a1, const Char* a2, Bool a3);
    virtual void DrawString(const Vec3f& a1, const Char* a2, const Color& a3, Bool a4);
    virtual void MakeScreenShot(Char* a1);
    virtual void FlushActiveViewport();
    virtual void InitRenderStates();
    virtual void SetProfiler(Bool a1);
    virtual void PushADraw(StreamList_Z* a1, BaseDisplayList_Z* a2, S32 a3);

    U16 SortRendererDatas(SortElem_Z* i_SortElems);

private:
    GXFifoObj* m_FifoObject;
    U8* m_FifoBuffer; // Size of 380 * 1024
    U8* m_FrameBuffers[2];
    U8* m_CurFrameBuffer;
    S32 m_FrameBufferIdx;
    GXRenderModeObj m_RenderModeObj;
    U32 m_CurBlendFlags;
    Float m_PushedOrder;
    U8 m_PushedDrawOrderGroup;
    U8 m_CurDrawOrderGroup;
    U16 m_PushedDrawState;
    U16 m_CurDrawState;
    U8 m_PushedUnusedSortKeyInsideGroup_0x2672;
    U8 m_UnkU8_SetTo0_0x2673;
    S32 m_DrawOrderGroupDrawCallCount[do_count];
    Bool m_DrawOrderGroupShouldDraw[do_count];
    ExtPrimitiveInfo_ZDA m_DrawCalls;
    U32 m_FrameBufferTextureSize;
    U8* m_FrameBufferTextureData;
    GXTexObj m_FrameBufferTexObj;
    S32 m_VizQueryDisplayListCount;
    DisplayList_Z m_VizQueryDisplayLists[32];
    GXLightObj m_CurMainLight;
    GXColor m_CurAmbientColor;
    Vec3f m_CurObjDatasColor;
    Float m_CurFadeValue;
    S32 m_CurExtraLightCount;
    GXLightObj m_CurExtraLights[3];
    U32 m_UnkU32_0x2a24;
    HFogData_Z* m_CurMainFog;
    HFogData_Z* m_CurEnabledFog;
    Float m_FogNear;
    Float m_FogFar;
    Float m_FogStartZ;
    Float m_FogEndZ;
    U32 m_RenderContextFlag;
    U32 m_ActiveMaterialTextureFlag; // Max FL_TEX_ALL (all bitmaps)
    U32 m_CurMtxId;
    U32 m_CurMtxKey;
    Mtx44 m_Local2Cam Aligned_Z(64);
    Mtx44 m_InvTransposed Aligned_Z(64);
    Mtx44 m_CameraMatrix Aligned_Z(64);
    Mtx44 m_ProjMatrix Aligned_Z(64);
    Mtx44 m_OrthoMatrix Aligned_Z(64);
    Bool m_SkipFrameBufferEffects;
    Bool m_CopyFrameBufferAlpha;
    FontString_Z m_FontString;
    Draw2D_Z m_Draw2D;
    Draw3D_Z m_Draw3D;
    ARamXAllocator_Z<256, 32, 262144> m_ARamAllocator;
};

#endif // _GCRENDERER_Z_H_
