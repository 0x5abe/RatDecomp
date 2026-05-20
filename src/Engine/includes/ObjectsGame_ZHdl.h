#ifndef _OBJECTSGAME_ZHDL_H_
#define _OBJECTSGAME_ZHDL_H_
#include "ObjectGame_ZHdl.h"

class ObjectsGame_Z;
class ObjectGame_Z;

HANDLE_Z(ObjectsGame_Z, ObjectGame_Z);

typedef DynArray_Z<ObjectsGame_ZHdl, 32> ObjectsGame_ZHdlDA;

class ObjectsGameClip_Z;

HANDLE_Z(ObjectsGameClip_Z, ObjectGame_Z);

typedef DynArray_Z<ObjectsGameClip_ZHdl, 32> ObjectsGameClip_ZHdlDA;


#endif
