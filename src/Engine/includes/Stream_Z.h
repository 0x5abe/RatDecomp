#ifndef _STREAM_Z_H_
#define _STREAM_Z_H_
#include "Types_Z.h"
#include "BaseStream_Z.h"

#define STR_FILE_ERROR_NONE 0

struct StrBuffer {
    void* m_RealPtr;
    void* m_AlignedPtr;

    StrBuffer() {
        m_RealPtr = NULL;
    }
};

class Stream_Z : public BaseStream_Z {
    friend class StreamFile_Z;

public:
    Stream_Z()
        : m_LoadStage(0)
        , m_ErrorCode(0) {
    }

    virtual void Open(const Char* i_Buffer);
    virtual void Process(void* o_Buffer, S32 i_Offset, S32 i_Size);
    virtual void Close();
    virtual void Update();

    S32 GetErrorCode() const { return m_ErrorCode; }

private:
    S32 m_LoadStage;
    S32 m_ErrorCode;
    S32 m_Size;
};

#endif // _STREAM_Z_H_
