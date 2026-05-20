#include "KSys_Z.h"
#include "Program_Z.h"

Extern_Z "C" U32 strlen(const char* str);
Extern_Z "C" int strncmp(const char* str1, const char* str2, int n);
Extern_Z "C" Char* strpbrk(const Char* str, const Char* accept);

// $SABE TODO: FIX

// void PathKDBToSys(const Char* i_KName, Char* o_SysName) {
// #define DB_SIZE 3

//     Char l_KName[256];
//     l_KName[0] = 0;

//     U32 l_Len = strlen(i_KName);
//     U32 i;
//     for (i = 0; i < l_Len; i++) {
//         if (i_KName[i] == K_DIRECTORY_CHAR) {
//             l_KName[i] = '\\';
//         }
//         else {
//             l_KName[i] = i_KName[i];
//         }
//     }
//     l_KName[i] = 0;

//     if (strncmp(l_KName, "DB:", DB_SIZE) == 0) {
//         if (strpbrk(l_KName, "/")) {
//             U32 l_OldError1 = gData.UnkError1;
//             U32 l_OldError2 = gData.UnkError2;

//             gData.UnkError1 = 0;
//             gData.UnkError2 = 0;

//             Error_Z l_Error(0x8000000, "Invalid DB path !");
//             Console_Z::PrintErrorString(0x8000000, "Invalid DB path : %s", l_KName);

//             gData.UnkError2 = l_OldError2;
//             gData.UnkError1 = l_OldError1;
//         }
//     }

//     if (gData.ClassMgr->IsBigFileRead()) {
//         if (strlen(gData.BFPathList) && strlen(gData.BFMatchList)) {
//             const Char* l_PathName;

//             strcpy(o_SysName, gData.m_AliasPath);

//             if (strncmp(l_KName, "DB:", DB_SIZE) == 0) {
//                 l_PathName = l_KName + DB_SIZE;
//                 strcat(o_SysName, l_PathName);
//             }
//             else {
//                 l_PathName = l_KName;
//                 strcat(o_SysName, l_PathName);
//             }

//             if (File_Z::DoFileExists(o_SysName)) {
//                 return;
//             }

//             Char* l_Match = strstr(gData.BFMatchList, "*");

//             while (l_Match) {
//                 Char l_MatchName[5];

//                 strncpy(l_MatchName, l_Match, 4);
//                 l_MatchName[4] = 0;

//                 if (strstr(l_KName, l_MatchName)) {
//                     const Char* l_BFPath = gData.BFPathList;

//                     while (*l_BFPath) {
//                         strcpy(o_SysName, l_BFPath);

//                         if (strncmp(l_KName, "DB:", DB_SIZE) == 0) {
//                             l_PathName = l_KName + DB_SIZE;
//                             strcat(o_SysName, l_PathName);
//                         }
//                         else {
//                             l_PathName = l_KName;
//                             strcat(o_SysName, l_PathName);
//                         }

//                         if (File_Z::DoFileExists(o_SysName)) {
//                             return;
//                         }

//                         l_BFPath += strlen(l_BFPath) + 1;
//                     }
//                 }

//                 l_Match = strstr(l_Match + 1, "*");
//             }
//         }
//     }

//     if (strncmp(l_KName, "DB:", DB_SIZE) == 0) {
//         strcpy(o_SysName, gData.DBPath);
//         strcat(o_SysName, l_KName + DB_SIZE);
//     }
//     else {
//         strcpy(o_SysName, l_KName);
//     }

// #undef DB_SIZE
// }

void PathSysToDB(const Char* i_SysName, Char* o_KName) {
}
