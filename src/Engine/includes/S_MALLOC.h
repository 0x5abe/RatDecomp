#ifndef _S_MALLOC_H_
#define _S_MALLOC_H_

#include "Types_Z.h"

//---- Constants and macros ----//

#define s_MEM_BUCKET_COUNT 10
#define s_MEM_BUCKET_INITIAL_BLOCKS 16

// Encoded block address/size fields are biased by this value.
// A stored value of 0x400 decodes to zero, which is used as a sentinel in some cases.
#define s_MEM_BLOCK_ENCODE_BIAS 0x400

// Allocation block headers are 8 bytes: two encoded 32-bit words.
#define s_MEM_BLOCK_HEADER_SIZE 8

struct s_MEM_BLOCK;
struct s_FREE_MEM_BUCKETS;

//---- Function declarations ----//

void s_Init(void* i_StartOfMemory, U32 i_TotalMemory);
void s_MarkMem(U32);
U32 s_ShowUnMarkedMem();
U32 s_GetAllocatedMem();
void s_ShowMostNbMalloc();
U32 s_getnbfindalloc(void*, void*);
U32 s_getfindalloc(S32, Char*, void*, void*);
void s_findalloc(void* i_Start, void* i_End);
Bool s_VerifyMem();
U32 s_GetFreeMem();
U32 s_GetNbFreeBlocks();
U32 s_GetLargestFree();
S32 s_Dicho_RecEqual(s_MEM_BLOCK**, U32, S32, S32);
U32 s_Dicho_RecAfter(s_MEM_BLOCK**, U32, S32, S32);
S32 s_Dicho_RecBigger(s_MEM_BLOCK**, U32, S32, S32);
Bool s_QuickTestIntegrity(s_MEM_BLOCK*);
Bool s_TestIntegrity(s_MEM_BLOCK*);
void s_SplitToAllocAndFreeBlock(s_MEM_BLOCK*, U32);
void s_free(void* i_Ptr);
void* s_malloc(U32 i_Size, U32 i_Alignment);
void* s_malloc_end(U32 i_Size, U32 i_Alignment);
void* s_fullrealloc(void* i_Ptr, U32 i_NewSize);
void* s_mergewithnextrealloc(void* i_Ptr, U32 i_NewSize);
void* s_realloc(void* i_Ptr, U32 i_NewSize);

//---- Global variables ----//

// Arena bounds.
U32 EndOfMemory;
void* StartOfMemory;

// Address inside the arena used as a threshold for allocation strategy.
// It is initialized around 4/5 into the arena, aligned down to 8 bytes.
U32 BestFitLimit;

// Allocator state / diagnostics.
Bool IsReallocating;
Bool HasAllocatedFreeBlock;
U32 RealAllocatedMem;
U32 MAXnbFreeBlocks;

// Active free-list manager and backing table for bucket entries.
s_FREE_MEM_BUCKETS* FreeBuckets;
s_MEM_BLOCK* TMPmem[s_MEM_BUCKET_COUNT * s_MEM_BUCKET_INITIAL_BLOCKS];

// Set when a bucket is close to running out of tracking slots.
Bool NeedToExtend;

//---- Structure definitions ----//

struct s_MEM_BLOCK {
    union {
        U32 m_BlockFlagsRaw;

        struct {
            // Top bit of the first byte. Set when the block is in a free bucket.
            U32 m_IsFree : 1;

            // Is it marked
            U32 m_IsMarked : 1;

            // Encoded block metadata value. It uses the same 0x400 bias scheme.
            U32 m_BlockValue : 30;
        } m_BlockFlags;
    };

    union {
        U32 m_EncodedSizeRaw;

        struct {
            // Small encoded size-class/index field.
            U32 m_SizeBits : 3;

            // Encoded maximum-address field.
            // Decoded as: (m_SizeValue - 0x400) << 2.
            U32 m_SizeValue : 29;
        } m_EncodedSize;
    };

    void Init() {
        // Initialize the root block with the neutral encoded value.
        // For m_EncodedSize, this makes GetMaxAddress() resolve to EndOfMemory.
        m_BlockFlags.m_BlockValue = s_MEM_BLOCK_ENCODE_BIAS;
        m_EncodedSize.m_SizeValue = s_MEM_BLOCK_ENCODE_BIAS;

        // Root block starts in the base size class.
        SetSizeBitsFromMask(1);

        // The root block initially represents all free arena memory.
        m_BlockFlags.m_IsFree = TRUE;
    } // Fully inlined

    U32 GetMaxAddress() {
        s_MEM_BLOCK* l_NextBlock = GetNext();
        if (!l_NextBlock) {
            l_NextBlock = (s_MEM_BLOCK*)EndOfMemory;
        }
        return (U32)l_NextBlock;
    } // Fully inlined

    void SetSizeBitsFromMask(U32 i_Mask) {
        m_EncodedSize.m_SizeBits = 0;

        while (m_EncodedSize.m_SizeBits < 0x20) {
            if ((1 << m_EncodedSize.m_SizeBits) & i_Mask) {
                break;
            }

            m_EncodedSize.m_SizeBits++;
        }
    } // Fully inlined

