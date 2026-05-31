#ifndef _BNKDYNARRAY_Z_H_
#define _BNKDYNARRAY_Z_H_

#include "Types_Z.h"
#include "Memory_Z.h"
#include "DynArray_Z.h"

template <class T, S32 Granularity = 8, Bool DeleteObject = TRUE, Bool InitObject = TRUE, S32 Alignment = _ALLOCDEFAULTALIGN>
struct BnkDynArrayEle_Z {
    typedef BnkDynArrayEle_Z<T, Granularity, DeleteObject, InitObject, Alignment> Bank_Z;

    Bank_Z* m_NextBank;
    DynArray_Z<T, Granularity, DeleteObject, InitObject, Alignment> m_DA;

    BnkDynArrayEle_Z() {
        m_NextBank = NULL;
    }
};

template <class T, S32 Granularity = 8, Bool DeleteObject = TRUE, Bool InitObject = TRUE, S32 Alignment = _ALLOCDEFAULTALIGN>
class BnkDynArray_Z {
public:
    typedef BnkDynArrayEle_Z<T, Granularity, DeleteObject, InitObject, Alignment> Bank_Z;

    BnkDynArray_Z() {
        m_HeadBank = NULL;
    }

    ~BnkDynArray_Z() {
        Flush();
    }

    S32 GetSize() const {
        S32 l_Size = 0;

        Bank_Z* l_Bank = m_HeadBank;
        while (l_Bank) {
            l_Size += l_Bank->m_DA.GetSize();
            l_Bank = l_Bank->m_NextBank;
        }

        return l_Size;
    }

    T& Add() {
        Bank_Z** l_Link = &m_HeadBank;
        Bank_Z* l_Bank;

        while ((l_Bank = *l_Link)) {
            if (!l_Bank->m_DA.GetSize()) {
                break;
            }

            if (l_Bank->m_DA.GetFree()) {
                break;
            }

            l_Link = &l_Bank->m_NextBank;
        }

        if (!l_Bank) {
            l_Bank = NewL_Z(84) Bank_Z;
            *l_Link = l_Bank;
        }

        if (!l_Bank->m_DA.GetFree()) {
            l_Bank->m_DA.SetSize(Granularity);
        }

        return l_Bank->m_DA[l_Bank->m_DA.Add()];
    }

    void Empty() {
        Bank_Z* l_Bank = m_HeadBank;

        while (l_Bank) {
            l_Bank->m_DA.Empty();
            l_Bank = l_Bank->m_NextBank;
        }
    }

    void Flush() {
        Bank_Z* l_Bank = m_HeadBank;

        while (l_Bank) {
            m_HeadBank = l_Bank->m_NextBank;
            Delete_Z l_Bank;
            l_Bank = m_HeadBank;
        }
    }

private:
    Bank_Z* m_HeadBank;
};

#endif
