#ifndef _KSYS_Z_H_
#define _KSYS_Z_H_
#include "Types_Z.h"

#define K_DIRECTORY_CHAR '>'

void PathKToSys(const Char* i_KName, Char* o_SysName);
void PathKDBToSys(const Char* i_KName, Char* o_SysName);
void PathSysToDB(const Char* i_SysName, Char* o_KName);

#endif // _KSYS_Z_H_
