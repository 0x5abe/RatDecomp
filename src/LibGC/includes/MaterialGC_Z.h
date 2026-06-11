#ifndef _MATERIALGC_Z_H_
#define _MATERIALGC_Z_H_
#include "Material_Z.h"

class MaterialGC_Z : public Material_Z {
public:
    MaterialGC_Z();
    virtual ~MaterialGC_Z();
    virtual void EndLoad();
    virtual void Clone(Material_ZHdl& o_MaterialHdl);

    static BaseObject_Z* NewObject() {
        return NewL_Z(21) MaterialGC_Z;
    }

private:
    U8 m_Pad_0xcc[16];
};

#endif // _MATERIALGC_Z_H_
