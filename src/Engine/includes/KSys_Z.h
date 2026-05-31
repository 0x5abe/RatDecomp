#ifndef _KSYS_Z_H_
#define _KSYS_Z_H_
#include "Types_Z.h"

#define KSYS_DIRECTORY_CHAR '>'
#define KSYS_DB_SIZE 3

void PathKToSys(const Char* i_KName, Char* o_SysName);
void PathKDBToSys(const Char* i_KName, Char* o_SysName);
void PathSysToDB(const Char* i_SysName, Char* o_KName);

Bool SetDBPath();
Bool SetDFPath();
Bool SetBFPath();
Bool EnableBF();

#endif // _KSYS_Z_H_
