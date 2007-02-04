/*
============================================================================
 Name        : AutoPrefixAppUi.cpp
 Author      : Guo Yong
 Copyright   : GPL
 Description : CAutoPrefixAppUi implementation
============================================================================
*/

// INCLUDE FILES
#include <AutoPrefix.rsg>
#include "AutoPrefixAppui.h"
#include "AutoPrefixView.h"
#include "AutoPrefix.hrh"
#include "AutoPrefixSettingList.h"
#include "AutoPrefixSettingsData.h"
#include "AutoPrefixEngine.h"

#include <avkon.hrh>
#include <aknutils.h> 
#include <S32FILE.H>
#include <f32file.h>
#include <EIKAPP.H>
#include <apgtask.h>
#include <w32std.h>
#include <aknnotewrappers.h>
#include <e32keys.h>

// Constants
_LIT (KSettingsFile, "AutoPrefix.dat");
_LIT (KEmulatorError, "Dialing is not currently supported by this emulator.");
_LIT (KPhoneWinName, "*phone?");
const TInt KOneSecond = 1000000;

// ================= MEMBER FUNCTIONS =======================
//
// ----------------------------------------------------------
// CAutoPrefixAppUi::ConstructL()
// 
// ----------------------------------------------------------
//
    
void CAutoPrefixAppUi::ConstructL()
    {
    // Enable skins
    BaseConstructL(EAknEnableSkin);
    
    TFileName appFullName = Application()->AppFullName();
    TParsePtr appPath(appFullName);
#ifdef __WINS__
    iSettingsFile = _L("c:");
    iSettingsFile.Append(appPath.Path());
    RFs& fsSession = iEikonEnv->FsSession();
    fsSession.MkDir(iSettingsFile);
#else
    iSettingsFile = appPath.DriveAndPath();
#endif // __WINS__
	iSettingsFile.Append(KSettingsFile);
	
	// construct the data object the settings list will use
	iData = CAutoPrefixSettingsData::NewL();
    InternalizeSettingsDataL();
	
    // construct the view as well.
	CAknView* view;
	view = CAutoPrefixView::NewLC(*iData);
	AddViewL(view);
	CleanupStack::Pop(view);
	ActivateLocalViewL(view->Id());
	
#ifdef __WINS__	
#else
	iEngine = CAutoPrefixEngine::NewL(*iData, *this);
#endif
    }
    
CAutoPrefixAppUi::CAutoPrefixAppUi()
	{
   	}
   	
CAutoPrefixAppUi::~CAutoPrefixAppUi()
	{
    delete iData;
#ifdef __WINS__	
#else
	delete iEngine;
#endif    
   	}

// public Functions from base classes
void CAutoPrefixAppUi::OnTelephoneEventL(TInt aError)
    {
    _LIT(KAutoPrefixPanic, "AutoPrefix");
    User::Panic(KAutoPrefixPanic, aError);
    }

   
void CAutoPrefixAppUi::OnHangUpCurrentCallL(const TDesC& aPhoneNumber, TInt aOldNumLen)
	{	
	//BringToForeground(); 	
	//DisplayInfo( aPhoneNumber ); 	
	
	RWsSession& sess = iEikonEnv->WsSession();
	
	// Find the id of the Phone app
	TInt id = sess.FindWindowGroupIdentifier(0, KPhoneWinName);
	
	if (id != KErrNotFound) 
		{
		//TBuf<20> windowName;
		//sess.GetWindowGroupNameFromIdentifier(id, windowName);
		//DisplayInfo( windowName );
		
		// Bring the Phone app to foreground
		TApaTask task = TApaTask(sess);
 		task.SetWgId(id);
 		task.BringToForeground(); 
 		
 		// Press clean key to clean old phone number
 		for (TInt i = 0; i < aOldNumLen; i++)
 			{
 			SimulateKeyEvent(sess, id, EKeyBackspace);	
 			}
		
		// Enter new phone number
		for (TInt j = 0; j < aPhoneNumber.Length(); j++)
			{
			SimulateKeyEvent(sess, id, (TInt)aPhoneNumber[j]);
			}
		// Press Green Button. Also can use EKeyPhoneSend defined in ukkon.hrh
		// Big issue here: dialling new number will cause app abort.		
		if (iData->AutoDial())
			{
			if (iData->Delay() > 0)
				{
				User::After(KOneSecond * iData->Delay());
				}
			SimulateKeyEvent(sess, id, EKeyYes);
			}
		}
	}
	
void CAutoPrefixAppUi::SimulateKeyEvent(RWsSession& aWsSession, TInt aId, TInt aKeyCode)
	{
	TKeyEvent key_event;
    key_event.iCode = aKeyCode;
    key_event.iModifiers = 0;
    key_event.iRepeats = 0;
    key_event.iScanCode = EStdKeyNull;
	
	TInt events[] = {EEventKeyDown, EEventKey, EEventKeyUp};
	
	for(int i = 0; i < 3; i++) 
		{
		TWsEvent ws_event;
		ws_event.SetType(events[i]);
		ws_event.SetHandle(0);
		*(ws_event.Key()) = key_event;
		ws_event.SetTimeNow();

		aWsSession.SendEventToWindowGroup(aId, ws_event);
        }
	User::ResetInactivityTime();
	}
    
