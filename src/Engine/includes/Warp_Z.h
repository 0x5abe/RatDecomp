#ifndef _WARP_Z_H_
#define _WARP_Z_H_
#include "ResourceObject_Z.h"

class Warp_Z : public ResourceObject_Z {
public:
    Warp_Z();
    virtual ~Warp_Z();
    virtual void Load(void** i_Data);
    virtual void EndLoad();
    virtual void AfterEndLoad();
    virtual void LoadDone();
    virtual Bool MarkHandles();
    virtual void Draw(DrawInfo_Z& i_DrawInfo);
    virtual void GetUser3D(U32 i_Idx);

protected:
    U8 m_Pad_0x14[180];
};

#endif // _WARP_Z_H_
