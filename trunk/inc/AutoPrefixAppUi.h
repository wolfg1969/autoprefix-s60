/*
============================================================================
 Name        : AutoPrefixAppUi.h
 Author      : Guo Yong
 Copyright   : GPL
 Description : Declares UI class for application.
============================================================================
*/

#ifndef AUTOPREFIXAPPUI_H
#define AUTOPREFIXAPPUI_H

// INCLUDES
#include <aknviewappui.h>
#include <aknnavi.h>
#include "AutoPrefixEngine.h"

// FORWARD DECLARATIONS
class CAutoPrefixSettingsData;


// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following features:
* - EIKON control architecture
* - view architecture
* - status pane
* 
*/
class CAutoPrefixAppUi : public CAknViewAppUi, public CAutoPrefixEngine::MObserver
    {
    public: // // Constructors and destructor

        /**
        * EPOC default constructor.
        */      
        void ConstructL();
        
        /**
         * Constructor.
         */
        
        CAutoPrefixAppUi();

        /**
        * Destructor.
        */      
        ~CAutoPrefixAppUi();
        
    public: 
    	void HandleCommandL(TInt aCommand); 
    	
    public: // Functions from base classes
        void OnTelephoneEventL(TInt aError); 
        void OnHangUpCurrentCallL(const TDesC& aPhoneNumber, TInt aOldNumLen);  	
	
    private:
        void InternalizeSettingsDataL();
    	void ExternalizeSettingsDataL() const;
    	
    	void BringToForeground();
    	void SendToBackground();
    	
    	void SimulateKeyEvent(RWsSession& aWsSession, TInt aId, TInt aKeyCode);
    	
    	void DisplayInfo(const TDesC& aInfo);
    	
    	//void DialNumberL(const TDesC& aPhoneNumber);

    private: //Data
    	CAutoPrefixSettingsData* iData;	/* Pointer to settings data - OWNED */
    	CAutoPrefixEngine* iEngine;
    	TFileName iSettingsFile;        
    };

#endif


