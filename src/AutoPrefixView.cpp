/*
============================================================================
 Name        : AutoPrefixView.cpp
 Author      : Guo Yong
 Copyright   : GPL
 Description : CAutoPrefixView implementation
============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>
#include <barsread.h>
#include <AutoPrefix.rsg>
#include "AutoPrefix.hrh"
#include "AutoPrefixView.h"
#include "AutoPrefixAppUi.h"
#include "AutoPrefixSettingList.h"

// UID of view
const TUid KViewId = {1};

// ================= MEMBER FUNCTIONS =======================

// factory constructor leaving instance on cleanup
CAutoPrefixView* CAutoPrefixView::NewLC(CAutoPrefixSettingsData &aData)
	{
	CAutoPrefixView* self = new (ELeave) CAutoPrefixView(aData);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// factory constructor - no instance left on cleanup
CAutoPrefixView* CAutoPrefixView::NewL(CAutoPrefixSettingsData &aData)
	{
	CAutoPrefixView* self = CAutoPrefixView::NewLC(aData);
	CleanupStack::Pop(self);
	return self;
	}

// second phase constructor
void CAutoPrefixView::ConstructL()
	{
	// construct from resource
	BaseConstructL(R_FIRSTVIEW);
	}

// first phase (non-leaving) constructor
CAutoPrefixView::CAutoPrefixView(CAutoPrefixSettingsData &aData)
: CAknView(), iSettingsData(aData)
	{
	}

// activation of view
void CAutoPrefixView::DoActivateL(const TVwsViewId& /*aPrevViewId*/, 
										 TUid /*aCustomMessageId*/, 
								   const TDesC8& /*aCustomMessage*/)
	{
	if(!iSettingList)	// if we haven't already created iSettingList
		{
		// construct control and set parent
		iSettingList = CAutoPrefixSettingList::NewL(iSettingsData);
		iSettingList->SetMopParent(this);		

		// construct control based on resource definition
		TResourceReader reader;

		// CreateResourceReaderLC will allocate a buffer to be used by
		// the TResourceReader. This buffer is pushed onto the cleanup
		// stack - not the TResourceReader itself
		CEikonEnv::Static()->CreateResourceReaderLC(reader, R_SETTINGS);
		iSettingList->ConstructFromResourceL(reader);

		// Clean up the buffer allocated above, NOT the reader itself.
		// Cannot use expected item overload of PopAndDestroy() as buffer 
		// is inaccessible. 
		CleanupStack::PopAndDestroy();	

		// register view and activate
		AppUi()->AddToViewStackL(*this, iSettingList);
		iSettingList->ActivateL();
		}
	}

// deactivation of view
void CAutoPrefixView::DoDeactivate()
	{
	if(iSettingList)	// if setting list has been created
		{
		// remove setting list from stack
		AppUi()->RemoveFromViewStack(*this, iSettingList);

		// clean up 
		delete iSettingList;
		iSettingList = NULL;
		}
	}

TUid CAutoPrefixView::Id() const
	{
	return KViewId;
	}

void CAutoPrefixView::HandleCommandL(TInt aCommand)
    {
	switch(aCommand)
		{
	/*case ESettingCmdEdit :					// edit current item
		iSettingList->EditCurrentItemL();
		break;*/
	default :								// anything else
		AppUi()->HandleCommandL(aCommand);	// handled by AppUi
		break;
		}
	}
	
// ---------------------------------------------------------
// CSettingListView::HandleResourceChange()
// Called by framework when resource is changed.
// ------
void CAutoPrefixView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange(); //call to upper class
	iSettingList->SetRect(ClientRect());
	}



