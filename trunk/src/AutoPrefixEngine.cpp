/*
============================================================================
 Name        : AutoPrefixEngine.cpp
 Author      : Guo Yong
 Version     :
 Copyright   : GPL
 Description : CAutoPrefixEngine implementation
============================================================================
*/

// INCLUDES
#include "AutoPrefixEngine.h"
#include "AutoPrefixSettingsData.h"

// public standard construction sequence
CAutoPrefixEngine* CAutoPrefixEngine::NewL(CAutoPrefixSettingsData& aData, MObserver& aObserver)
    {
    CAutoPrefixEngine* self = CAutoPrefixEngine::NewLC(aData, aObserver);
    CleanupStack::Pop();
    return self;
    }
    
CAutoPrefixEngine* CAutoPrefixEngine::NewLC(CAutoPrefixSettingsData& aData, MObserver& aObserver)
    {
    CAutoPrefixEngine* self = new (ELeave) CAutoPrefixEngine(aData, aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CAutoPrefixEngine::~CAutoPrefixEngine()
    {
    iTelServer.Close();
    iPhone.Close();
    iLine.Close();
    iCall.Close();
    }
    
// public new functions
   
// private standard construction sequence
CAutoPrefixEngine::CAutoPrefixEngine(CAutoPrefixSettingsData& aData, MObserver& aObserver): 
	CActive(EPriorityStandard), // Standard priority
	iSettingsData(aData),
	iObserver(aObserver)
    {
    // No implementation required
    }

void CAutoPrefixEngine::ConstructL()
    {
    CActiveScheduler::Add(this);

    TInt err = iTelServer.Connect();
    if(err!=KErrNone)
        {
        iObserver.OnTelephoneEventL(1);
        }

    // Find the number of phones available from the tel server 
    TInt numberPhones; 
    err = iTelServer.EnumeratePhones(numberPhones); 
    if(err!=KErrNone)
        {
        iObserver.OnTelephoneEventL(2);
        }

    TFileName name;
    // Read the TSY module name 
    err = iTelServer.GetTsyName(0, name); 
    if(err!=KErrNone)
        {
        iObserver.OnTelephoneEventL(3);
        }

    // Load in the phone device driver 
    err = iTelServer.LoadPhoneModule(name); 
    if(err!=KErrNone)
        {
        iObserver.OnTelephoneEventL(4);
        }

    // Get info about the first available phone 
    RTelServer::TPhoneInfo info;
    err = iTelServer.GetPhoneInfo(0, info); 
    if(err!=KErrNone)
        {
        iObserver.OnTelephoneEventL(5);
        }

    // Use this info to open a connection to the phone, the phone is identified by its name 
    err = iPhone.Open(iTelServer, info.iName); 
    if(err!=KErrNone)
        {
        iObserver.OnTelephoneEventL(6);
        }

    RPhone::TLineInfo lineInfo; 
    err = iPhone.GetLineInfo(0, lineInfo); 
    if(err!=KErrNone)
        {
        iObserver.OnTelephoneEventL(7);
        }

    err = iLine.Open(iPhone, lineInfo.iName); 
    if(err!=KErrNone)
        {
        iObserver.OnTelephoneEventL(8);
        }

    Start();
    }
    
void CAutoPrefixEngine::Start()
    {
    Cancel();
    iLine.NotifyStatusChange(iStatus, iCallStatus);
    SetActive();
    }

// private from CTimer
void CAutoPrefixEngine::RunL()
    {
    TInt err = iStatus.Int();
    if(err!=KErrNone) 
        {
        iObserver.OnTelephoneEventL(10);
        return;
        }

    switch(iCallStatus)
        {
        case RCall::EStatusHangingUp:
        case RCall::EStatusIdle:
        case RCall::EStatusUnknown:   
            {
            iCall.Close();            
            break;
            } 
        case RCall::EStatusDialling:
            {			
            if (iSettingsData.Enable() && NotRoaming()) 
            	{
            	GetCallingPhoneNumber();
            	TInt len = iCallingPhoneNumber.Length();
            	
            	if (NotInSkipList())
            		{            	
            			TBuf<KPrefixNumLen> prefixNumber;
            			prefixNumber.Copy(iSettingsData.PrefixNumber());
            			prefixNumber.Append(_L("*"));
            	
            			if (iCallingPhoneNumber.Match(prefixNumber) == KErrNotFound)
            				{
            				MakeNewPhoneNumber(); 
            				iCall.HangUp();           		 
            				iObserver.OnHangUpCurrentCallL(iNewPhoneNumber, len);            		              		          		 		           		
            				}
            		}
            	}
            break;
            }
        }

    Start();

    }

void CAutoPrefixEngine::DoCancel()
    {
    iLine.NotifyStatusChangeCancel();
    iCall.Close();
    }
    
// private methods
void CAutoPrefixEngine::GetCallingPhoneNumber()
	{
	RLine::TLineInfo lineInfo; 
	iLine.GetInfo(lineInfo); 
	TInt err = iCall.OpenExistingCall(iLine, lineInfo.iNameOfLastCallAdded); 
	if(err!=KErrNone)
		{
		iObserver.OnTelephoneEventL(11);
		}
	RMobileCall::TMobileCallInfoV1 remotePartyInfo; 
	TPckg<RMobileCall::TMobileCallInfoV1> des(remotePartyInfo);
	iCall.GetMobileCallInfo(des);
	remotePartyInfo = des(); 
	iCallingPhoneNumber.Copy( remotePartyInfo.iDialledParty.iTelNumber );
	}

// need to refactor
TBool CAutoPrefixEngine::NotInSkipList()
	{
	if (iCallingPhoneNumber.Match(_L("1??")) == KErrNotFound &&
		   iCallingPhoneNumber.Match(_L("10086")) == KErrNotFound &&
		   iCallingPhoneNumber.Match(_L("13800138000*")) == KErrNotFound &&
		   iCallingPhoneNumber.Match(_L("800*")) == KErrNotFound &&
		   iCallingPhoneNumber.Match(_L("1258*")) == KErrNotFound &&
		   iCallingPhoneNumber.Match(_L("1259*")) == KErrNotFound &&
		   iCallingPhoneNumber.Match(_L("179*")) == KErrNotFound &&
		   iCallingPhoneNumber.Match(_L("00*")) == KErrNotFound)
		   
		{
		return ETrue;
		}
	else
		{
		return EFalse;
		}
	}
	
// TODO: get roaming status using CTelephony
TBool CAutoPrefixEngine::NotRoaming()
	{
	return ETrue;
	}
void CAutoPrefixEngine::MakeNewPhoneNumber()
	{
	iNewPhoneNumber.Copy(iSettingsData.PrefixNumber());            		
	if (iCallingPhoneNumber.Match(_L("0*")) == KErrNotFound)
		{ 
		if (iCallingPhoneNumber.Match(_L("13*")) == KErrNotFound &&
			iCallingPhoneNumber.Match(_L("15*")) == KErrNotFound) 
			{
			// local number, need to add area code
			iNewPhoneNumber.Append(iSettingsData.AreaCode());
			}
		}
	iNewPhoneNumber.Append(iCallingPhoneNumber);
	}

