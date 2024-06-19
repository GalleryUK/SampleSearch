#include "SampleSearch.h"#include "Globals.h"#define kAEFinderEvents	'FNDR'#define kAEOpenSelection	'sope'#define keySelection	'fsel'#include "undoStuff.h"void saveForUndo (void);extern OSType  myeventFileType;    //	'APPL'extern OSType  myeventCreatorType;   //'WILD'extern unsigned long myEventID;	//kAEOpenDocumentsextern unsigned long myEventClass;  //kCoreEventClass						extern Boolean DialogPresent;extern Boolean divertIt;void LaunchAnApplication (FSSpec	mySpec); #define SFSaveDisk 	0x00000214#define CurDirStore 0x00000398extern Boolean isSample;OSErr ShowSelection(FSSpec theDoc);OSErr ShowSelection(FSSpec theDoc){	AppleEvent	aeEvent;	/* the event to create*/	AEDesc	myAddressDesc;	/*descriptors for the */	AEDesc	aeDirDesc;	AEDesc	listElem;	AEDesc	fileList;		/* our list*/	FSSpec	dirSpec;	AliasHandle	dirAlias;		/* alias to directory with our file*/	AliasHandle	fileAlias;		//alias of the file itself*/	AliasHandle	theAliasH;	ProcessSerialNumber process;	/* the finder's psn*/	OSErr		myErr;				/* duh*/	FSSpec	mySpec;	FInfo	fndrInfo;	Boolean	CreatorChanged;	OSType	preserveCreator;//	Boolean	isSample;	short z;	CInfoPBRec	pb;	StandardFileReply	reply;	short temprefNum;	OSErr	iErr;	short switchCount;	char	myChar;	long	theParID;	EventRecord	theEvent;	short itemHit;				/** for dialog enquiry **/	DialogPtr	myDlg;			/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Handle  myHand;	Rect	iRect;				/** for dialog enquiry **/	Rect	myRect;	short	iType;				/** for dialog enquiry **/			iErr = FSpGetFInfo(&theDoc,&fndrInfo);		CreatorChanged = false;		isSample = false;	BlockMove(&theDoc,&mySpec,70L);	if (divertSamples)	{			numTypesToSearch = 2;			Fiyltype[0] = 'AIFF';			Fiyltype[1] = 'SFIL';			Fiyltype[2] = 'Sd2f';				myErr = FSpGetFInfo(&theDoc,&fndrInfo);		if (myErr!=0)			genError("\pCould not get file info");		/******** here *********/		isSample = false;		for (z =0 ;z<=numTypesToSearch;z++)		{			if (fndrInfo.fdType == Fiyltype[z])			{				isSample = true;			}		}			if (isSample)		{			myeventFileType = 'APPL';			myeventCreatorType = divertDocCreator;			myEventID = kAEOpenDocuments;			myEventClass = kCoreEventClass;		}		else		{			myeventFileType = 'FNDR';			myeventCreatorType = 'MACS';			myEventID = kAEOpenSelection;			myEventClass = kAEFinderEvents;			}	}	else	{		if (divertIt)		{			myeventFileType = 'APPL';			myeventCreatorType = divertDocCreator;			myEventID = kAEOpenDocuments;			myEventClass = kCoreEventClass;		}		else		{			myeventFileType = 'FNDR';			myeventCreatorType = 'MACS';			myEventID = kAEOpenSelection;			myEventClass = kAEFinderEvents;		}	}		if(FindAProcess(myeventFileType,myeventCreatorType,&process))	{			genError ("\pProcess not found");			return;	}	myErr = AECreateDesc(typeProcessSerialNumber,(Ptr) &process,							sizeof(process), &myAddressDesc);	if(myErr)		{		genError("\pAppleEvent error");		return;	}	// Create an empty 	myErr = AECreateAppleEvent (myEventClass, myEventID,					&myAddressDesc, kAutoGenerateReturnID, kAnyTransactionID,&aeEvent);	if(myErr)	{		genError("\pAppleEvent error");		return;	}	/* Make an FSSpec and alias for the parent folder, and an alias for the file */	myErr = FSMakeFSSpec(theDoc.vRefNum,theDoc.parID,nil,&dirSpec);	NewAlias(nil,&dirSpec,&dirAlias);	NewAlias(nil,&theDoc,&fileAlias);		if (isSample && divertSamples)	{		theAliasH = fileAlias;	}	else	{		if (divertIt)			theAliasH = fileAlias;		else			theAliasH = dirAlias;	}	if(myErr=AECreateList(nil,0,false,&fileList))	{		genError("\pAppleEvent error");		return;	}	/* Create the folder descriptor*/	HLock((Handle)theAliasH);	AECreateDesc(typeAlias, (Ptr) *theAliasH, GetHandleSize					((Handle) theAliasH), &aeDirDesc);	HUnlock((Handle)theAliasH);	DisposHandle((Handle)dirAlias);	if((myErr = AEPutParamDesc(&aeEvent,keyDirectObject,&aeDirDesc)) ==			noErr)	{			AEDisposeDesc(&aeDirDesc);			HLock((Handle)fileAlias);			AECreateDesc(typeAlias, (Ptr)*fileAlias,					GetHandleSize((Handle)fileAlias), &listElem);			HUnlock((Handle)fileAlias);			DisposHandle((Handle)fileAlias);			myErr = AEPutDesc(&fileList,0,&listElem);	}	if(myErr)	{		genError("\pAppleEvent error");		return;	}	AEDisposeDesc(&listElem);	if(myErr = AEPutParamDesc(&aeEvent,keySelection,&fileList))			return myErr;	myErr = AEDisposeDesc(&fileList);	myErr = AESend(&aeEvent, nil,kAENoReply+kAEAlwaysInteract+kAECanSwitchLayer,kAEHighPriority, kAEDefaultTimeout, nil, nil);	AEDisposeDesc(&aeEvent);			return;	}