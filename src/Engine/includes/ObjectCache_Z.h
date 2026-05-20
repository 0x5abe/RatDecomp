#ifndef _OBJECTCACHE_Z_H_
#define _OBJECTCACHE_Z_H_

#include "DynArray_Z.h"
#include "BaseObject_Z.h"
#include "Math_Z.h"

struct CacheStateLRU_Z {
    BaseObject_Z* m_OwnerPtr;
    U16 m_OwnerId;

    CacheStateLRU_Z() {
        m_OwnerPtr = NULL;
        m_OwnerId = -1;
    }
};

template <class T, class V>
class LRU_Z {
public:
    struct List_Ele {
        T m_Val;
        V m_PrevEntry;
        V m_NextEntry;
    };

    void Init(S32 i_Size) {
        m_LRUList.SetSize(i_Size + 2);

        S32 l_PlusOne = i_Size + 1;
        for (S32 i = 0; i < i_Size + 2; i++) {
            m_LRUList[i].m_PrevEntry = Max(i - 1, (S32)0);
            m_LRUList[i].m_NextEntry = Min(i + 1, l_PlusOne);
        }
        FIXDEBUGINLINING_Z();
    }

private:
    DynArray_Z<List_Ele, 32, 0, 1, 4> m_LRUList;
};

template <class T>
class CacheEntryLRU_Z {
public:
    CacheEntryLRU_Z() {
        m_CacheData = NULL;
    }

    inline void SetSize(S32 i_LRUCount, S32 i_EntryCount) {
        m_CacheEntryCount = i_EntryCount;
        m_LRU.Init(i_LRUCount);
        if (m_CacheData) {
            if (TRUE) {
                Delete_Z[] m_CacheData;
            }
        }
        m_CacheData = NewL_Z(34) T[(i_LRUCount * m_CacheEntryCount)];
        return;
    }

private:
    LRU_Z<CacheStateLRU_Z, U16> m_LRU;
    S32 m_CacheEntryCount;
    T* m_CacheData;
};

#endif
