#ifndef _AGENTFLAGS_ENGINE_H_
#define _AGENTFLAGS_ENGINE_H_

#define FL_AGENT_UNK_0x1 ((U32)1 << 0)                 // 0x1 - Unknown
#define FL_AGENT_UNK_0x2 ((U32)1 << 1)                 // 0x2 - Unknown
#define FL_AGENT_UNK_0x4 ((U32)1 << 2)                 // 0x4 - Unknown
#define FL_AGENT_UNK_0x8 ((U32)1 << 3)                 // 0x8 - Unknown
#define FL_AGENT_UNK_0x10 ((U32)1 << 4)                // 0x10 - Unknown
#define FL_AGENT_LODDYN ((U32)1 << 5)                  // 0x20 - LodDynAgent_Z
#define FL_AGENT_UNK_0x40 ((U32)1 << 6)                // 0x40 - Unknown
#define FL_AGENT_ANIMATED ((U32)1 << 7)                // 0x80 - It's animated
#define FL_AGENT_ANIMATED_MIX ((U32)1 << 8)            // 0x100 - It's mixed anim (smoothing)
#define FL_AGENT_ANIMATED_SEQ ((U32)1 << 9)            // 0x200 - It's sequenced (rtc?/animframe?)
#define FL_AGENT_UNK_0x400 ((U32)1 << 10)              // 0x400 - Maybe skel collide
#define FL_AGENT_CAMERA ((U32)1 << 11)                 // 0x800 - CameraAgent_Z
#define FL_AGENT_PARTICLES ((U32)1 << 12)              // 0x1000 - ParticlesAgent_Z
#define FL_AGENT_RTC ((U32)1 << 13)                    // 0x2000 - RtcAgent_Z
#define FL_AGENT_NEED_SOUND ((U32)1 << 14)             // 0x4000 - Needs sound
#define FL_AGENT_UNK_0x8000 ((U32)1 << 15)             // 0x8000 - Unknown
#define FL_AGENT_THROWN ((U32)1 << 16)                 // 0x10000 - Being thrown
#define FL_AGENT_NO_SUSPEND ((U32)1 << 17)             // 0x20000 - Don't suspend
#define FL_AGENT_NO_RESTORE ((U32)1 << 18)             // 0x40000 - Don't restore
#define FL_AGENT_UNK_0x80000 ((U32)1 << 19)            // 0x80000 - Unknown
#define FL_AGENT_PAUSED ((U32)1 << 20)                 // 0x100000 - Will get executed even if ScriptMgr is paused
#define FL_AGENT_DEFAULT ((U32)1 << 21)                // 0x200000 - Unknown
#define FL_AGENT_RTC_PLAYING ((U32)1 << 22)            // 0x400000 - Rtc is playing
#define FL_AGENT_UNK_0x800000 ((U32)1 << 23)           // 0x800000 - Unknown
#define FL_AGENT_CAMERA_NO_SUSPEND ((U32)1 << 24)      // 0x1000000 - Don't suspend camera agent
#define FL_AGENT_HAS_EMITTER_FLAG_0x100 ((U32)1 << 25) // 0x2000000 - Has emitter flag 0x100
#define FL_AGENT_OBJECTMOVE_SET ((U32)1 << 26)         // 0x4000000 - ObjectMove was set for MovingAgent_Z
#define FL_AGENT_BREAKABLE ((U32)1 << 27)              // 0x8000000 - Breakable_Z
#define FL_AGENT_UPDATE_BREAK ((U32)1 << 28)           // 0x10000000 - Breakable_Z Suspend/Restore
#define FL_AGENT_SKIN ((U32)1 << 29)                   // 0x20000000 - SkinAgent_Z
#define FL_AGENT_UNK_0x40000000 ((U32)1 << 30)         // 0x40000000 - Unknown
#define FL_AGENT_ENGINE_LAST ((U32)1 << 31)            // 0x80000000 - Unknown

#endif
