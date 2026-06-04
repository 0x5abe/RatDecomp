#ifndef _OBJECTCACHE_Z_H_
#define _OBJECTCACHE_Z_H_

#include "DynArray_Z.h"
#include "BaseObject_Z.h"
#include "Math_Z.h"
#include "Types_Z.h"
#include "DynArray_Z.h"

struct CacheStateFrame_Z {
    U16 m_Key;          // 0x00 - User/key value, 0xffff when free
    U8 m_Age;           // 0x02 - Incremented by Update, freed when it reaches 2
    U8 m_UsedThisFrame; // 0x03 - Set to 1 when allocated/refreshed
    void* m_Object;     // 0x04 - Owner/key pointer, often BaseObject_Z*
};

template <class T, Bool DeleteObject = TRUE, S32 Align = _ALLOCDEFAULTALIGN>
class CacheEntryFrame_Z {
public:
    S32 GetEntryCount() const {
        return m_CacheStates.GetSize();
    }

    S32 GetFreeCount() const {
        return m_NbFree;
    }

    S32 GetMaxInUseNb() const {
        return m_MaxInUseNb;
    }

    //private:
    DynArray_Z<CacheStateFrame_Z, 8, FALSE, TRUE, 4> m_CacheStates; // 0x00
    DynArray_Z<U16, 32, FALSE, FALSE, 4> m_FreeIndices;             // 0x08
    S32 m_NbFree;                                                   // 0x10
    S32 m_Stride;                                                   // 0x14
    S32 m_MaxInUseNb;                                               // 0x18
    S32 m_MaxUsedIndex;                                             // 0x1c
    T* m_Datas;                                                     // 0x20
    S32 m_DataCount;                                                // 0x24
};

template <class T, S32 Count, Bool DeleteObject, Bool InitObject, S32 Align>
class BnkCacheEntryFrame_Z {
public:
    BnkCacheEntryFrame_Z* GetNext() const {
        return m_Next;
    }

    S32 GetEntryCount() const {
        return m_Frame.GetEntryCount();
    }

    S32 GetFreeCount() const {
        return m_Frame.GetFreeCount();
    }

    S32 GetMaxInUseNb() const {
        return m_Frame.GetMaxInUseNb();
    }

    //private:
    BnkCacheEntryFrame_Z* m_Next;                      // 0x00
    U16 m_BaseIndex;                                   // 0x04
    CacheEntryFrame_Z<T, DeleteObject, Align> m_Frame; // 0x08
};

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
    DynArray_Z<List_Ele, 32, FALSE, TRUE, 4> m_LRUList;
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
