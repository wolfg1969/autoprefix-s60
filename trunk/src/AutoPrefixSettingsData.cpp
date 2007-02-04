/*
============================================================================
 Name        : AutoPrefixSettingsData.cpp
 Author      : Guo Yong
 Version     :
 Copyright   : GPL
 Description : CAutoPrefixSettingsData implementation
============================================================================
*/

#include "AutoPrefixSettingsData.h"
#include <S32STRM.H> // Streams

// Constants
_LIT(KDefaultPrefixNumber, "12593");
_LIT(KDefaultAreaCode, "010");
//_LIT(KDefaultIgnoreList, "1??\n119\n10086\n13800138000*\n800*\n1258*\n1259*\n179*\n00*");

CAutoPrefixSettingsData::CAutoPrefixSettingsData():
	iEnable(EFalse),
	iPrefixNumber(KDefaultPrefixNumber),
	iAreaCode(KDefaultAreaCode),
	//iIgnoreList(KDefaultIgnoreList),
	iAutoDial(EFalse),
	iDelay(1)
{
}


CAutoPrefixSettingsData::~CAutoPrefixSettingsData()
{
}

CAutoPrefixSettingsData* CAutoPrefixSettingsData::NewLC()
{
	CAutoPrefixSettingsData* self = new (ELeave)CAutoPrefixSettingsData();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

CAutoPrefixSettingsData* CAutoPrefixSettingsData::NewL()
{
	CAutoPrefixSettingsData* self=CAutoPrefixSettingsData::NewLC();
	CleanupStack::Pop(); // self;
	return self;
}

void CAutoPrefixSettingsData::ConstructL()
{

}

void CAutoPrefixSettingsData::LoadL(RReadStream& aStream)
{
    iEnable = aStream.ReadInt16L();
    aStream >> iPrefixNumber;
    aStream >> iAreaCode;
    //aStream >> iIgnoreList;
    iAutoDial = aStream.ReadInt16L();
    iDelay = aStream.ReadInt16L();
}
    
void CAutoPrefixSettingsData::SaveL(RWriteStream& aStream) const
{
    aStream.WriteInt16L(iEnable);
    aStream << iPrefixNumber;
    aStream << iAreaCode;
    //aStream << iIgnoreList;
    aStream.WriteInt16L(iAutoDial);
    aStream.WriteInt16L(iDelay);
}
