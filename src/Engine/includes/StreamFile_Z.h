#ifndef _STREAMFILE_Z_H_
#define _STREAMFILE_Z_H_
#include "Manipulator_Z.h"
#include "StreamAgent_ZHdl.h"
#include "Streaming_Z.h"
#include "ClassManager_Z.h"
#include "DynPtrArray_Z.h"
#include "Types_Z.h"

#define STR_FILE_LOAD_STAGE_ABORT -1
#define STR_FILE_LOAD_STAGE_INIT 0

struct BlockDescription_Z {
    U32 m_ObjectCount;
    U32 m_PaddedSize;
    U32 m_DataSize;
    U32 m_WorkingBufferOffset;
    Name_Z m_FirstResourceName;
    U32 m_BlockHash;
};

struct BigFileHeader_Z {
    Char m_VersionString[ARRAY_CHAR_MAX];
    U32 m_IsNotRtc;
    U32 m_BlockCount;
    U32 m_WorkingBufferCapacityEven;
    U32 m_WorkingBufferCapacityOdd;
    U32 m_PaddedSize;
    U32 m_VersionPatch;
    U32 m_VersionMinor;
    U32 m_UnkS32_0x11c;
    BlockDescription_Z m_Blocks[64];
    U32 m_UnkS32_0x720;
    U32 m_PoolManifestPaddedSize;
} Aligned_Z(2048);

#define g_BigFileHeader ((BigFileHeader_Z&)StreamFile_Z::gBigFileHeader)

class StreamFile_Z : public Manipulator_Z {
public:
    StreamFile_Z() { }

    virtual ~StreamFile_Z();
    virtual void Init();
    virtual void Update(Float i_DeltaTime);

    static BaseObject_Z* NewObject() { return NewL_Z(56) StreamFile_Z; }

    void Start(const Char* i_FilePath, const StreamAgent_ZHdl& i_AgentHdl);
    void Resume();

    Stream_Z& GetStream() { return m_Str; }

    void SetLoadStage(S32 i_LoadStage) { m_LoadStage = i_LoadStage; }

private:
    S32 m_LoadStage;
    S32 m_LoadStageBeforeResume;
    S32 m_BlockOffsetToRead;
    StreamX_Z m_Str;
    StrBuffer m_Buf[2];
    S32 m_CurBlockIdx;
    BigFileRsc_Z m_CurResource;
    StreamAgent_ZHdl m_AgentHdl;
    String_Z<ARRAY_CHAR_MAX> m_BfPath;
    DynPtrArray_Z<BaseObject_Z*, 32> m_Resources;
    S32 m_CurResourceIdx;
    S32 m_UnkS32_0x174;
    Bool m_RestoreVSync;

    static U8 gBigFileHeader[sizeof(BigFileHeader_Z)];
};

#endif // _STREAMFILE_Z_H_