// ----------------------------------------------------
// CAutoPrefixAppUi::HandleCommandL(TInt aCommand)
// takes care of command handling
// ----------------------------------------------------
//
void CAutoPrefixAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAutoPrefixCmdHide:
        	SendToBackground();
        	break;
        case EEikCmdExit:
		case EAknSoftkeyExit:	// only softkey handled at this level
            ExternalizeSettingsDataL();
            Exit();
            break;
        default:
            break;
        }
    }
    
void CAutoPrefixAppUi::DisplayInfo(const TDesC& aInfo)
	{
	CAknInformationNote* informationNote;
    informationNote = new ( ELeave ) CAknInformationNote;
    informationNote->ExecuteLD( aInfo );
	}
    
void CAutoPrefixAppUi::BringToForeground()
	{
	// Construct en empty TApaTask object
 	// giving it a reference to the Window Server session
 	TApaTask task(iEikonEnv->WsSession( ));
               
 	// Initialise the object with the window group id of
 	// our application (so that it represent our app)
 	task.SetWgId(CEikonEnv::Static()->RootWin().Identifier());

 	// Request window server to bring our application
 	// to foreground
 	task.BringToForeground(); 
	}
    
void CAutoPrefixAppUi::SendToBackground()
	{
	// Construct en empty TApaTask object
 	// giving it a reference to the Window Server session
 	TApaTask task(iEikonEnv->WsSession( ));
               
 	// Initialise the object with the window group id of
 	// our application (so that it represent our app)
 	task.SetWgId(CEikonEnv::Static()->RootWin().Identifier());

 	// Request window server to bring our application
 	// to foreground
 	task.SendToBackground(); 
	}
	
/*
void CAutoPrefixAppUi::DialNumberL(const TDesC& aPhoneNumber)
	{
	//Create a connection to the tel server
	RTelServer server;
	CleanupClosePushL(server);
	User::LeaveIfError(server.Connect());

	//Load in the phone device driver
	TFileName TsyName;
    // Read the TSY module name 
    User::LeaveIfError(server.GetTsyName(0, TsyName));
	
	//Find the number of phones available from the tel server
	TInt numberPhones;
	User::LeaveIfError(server.EnumeratePhones(numberPhones));

	//Check there are available phones
	if (numberPhones < 1)
		{
		User::Leave(KErrNotFound);
		}

	//Get info about the first available phone
	RTelServer::TPhoneInfo info;
	User::LeaveIfError(server.GetPhoneInfo(0, info));

	//Use this info to open a connection to the phone, the phone is identified by its name
	RPhone phone;
	CleanupClosePushL(phone);
	User::LeaveIfError(phone.Open(server, info.iName));

	//Get info about the first line from the phone
	RPhone::TLineInfo lineInfo;
	User::LeaveIfError(phone.GetLineInfo(0, lineInfo));

	//Use this to open a line
	RLine line;
	CleanupClosePushL(line);
	User::LeaveIfError(line.Open(phone, lineInfo.iName));

	//Open a new call on this line
	TBuf <100> newCallName;
	RCall call;
	CleanupClosePushL(call);
	User::LeaveIfError(call.OpenNewCall(line, newCallName));

	//newCallName will now contain the name of the call
	User::LeaveIfError(call.Dial(aPhoneNumber));

	//Close the phone, line and call connections and remove them from the cleanup stack
	//NOTE: This does not hang up the call
	CleanupStack::PopAndDestroy(3);//phone, line, call

	//Unload the phone device driver
	User::LeaveIfError(server.UnloadPhoneModule(TsyName));

	//Close the connection to the tel server and remove it from the cleanup stack
	CleanupStack::PopAndDestroy(&server);
	}
*/

void CAutoPrefixAppUi::InternalizeSettingsDataL()
    {
    RFs& fs = iEikonEnv->FsSession();
    RFileReadStream readStream;
    TInt error = readStream.Open(fs, iSettingsFile, EFileRead);
    TInt internalizationError = KErrNone;
    // if file existed, try to read settings.
    if (error == KErrNone)
        {
        TRAP(internalizationError, iData->LoadL(readStream);)
        }
    readStream.Release();

    // reading failed, settings file might be corrupted.    
    if (internalizationError != KErrNone)
        {
        User::LeaveIfError(fs.Delete(iSettingsFile));
        }
    }


void CAutoPrefixAppUi::ExternalizeSettingsDataL() const
    {
    RFs& fs = iEikonEnv->FsSession();
    RFileWriteStream writeStream;
    TInt error = writeStream.Open(fs, iSettingsFile, EFileWrite);
    // setting file did not exist, create one.
    if (error != KErrNone)
        {
        User::LeaveIfError(writeStream.Create(fs, iSettingsFile, EFileWrite));
        }
    writeStream.PushL();
    iData->SaveL(writeStream);
    writeStream.CommitL();
    writeStream.Pop();
    writeStream.Release();
    }  

  
