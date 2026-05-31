#ifndef _INGAMEDATAS_Z_H_
#define _INGAMEDATAS_Z_H_
#include "Manipulator_Z.h"
#include "MaterialAnim_ZHdl.h"
#include "Math_Z.h"
#include "Agent_ZHdl.h"

#define INGAME_DATAS_ITEM_NB_PARAM 4

struct ItemData {
    MaterialAnim_ZHdl m_IconMaterialAnimHdl;
    Name_Z m_KeywordName;
    Char m_ItemDataName[128];
    Name_Z m_NameParam[INGAME_DATAS_ITEM_NB_PARAM];
    S32 m_S32Param[INGAME_DATAS_ITEM_NB_PARAM];
    U8 m_ParamNb;
    U8 m_Flag;
    S32 m_UnkS32_0xac;
    S32 m_UnkS32_0xb0;
    U8 m_CenterX;
    U8 m_CenterY;
    U8 m_FontId;
    Vec3f m_StartColor;
    Vec3f m_EndColor;
    Float m_Scale;
};

typedef DynArray_Z<ItemData, 8> ItemDataDA;

class InGameDatas_Z : public ManipulatorDraw_Z {
public:
    virtual ~InGameDatas_Z();

    virtual void Update(Float i_DeltaTime) { }

    virtual void Draw(const Viewport_Z* a1);
    virtual void RecalcPositions();
    virtual void LoadDataDesc(const Char* a1);

    void SetViewport(S32 i_VpId);
    void ActivateDatas(S32 i_VpId);
    void DeactivateDatas();

    static BaseObject_Z* NewObject() { return NewL_Z(119) InGameDatas_Z; }

private:
    ItemDataDA m_ItemDatas;
    Agent_ZHdl m_AgentHdl;
};

#endif // _INGAMEDATAS_Z_H_
