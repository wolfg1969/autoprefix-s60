/*
============================================================================
 Name        : AutoPrefixApp.h
 Author      : Guo Yong
 Copyright   : GPL
 Description : Declares main application class.
============================================================================
*/

#ifndef AUTOPREFIXAPP_H
#define AUTOPREFIXAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// UID of the application
const TUid KUidAutoPrefix = { 0x200097D2 };

// CLASS DECLARATION

/**
* CAutoPrefixApp application class.
* Provides factory to create concrete document object.
* 
*/
class CAutoPrefixApp : public CAknApplication
    {
    
    public: // Functions from base classes
    private:

        /**
        * From CApaApplication, creates CAutoPrefixDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
        
        /**
        * From CApaApplication, returns application's UID (KUidAutoPrefix).
        * @return The value of KUidAutoPrefix.
        */
        TUid AppDllUid() const;
    };

#endif



