#include "RtcAgent_Z.h"
#include "Renderer_Z.h"

// clang-format off

BEGIN_INIT_AGENT_CLASS(RtcAgent_Z, AnimatedMsgAgent_Z)
    ADD_BEHAVIOR(RtcEnd)
END_INIT_AGENT_CLASS

BEHAVIOR(RtcAgent_Z,RtcEnd)
    CATEGORY(cat_running_rtc)
BEGIN_BEHAVIOR
    CONDITION
        Message(msg_rtc_ended)
    ACTION
        End();
END_BEHAVIOR

// clang-format on

RtcAgent_Z::RtcAgent_Z() {
    m_ViewportId = NONE_VIEWPORT;
    EnableFlag(FL_AGENT_RTC);
}
