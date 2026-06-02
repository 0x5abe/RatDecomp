#include "S_MALLOC.h"
#include "Sys_Z.h"

void s_FREE_MEM_BUCKETS::Extend() {
    if (IsReallocating) {
        return;
    }

    if (!NeedToExtend) {
        return;
    }

    IsReallocating = TRUE;

    S32 l_NewBucketTotalBlocks = (m_BucketTotalBlocks * 3) >> 1;

    s_MEM_BLOCK** l_NewBucketBlocks = (s_MEM_BLOCK**)s_malloc(l_NewBucketTotalBlocks * (s_MEM_BUCKET_COUNT * sizeof(s_MEM_BLOCK*)), 4);
    s_MEM_BLOCK** l_OldBucketBlocks = m_BucketBlocks;

    S32 l_BucketIdx = 0;
    S32 l_NewBucketOffset = 0;

    do {
        S32 l_BucketCount = m_BucketFreeBlocks[l_BucketIdx];

        if (l_BucketCount) {
            Sys_Z::MemCpyFrom(
                l_NewBucketBlocks + l_NewBucketTotalBlocks * l_BucketIdx,
                l_OldBucketBlocks + (l_BucketIdx * m_BucketTotalBlocks),
                l_BucketCount * sizeof(s_MEM_BLOCK*)
            );
        }

        l_BucketIdx++;
    } while (l_BucketIdx < s_MEM_BUCKET_COUNT);

    m_BucketBlocks = l_NewBucketBlocks;
    m_BucketTotalBlocks = l_NewBucketTotalBlocks;

    if (HasAllocatedFreeBlock) {
        s_free(l_OldBucketBlocks);
    }

    HasAllocatedFreeBlock = TRUE;
    IsReallocating = FALSE;
    NeedToExtend = FALSE;
}

s_MEM_BLOCK* s_FREE_MEM_BUCKETS::FindBlock(S32 i_BucketIdx, S32 i_MinSize) {
    S32 l_Count = m_BucketFreeBlocks[i_BucketIdx];

    if (!l_Count) {
        return NULL;
    }

    s_MEM_BLOCK** l_BucketTrack = m_BucketBlocks + (m_BucketTotalBlocks * i_BucketIdx);

    S32 l_Idx = s_Dicho_RecBigger(l_BucketTrack, i_MinSize, 0, l_Count - 1);

    if (l_Idx < 0) {
        return NULL;
    }

    S32 l_Size = l_BucketTrack[l_Idx]->GetSize();
    s_MEM_BLOCK** l_Backward = l_BucketTrack + (l_Idx - 1);
    s_MEM_BLOCK** l_Forward = l_BucketTrack + (l_Idx + 1);
    s_MEM_BLOCK** l_End = l_BucketTrack + l_Count;
    s_MEM_BLOCK* l_BestBlock = l_BucketTrack[l_Idx];

    while (TRUE) {
        if (l_Backward < l_BucketTrack) {
            break;
        }

        if (l_Forward >= l_End) {
            goto scanBackward;
        }

        s_MEM_BLOCK* l_BackwardBlock = *l_Backward;
        s_MEM_BLOCK* l_ForwardBlock = *l_Forward;

        if (l_BackwardBlock->GetSize() != l_Size) {
            break;
        }

        if (l_ForwardBlock->GetSize() != l_Size) {
            goto scanBackward;
        }

        if (l_BackwardBlock < l_BestBlock) {
            l_BestBlock = l_BackwardBlock;
        }

        if (l_ForwardBlock < l_BestBlock) {
            l_BestBlock = l_ForwardBlock;
        }

        l_Backward--;
        l_Forward++;
    }

    while (TRUE) {
        if (l_Forward >= l_End) {
            goto returnBestBlock;
        }

        s_MEM_BLOCK* l_Block = *l_Forward;

        if (l_Block->GetSize() != l_Size) {
            goto returnBestBlock;
        }

        if (l_Block < l_BestBlock) {
            l_BestBlock = l_Block;
        }

        l_Forward++;
    }

scanBackward:
    while (TRUE) {
        if (l_Backward < l_BucketTrack) {
            break;
        }

        s_MEM_BLOCK* l_Block = *l_Backward;

        if (l_Block->GetSize() != l_Size) {
            break;
        }

        if (l_Block < l_BestBlock) {
            l_BestBlock = l_Block;
        }

        l_Backward--;
    }
returnBestBlock:
    return l_BestBlock;
}

