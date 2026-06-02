#include "Sys_Z.h"
#include "Types_Z.h"
ExternC_Z U32 strlen(const Char* str);
ExternC_Z int strcpy(Char* dest, const Char* src);
ExternC_Z int strncpy(Char* dest, const Char* src, S32 n);
ExternC_Z Char* strstr(Char* str, const char* substr);

void Sys_Z::GetAbsoluteFromPath(const Char* i_Path, Char* o_AbsPath, Char* i_Unk) {
}
