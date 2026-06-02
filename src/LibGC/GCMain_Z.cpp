#include "GCMain_Z.h"
#include "Assert_Z.h"
#include "LowMemory_Z.h"
#include "GCConsole_Z.h"

GCGlobals gData;

Extern_Z void GetFlagsFromGame();
Extern_Z void MathInitTables();

ExternC_Z void OSInit();
ExternC_Z void DVDInit();
ExternC_Z void OSReport(const Char* __msg, ...);
ExternC_Z void __start();

ExternC_Z void exit(S32 __status);
ExternC_Z void* OSGetArenaHi();
ExternC_Z void* OSGetArenaLo();

ExternC_Z void* _stack_end;
ExternC_Z void* _stack_addr;
ExternC_Z void* _db_stack_end;
ExternC_Z void* _db_stack_addr;

// $SABE: Not fully matching yet, need to fix
void PrintMemoryStatus(Char* i_Comment) {
    void* l_ArenaLo = OSGetArenaLo();
    void* l_ArenaHi = OSGetArenaHi();
    U32 l_Size = ((U32)l_ArenaHi - (U32)l_ArenaLo);
    U32 l_HeapSize = MemManager.GetHeapSize() - MemManager.GetFreeMem();
    U32 l_StackAddr = (U32)_stack_addr;
    U32 l_StackEnd = (U32)_stack_end;

    OSReport("\n\n");
    OSReport("> %s :\n", i_Comment ? i_Comment : "Memory Status");
    OSReport(">              start       end         size         usage\n");
    OSReport(">     ELF      0x%08x  0x%08x  %08d ko\n", __start, 0x803c317e, (0x803c317e - (U32)&__start) >> 10);
    OSReport(">     STACK    0x%08x  0x%08x  %08d ko\n", l_StackEnd, l_StackAddr, ((U32)&l_StackEnd - (U32)&l_StackAddr) >> 10);
    OSReport(">     DBSTACK  0x%08x  0x%08x  %08d ko\n", _db_stack_end, _db_stack_addr, ((U32)&_db_stack_end - (U32)&_db_stack_addr) >> 10);
    OSReport(">     HEAP     0x%08x  0x%08x  %08d ko  %.2f mo\n", l_ArenaLo, l_ArenaHi, l_Size >> 10, (Float)l_HeapSize / (1024.0f * 1024.0f));
    OSReport("\n\n");
}

S32 ConsoleConfiguration::GetAspectRatio() {
    return 0;
}

void InitProgram(int i_Argc, Char** i_Argv) {
    OSInit();
    ExceptionHandler();
    MemManager.Init();
    gData.m_GameFlag = FL_GAME_NONE;
    GetFlagsFromGame();
    gData.Cons = NewL_Z(283) GCConsole_Z;
    if (!gData.Cons->InitConsole()) {
        exit(0x14);
    }
    gData.Cons->Init();
    gData.Cons->SetVar("_GC");
    gData.Cons->SetVar("_FORCEBFREAD");
    MathInitTables();
    strcpy(gData.m_AliasPath, ".\\");
    DVDInit();
}

LanguageEnum_Z ConsoleConfiguration::GetLanguage() {
    // TODO: Implement
    return LANG_NONE;
}
