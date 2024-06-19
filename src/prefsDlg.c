#include "SampleSearch.h"#include "Globals.h"void ExcludeList(void);void RetrievePrefs(void);#include "prefs.h"extern newPrefsRec theNewPrefs;typedef struct listFontRec {Str255 fontName;short fontSize;} listFontRec, *listFontRecPtr;extern listFontRec  theFontRec;pascal void MyColorProc(WindowPtr theDlg,short theItem);extern Boolean AutoLaunchDivert;extern Boolean ExcludeDrives;extern Boolean stickyInfo;extern Boolean freshSearch;extern Boolean PreservePopups;extern long dblBufferSize;extern long normBuffer;extern Boolean MakeCompositeAE;void PrefsPage(void);OSType writeResToPrefs(Handle rpHandle, OSType thePrefType, short prefID,  long handleSize);void PrefsPage(void){	short itemHit;				/** for dialog enquiry **/	DialogPtr	myDlg;			/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	short iCtlValue;	short refNum;	OSErr	iErr;	long inOutCount,theLongTemp;	Str255 textStr;	MenuHandle	fontMenu;	MenuHandle  sizeMenu;	short  iItemCnt;	short z;	RGBColor tempColor;	long tempLong;	long theNum;	Str255 itemString;	short fontNum;	Handle tempH, SDBHandle;	Point wherept = {-1,-1};	short presLeft;		RetrievePrefs();	fontMenu = GetMenu(2222);	if (!fontMenu)	{		genError ("\pCan't load fonts menu");		return;	}	sizeMenu = GetMenu(2223);	if (!sizeMenu)	{		genError ("\pCan't load fontsize menu");		return;	}	AddResMenu(fontMenu,'FONT');		myDlg = GetNewDialog ( 1812, 0L,(WindowPtr)-1);				SetPort (myDlg);		GetDItem(myDlg,15,&iType,&iHndl,&iRect);		iItemCnt = CountMItems(fontMenu);	for (z=1;z<=iItemCnt;z++)	{		GetItem(fontMenu,z,itemString);		if(EqualString(itemString,theFontRec.fontName,false,false)) 		{			SetCtlValue((ControlHandle)iHndl,z);		}	}		GetDItem(myDlg,25,&iType,&iHndl,&iRect);	SetDItem(myDlg,25,iType,(Handle)NewUserItemProc(MyColorProc),&iRect);		GetDItem(myDlg,26,&iType,&iHndl,&iRect);	SetDItem(myDlg,26,iType,(Handle)NewUserItemProc(MyColorProc),&iRect);			GetDItem(myDlg,17,&iType,&iHndl,&iRect);	GetFNum(theFontRec.fontName,&fontNum);	for (z=1;z<=8;z++)	{		GetItem(sizeMenu,z,itemString);		StringToNum(itemString,&theNum);		if(RealFont(fontNum,LoWord(theNum))) 		{			SetItemStyle(sizeMenu,z,outline);		}		if (LoWord(theNum) == theFontRec.fontSize)			SetCtlValue((ControlHandle)iHndl,z);	}		GetDItem(myDlg,3,&iType,&iHndl,&iRect);	SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);		/*color.red = 56797;	color.green = 56797;	color.blue = 56797;	RGBBackColor(&color);*/	//GetDItem ( myDlg, 3, &iType, &iHndl, &iRect ); /** read data from textedit **/	//SetCtlValue((ControlHandle)iHndl,MakeCompositeAE);		GetDItem ( myDlg, 4, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,AutoLaunchDivert);	GetDItem ( myDlg, 5, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,ExcludeDrives);	GetDItem ( myDlg, 18, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,stickyInfo);	GetDItem ( myDlg, 8, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,PreservePopups);	GetDItem ( myDlg, 19, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,theNewPrefs.noSearch);		GetDItem ( myDlg, 20, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,theNewPrefs.PTResolveFindOne);		GetDItem ( myDlg, 21, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,theNewPrefs.waveFormWindow);		GetDItem ( myDlg, 29, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,theNewPrefs.useMoreFiles);		GetDItem ( myDlg, 30, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,theNewPrefs.dontFindAliases);	GetDItem ( myDlg, 32, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,theNewPrefs.ignorePTFades);	GetDItem ( myDlg, 31, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,theNewPrefs.dontAddToList);		GetDItem ( myDlg, 34, &iType, &iHndl, &iRect ); /** read data from textedit **/	SetCtlValue((ControlHandle)iHndl,theNewPrefs.deselectAsPlayed);	GetDItem(myDlg,9,&iType,&iHndl,&iRect);	SetDItem(myDlg,9,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);	GetDItem(myDlg,11,&iType,&iHndl,&iRect);	NumToString(dblBufferSize,textStr);	SetIText(iHndl,textStr);	GetDItem(myDlg,13,&iType,&iHndl,&iRect);	NumToString(normBuffer,textStr);	SetIText(iHndl,textStr);		GetDItem(myDlg,23,&iType,&iHndl,&iRect);	NumToString((long)theNewPrefs.theWaveFormHeight,textStr);	SetIText(iHndl,textStr);			ShowWindow(myDlg);	while (itemHit != 1 && itemHit !=2)	{		ModalDialog(xAlertFilter,&itemHit);		switch (itemHit)		{			case 6:				ExcludeList();				GetDItem ( myDlg, 5, &iType, &iHndl, &iRect ); /** read data from textedit **/				SetCtlValue((ControlHandle)iHndl,1);			break;						case 4: case 5: case 8: case 18:				GetDItem ( myDlg, itemHit, &iType, &iHndl, &iRect ); /** read data from textedit **/				SetCtlValue((ControlHandle)iHndl,!GetCtlValue((ControlHandle)iHndl));			break;						case 15:				GetDItem ( myDlg, 15, &iType, &iHndl, &iRect ); 				iCtlValue = GetCtlValue((ControlHandle)iHndl);				GetItem(fontMenu,iCtlValue,theFontRec.fontName);				GetDItem(myDlg,17,&iType,&iHndl,&iRect);				GetFNum(theFontRec.fontName,&fontNum);				for (z=1;z<=8;z++)				{					GetItem(sizeMenu,z,itemString);					StringToNum(itemString,&theNum);					if(RealFont(fontNum,LoWord(theNum))) 					{						SetItemStyle(sizeMenu,z,outline);					}					else					{						SetItemStyle(sizeMenu,z,0);					}					if (LoWord(theNum) == theFontRec.fontSize)						SetCtlValue((ControlHandle)iHndl,z);				}				UpdtControl(myDlg,myDlg->visRgn);							break;						case 19:				GetDItem ( myDlg, itemHit, &iType, &iHndl, &iRect ); /** read data from textedit **/				SetCtlValue((ControlHandle)iHndl,theNewPrefs.noSearch = !GetCtlValue((ControlHandle)iHndl));			break;						case 29:				GetDItem ( myDlg, itemHit, &iType, &iHndl, &iRect ); 				SetCtlValue((ControlHandle)iHndl,theNewPrefs.useMoreFiles = !GetCtlValue((ControlHandle)iHndl));			break;						case 30:				GetDItem ( myDlg, itemHit, &iType, &iHndl, &iRect ); 				SetCtlValue((ControlHandle)iHndl,theNewPrefs.dontFindAliases = !GetCtlValue((ControlHandle)iHndl));			break;						case 32:				GetDItem ( myDlg, itemHit, &iType, &iHndl, &iRect ); 				SetCtlValue((ControlHandle)iHndl,theNewPrefs.ignorePTFades = !GetCtlValue((ControlHandle)iHndl));			break;						case 31:				GetDItem ( myDlg, itemHit, &iType, &iHndl, &iRect ); 				SetCtlValue((ControlHandle)iHndl,theNewPrefs.dontAddToList = !GetCtlValue((ControlHandle)iHndl));			break;						case 20:				GetDItem ( myDlg, itemHit, &iType, &iHndl, &iRect ); /** read data from textedit **/				SetCtlValue((ControlHandle)iHndl,theNewPrefs.PTResolveFindOne = !GetCtlValue((ControlHandle)iHndl));			break;						case 34:				GetDItem ( myDlg, itemHit, &iType, &iHndl, &iRect ); /** read data from textedit **/				SetCtlValue((ControlHandle)iHndl,theNewPrefs.deselectAsPlayed = !GetCtlValue((ControlHandle)iHndl));			break;						case 21:				GetDItem ( myDlg, itemHit, &iType, &iHndl, &iRect ); /** read data from textedit **/				SetCtlValue((ControlHandle)iHndl,theNewPrefs.waveFormWindow = !GetCtlValue((ControlHandle)iHndl));				theNewPrefs.SDIIToolBar = theNewPrefs.waveFormWindow;			break;						case 25:				if(GetColor(wherept,"\pSelect Background Color",&theNewPrefs.theWaveFormBackGround,&tempColor)) 				{					BlockMove(&tempColor,&theNewPrefs.theWaveFormBackGround,sizeof(RGBColor));					GetDItem ( myDlg, 25, &iType, &iHndl, &iRect);					RGBForeColor(&theNewPrefs.theWaveFormBackGround);					FillRect(&iRect, &qd.black);					presLeft = iRect.left;					iRect.left = iRect.right - 10;					InvertRect(&iRect);					iRect.left = presLeft;					tempColor.red = 0;					tempColor.green = 0;					tempColor.blue = 0;					RGBForeColor(&tempColor);					FrameRect(&iRect);				}			break;						case 26:				if(GetColor(wherept,"\pSelect Waveform Color",&theNewPrefs.theWaveFormColor,&tempColor)) 				{					BlockMove(&tempColor,&theNewPrefs.theWaveFormColor,sizeof(RGBColor));					GetDItem ( myDlg, 26, &iType, &iHndl, &iRect);					RGBForeColor(&theNewPrefs.theWaveFormColor);					FillRect(&iRect, &qd.black);					presLeft = iRect.left;					iRect.left = iRect.right - 10;					InvertRect(&iRect);					iRect.left = presLeft;					tempColor.red = 0;					tempColor.green = 0;					tempColor.blue = 0;					RGBForeColor(&tempColor);					FrameRect(&iRect);				}			break;						default:			break;		}			}	if (itemHit ==2)	{		DisposDialog (myDlg);		ReleaseResource((Handle)fontMenu);		ReleaseResource((Handle)sizeMenu);		return;	}		GetDItem ( myDlg, 15, &iType, &iHndl, &iRect ); 	iCtlValue = GetCtlValue((ControlHandle)iHndl);	GetItem(fontMenu,iCtlValue,theFontRec.fontName);	GetDItem ( myDlg, 18, &iType, &iHndl, &iRect ); 	iCtlValue = GetCtlValue((ControlHandle)iHndl);	if (iCtlValue)		stickyInfo = true;	else		stickyInfo = false;			GetDItem ( myDlg, 34, &iType, &iHndl, &iRect );	theNewPrefs.deselectAsPlayed = GetCtlValue((ControlHandle)iHndl);					SDBHandle = NewHandle(sizeof(Boolean));		**SDBHandle = stickyInfo;	writeResToPrefs(SDBHandle,'SDbf', 1000,  sizeof(Boolean));			GetDItem ( myDlg, 17, &iType, &iHndl, &iRect ); 	iCtlValue = GetCtlValue((ControlHandle)iHndl);	GetItem(sizeMenu,iCtlValue,textStr);	StringToNum(textStr, &theLongTemp);	theFontRec.fontSize = LoWord(theLongTemp);	tempH = NewHandle(sizeof(listFontRec));	if (tempH)	{		BlockMove(&theFontRec,*tempH,sizeof(listFontRec));		iErr = writeResToPrefs(tempH, 'LFon',1000,sizeof(listFontRec));		if (iErr != noErr)		{			genErrorN("\pProblem writing prefs",iErr);		}		DisposHandle(tempH);	}		ReleaseResource((Handle)fontMenu);	ReleaseResource((Handle)sizeMenu);		//GetDItem ( myDlg, 3, &iType, &iHndl, &iRect ); /** read data from textedit **/	//MakeCompositeAE = GetCtlValue((ControlHandle)iHndl);	GetDItem ( myDlg, 4, &iType, &iHndl, &iRect ); /** read data from textedit **/	AutoLaunchDivert = GetCtlValue((ControlHandle)iHndl);	GetDItem ( myDlg, 5, &iType, &iHndl, &iRect ); /** read data from textedit **/	ExcludeDrives = GetCtlValue((ControlHandle)iHndl);	GetDItem ( myDlg, 8, &iType, &iHndl, &iRect ); /** read data from textedit **/	PreservePopups = GetCtlValue((ControlHandle)iHndl);	GetDItem ( myDlg, 11, &iType, &iHndl, &iRect ); /** read data from textedit **/	GetIText(iHndl,textStr);	if (*textStr)	{		StringToNum(textStr,&dblBufferSize);	}	GetDItem ( myDlg, 13, &iType, &iHndl, &iRect ); /** read data from textedit **/	GetIText(iHndl,textStr);	if (*textStr)	{		StringToNum(textStr,&normBuffer);	}			GetDItem(myDlg,23,&iType,&iHndl,&iRect);	GetIText(iHndl,textStr);	StringToNum (textStr, &tempLong);	if (tempLong < 15)	{		tempLong = 15;	}	if (tempLong > 600)	{		tempLong = 600;	}	theNewPrefs.theWaveFormHeight = LoWord(tempLong);				DisposDialog (myDlg);		refNum = openPrefFile();	if (!refNum)	{		genError ("\pCan't open Prefs");		return;	}		iErr = SetFPos(refNum,1,100L);	if (iErr !=0)	{		FSClose(refNum);		genError ("\pProblem with prefs file");		return;	}	inOutCount = 2;	iErr = FSWrite(refNum,&inOutCount,&MakeCompositeAE);	if (iErr !=0)	{		FSClose(refNum);		genError ("\pProblem with prefs file");		return;	}	AutoLaunchDivert = !AutoLaunchDivert;	iErr = FSWrite(refNum,&inOutCount,&AutoLaunchDivert);	if (iErr !=0)	{		FSClose(refNum);		genError ("\pProblem with prefs file");		return;	}	AutoLaunchDivert = !AutoLaunchDivert;	iErr = FSWrite(refNum,&inOutCount,&ExcludeDrives);	if (iErr !=0)	{		FSClose(refNum);		genError ("\pProblem with prefs file");		return;	}	PreservePopups = !PreservePopups;	iErr = FSWrite(refNum,&inOutCount,&PreservePopups);	if (iErr !=0)	{		FSClose(refNum);		genError ("\pProblem with prefs file");		return;	}	PreservePopups = !PreservePopups;	inOutCount = 4;	iErr = FSWrite(refNum,&inOutCount,&dblBufferSize);	if (iErr !=0)	{		FSClose(refNum);		genError ("\pProblem with prefs file");		return;	}	inOutCount = 4;	iErr = FSWrite(refNum,&inOutCount,&normBuffer);	if (iErr !=0)	{		FSClose(refNum);		genError ("\pProblem with prefs file");		return;	}	FSClose(refNum);		saveNewPrefs();	return;}