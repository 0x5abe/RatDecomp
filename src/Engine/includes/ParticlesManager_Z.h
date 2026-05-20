#ifndef _PARTICLESMANAGER_Z_H_
#define _PARTICLESMANAGER_Z_H_

#include "DataManager_Z.h"
#include "Math_Z.h"

struct _ParticleElement_Z {
    Vec4f m_Position;
    Vec4f m_Speed;
    Vec4f m_BubbleAxis;
    Vec4f m_EmitterColor;
    Color m_Color3D;
    Float m_GravityAcc;
    Float m_GravitySpeed;
    Float m_Rotation;
    Float m_RotationSpeed;
    Float m_LifeSpend;
    Float m_Life;
    Float m_UnkLifeRelated;
    Float m_SizeX;
    Float m_SizeY;
    Float m_BubbleAmplitude;
    Float m_BubblePeriod;
    Vec3f m_Pos3D;
    Float m_Size3Dx;
    Float m_Size3Dy;
} Aligned_Z(16);

class ParticlesManager_Z : public DataManager_Z<_ParticleElement_Z> {
public:
    ParticlesManager_Z(Char* i_Name)
        : DataManager_Z<_ParticleElement_Z>(i_Name) { }
};

typedef ParticlesManager_Z::Item ParticleElement_Z;

#endif
