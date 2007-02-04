/*
============================================================================
 Name        : AutoPrefixSettingList.cpp
 Author      : Guo Yong
 Version     :
 Copyright   : GPL
 Description : CAutoPrefixSettingList implementation
============================================================================
*/

#include <barsread.h>
#include <AutoPrefix.rsg>
#include "AutoPrefix.hrh"
#include "AutoPrefixSettingsData.h"
#include "AutoPrefixSettingList.h"

CAutoPrefixSettingList::CAutoPrefixSettingList(CAutoPrefixSettingsData &aData):
	CAknSettingItemList(),
	iSettingsData(aData)
{
	// No implementation required
}


CAutoPrefixSettingList::~CAutoPrefixSettingList()
{
}

CAutoPrefixSettingList* CAutoPrefixSettingList::NewLC(CAutoPrefixSettingsData &aData)
{
	CAutoPrefixSettingList* self = new (ELeave)CAutoPrefixSettingList(aData);
	CleanupStack::PushL(self);
	return self;
}

CAutoPrefixSettingList* CAutoPrefixSettingList::NewL(CAutoPrefixSettingsData &aData)
{
	CAutoPrefixSettingList* self=CAutoPrefixSettingList::NewLC(aData);
	CleanupStack::Pop(); // self;
	return self;
}

void CAutoPrefixSettingList::SizeChanged()
    {
	// if size changes, make sure component takes whole available space
	CEikFormattedCellListBox *listbox = ListBox();

    if (listbox) 
        {
        listbox->SetRect(Rect());
        }
    }

void CAutoPrefixSettingList::HandleListBoxEventL(CEikListBox* /*aListBox*/, TListBoxEvent aEventType)
	{
	if(aEventType == EEventEnterKeyPressed)
		{
		EditCurrentItemL();
		}
	}
	

void CAutoPrefixSettingList::EditCurrentItemL()
	{
	// invoke EditItemL on the current item
	EditItemL(ListBox()->CurrentItemIndex(),	// the item index
			  ETrue);							// invoked from menu
			  
	StoreSettingsL();
	}

CAknSettingItem * CAutoPrefixSettingList::CreateSettingItemL (TInt aIdentifier) 
	{
	// method is used to create specific setting item as required at run-time.
	// aIdentifier is used to determine what kind of setting item should be 
	// created
	CAknSettingItem* settingItem = NULL;

    switch (aIdentifier)
		{
		case ESettingEnable:
			settingItem = new (ELeave) CAknBinaryPopupSettingItem (
											aIdentifier, 
											iSettingsData.Enable());
			break;
		case ESettingPrefixNumber:
			settingItem = new (ELeave) CAknTextSettingItem (
											aIdentifier, 
							 				iSettingsData.PrefixNumber());
			break;
		case ESettingAreaCode:
			settingItem = new (ELeave) CAknTextSettingItem (
											aIdentifier, 
							 				iSettingsData.AreaCode());
			break;
		case ESettingIgnoreList:
			settingItem = new (ELeave) CAknTextSettingItem (
											aIdentifier, 
							 				iSettingsData.IgnoreList());
			break;
		case ESettingAutoDial:
			settingItem = new (ELeave) CAknBinaryPopupSettingItem (
											aIdentifier, 
											iSettingsData.AutoDial());
			break;
		case ESettingDelay:
			settingItem = new (ELeave) CAknBinaryPopupSettingItem (
											aIdentifier, 
											iSettingsData.Delay());
			break;		
		default:
			break;
        }
        
    return settingItem;
	}
