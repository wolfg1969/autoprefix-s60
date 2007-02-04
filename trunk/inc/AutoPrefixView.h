/*
============================================================================
 Name        : AutoPrefixView.h
 Author      : Guo Yong
 Copyright   : GPL
 Description : Declares view class for application.
============================================================================
*/

#ifndef AUTOPREFIXVIEW_H
#define AUTOPREFIXVIEW_H

// INCLUDES
#include <aknview.h>
#include <eiklbo.h>

// FORWARD DECLARATIONS
class CAutoPrefixSettingList;
class CAutoPrefixSettingsData;

// CLASS DECLARATION

/**
*  CAutoPrefixView view class.
* 
*/
class CAutoPrefixView : public CAknView
    {
    public: 
    
    	/**
     	 * Function: 	NewL
     	 *
     	 * Discussion: 	Construct a CAutoPrefixView two phase construction, and
     	 * 			   	return a pointer to the created object.
     	 *
     	 * Param:      	CAutoPrefixSettingsData - the data which is being edited by the
     	 *								Settings list
     	 *
     	 * Returns:    	A pointer to the created instance of CAutoPrefixView
     	 */
		static CAutoPrefixView* NewL(CAutoPrefixSettingsData &aData);

    	/**
     	 * Function: 	NewLC
     	 *
     	 * Discussion: 	Construct a CAutoPrefixView two phase 
     	 * 			   	construction, and return a pointer to the created 
	 	 *				object. Pointer to object is left on the cleanup stack.
     	 *
     	 * Param:      	CAutoPrefixSettingsData - the data which is being edited
     	 *				by the	Settings list
     	 *
     	 * Returns:    	A pointer to the created instance of CAutoPrefixView
     	 * 				
     	 */
		static CAutoPrefixView* NewLC(CAutoPrefixSettingsData &aData);
        
        /**
        * From CAknView returns Uid of View
        * @return TUid uid of the view
        */
        TUid Id() const;

        /**
        * From MEikMenuObserver delegate commands from the menu
        * @param aCommand a command emitted by the menu 
        * @return void
        */
        void HandleCommandL(TInt aCommand);

        /**
        * From CAknView activate the view
        * @param aPrevViewId 
        * @param aCustomMessageId 
        * @param aCustomMessage 
        * @return void
        */
        void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
            const TDesC8& aCustomMessage);

        /**
        * From CAknView deactivate the view (free resources)
        * @return void
        */
        void DoDeactivate();

    private:
        /**
     	 * Function:  	CSettingListView
     	 *
     	 *  Discussion: 	Private first-stage non-leaving constructor.
     	 *
     	 * Param:		aData - the data to be editted within this view.
     	 */
		CAutoPrefixView(CAutoPrefixSettingsData &aData);


    	/**
     	 * Function:  	ConstructL
     	 *	
     	 * Discussion: 	Private second-stage constructor. Used for all
     	 *				construction that might result in a leave
     	 */
		void ConstructL();                
        
        /**
	 	 * HandleStatusPaneSizeChange()
	 	 * Called by framework when resource is changed.
	 	*/
		void HandleStatusPaneSizeChange ();

    private: // Data
        /**
	 	 * Often, the setting list would be the child control of some container.
	 	 * In this case, as only a single control is used, there is no container 
	 	 * class.
	 	 *
	 	 * This control is owned by the SettingListView and must be deleted in 
	 	 * the destructor.
	 	 */
		CAutoPrefixSettingList* iSettingList;
		
		/**
	 	 * the data which will be modified by the settings list.
	 	*/
		CAutoPrefixSettingsData& iSettingsData;        
};

#endif


