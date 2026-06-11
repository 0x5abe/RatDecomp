#ifndef _GCMCMANAGER_Z_H_
#define _GCMCMANAGER_Z_H_
#include "SaveGame_Z.h"
#include "BaseStream_Z.h"
#include <card.h>

enum GC_MC_STATE {
    GC_MC_STATE_NONE = 0,
    GC_MC_STATE_RUNNING = 1,
    GC_MC_STATE_FINISHED = 2
};

enum GC_MC_CMD {
    GC_MC_CMD_NONE = 0,
    GC_MC_CMD_LOAD_ASYNC = 1,
    GC_MC_CMD_FORMAT_ASYNC = 2,
    GC_MC_CMD_DELETE_ASYNC = 3,
    GC_MC_CMD_FINISHED = 4
};

typedef enum GC_ICONANIM_PLAYBACKRATE {
    GC_ICONANIM_PLAYBACKRATE_FAST = 1,
    GC_ICONANIM_PLAYBACKRATE_MED = 2,
    GC_ICONANIM_PLAYBACKRATE_SLOW = 3
} GC_ICONANIM_PLAYBACKRATE;

class McFiles_Z : public BaseStream_Z {
public:
    McFiles_Z() { }

    virtual void Opened(S32 i_ErrorCode, S32 i_FileSize, S32 i_UserDefined);
    virtual void Readed(S32 i_ErrorCode, S32 i_NbBytesRead, S32 i_UserDefined);

private:
    U8 m_Unk_0x8[12];
};

struct UnkSaveRelatedStruct {
    U8 m_UnkFlag_0x0;
    U8 m_Unk_0x1;
    U8 m_Unk_0x2;
    U8 m_Unk_0x3;
};

struct IconEntry {
    U32 m_BitmapType;
    GC_ICONANIM_PLAYBACKRATE m_Rate;
    Char* m_FileName;
};

class GCMcManager_Z : public SaveGame_Z {
public:
    GCMcManager_Z();
    virtual ~GCMcManager_Z();
    virtual Bool Init();
    virtual void Shut();
    virtual void SetGameName(Char* a1);
    virtual void SetCountry(MCCOUNTRY a1);
    virtual void SetProductNumber(Char* a1);
    virtual void SetTitleName(Char* a1);
    virtual void SetFileComment(Char* a1);
    virtual void SaveFile(Char* a1, void* a2, S32 a3);
    virtual void SaveFileA(Char* a1, void* a2, S32 a3);
    virtual void LoadFile(Char* a1, void* a2, S32 a3);
    virtual void LoadFileA(Char* a1, void* a2, S32 a3);
    virtual void DelFile(Char* a1);
    virtual void DelFileA(Char* a1);
    virtual void RefreshCards();
    virtual void RefreshCard();
    virtual void GetCardStatus();
    virtual void GetCardFreeSpace();
    virtual void CalculateSpaceNeeded(S32 a1, S32* a2);
    virtual void CalculateSpaceNeededForOneFile(S32 a1);
    virtual void QueryFile(Char* a1);
    virtual void QueryFileDateAndSize(Char* a1, SaveDate_Z* a2, S32* a3);
    virtual void GetDirectory(FileInfo_Z* a1, S32 a2);
    virtual void GetActualFileSize(S32 a1);
    virtual void CardSync(S32& a1, S32& a2);
    virtual void FormatCard();
    virtual void FormatCardA();
    virtual void CreateDirectoryA();
    virtual void UnFormatCard();
    virtual void IsNewCardConnected();
    virtual void SetPortAndSlot(int a1, int a2);
    virtual void ResetManageMC();
    virtual void Update(Float a1);
    virtual void RegisterAgentAndMessage(ABC_Agent* a1, int a2);

    S32 GetIsBusy() const { return m_IsBusy; }

private:
    Char m_GameName[32];
    Char m_ProductNumber[32];
    Char m_FileComment[32];
    MCCOUNTRY m_Localization;
    void* m_MountWorkBuffer;
    U32 m_SectorSize;
    S32 m_BytesFree;
    S32 m_FileSlotsFree;
    U32 m_UseSlot;
    U8 m_UnkBytes_0x80[32];
    Char* m_ReadBuffer;
    void* m_DataToSave;
    void* m_BannerData;
    S32 m_DataToSaveSize;
    U8 m_DataToSaveFileName[32];
    CARDFileInfo m_CardFileInfo;
    CARDStat m_CardStat;
    U32 m_ErrorNum;
    GC_MC_STATE m_State;
    U32 m_Unk_0x158;
    GC_MC_CMD m_CommandToRun;
    S32 m_IsBusy;
    U32 m_ReadBufferSize;
    U32 m_Unk_0x168;
    UnkSaveRelatedStruct m_UnkInfo;
    U32 m_Unk_0x170;
    U32 m_BannerDataSize;
    U32 m_Unk_0x178;
    U32 m_Unk_0x17c;
    U32 m_Unk_0x180;
    U32 m_IconCount;
    IconEntry m_IconData[8];
    Char m_Comment[64];
    U32 m_IconAnimPlaybackType;
    U32 m_Unk_0x22c;
    McFiles_Z m_McFiles[2];
    Bool m_Access;
};

#endif // _GCMCMANAGER_Z_H_
