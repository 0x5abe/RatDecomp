#ifndef _STREAMAGENT_Z_H_
#define _STREAMAGENT_Z_H_
#include "ABC_Agent.h"
#include "StreamFile_ZHdl.h"
// clang-format off

BEGIN_AGENT_CLASS(StreamAgent_Z, ABC_Agent, 8)
public:
    StreamAgent_Z() {
        EnableFlag(FL_AGENT_PAUSED);
    }

    virtual ~StreamAgent_Z() { }
    virtual Bool MarkHandles();

    DECL_BHV(StreamEnd);
    DECL_BHV(StreamAborted);
    DECL_BHV(StreamError);
    DECL_BHV(StreamResumed);

    virtual void Start() {}
    virtual void End();
    virtual void Resume(S32 i_Cause);
    virtual void Resumed() {}
    virtual void Abort();
    virtual void Aborted();

    void OpenBigFile(const Char* i_BfName);

private:
    StreamFile_ZHdl m_StreamHdl;
END_AGENT_CLASS

// clang-format on
#endif // _STREAMAGENT_Z_H_
