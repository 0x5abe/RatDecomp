#ifndef _INGAMEOBJECTS_Z_H_
#define _INGAMEOBJECTS_Z_H_
#include "Manipulator_Z.h"
#include "Node_ZHdl.h"

class InGameObjects_Z : public ManipulatorDraw_Z {
public:
    InGameObjects_Z();
    virtual void Init();
    virtual ~InGameObjects_Z();
    virtual Bool MarkHandles();
    virtual void Draw(const Viewport_Z* i_Viewport);
    virtual void SetLights(Node_ZHdl& i_LightNodeHdl1, Node_ZHdl& i_LightNodeHdl2, Node_ZHdl& i_LightNodeHdl3, Node_ZHdl& i_LightNodeHdl4);
    virtual void LoadDataDesc(const Char* i_Path);

protected:
    U8 m_Pad_0x24[84];
};
#endif // _INGAMEOBJECTS_Z_H_
