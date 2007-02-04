/*
============================================================================
 Name        : AutoPrefixSettingsData.h
 Author      : Guo Yong
 Version     :
 Copyright   : GPL
 Description : CAutoPrefixSettingsData declaration
============================================================================
*/

#ifndef AutoPrefixSettingsData_H
#define AutoPrefixSettingsData_H

// INCLUDES
#include <e32base.h>

// size for data descriptors
const TInt KPrefixNumLen = 6;
const TInt KAreaCodeLen = 4;
const TInt KIgnoreListLen = 100;

// Forward declarations
class RReadStream;
class RWriteStream;

// CLASS DECLARATION

/**
*  CCAutoPrefixSettingsData
* 
*/
class CAutoPrefixSettingsData : public CBase
{
public: // Constructors and destructor

	/**
    * Destructor.
    */
	~CAutoPrefixSettingsData();

    /**
    * Two-phased constructor.
    */
	static CAutoPrefixSettingsData* NewL();

    /**
    * Two-phased constructor.
    */
	static CAutoPrefixSettingsData* NewLC();
	
	/**
    * Function:    LoadL
    * 
    * Discussion:  Loads itself from stream.
    * 
    */
    void LoadL(RReadStream& aStream);
    
    /**
    * Function:     SaveL
    * 
    * Discussion:   Saves itself to stream.
    * 
    */
	void SaveL(RWriteStream& aStream) const;
	
	/**
 	* Function: 	Enable
	*
 	* Discussion:	Trivial accessor function
	*
 	* Returns:		A reference to the iEnable member
	*/
	inline TBool& Enable() { return iEnable; }
	
	/**
 	* Function: 	PrefixNumber
	*
 	* Discussion:	Trivial accessor function
	*
 	* Returns:		A reference to the iPrefixNumber member
	*/
	inline TBuf<KPrefixNumLen>& PrefixNumber() { return iPrefixNumber; }
	
	inline TBuf<KAreaCodeLen>& AreaCode() { return iAreaCode; }
	
	inline TBuf<KIgnoreListLen>& IgnoreList() { return iIgnoreList; }
	
	inline TBool& AutoDial() { return iAutoDial; }
	
	inline TInt& Delay() { return iDelay; }

private:

	/**
    * Constructor for performing 1st stage construction
    */
	CAutoPrefixSettingsData();

	/**
    * EPOC default constructor for performing 2nd stage construction
    */
	void ConstructL();
	
public:
	TBool iEnable;							/* Data for enable field          */
	TBuf<KPrefixNumLen> iPrefixNumber;			/* Data for prefix number field   */
	TBuf<KAreaCodeLen> iAreaCode;
	TBuf<KIgnoreListLen> iIgnoreList;
	TBool iAutoDial;
	TInt iDelay;
};

#endif // AutoPrefixSettingsData_H
