#ifndef _ARAMXALLOCATOR_Z_H_
#define _ARAMXALLOCATOR_Z_H_

#include "Types_Z.h"

template <S32 BlockCount, S32 Alignment, S32 TotalSize>
class ARamXAllocator_Z {
public:
    struct Block {
        S32 m_User;
        S32 m_UserParam1;
        S32 m_UserParam2;
        S32 m_StartAddress;
        S32 m_Size;
        S32 m_InUse;
        S16 m_PrevBlockIdx;
        S16 m_NextBlockIdx;
    };

    S32 AllocBlock(S32 i_Size, S32 i_UserParam1, S32 i_UserParam2) {
        if (!i_Size) {
            return -1;
        }

        S32 l_Size = (i_Size + (Alignment - 1)) & ~(Alignment - 1);

        if (m_FirstFreeBlockIdx == -1) {
            return -1;
        }

        S32 l_NewBlockIdx = m_FirstFreeBlockIdx;

        if (m_FirstUsedBlockIdx == -1) {
            S32 l_FreeSize = m_EndAddress - m_StartAddress;

            if (l_Size > l_FreeSize) {
                return -1;
            }

            Block* l_NewBlock = &m_Blocks[l_NewBlockIdx];

            m_FirstUsedBlockIdx = l_NewBlockIdx;
            m_FirstFreeBlockIdx = l_NewBlock->m_NextBlockIdx;

            l_NewBlock->m_StartAddress = m_StartAddress;
            l_NewBlock->m_Size = l_Size;
            l_NewBlock->m_InUse = TRUE;
            l_NewBlock->m_UserParam1 = i_UserParam1;
            l_NewBlock->m_UserParam2 = i_UserParam2;
            l_NewBlock->m_User = -1;
            l_NewBlock->m_PrevBlockIdx = -1;
            l_NewBlock->m_NextBlockIdx = -1;

            m_AllocatedSize += l_NewBlock->m_Size;

            return l_NewBlockIdx;
        }

        S32 l_BlockIdx = m_FirstUsedBlockIdx;

        while (TRUE) {
            Block* l_Block = &m_Blocks[l_BlockIdx];

            if (l_Block->m_PrevBlockIdx == -1) {
                S32 l_FreeSize = l_Block->m_StartAddress - m_StartAddress;

                if (l_Size <= l_FreeSize) {
                    Block* l_NewBlock = &m_Blocks[l_NewBlockIdx];

                    m_FirstUsedBlockIdx = l_NewBlockIdx;
                    m_FirstFreeBlockIdx = l_NewBlock->m_NextBlockIdx;

                    l_NewBlock->m_StartAddress = m_StartAddress;
                    l_NewBlock->m_Size = l_Size;
                    l_NewBlock->m_InUse = TRUE;
                    l_NewBlock->m_PrevBlockIdx = -1;
                    l_NewBlock->m_NextBlockIdx = l_BlockIdx;
                    l_NewBlock->m_UserParam1 = i_UserParam1;
                    l_NewBlock->m_UserParam2 = i_UserParam2;
                    l_NewBlock->m_User = -1;

                    l_Block->m_PrevBlockIdx = l_NewBlockIdx;

                    m_AllocatedSize += l_NewBlock->m_Size;

                    return l_NewBlockIdx;
                }
            }
            else {
                S32 l_PrevBlockIdx = l_Block->m_PrevBlockIdx;
                Block* l_PrevBlock = &m_Blocks[l_PrevBlockIdx];

                S32 l_FreeStart = l_PrevBlock->m_StartAddress + l_PrevBlock->m_Size;
                S32 l_FreeSize = l_Block->m_StartAddress - l_FreeStart;

                if (l_Size <= l_FreeSize) {
                    Block* l_NewBlock = &m_Blocks[l_NewBlockIdx];

                    m_FirstFreeBlockIdx = l_NewBlock->m_NextBlockIdx;

                    l_NewBlock->m_StartAddress = l_FreeStart;
                    l_NewBlock->m_Size = l_Size;
                    l_NewBlock->m_InUse = TRUE;
                    l_NewBlock->m_PrevBlockIdx = l_Block->m_PrevBlockIdx;
                    l_NewBlock->m_NextBlockIdx = l_BlockIdx;
                    l_NewBlock->m_UserParam1 = i_UserParam1;
                    l_NewBlock->m_UserParam2 = i_UserParam2;
                    l_NewBlock->m_User = -1;

                    l_PrevBlock->m_NextBlockIdx = l_NewBlockIdx;
                    l_Block->m_PrevBlockIdx = l_NewBlockIdx;

                    m_AllocatedSize += l_NewBlock->m_Size;

                    return l_NewBlockIdx;
                }
            }

            if (l_Block->m_NextBlockIdx == -1) {
                S32 l_FreeStart = l_Block->m_StartAddress + l_Block->m_Size;
                S32 l_FreeSize = m_EndAddress - l_FreeStart;

                if (l_Size > l_FreeSize) {
                    return -1;
                }

                Block* l_NewBlock = &m_Blocks[l_NewBlockIdx];

                m_FirstFreeBlockIdx = l_NewBlock->m_NextBlockIdx;

                l_NewBlock->m_StartAddress = l_FreeStart;
                l_NewBlock->m_Size = l_Size;
                l_NewBlock->m_InUse = TRUE;
                l_NewBlock->m_PrevBlockIdx = l_BlockIdx;
                l_NewBlock->m_NextBlockIdx = -1;
                l_NewBlock->m_UserParam1 = i_UserParam1;
                l_NewBlock->m_UserParam2 = i_UserParam2;
                l_NewBlock->m_User = -1;

                l_Block->m_NextBlockIdx = l_NewBlockIdx;

                m_AllocatedSize += l_NewBlock->m_Size;

                return l_NewBlockIdx;
            }

            l_BlockIdx = l_Block->m_NextBlockIdx;
        }
    }

public:
    Block m_Blocks[BlockCount];
    S32 m_FirstUsedBlockIdx;
    S32 m_FirstFreeBlockIdx;
    S32 m_StartAddress;
    S32 m_EndAddress;
    S32 m_Unk_0x1c10;
    S32 m_AllocatedSize;
    Bool m_IsInitialized;
};

#endif
