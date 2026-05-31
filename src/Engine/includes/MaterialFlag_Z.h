#ifndef _MATERIALFLAG_Z_H_
#define _MATERIALFLAG_Z_H_

// Material flags

// Render flags (and Code)

// Used for shaders and other material specific rendering logic
enum MaterialCode_Z {
    FL_MTL_CODE_DIFFUSE = 0,
    FL_MTL_CODE_TRANSFORM = 1, // Set to use alpha mask for envmap (maybe not this name)
    FL_MTL_CODE_UNK2 = 2,
    FL_MTL_CODE_UNK3 = 3,
    FL_MTL_CODE_UNK4 = 4,
    FL_MTL_CODE_EAU = 5, // Water
    FL_MTL_CODE_LAYER = 6,
    FL_MTL_CODE_EAU_DYNAMIC = 7, // Dynamic water
    FL_MTL_CODE_WATER_OCEAN = 8,
    FL_MTL_CODE_UNK9 = 9,
    FL_MTL_CODE_UNK10 = 10,
    FL_MTL_CODE_UNK11 = 11,
    FL_MTL_CODE_BLOOM = 12,
    FL_MTL_CODE_UNK13 = 13,
    FL_MTL_CODE_UNK14 = 14,
    FL_MTL_CODE_SONAR = 15,
    FL_MTL_CODE_STENCIL = 16,
    FL_MTL_CODE_UNK17 = 17,
    FL_MTL_CODE_UNK18 = 18,
    FL_MTL_CODE_UNK19 = 19,
    FL_MTL_CODE_UNK20 = 20,
    FL_MTL_CODE_UNK21 = 21,
    FL_MTL_CODE_UNK22 = 22,
    FL_MTL_CODE_UNK23 = 23,
    FL_MTL_CODE_UNK24 = 24,
    FL_MTL_CODE_UNK25 = 25,
    FL_MTL_CODE_UNK26 = 26,
    FL_MTL_CODE_UNK27 = 27,
    FL_MTL_CODE_UNK28 = 28,
    FL_MTL_CODE_LAST = 29
};

#define FL_MTL_CODE_ALL (FL_MTL_CODE_TRANSFORM | FL_MTL_CODE_UNK2 | FL_MTL_CODE_UNK4 | FL_MTL_CODE_WATER_OCEAN | FL_MTL_CODE_STENCIL) // 0x1f - All bits used for code
#define FL_IS_ALPHABLENDED (1 << 5)                                                                                                   // 0x20 - Alpha blended material
#define FL_IS_TRANSPARENT (1 << 6)                                                                                                    // 0x40 - Transparent material
#define FL_INVISIBLE (1 << 7)                                                                                                         // 0x80 - Invisible material, not rendered at all
#define FL_TEX_ADDRESS_CLAMP_U (1 << 8)                                                                                               // 0x100 - Clamp U texture coordinates
#define FL_TEX_ADDRESS_CLAMP_V (1 << 9)                                                                                               // 0x200 - Clamp V texture coordinates
#define FL_STENCIL_OCCLUDER (1 << 10)                                                                                                 // 0x400 - Stencil occluder
#define FL_STENCIL_OCCLUDEE (1 << 11)                                                                                                 // 0x800 - Stencil occludee
#define FL_ADDITIF (1 << 12)                                                                                                          // 0x1000 - Additive blending
#define FL_SOUSTRACTIF (1 << 13)                                                                                                      // 0x2000 - Subtractive blending
#define FL_DESTADDITIF (1 << 14)                                                                                                      // 0x4000 - Destination additive blending
#define FL_MAT_RDR_UNK15 (1 << 15)                                                                                                    // 0x8000 - Unknown
#define FL_MAT_RDR_UNK16 (1 << 16)                                                                                                    // 0x10000 - Unknown
#define FL_TWO_SIDE (1 << 17)                                                                                                         // 0x20000 - Two-sided material, disables backface culling
#define FL_RESERVED_6 (1 << 18)                                                                                                       // 0x40000 - Reserved
#define FL_RESERVED_7 (1 << 19)                                                                                                       // 0x80000 - Reserved
#define FL_TRANSP_ATFIRST (1 << 20)                                                                                                   // 0x100000 - Unknown
#define FL_MAT_RDR_UNK21 (1 << 21)                                                                                                    // 0x200000 - Unknown
#define FL_MAT_RDR_UNK22 (1 << 22)                                                                                                    // 0x400000 - Unknown
#define FL_MAT_RDR_UNK23 (1 << 23)                                                                                                    // 0x800000 - Unknown
#define FL_MAT_RDR_UNK24 (1 << 24)                                                                                                    // 0x1000000 - Unknown
#define FL_MAT_RDR_UNK25 (1 << 25)                                                                                                    // 0x2000000 - Unknown
#define FL_MAT_RDR_UNK26 (1 << 26)                                                                                                    // 0x4000000 - Unknown
#define FL_MAT_RDR_UNK27 (1 << 27)                                                                                                    // 0x8000000 - Unknown
#define FL_MAT_RDR_UNK28 (1 << 28)                                                                                                    // 0x10000000 - Unknown
#define FL_MAT_RDR_UNK29 (1 << 29)                                                                                                    // 0x20000000 - Unknown
#define FL_TRANSP_RESET ~(FL_IS_ALPHABLENDED | FL_IS_TRANSPARENT)