void s_FREE_MEM_BUCKETS::AddBlock(s_MEM_BLOCK* i_Block) {
    S32 l_Bucket = FindBucket(i_Block->GetSize());
    AddBlockToBucket(l_Bucket, i_Block);
}

// TODO: Implement
void s_FREE_MEM_BUCKETS::RemoveBlock(s_MEM_BLOCK* i_Block) {
}

// TODO: Finish matching
s_MEM_BLOCK* s_FREE_MEM_BUCKETS::FindBlock(S32 i_MinSize) {
    s_MEM_BLOCK* l_Block = FindBestBlock(i_MinSize);

    if ((U32)l_Block >= BestFitLimit) {
        l_Block = FindFirstBlock(i_MinSize);
    }

    return l_Block;
}

S32 s_FREE_MEM_BUCKETS::s_GetInBucket(S32 i_BucketIdx, s_MEM_BLOCK* i_Block) {
    s_MEM_BLOCK** l_BucketTrack;
    S32 l_Count = m_BucketFreeBlocks[i_BucketIdx];

    if (l_Count) {
        l_BucketTrack = m_BucketBlocks + (m_BucketTotalBlocks * i_BucketIdx);
        U32 l_BlockSpan = i_Block->GetSize();

        S32 l_Idx = s_Dicho_RecEqual(l_BucketTrack, l_BlockSpan, 0, l_Count - 1);

        if (l_Idx < l_Count) {
            s_MEM_BLOCK** l_Backward = l_BucketTrack + l_Idx;
            s_MEM_BLOCK** l_Forward = l_BucketTrack + (l_Idx + 1);
            s_MEM_BLOCK** l_End = l_BucketTrack + l_Count;

            while (TRUE) {
                if (l_Backward < l_BucketTrack) {
                    break;
                }

                if (l_Forward >= l_End) {
                    goto lastCheck;
                }

                s_MEM_BLOCK* l_BackwardBlock = *l_Backward;
                s_MEM_BLOCK* l_ForwardBlock = *l_Forward;

                if (l_BackwardBlock == i_Block) {
                    return l_Backward - l_BucketTrack;
                }

                if (l_ForwardBlock == i_Block) {
                    return l_Forward - l_BucketTrack;
                }

                l_Backward--;
                l_Forward++;
            }

            while (TRUE) {
                if (l_Forward >= l_End) {
                    goto returnMinusOne;
                }

                if (*l_Forward == i_Block) {
                    return l_Forward - l_BucketTrack;
                }

                l_Forward++;
            }

        lastCheck:
            while (TRUE) {
                if (l_Backward < l_BucketTrack) {
                    break;
                }

                if (*l_Backward == i_Block) {
                    return l_Backward - l_BucketTrack;
                }

                l_Backward--;
            }
        }
    }
returnMinusOne:
    return -1;
}

void s_Init(void* i_StartOfMemory, U32 i_TotalMemory) {
    // Reset global allocator state.
    IsReallocating = FALSE;
    HasAllocatedFreeBlock = FALSE;
    RealAllocatedMem = 0;

    // Store arena bounds.
    StartOfMemory = i_StartOfMemory;
    EndOfMemory = (U32)i_StartOfMemory + i_TotalMemory;

    // At initialization, the allocator has one free block: the root block.
    MAXnbFreeBlocks = 1;

    // Place the allocation-strategy threshold around 4/5 into the arena.
    // The result is aligned down to 8 bytes.
    BestFitLimit = (U32)i_StartOfMemory + AlignDown_Z((i_TotalMemory / 5) * 4, 8);

    // The free-bucket manager is stored at the beginning of the arena itself.
    FreeBuckets = (s_FREE_MEM_BUCKETS*)i_StartOfMemory;

    // The root block is embedded inside the bucket manager and represents the
    // initial free memory range.
    s_MEM_BLOCK* l_RootBlock = &FreeBuckets->m_RootBlock;

    // Initialize bucket tracking.
    FreeBuckets->Init();

    // Initialize the root block as the single initial free block.
    l_RootBlock->Init();

    // Insert the root block into the correct free bucket.
    FreeBuckets->AddBlock(l_RootBlock);
}

