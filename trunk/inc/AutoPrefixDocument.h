/*
============================================================================
 Name        : AutoPrefixDocument.h
 Author      : Guo Yong
 Copyright   : GPL
 Description : Declares document class for application.
============================================================================
*/

#ifndef AUTOPREFIXDOCUMENT_H
#define AUTOPREFIXDOCUMENT_H

// INCLUDES
#include <akndoc.h>

// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CAutoPrefixDocument application class.
*/
class CAutoPrefixDocument : public CAknDocument
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        */
        static CAutoPrefixDocument* NewL(CEikApplication& aApp);

        /**
        * Destructor.
        */
        virtual ~CAutoPrefixDocument();

    public: // New functions

    public: // Functions from base classes
    protected:  // New functions

    protected:  // Functions from base classes

    private:

        /**
        * EPOC default constructor.
        */
        CAutoPrefixDocument(CEikApplication& aApp);
        void ConstructL();

    private:

        /**
        * From CEikDocument, create CAutoPrefixAppUi "App UI" object.
        */
        CEikAppUi* CreateAppUiL();
    };

#endif



