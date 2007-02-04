/*
============================================================================
 Name        : AutoPrefixEngine.h
 Author      : Guo Yong
 Version     :
 Copyright   : GPL
 Description : CAutoPrefixEngine declaration
============================================================================
*/

#ifndef AutoPrefixEngine_H
#define AutoPrefixEngine_H

#include <e32base.h>	// For CActive, link against: euser.lib
#include <etel.h>    // for ETEL APIs, link against: etel.lib
#include <etelmm.h>  // for RMobileCall, link against: etelmm.lib
//#include <etel3rdparty.h> // for TRegistrationStatus, link against: etel3rdparty.lib

// CONTANTS
const TInt KMaxMobileTelNumberSize = 100;

// FORWARD DECLARATIONS
class CAutoPrefixSettingsData;

class CAutoPrefixEngine : public CActive
{
public: // interface
	/**
	 *  The object which wants to receive timer event will implements 
	 *  this interface
	 */
	class MObserver
	{
	public:
		/*
  		 *  Called when timer request completed
		 *  @param aTime The current time
		 */
		 
		virtual void OnTelephoneEventL(TInt aError) = 0;
		virtual void OnHangUpCurrentCallL(const TDesC& aPhoneNumber, TInt aOldNumLen) = 0;
		//virtual void OnTelephoneNumberL(const TDesC& aDesC) = 0;
	};
public:

	static CAutoPrefixEngine* NewL(CAutoPrefixSettingsData& aData, MObserver& aObserver);
	
	static CAutoPrefixEngine* NewLC(CAutoPrefixSettingsData& aData, MObserver& aObserver);
	
	// Cancel and destroy
	~CAutoPrefixEngine();

public: // New functions
	void Start();

private: 
	// C++ constructor
	CAutoPrefixEngine(CAutoPrefixSettingsData& aData, MObserver& aObserver);
	
	// Second-phase constructor
	void ConstructL();
	
private: //from CActive
        /**
         *  Used to trigger timer event
         */
        void RunL();

        void DoCancel();

private:
	void GetCallingPhoneNumber();
	void MakeNewPhoneNumber();
	TBool NotInSkipList();
	TBool NotRoaming();

private:
	CAutoPrefixSettingsData& iSettingsData;
	MObserver& iObserver;
	
	TBuf<KMaxMobileTelNumberSize> iCallingPhoneNumber;
	TBuf<KMaxMobileTelNumberSize> iNewPhoneNumber;
	
    RTelServer iTelServer;
    RPhone iPhone;
    RLine iLine;
	//RCall iCall;
    RCall::TStatus iCallStatus;
    RMobileCall iCall;     
};

#endif