// Collision flags

#define FL_MAT_COL_UNK0 (1 << 0)
#define FL_MAT_COL_COLLIDABLE (1 << 1)
#define FL_MAT_COL_UNK2 (1 << 2)
#define FL_MAT_COL_UNK3 (1 << 3)
#define FL_MAT_COL_UNK4 (1 << 4)
#define FL_MAT_COL_UNK5 (1 << 5)
#define FL_MAT_COL_UNK6 (1 << 6)
#define FL_MAT_COL_UNK7 (1 << 7)
#define FL_MAT_COL_UNK8 (1 << 8)
#define FL_MAT_COL_UNK9 (1 << 9)
#define FL_MAT_COL_UNK10 (1 << 10)
#define FL_MAT_COL_UNK11 (1 << 11)
#define FL_MAT_COL_UNK12 (1 << 12)
#define FL_MAT_COL_UNK13 (1 << 13)
#define FL_MAT_COL_UNK14 (1 << 14)
#define FL_MAT_COL_UNK15 (1 << 15)
#define FL_MAT_COL_UNK16 (1 << 16)
#define FL_MAT_COL_UNK17 (1 << 17)
#define FL_MAT_COL_SOUND1 (1 << 18) // changes sound with 80000,100000,200000
#define FL_MAT_COL_SOUND2 (1 << 19) // changes sound with 40000,100000,200000
#define FL_MAT_COL_SOUND3 (1 << 20) // changes sound with 40000,80000,200000
#define FL_MAT_COL_SOUND4 (1 << 21) // changes sound + particles with 40000,80000,100000
#define FL_MAT_COL_SLIDE1 (1 << 22) // Slide surface 1 - slippery w/ sticky
#define FL_MAT_COL_SLIDE2 (1 << 23) // Slide surface 2
#define FL_MAT_COL_STICKY (1 << 24) // Sticky surface - slippery w/ Slide 1
#define FL_MAT_COL_UNK25 (1 << 25)
#define FL_MAT_COL_UNK26 (1 << 26)
#define FL_MAT_COL_UNK27 (1 << 27)
#define FL_MAT_COL_UNK28 (1 << 28)
#define FL_MAT_COL_UNK29 (1 << 29)

// Texture flags

#define FL_TEX_DIFFUSE (U8)(1 << 0)                                              // Diffuse texture
#define FL_TEX_ENV (U8)(1 << 1)                                                  // Environment texture
#define FL_TEX_BUMP (U8)(1 << 2)                                                 // Bump texture
#define FL_TEX_SPECULAR (U8)(1 << 3)                                             // Specular texture
#define FL_TEX_ALL (FL_TEX_DIFFUSE | FL_TEX_ENV | FL_TEX_BUMP | FL_TEX_SPECULAR) // All bits used for textures
#define FL_TEX_RESET (U8) ~(FL_TEX_ALL)
#define FL_MATERIAL_PAWAP (1 << 4) // Pawap material

#endif
