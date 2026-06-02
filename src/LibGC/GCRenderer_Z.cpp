#include "GCRenderer_Z.h"
#include "TextureManager_Z.h"

Bool GCRenderer_Z::Init(S32 i_SizeX, S32 i_SizeY) { }

void GCRenderer_Z::ClearAFrameBuffer(U8* i_Buffer, S32 i_Size) {
    U32* l_WritePtr = (U32*)i_Buffer;
    U32* l_WriteEnd = (U32*)(i_Buffer + i_Size);
    while (l_WritePtr < l_WriteEnd) {
        *l_WritePtr++ = 0x00800080;
    }
    DCFlushRange(i_Buffer, i_Size);
}

void GCRenderer_Z::InitRenderStates() { }

void GCRenderer_Z::BeginRender() { }

void GCRenderer_Z::EndRender(Float i_DeltaTime) { }

void GCRenderer_Z::FlushActiveViewport() {
    m_Draw2D.End();
}

void GCRenderer_Z::Draw(S32 i_ViewportId, Float i_DeltaTime) {
}

void GCRenderer_Z::SetActiveMaterial(Material_Z* i_Material) {
    if (!i_Material) {
        SetBlankMaterial();
        return;
    }
    m_CurObjColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
    SetMaterial(i_Material, GX_COLOR0A0);
}

void GCRenderer_Z::SetMaterial(Material_Z* i_Material, GXChannelID i_Channel) {
}

void GCRenderer_Z::SetRenderBlendOp(U32 i_BlendFlag) {
}

void GCRenderer_Z::DrawState(U16 i_StateFlag) {
}

void GCRenderer_Z::SetRenderContext(U32 i_ContextFlag) {
}

void GCRenderer_Z::SetTexture(Bitmap_Z* i_Bitmap, GXTexWrapMode i_WrapS, GXTexWrapMode i_WrapT, GXTexMapID i_TexMapID) {
    if (!i_Bitmap) {
        return;
    }
    gData.TextureMgr->LoadTexture(i_Bitmap, i_WrapS, i_WrapT, i_TexMapID);
}
