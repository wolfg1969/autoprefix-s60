/*
============================================================================
 Name        : AutoPrefixDocument.cpp
 Author      : Guo Yong
 Copyright   : GPL
 Description : CAutoPrefixDocument implementation
============================================================================
*/

// INCLUDE FILES
#include "AutoPrefixDocument.h"
#include "AutoPrefixAppui.h"

// ================= MEMBER FUNCTIONS =======================

// constructor
CAutoPrefixDocument::CAutoPrefixDocument(CEikApplication& aApp)
: CAknDocument(aApp)    
    {
    }

// destructor
CAutoPrefixDocument::~CAutoPrefixDocument()
    {
    }

// EPOC default constructor can leave.
void CAutoPrefixDocument::ConstructL()
    {
    }

// Two-phased constructor.
CAutoPrefixDocument* CAutoPrefixDocument::NewL(
        CEikApplication& aApp)     // CAutoPrefixApp reference
    {
    CAutoPrefixDocument* self = new (ELeave) CAutoPrefixDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }
    
// ----------------------------------------------------
// CAutoPrefixDocument::CreateAppUiL()
// constructs CAutoPrefixAppUi
// ----------------------------------------------------
//
CEikAppUi* CAutoPrefixDocument::CreateAppUiL()
    {
    return new (ELeave) CAutoPrefixAppUi;
    }
  
