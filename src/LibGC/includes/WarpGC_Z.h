#ifndef _WARPGC_Z_H_
#define _WARPGC_Z_H_
#include "Warp_Z.h"

class WarpGC_Z : public Warp_Z {
public:
    WarpGC_Z();
    virtual ~WarpGC_Z();
    virtual void EndLoad();
    virtual void Draw(DrawInfo_Z& i_DrawInfo);

    static BaseObject_Z* NewObject() {
        return NewL_Z(30) WarpGC_Z;
    }

private:
    U8 m_Pad_0xc8[248];
};

#endif // _WARPGC_Z_H_
