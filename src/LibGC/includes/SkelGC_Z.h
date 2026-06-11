#ifndef _SKELGC_Z_H_
#define _SKELGC_Z_H_
#include "Skel_Z.h"

class SkelGC_Z : public Skel_Z {
public:
    SkelGC_Z();
    virtual ~SkelGC_Z();
    virtual void AfterEndLoad();
    virtual void Clone(ObjectDatas_ZHdl& o_ObjectDatasHdl, Object_ZHdl& o_ObjectHdl);
    virtual void Draw(DrawInfo_Z& i_DrawInfo);

    static BaseObject_Z* NewObject() {
        return NewL_Z(75) SkelGC_Z;
    }

private:
    U8 m_Pad_0x90[32];
};

#endif // _SKELGC_Z_H_
