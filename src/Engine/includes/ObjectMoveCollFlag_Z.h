#ifndef _OBJECTMOVECOLLFLAG_Z_H_
#define _OBJECTMOVECOLLFLAG_Z_H_
#include "Types_Z.h"

#define INT_BOL_LODMOVE (U64)(1 << 2)     // It's a LodMove_Z
#define INT_BOL_UNK (U64)(1 << 3)         // Unknown, used in ObjectMove_Z::Reset (to keep it set)
#define COL_BOL_FIT_GROUND (U64)(1 << 24) // Collision is a simple ray down
#define COL_BOL_THROWN (U64)(1 << 38)     // Collision when being thrown

#endif