    s_MEM_BLOCK* GetNext() {
        s_MEM_BLOCK* l_NextBlock = (s_MEM_BLOCK*)((m_EncodedSize.m_SizeValue - s_MEM_BLOCK_ENCODE_BIAS) << 2);
        if (l_NextBlock) {
            l_NextBlock = (s_MEM_BLOCK*)((U32)l_NextBlock | 0x80000000);
        }
        return l_NextBlock;
    } // Matched 100%

    s_MEM_BLOCK* MergeNext() {
        return this;
    } // Matched 100%

    s_MEM_BLOCK* GetPrev() {
        s_MEM_BLOCK* l_PrevBlock = (s_MEM_BLOCK*)((m_BlockFlags.m_BlockValue - s_MEM_BLOCK_ENCODE_BIAS) << 2);
        if (l_PrevBlock) {
            l_PrevBlock = (s_MEM_BLOCK*)((U32)l_PrevBlock | 0x80000000);
        }
        return l_PrevBlock;
    } // Matched 100%

    U32 GetFree() {
        return m_BlockFlags.m_IsFree;
    } // Matched 100%

    U32 GetAlignDecal() {
        U32 l_Align = 1 << (m_EncodedSize.m_SizeBits + 2);
        U32 l_Address = (U32)this + s_MEM_BLOCK_HEADER_SIZE;
        U32 l_Decal = l_Address & (l_Align - 1);

        if (l_Decal) {
            return l_Align - l_Decal;
        }

        return 0;
    } // Matched 100%

    U32 GetSize() {
        return GetMaxAddress() - (U32)this;
    } // Matched 100%

    static void* GetRealPtr(void* i_Ptr) {
        U32 l_Decal = *((U32*)i_Ptr - 1);

        if (l_Decal >= s_MEM_BLOCK_ENCODE_BIAS) {
            return (void*)((U32)i_Ptr - s_MEM_BLOCK_HEADER_SIZE);
        }

        return (void*)((U32)i_Ptr - l_Decal - s_MEM_BLOCK_HEADER_SIZE);
    } // Matched 100%

    void SetMarked(U32 i_Mark) {
        m_BlockFlags.m_IsMarked = i_Mark;
    } // Matched 100%

    void AddAfter(s_MEM_BLOCK* i_Block) {
        if (!i_Block) {
            return;
        }

        i_Block->SetPrev(this);

        s_MEM_BLOCK* l_NextBlock = GetNext();

        i_Block->SetNext(l_NextBlock);

        if (l_NextBlock) {
            l_NextBlock->SetPrev(i_Block);
        }

        SetNext(i_Block);
    } // Matched 100%

    void SetAlign(U32 i_Align) {
        U32 l_AlignMask = (i_Align + 3) >> 2;

        if (!l_AlignMask) {
            l_AlignMask = 1;
        }

        m_EncodedSize.m_SizeBits = 0;

        while (m_EncodedSize.m_SizeBits < 0x20) {
            U32 l_Bits = m_EncodedSize.m_SizeBits;

            if (l_AlignMask & (1 << l_Bits)) {
                return;
            }

            m_EncodedSize.m_SizeBits = l_Bits + 1;
        }
    } // Matched 100%

    void SetPrev(s_MEM_BLOCK* i_Block) {
        m_BlockFlags.m_BlockValue = ((U32)i_Block >> 2) + s_MEM_BLOCK_ENCODE_BIAS;
    } // Matched 100%

    void SetNext(s_MEM_BLOCK* i_Block) {
        m_EncodedSize.m_SizeValue = ((U32)i_Block >> 2) + s_MEM_BLOCK_ENCODE_BIAS;
    } // Matched 100%
};

struct s_FREE_MEM_BUCKETS {
    // Flat table storing all bucket entries.
    // Bucket N starts at m_BucketBlocks + (m_BucketTotalBlocks * N).
    s_MEM_BLOCK** m_BucketBlocks;

    // Number of tracking slots available per bucket.
    S32 m_BucketTotalBlocks;

    // Number of blocks currently stored in each bucket.
    S32 m_BucketFreeBlocks[s_MEM_BUCKET_COUNT];

    // Initial free block. It is embedded in the bucket manager at the arena start.
    s_MEM_BLOCK m_RootBlock;

    void Init() {
        m_BucketTotalBlocks = s_MEM_BUCKET_INITIAL_BLOCKS;
        m_BucketBlocks = TMPmem;

        for (S32 i = 0; i < s_MEM_BUCKET_COUNT; i++) {
            m_BucketFreeBlocks[i] = 0;
        }
    } // Fully inlined

