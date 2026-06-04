#ifndef _DISPLAYLIST_Z_H_
#define _DISPLAYLIST_Z_H_
#include "Memory_Z.h"
#include "Assert_Z.h"
#include <gx.h>

class BaseDisplayList_Z {
    virtual void GetSize();
    virtual void GetCurSize();
    virtual void GetData();
    virtual void Call();
};

class DisplayList_Z : public BaseDisplayList_Z {
    U8* m_Data;
    U32 m_CurrSize;
    U32 m_Size;

public:
    DisplayList_Z() {
        m_Data = NULL;
        m_CurrSize = 0;
        m_Size = 0;
    };

    ~DisplayList_Z() {
        if (m_Data) {
            Free_Z(m_Data);
        }
        m_Data = NULL;
        m_CurrSize = 0;
        m_Size = 0;
    };

    void Begin() {
        DCInvalidateRange(m_Data, m_CurrSize);
        GXBeginDisplayList(m_Data, m_CurrSize);
    }

    void Alloc(S32 i_Size, const Char* i_Comment = NULL) {
        m_CurrSize = i_Size;
        m_Data = (U8*)AllocAlignCL_Z(m_CurrSize, i_Comment, 64, 32);
    }

    U32 End() {
        m_Size = GXEndDisplayList();
        ASSERTLE_Z(m_CurrSize <= m_Size, "Display List Overflow.", 112, "CurrSize<=Size");
        DCStoreRange(m_Data, m_CurrSize);
        return m_Size;
    }

    virtual void GetSize();
    virtual void GetCurSize();
    virtual void GetData();
};

#endif // _DISPLAYLIST_Z_H_
