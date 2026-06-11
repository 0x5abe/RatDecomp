#ifndef _PARTICLESGC_Z_H_
#define _PARTICLESGC_Z_H_
#include "Particles_Z.h"

class ParticlesGCData_Z : public ParticlesData_Z {
public:
    ParticlesGCData_Z();
    virtual ~ParticlesGCData_Z();
    virtual void EndLoad();
    virtual void Draw(DrawInfo_Z& i_DrawInfo);

    static BaseObject_Z* NewObject() {
        return NewL_Z(23) ParticlesGCData_Z;
    }

private:
    U8 m_Pad_0x60[16];
};

#include "DataManager_Z.h"

struct ParticlesGDL_Z {
    U8 m_Unk_0x0[16];
} Aligned_Z(16);

class GCParticlesManager_Z : public DataManager_Z<ParticlesGDL_Z> {
public:
    GCParticlesManager_Z(Char* i_Name)
        : DataManager_Z<ParticlesGDL_Z>(i_Name) { }
};

typedef GCParticlesManager_Z::Item ParticlesGDL_ZEle;

#endif // _PARTICLESGC_Z_H_