    S32 FindBucket(S32 i_MinSize) {
        i_MinSize -= s_MEM_BLOCK_HEADER_SIZE;

        S32 l_BucketIndex;

        // Large blocks start in a higher bucket range.
        if (i_MinSize & 0xFFFF0000) {
            l_BucketIndex = 12;

            if (l_BucketIndex >= s_MEM_BUCKET_COUNT - 1) {
                return s_MEM_BUCKET_COUNT - 1;
            }

            i_MinSize = (S32)i_MinSize >> 16;
        }
        else {
            l_BucketIndex = -4;
        }

        // Classify the size by finding its approximate highest set bit.
        if (i_MinSize & 0xFF00FF00) {
            i_MinSize = (S32)i_MinSize >> 8;
            l_BucketIndex += 8;
        }

        if (i_MinSize & 0xF0F0F0F0) {
            i_MinSize = (S32)i_MinSize >> 4;
            l_BucketIndex += 4;
        }

        if (i_MinSize & 0xCCCCCCCC) {
            i_MinSize = (S32)i_MinSize >> 2;
            l_BucketIndex += 2;
        }

        if (i_MinSize & 0xAAAAAAAA) {
            l_BucketIndex += 1;
        }

        if (l_BucketIndex < 0) {
            l_BucketIndex = 0;
        }

        if (l_BucketIndex >= s_MEM_BUCKET_COUNT) {
            return s_MEM_BUCKET_COUNT - 1;
        }

        return l_BucketIndex;
    } // Matched 100%

    void AddBlockToBucket(S32 i_BucketIdx, s_MEM_BLOCK* i_Block) {
        S32 l_Count = m_BucketFreeBlocks[i_BucketIdx];

        // Ask for bucket expansion if this bucket is nearly full.
        if (l_Count >= (m_BucketTotalBlocks - 6)) {
            NeedToExtend = TRUE;
        }

        // Locate this bucket's slice in the flat block table.
        s_MEM_BLOCK** l_BucketTrack = m_BucketBlocks + (m_BucketTotalBlocks * i_BucketIdx);

        S32 l_InsertIdx;

        // Keep each bucket sorted by block span.
        if (l_Count) {
            l_InsertIdx = s_Dicho_RecAfter(l_BucketTrack, i_Block->GetSize(), 0, l_Count - 1);
        }
        else {
            l_InsertIdx = 0;
        }

        // Make room for the new block if it belongs before existing entries.
        if (l_InsertIdx < l_Count) {
            s_MEM_BLOCK** l_Current = l_BucketTrack + (l_Count - 1);
            s_MEM_BLOCK** l_Target = l_BucketTrack + l_InsertIdx;

            while (l_Current >= l_Target) {
                l_Current[1] = *l_Current;
                l_Current--;
            }
        }

        l_BucketTrack[l_InsertIdx] = i_Block;

        // A block in a free bucket is marked free.
        i_Block->m_BlockFlags.m_IsFree = TRUE;

        m_BucketFreeBlocks[i_BucketIdx]++;
    } // Fully inlined

    S32 FindFreeBucket(S32 i_MinSize) {
        for (S32 l_Idx = FindBucket(i_MinSize); l_Idx < s_MEM_BUCKET_COUNT; l_Idx++) {
            if (m_BucketFreeBlocks[l_Idx]) {
                return l_Idx;
            }
        }
        return -1;
    } // Fully inlined

    s_MEM_BLOCK* FindFirstBlock(S32 i_MinSize) {
        s_MEM_BLOCK* l_Block = NULL;

        S32 l_BucketIdx = FindFreeBucket(i_MinSize);

        if (l_BucketIdx >= 0) {
            while (l_BucketIdx < s_MEM_BUCKET_COUNT) {
                S32 l_Count = m_BucketFreeBlocks[l_BucketIdx];

                s_MEM_BLOCK** l_BucketTrack = m_BucketBlocks + (m_BucketTotalBlocks * l_BucketIdx);
                s_MEM_BLOCK** l_Cur = l_BucketTrack;
                s_MEM_BLOCK** l_End = l_BucketTrack + l_Count;

                while (l_Cur < l_End) {
                    s_MEM_BLOCK* l_CurBlock = *l_Cur;

                    if (l_CurBlock->GetSize() >= (U32)i_MinSize) {
                        if (!l_Block || l_CurBlock < l_Block) {
                            l_Block = l_CurBlock;
                        }
                    }

                    l_Cur++;
                }

                l_BucketIdx++;
            }
        }

        return l_Block;
    } // Fully inlined

    s_MEM_BLOCK* FindBestBlock(S32 i_MinSize) {
        S32 l_BucketIdx = FindFreeBucket(i_MinSize);

        if (l_BucketIdx >= 0) {
            while (l_BucketIdx < s_MEM_BUCKET_COUNT) {
                s_MEM_BLOCK* l_Block = FindBlock(l_BucketIdx, i_MinSize);

                if (l_Block) {
                    return l_Block;
                }

                l_BucketIdx++;
            }
        }

        return NULL;
    } // Fully inlined

    void Extend();
    S32 s_GetInBucket(S32 i_BucketIdx, s_MEM_BLOCK* i_Block);
    s_MEM_BLOCK* FindBlock(S32 i_BucketIdx, S32 i_MinSize);
    void AddBlock(s_MEM_BLOCK* i_Block);
    void RemoveBlock(s_MEM_BLOCK* i_Block);
    s_MEM_BLOCK* FindBlock(S32 i_MinSize);
};

#endif