// TODO: Implement
void s_MarkMem(U32) { }

// TODO: Implement
U32 s_ShowUnMarkedMem() {
    return 0;
}

U32 s_GetAllocatedMem() {
    return RealAllocatedMem;
}

// TODO: Implement
void s_ShowMostNbMalloc() {
    return;
}

// TODO: Finish matching
U32 s_getnbfindalloc(void* i_Start, void* i_End) {
    U32 l_Count = 0;

    s_MEM_BLOCK* l_Block = FreeBuckets->FindBlock(0);

    if (!l_Block) {
        return 0;
    }

    if (!l_Block->GetFree()) {
        if ((U32)i_End >= (U32)l_Block) {
            if ((U32)i_Start <= l_Block->GetMaxAddress()) {
                l_Count = 1;
            }
        }
    }

    s_MEM_BLOCK* l_PrevBlock = l_Block->GetPrev();

    while (l_PrevBlock) {
        if (!l_PrevBlock->GetFree()) {
            if ((U32)i_End >= (U32)l_PrevBlock) {
                if ((U32)i_Start <= l_PrevBlock->GetMaxAddress()) {
                    l_Count++;
                }
            }
        }

        l_PrevBlock = l_PrevBlock->GetPrev();
    }

    s_MEM_BLOCK* l_NextBlock = l_Block->GetNext();

    while (l_NextBlock) {
        if (!l_NextBlock->GetFree()) {
            if ((U32)i_End >= (U32)l_NextBlock) {
                if ((U32)i_Start <= l_NextBlock->GetMaxAddress()) {
                    l_Count++;
                }
            }
        }

        l_NextBlock = l_NextBlock->GetNext();
    }

    return l_Count;
}

// TODO: Implement
U32 s_getfindalloc(S32, Char*, void*, void*) {
    return 0;
}

// TODO: Fininsh matching
void s_findalloc(void* i_Start, void* i_End) {
    U32 l_Count = s_getnbfindalloc(i_Start, i_End);

    Char l_Buffer[512];

    for (U32 i = 0; i < l_Count; i++) {
        s_getfindalloc(i, l_Buffer, i_Start, i_End);
    }
}

// TODO: Implement
Bool s_VerifyMem() {
    return FALSE;
}

// TODO: Implement
U32 s_GetFreeMem() {
    return 0;
}

// TODO: Implement
U32 s_GetNbFreeBlocks() {
    return 0;
}

// TODO: Implement
U32 s_GetLargestFree() {
    return 0;
}

// TODO: Implement
S32 s_Dicho_RecEqual(s_MEM_BLOCK**, U32, S32, S32) {
    return 0;
}

// TODO: Implement
U32 s_Dicho_RecAfter(s_MEM_BLOCK**, U32, S32, S32) {
    return 0;
}

// TODO: Implement
S32 s_Dicho_RecBigger(s_MEM_BLOCK**, U32, S32, S32) {
    return 0;
}

// TODO: Implement
Bool s_QuickTestIntegrity(s_MEM_BLOCK*) {
    return FALSE;
}

// TODO: Implement
Bool s_TestIntegrity(s_MEM_BLOCK*) {
    return FALSE;
}

// TODO: Implement
void s_SplitToAllocAndFreeBlock(s_MEM_BLOCK*, U32) {
}

// TODO: Implement
void s_free(void* i_Ptr) {
}

// TODO: Implement
void* s_malloc(U32 i_Size, U32 i_Alignment) {
    return NULL;
}

// TODO: Implement
void* s_malloc_end(U32 i_Size, U32 i_Alignment) {
    return NULL;
}

// TODO: Implement
void* s_fullrealloc(void* i_Ptr, U32 i_NewSize) {
    return NULL;
}

// TODO: Implement
void* s_mergewithnextrealloc(void* i_Ptr, U32 i_NewSize) {
    return NULL;
}

// TODO: Implement
void* s_realloc(void* i_Ptr, U32 i_NewSize) {
    return NULL;
}
