#include "TriangleCache_Z.h"

void ColTriangleCache_Z::Flush() {
    m_OwnerLookup.SetSize(COL_TRI_OWNER_LOOKUP_SIZE);
    // $SABE: This is so disgusting
    S32 i = COL_TRI_OWNER_LOOKUP_SIZE;
    S32 j = 0;
    while (i--) {
        m_OwnerLookup[j] = 0xFFFF;
        j++;
    }

    m_FreeTriangleListHead = 0;
    m_FreeTriangleCount = COL_TRI_CACHE_SIZE;

    m_TriPool.SetSize(COL_TRI_CACHE_SIZE);
    // $SABE: This is so disgusting
    i = COL_TRI_CACHE_SIZE;
    j = 0;
    while (i--) {
        m_TriPool[j].m_NextIdx = j + 1;
        j++;
    }

    m_Owners.SetSize(COL_TRI_OWNER_COUNT);
    // $SABE: This is so disgusting
    i = COL_TRI_OWNER_COUNT;
    j = 0;
    while (i--) {
        m_Owners[j].m_TriIdx = 0xFFFFFFFF;
        j++;
    }

    m_NextInsertOwnerIndex = 0;
    m_EvictionScanIndex = 0;
    m_OwnerHashMask = COL_TRI_OWNER_LOOKUP_SIZE - 1;
    m_OwnerIndexMask = COL_TRI_OWNER_COUNT - 1;
}
