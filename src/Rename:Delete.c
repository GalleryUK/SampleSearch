#include "SampleSearch.h"#include "Globals.h"OSErr prefixName(FSSpec *mySpec, Str255 thePrefixer);void addLeadingZeros (StringPtr theString, short totalDigits);#include <ToolUtils.h>typedef struct renameRect {	short renameMode;	short suffPreType;	short removeCharsType;	Str31 searchText;	Str31 replaceText;	Str31 suffPreText;	long suffPreCountStart;	long suffPreCountMode;	long suffPreCountDigits;	long removeCharsCount;	long cropNameCount;	long extendNumbersNumDigits;} renameRect;#define kReplaceText 0#define kSuffixNames 1#define kPrefixNames 2#define kRemoveChars 3#define kCropNameType 4#define kExtendDigits 5#define kSuffPreAddText 0#define kSuffPreCount 1#define kStart 0#define kEnd 1#define kUp 0#define kDown 1OSErr extendAllNumbersLeadingZeros(Str255 inString, StringPtr outString, long NumDigits);OSErr processName (FSSpec * fileSpec);	pascal void MyZItemProc(WindowPtr theDlg,short theItem);	/** draws the line round the default dialog item **/OSErr appendName(FSSpec *mySpec, Str255 theAppender);pascal void MyZItemProc(WindowPtr theDlg,short theItem)		/** draws the line round the default dialog item **/{	Rect	iRect;	Handle	iHndl;	short	iType;		color.red = 0xFFFF;	color.green = 0xFFFF;	color.blue = 0xFFFF;	RGBBackColor(&color);}pascal void MyYItemProc(WindowPtr theDlg,short theItem)	;pascal void MyYItemProc(WindowPtr theDlg,short theItem)		/** draws the line round the default dialog item **/{	Rect	iRect;	Handle	iHndl;	short	iType;		color.red = 56797;	color.green = 56797;	color.blue = 56797;	RGBBackColor(&color);}OSErr RenameItem(FSSpec theDoc, short theselected){	OSErr		iErr;					FSSpec	mySpec;	FInfo	fndrInfo;	short z;	CInfoPBRec	pb;	StandardFileReply	reply;	short temprefNum;	Str255 newName;	short itemHit;				/** for dialog enquiry **/	DialogPtr	myDlg;			/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Handle  myHand;	Rect	iRect;				/** for dialog enquiry **/	Rect	myRect;	short	iType;				/** for dialog enquiry **/	if (-(theDoc.vRefNum) > maxVRef)	{		genError("\pYou cannot rename a ghost item");		return;	}		iErr = FSpGetFInfo(&theDoc,&fndrInfo);				myDlg = GetNewDialog(8999,0L,(WindowPtr)-1);		SetPort (myDlg);	color.red = 56797;	color.green = 56797;	color.blue = 56797;	RGBBackColor(&color);	GetDItem(myDlg,3,&iType,&iHndl,&iRect);	SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);	GetDItem(myDlg,6,&iType,&iHndl,&iRect);	SetDItem(myDlg,6,iType,(Handle)NewUserItemProc(MyZItemProc),&iRect);	GetDItem(myDlg,7,&iType,&iHndl,&iRect);	SetIText(iHndl,theDoc.name);	SelIText(myDlg,7,0,32767);	switch (fndrInfo.fdType)	{		case 'Sd2f': case 'AIFF':  case '.WAV': case '.wav': case 'WAVE': case 'bin ':case 'AIFC':case 'SFIL':			ShowDItem(myDlg,8);		break;	}	ShowWindow(myDlg);	itemHit = 7;	while(itemHit ==7 || itemHit == 8)	{			ModalDialog(xAlertFilter,&itemHit);		switch (itemHit)		{			case 7:				GetDItem(myDlg,7,&iType,&iHndl,&iRect);				GetIText(iHndl,newName);				if (*newName > 31)				{					*newName = 31;				}				SetIText(iHndl,newName);			break;			case 8:				Audition(theDoc, 0x3C);			break;		}	}	GetDItem(myDlg,7,&iType,&iHndl,&iRect);	GetIText(iHndl,newName);	DisposDialog(myDlg);	if (itemHit == 1)	{		iErr = FSpRename(&theDoc,newName);		BlockMove(newName,&(theDoc.name),64L);		if (iErr!=0) 		{			genError("\pCould not rename item");			return iErr;		}		LSetCell(newName+1,(*newName),lCellCoords,myList);		BlockMove(&newName,&((*therealResults)[theselected].name),64L);	}	else	{		return -1;	}	return iErr;		}OSErr DeleteItem(FSSpec theDoc){	OSErr		iErr;					FSSpec	mySpec;	FInfo	fndrInfo;	short z;	CInfoPBRec	pb;	StandardFileReply	reply;	short temprefNum;	Str255 newName = "\p";//"\p<deleted>";	Rect	myRect;	if (-(theDoc.vRefNum) > maxVRef)	{		return -1;	}	iErr = FSpDelete(&theDoc);	if (iErr!=0) 	{		SysBeep(5);		return true;	}	return 0;}renameRect theRenParams; void appendNameMany(void);void appendNameMany(void){	Cell theCell;	short theindex;	short itemHit;				/** for dialog enquiry **/	DialogPtr	myDlg;			/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	Str255 textStr;	Boolean memoryError = false;	Str255 tempStr;		myDlg = GetNewDialog(2875,0L,(WindowPtr)-1);	SetPort (myDlg);	/*color.red = 56797;	color.green = 56797;	color.blue = 56797;	RGBBackColor(&color);*/			GetDItem(myDlg,15,&iType,&iHndl,&iRect);	SetCtlValue((ControlHandle)iHndl,true);		GetDItem(myDlg,8,&iType,&iHndl,&iRect);	SetCtlValue((ControlHandle)iHndl,true);		GetDItem(myDlg,22,&iType,&iHndl,&iRect);	SetCtlValue((ControlHandle)iHndl,true);			ShowWindow(myDlg);		itemHit = 0;		while (itemHit != 1 && itemHit != 2)	{		ModalDialog(xAlertFilter,&itemHit);		switch (itemHit)		{			case 15: case 6: case 7: case 19: case 26:case 32:				GetDItem(myDlg,15,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,false);				GetDItem(myDlg,6,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,false);				GetDItem(myDlg,7,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,false);				GetDItem(myDlg,19,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,false);				GetDItem(myDlg,26,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,false);				GetDItem(myDlg,32,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,false);				GetDItem(myDlg,itemHit,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,true);			break;						case 8: case 10: case 12:				GetDItem(myDlg,8,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,false);				GetDItem(myDlg,10,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,false);				GetDItem(myDlg,12,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,false);				GetDItem(myDlg,itemHit,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,true);			break;						case 22: case 23:				GetDItem(myDlg,22,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,false);				GetDItem(myDlg,23,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,false);				GetDItem(myDlg,itemHit,&iType,&iHndl,&iRect);				SetCtlValue((ControlHandle)iHndl,true);			break;				}	}						GetDItem(myDlg,15,&iType,&iHndl,&iRect);	if (GetCtlValue((ControlHandle)iHndl)) /* replace text */	{		theRenParams.renameMode = kReplaceText;		GetDItem(myDlg,16,&iType,&iHndl,&iRect);		GetIText(iHndl,theRenParams.searchText);		GetDItem(myDlg,5,&iType,&iHndl,&iRect);		GetIText(iHndl,theRenParams.replaceText);	}		GetDItem(myDlg,32,&iType,&iHndl,&iRect);	if (GetCtlValue((ControlHandle)iHndl)) /* extend numeric digits text */	{		theRenParams.renameMode = kExtendDigits;		GetDItem(myDlg,33,&iType,&iHndl,&iRect);		GetIText(iHndl,tempStr);		StringToNum(tempStr,&theRenParams.extendNumbersNumDigits);	}	GetDItem(myDlg,6,&iType,&iHndl,&iRect);	if (GetCtlValue((ControlHandle)iHndl))	{		theRenParams.renameMode = kSuffixNames;		GetDItem(myDlg,8,&iType,&iHndl,&iRect); /* suffix text */		if (GetCtlValue((ControlHandle)iHndl))		{			theRenParams.suffPreType = kSuffPreAddText;			GetDItem(myDlg,9,&iType,&iHndl,&iRect);			GetIText(iHndl,theRenParams.suffPreText);		}				GetDItem(myDlg,10,&iType,&iHndl,&iRect); /* suffix count up */		if (GetCtlValue((ControlHandle)iHndl))		{			theRenParams.suffPreType = kSuffPreCount;			theRenParams.suffPreCountMode = kUp;			GetDItem(myDlg,11,&iType,&iHndl,&iRect);			GetIText(iHndl,tempStr);			StringToNum(tempStr,&theRenParams.suffPreCountStart);			GetDItem(myDlg,24,&iType,&iHndl,&iRect);			GetIText(iHndl,tempStr);			StringToNum(tempStr,&theRenParams.suffPreCountDigits);				}		GetDItem(myDlg,12,&iType,&iHndl,&iRect); /* suffix count down */		if (GetCtlValue((ControlHandle)iHndl))		{			theRenParams.suffPreType = kSuffPreCount;			theRenParams.suffPreCountMode = kDown;			GetDItem(myDlg,11,&iType,&iHndl,&iRect);			GetIText(iHndl,tempStr);			StringToNum(tempStr,&theRenParams.suffPreCountStart);			GetDItem(myDlg,24,&iType,&iHndl,&iRect);			GetIText(iHndl,tempStr);			StringToNum(tempStr,&theRenParams.suffPreCountDigits);		}	}		GetDItem(myDlg,7,&iType,&iHndl,&iRect);	if (GetCtlValue((ControlHandle)iHndl))	{		theRenParams.renameMode = kPrefixNames;		GetDItem(myDlg,8,&iType,&iHndl,&iRect); /* prefix text */		if (GetCtlValue((ControlHandle)iHndl))		{			theRenParams.suffPreType = kSuffPreAddText;			GetDItem(myDlg,9,&iType,&iHndl,&iRect);			GetIText(iHndl,theRenParams.suffPreText);		}				GetDItem(myDlg,10,&iType,&iHndl,&iRect); /* prefix count up */		if (GetCtlValue((ControlHandle)iHndl))		{			theRenParams.suffPreType = kSuffPreCount;			theRenParams.suffPreCountMode = kUp;			GetDItem(myDlg,11,&iType,&iHndl,&iRect);			GetIText(iHndl,tempStr);			StringToNum(tempStr,&theRenParams.suffPreCountStart);			GetDItem(myDlg,24,&iType,&iHndl,&iRect);			GetIText(iHndl,tempStr);			StringToNum(tempStr,&theRenParams.suffPreCountDigits);				}		GetDItem(myDlg,12,&iType,&iHndl,&iRect); /* prefix count down */		if (GetCtlValue((ControlHandle)iHndl))		{			theRenParams.suffPreType = kSuffPreCount;			theRenParams.suffPreCountMode = kDown;			GetDItem(myDlg,11,&iType,&iHndl,&iRect);			GetIText(iHndl,tempStr);			StringToNum(tempStr,&theRenParams.suffPreCountStart);			GetDItem(myDlg,24,&iType,&iHndl,&iRect);			GetIText(iHndl,tempStr);			StringToNum(tempStr,&theRenParams.suffPreCountDigits);		}	}			GetDItem(myDlg,19,&iType,&iHndl,&iRect);	if (GetCtlValue((ControlHandle)iHndl))	{		theRenParams.renameMode = kRemoveChars;		GetDItem(myDlg,22,&iType,&iHndl,&iRect);  /* remove n chars from start */		if (GetCtlValue((ControlHandle)iHndl))		{			theRenParams.removeCharsType = kStart;			GetDItem(myDlg,18,&iType,&iHndl,&iRect);			GetIText(iHndl,tempStr);			StringToNum(tempStr,&theRenParams.removeCharsCount);		}		GetDItem(myDlg,23,&iType,&iHndl,&iRect);  /* remove n chars from end */		if (GetCtlValue((ControlHandle)iHndl))		{			theRenParams.removeCharsType = kEnd;			GetDItem(myDlg,18,&iType,&iHndl,&iRect);			GetIText(iHndl,tempStr);			StringToNum(tempStr,&theRenParams.removeCharsCount);		}	}		GetDItem(myDlg,26,&iType,&iHndl,&iRect);	if (GetCtlValue((ControlHandle)iHndl))	{		theRenParams.renameMode = kCropNameType;		GetDItem(myDlg,27,&iType,&iHndl,&iRect);		GetIText(iHndl,tempStr);		StringToNum(tempStr,&theRenParams.cropNameCount);	}		DisposDialog(myDlg);			if (itemHit ==1)	{		watchcursor(true);		SetPt( &theCell, 0,0 );		/* start at top of list  */				writeLogS((unsigned char *)"Starting Name Manipulation");		while ( LGetSelect( TRUE, &theCell, myList) ) 		{			theindex = (theCell.v * DisplayedColumns) + (theCell.h * (DisplayedColumns != 1));						if (!processName (&((*therealResults)[theindex])))			{				writeLog((Ptr)(*therealResults)[theindex].name);				}			else			{				writeLogS((unsigned char *)"Failed to process :");				writeLog((Ptr)(*therealResults)[theindex].name);					writeLogS((unsigned char *)"Continuing.....");				memoryError = true;			}						LSetCell(((*therealResults)[theindex].name)+1L,*((*therealResults)[theindex].name),theCell,myList);			LNextCell( TRUE, TRUE, &theCell, myList ); 	/* advance to next */		}				watchcursor(false);		if (memoryError)			genError("\pSome files could not be converted, consult the SampleSearch™ Log for details");					genError("\pThe Finder can be slow to respond to remote name changes, so please open and close the folders containing the affected files");	}}void addLeadingZeros (StringPtr theString, short totalDigits){	Str255 theTempString;	short goBack;	short z;		makeStr255(theString,theTempString);	*theString = totalDigits;		goBack = *theTempString;		for (z = totalDigits;z > (totalDigits -  *theTempString) ;z--)	{		*(theString + (long)z) = *(theTempString + goBack);		goBack --;	}	for (z = (totalDigits -  *theTempString) ;z > 0 ;z--)	{		*(theString + (long)z) = '0';	}	return;	}OSErr processName (FSSpec * fileSpec){	OSErr error = noErr;	StringHandle tempStrH;	Str255 textStr,tempStr;	Size lByteCnt;		switch (theRenParams.renameMode)	{		case kReplaceText:			tempStrH = NewString(fileSpec->name);			Munger((Handle)tempStrH,1,theRenParams.searchText + 1,*theRenParams.searchText ,theRenParams.replaceText + 1,*theRenParams.replaceText);						lByteCnt = GetHandleSize((Handle)tempStrH);			**tempStrH = lByteCnt - 1;						error  = FSpRename (fileSpec,*tempStrH);			if (!error)			{				makeStr255 (*tempStrH,fileSpec->name);			}			DisposHandle((Handle)tempStrH);		break;				case kExtendDigits:			extendAllNumbersLeadingZeros(fileSpec->name, textStr, theRenParams.extendNumbersNumDigits);			error  = FSpRename (fileSpec,textStr);			if (!error)			{				makeStr255 (textStr,fileSpec->name);			}		break;			case kSuffixNames:			switch (theRenParams.suffPreType)			{				case kSuffPreAddText:					error = appendName(fileSpec,theRenParams.suffPreText);				break;								case kSuffPreCount:					/* do it */					NumToString (theRenParams.suffPreCountStart, textStr);					addLeadingZeros (textStr, LoWord(theRenParams.suffPreCountDigits));					error = appendName(fileSpec,textStr);					theRenParams.suffPreCountStart = (theRenParams.suffPreCountMode == kUp) ? theRenParams.suffPreCountStart + 1 : theRenParams.suffPreCountStart - 1; 				break;			}		break;				case kPrefixNames:			switch (theRenParams.suffPreType)			{				case kSuffPreAddText:					error = prefixName(fileSpec,theRenParams.suffPreText);				break;								case kSuffPreCount:					/* do it */					NumToString (theRenParams.suffPreCountStart, textStr);					addLeadingZeros (textStr, LoWord(theRenParams.suffPreCountDigits));					error = prefixName(fileSpec,textStr);					theRenParams.suffPreCountStart = (theRenParams.suffPreCountMode == kUp) ? theRenParams.suffPreCountStart + 1 : theRenParams.suffPreCountStart - 1; 				break;			}		break;				case kRemoveChars:			switch (theRenParams.removeCharsType)			{				case kStart:					if (*(fileSpec->name) <= theRenParams.removeCharsCount)					{						error = -1;					}					else					{						Str31 temper;						makeStr255 (fileSpec->name, temper);												BlockMove(fileSpec->name + 1 + theRenParams.removeCharsCount,temper + 1,*fileSpec->name - theRenParams.removeCharsCount);						*temper = *fileSpec->name - theRenParams.removeCharsCount;						error  = FSpRename (fileSpec,temper);						if (!error)						{							makeStr255 (temper,fileSpec->name);						}					}				break;								case kEnd:					if (*(fileSpec->name) <= theRenParams.removeCharsCount)					{						error = -3;					}					else					{						Str31 temper;						makeStr255 (fileSpec->name, temper);												*temper -= theRenParams.removeCharsCount;						error  = FSpRename (fileSpec,temper);						if (!error)						{							makeStr255 (temper,fileSpec->name);						}					}				break;			}		break;				case kCropNameType:			if (*(fileSpec->name) < theRenParams.cropNameCount)			{				error = -2;			}			else			{				Str31 temper;				makeStr255 (fileSpec->name, temper);								*temper = theRenParams.cropNameCount;				error  = FSpRename (fileSpec,temper);				if (!error)				{					makeStr255 (temper,fileSpec->name);				}			}		break;	}	return noErr;}OSErr appendName(FSSpec *mySpec, Str255 theAppender){	Str255 stringC = "\p";	OSErr iErr;		concatStrings(stringC,theAppender,mySpec->name);	iErr = FSpRename(mySpec,stringC);	if (!iErr)	{		BlockMove(stringC,mySpec->name,(*stringC)+1);	}	return (iErr);}OSErr prefixName(FSSpec *mySpec, Str255 thePrefixer){	Str255 stringC = "\p";	OSErr iErr;		concatStrings(stringC,mySpec->name,thePrefixer);	iErr = FSpRename(mySpec,stringC);	if (!iErr)	{		BlockMove(stringC,mySpec->name,(*stringC)+1);	}	return (iErr);}OSErr extendAllNumbersLeadingZeros(Str255 inString, StringPtr outString, long NumDigits){	short z=1;	Str255 thisNum;	*outString = 0;	while (z <= *inString)	{		while (((*(inString + z) < '0') || (*(inString + z) > '9')) && (z <= *inString))		{			*(outString + *outString + 1) =  *(inString + z);			*outString = *outString + 1;			z++;		}		if (z <= *inString)		{			*thisNum = 0;			while (((*(inString + z) >= '0') && (*(inString + z) <= '9')) && (z <= *inString))			{				*(thisNum + *thisNum + 1) =  *(inString + z);				*thisNum = *thisNum + 1;				z++;			}			addLeadingZeros (thisNum,LoWord(NumDigits));			concatStrings(outString,thisNum,"\p");		}	}	return;}