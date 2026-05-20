#ifndef _WATERHEIGHTMAP_Z_H_
#define _WATERHEIGHTMAP_Z_H_
#include "Material_Z.h"
#include "Memory_Z.h"
#include "PrimitiveBuffers_Z.h"

// $VIOLET: TODO: Actually implement this class.

#define WATER_HEIGHTMAP_VBUFFER_COUNT 2

class WaterHeightMap_Z : public MaterialUser_Z {
public:
    WaterHeightMap_Z();

    virtual void Release();
    virtual void Update(Material_Z* i_Material);

    static MaterialUser_Z* NewObject() {
        return NewL_Z(36) WaterHeightMap_Z;
    }

private:
    S32 m_LastUpdatedFrame;
    VertexBuffer_Z* m_VertexBuffer[WATER_HEIGHTMAP_VBUFFER_COUNT];
    S32 m_CurrentVertexBuffer;
};

#endif
