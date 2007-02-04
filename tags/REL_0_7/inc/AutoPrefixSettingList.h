/*
============================================================================
 Name        : AutoPrefixSettingList.h
 Author      : Guo Yong
 Version     :
 Copyright   : GPL
 Description : CAutoPrefixSettingList declaration
============================================================================
*/

#ifndef AutoPrefixSettingList_H
#define AutoPrefixSettingList_H

// INCLUDES
#include <coecntrl.h>
#include <aknsettingitemlist.h> 

#include "AutoPrefixView.h"

class CAutoPrefixSettingsData;

// CLASS DECLARATION

/**
*  CAutoPrefixSettingList
* 
*/
class CAutoPrefixSettingList : public CAknSettingItemList
{
public: // Constructors and destructor

	/**
        * Destructor.
        */
	~CAutoPrefixSettingList();

        /**
        * Two-phased constructor.
        */
	static CAutoPrefixSettingList* NewL(CAutoPrefixSettingsData &aData);

        /**
        * Two-phased constructor.
        */
	static CAutoPrefixSettingList* NewLC(CAutoPrefixSettingsData &aData);
	
	/**
	* Function:		SizeChanged
	*
	* Discussion: 	Inherited from CCoeControl. Calculates size based on
	*				contained control required sizes.
	*
	*/
	void SizeChanged();

	/**
	 * Function:	EditCurrentItemL
	 *
	 * Discussion:	Starts the setting page for the currently selected item 
	 *				in the list.
	 */
	void EditCurrentItemL();
	
private:

	/**
        * Constructor for performing 1st stage construction
        */
	CAutoPrefixSettingList(CAutoPrefixSettingsData &aData);

		/**
	* Function:		CreateSettingItemL
	*
	* Discussion: 	Factory function for creating CAknSettingItem derived
	*				SettingItem classes used t display current values
	*
	* Params:		aSettingId - the id of the control which should be created
	*
	*/
	CAknSettingItem* CreateSettingItemL (TInt aSettingId);
	
	
	void HandleListBoxEventL(CEikListBox* /*aListBox*/, TListBoxEvent aEventType);

private:
	CAutoPrefixSettingsData &iSettingsData;

};

#endif // AutoPrefixSettingList_H
