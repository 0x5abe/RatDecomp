#include "GCRenderer_Z.h"

Extern_Z "C" void exit(int);

// TODO: Finish matching
U16 GCRenderer_Z::SortRendererDatas(SortElem_Z* i_List) {
    U16 l_Head[256];
    U16 l_Tail[256];

    for (int i = 0; i < 256; i++) {
        l_Head[i] = INVALID_SORT_ELEM_IDX;
    }

    U16 l_CurIdx = 0;

    for (int i = 3; i >= 0; i--) {
        while (l_CurIdx != INVALID_SORT_ELEM_IDX) {
            U32 l_Key = ((U8*)&i_List[l_CurIdx].m_Key)[i];

            if (l_Head[l_Key] == INVALID_SORT_ELEM_IDX) {
                l_Head[l_Key] = l_CurIdx;
                l_Tail[l_Key] = l_CurIdx;
            }
            else {
                i_List[l_Tail[l_Key]].m_NextElemIdx = l_CurIdx;
                l_Tail[l_Key] = l_CurIdx;
            }

            l_CurIdx = i_List[l_CurIdx].m_NextElemIdx;
        }

        l_CurIdx = INVALID_SORT_ELEM_IDX;

        for (int j = 255; j >= 0; j--) {
            if (l_Head[j] != INVALID_SORT_ELEM_IDX) {
                i_List[l_Tail[j]].m_NextElemIdx = l_CurIdx;
                l_CurIdx = l_Head[j];
                l_Head[j] = INVALID_SORT_ELEM_IDX;
            }
        }
    }

    return l_CurIdx;
}
