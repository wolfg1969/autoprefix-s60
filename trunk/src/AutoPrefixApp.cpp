/*
============================================================================
 Name        : AutoPrefixApp.cpp
 Author      : Guo Yong
 Copyright   : GPL
 Description : Main application class
============================================================================
*/

// INCLUDE FILES
#include    "AutoPrefixApp.h"
#include    "AutoPrefixDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAutoPrefixApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CAutoPrefixApp::AppDllUid() const
    {
    return KUidAutoPrefix;
    }

   
// ---------------------------------------------------------
// CAutoPrefixApp::CreateDocumentL()
// Creates CAutoPrefixDocument object
// ---------------------------------------------------------
//
CApaDocument* CAutoPrefixApp::CreateDocumentL()
    {
    return CAutoPrefixDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CAutoPrefixApp
// Returns: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAutoPrefixApp;
    }

// ---------------------------------------------------------
// E32Dll(TDllReason) 
// Entry point function for EPOC Apps
// Returns: KErrNone: No error
// ---------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
    {
    return KErrNone;
    }

  

