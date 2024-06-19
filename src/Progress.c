#include "SampleSearch.h"#include "Globals.h"extern Boolean DialogPresent;Boolean appearanceAvailable = true;ControlHandle theProgressControl = 0;DialogPtr myProgDialog;GrafPtr	savePort;Boolean progressDispN(short percentFull, short theValue);Boolean progressDispN(short percentFull, short theValue){	short itemHit;				/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	short diff;	WindowPtr	whichWindow;					/** for event handling **/	RGBColor	color;	EventRecord theEvent;	DialogPtr	whichDlog;	Rect	dragRect;	short	thePart;							/** for event handling **/	short theQuay;	Str255 theIntStr;		if (DialogPresent)		return;				if (percentFull >100)	 percentFull = 100;	 	 if (percentFull <1)	 	percentFull = 1;	 	dragRect = qd.screenBits.bounds;	if (appearanceAvailable)	{		GetDItem(myProgDialog,2,&iType,(char***)&theProgressControl,&iRect);		SetCtlValue(theProgressControl,percentFull);	}	else	{		GetDItem(myProgDialog,2,&iType,&iHndl,&iRect);		InsetRect(&iRect,1,1);		color.red = 17476;		color.green = 17476;		color.blue = 17476;		diff = iRect.right - iRect.left;		iRect.right = iRect.left + ((percentFull*diff)/100);		RGBForeColor(&color);		FillRect(&iRect,&qd.black);		color.red = 0x0000;		color.green = 0x0000;		color.blue = 0x0000;		RGBForeColor(&color);	}	NumToString((long)theValue,theIntStr);	GetDItem(myProgDialog,4,&iType,&iHndl,&iRect);	SetIText(iHndl,theIntStr);	if(GetNextEvent(everyEvent,&theEvent)) 	{		if (theEvent.what == mouseDown)		{			thePart = FindWindow (theEvent.where,&whichWindow);			if (thePart == inDrag)			{				if (whichWindow == myProgDialog)				DragWindow(myProgDialog, theEvent.where, &dragRect);				InvalRect(&myProgDialog->portRect);			}		}		if(IsDialogEvent(&theEvent)) 		{			if(DialogSelect(&theEvent,&whichDlog,&itemHit)) 			{				if (itemHit == 1)				{					progressDispos();					return true;				}			}		}		if (theEvent.what == keyDown)		{			theQuay = (theEvent.message) & keyCodeMask;			if ((theQuay == 0x2F00) && (theEvent.modifiers & cmdKey)) 			{					progressDispos();					return true;			}		}	}	return false;}Boolean progressDisp(short percentFull){	short itemHit;				/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	short diff;	WindowPtr	whichWindow;					/** for event handling **/	RGBColor	color;	EventRecord theEvent;	DialogPtr	whichDlog;	Rect	dragRect;	short	thePart;							/** for event handling **/	short theQuay;			if (DialogPresent)		return;				if (percentFull >100)	 percentFull = 100;	 	 if (percentFull <1)	 	percentFull = 1;	 	if (appearanceAvailable)	{		GetDItem(myProgDialog,2,&iType,(char***)&theProgressControl,&iRect);		SetCtlValue(theProgressControl,percentFull);	}	else	{		dragRect = qd.screenBits.bounds;		GetDItem(myProgDialog,2,&iType,&iHndl,&iRect);		InsetRect(&iRect,1,1);		color.red = 17476;		color.green = 17476;		color.blue = 17476;		diff = iRect.right - iRect.left;		iRect.right = iRect.left + ((percentFull*diff)/100);		RGBForeColor(&color);		FillRect(&iRect,&qd.black);		color.red = 0x0000;		color.green = 0x0000;		color.blue = 0x0000;		RGBForeColor(&color);	}	if(WaitNextEvent(everyEvent,&theEvent,0,0)) 	{		if (theEvent.what == mouseDown)		{			thePart = FindWindow (theEvent.where,&whichWindow);			if (thePart == inDrag)			{				if (whichWindow == myProgDialog)				DragWindow(myProgDialog, theEvent.where, &dragRect);				InvalRect(&myProgDialog->portRect);			}			else			{				short iCtlPart;				Point localPt;				GrafPtr ZsavePort;				ControlHandle whichCtl;				if (whichWindow == myProgDialog)				{					GetPort(&ZsavePort);					SetPort (myProgDialog);					localPt = theEvent.where;					GlobalToLocal(&localPt);					iCtlPart = FindControl(localPt,whichWindow,&whichCtl);						if (iCtlPart && whichCtl)					{						long lRefCon = GetCRefCon(whichCtl);						if (lRefCon == 6502)						{							progressDispos();							return true;						}					}					SetPort (ZsavePort);				}					}		}	/*	if(IsDialogEvent(&theEvent)) 		{// appleshxare volume snapshot crashes here 			if(DialogSelect(&theEvent,&whichDlog,&itemHit)) 			{				if (itemHit == 1)				{					progressDispos();					return true;				}			}		}*/		if (theEvent.what == keyDown)		{			theQuay = (theEvent.message) & keyCodeMask;			if ((theQuay == 0x2F00) && (theEvent.modifiers & cmdKey)) 			{					progressDispos();					return true;			}		}	}	return false;}WindowPtr progressWindow = 0;ControlHandle progressAmount = 0, StopButton = 0, statusTextCtl = 0;void progressWindowCreate(Str255	theText);OSErr progressWinDisp(short percent);void progressWindowDispose(void);Str255 dlgTextData;void progressWindowCreate(Str255	theText){	Rect box = {6,12,21,231};	RGBColor zcolor = {60000,60000,60000};	if (!progressWindow)	{		progressWindow = GetNewCWindow(6000,0,(WindowPtr)-1);		SetPort(progressWindow);		TextFont(0);		}	if (progressWindow)	{		if (!progressAmount)			progressAmount = GetNewControl(6501,progressWindow);		if (!StopButton)			StopButton = GetNewControl(6502,progressWindow);	//	if (!statusTextCtl)	//		statusTextCtl = GetNewControl(6503,progressWindow);	//	SetCTitle(statusTextCtl,theText);		makeStr255(theText,dlgTextData);		ShowWindow(progressWindow);		RGBBackColor(&zcolor);		TextBox(dlgTextData+1,*dlgTextData,&box,0);	}}OSErr progressWinDisp(short percent){	short itemHit;				/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	short diff;	WindowPtr	whichWindow;					/** for event handling **/	RGBColor	color;	EventRecord theEvent;	DialogPtr	whichDlog;	Rect	dragRect;	short	thePart;							/** for event handling **/	short theQuay;	Rect box = {6,12,21,231};	SetCtlValue(progressAmount,percent);	DrawControls(progressWindow);	TextBox(dlgTextData+1,*dlgTextData,&box,0);	if(WaitNextEvent(everyEvent,&theEvent,0,0)) 	{		if (theEvent.what == mouseDown)		{			thePart = FindWindow (theEvent.where,&whichWindow);			if (thePart == inDrag)			{				if (whichWindow == progressWindow)				DragWindow(progressWindow, theEvent.where, &dragRect);			//	InvalRect(&progressWindow->portRect);			}			else			{				short iCtlPart;				Point localPt;				GrafPtr ZsavePort;				ControlHandle whichCtl;				if (whichWindow == progressWindow)				{					GetPort(&ZsavePort);					SetPort (progressWindow);					localPt = theEvent.where;					GlobalToLocal(&localPt);					iCtlPart = FindControl(localPt,whichWindow,&whichCtl);						if (iCtlPart && whichCtl)					{						if (StopButton == whichCtl)						{							progressWindowDispose();							return true;						}					}					SetPort (ZsavePort);				}					}		}		if (theEvent.what == keyDown)		{			theQuay = (theEvent.message) & keyCodeMask;			if ((theQuay == 0x2F00) && (theEvent.modifiers & cmdKey)) 			{					progressWindowDispose();					return true;			}		}	}	return noErr;}void progressWindowDispose(void){	if (progressWindow)		DisposeWindow(progressWindow);	if (StopButton)		DisposeControl(StopButton);/*	if (statusTextCtl)		DisposeControl(statusTextCtl);*/	if (progressAmount)		DisposeControl(progressAmount);	progressWindow = 0;	progressAmount = 0;	StopButton = 0;	statusTextCtl = 0;}void progressCreate(Str255	theText){	short itemHit;				/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	EventRecord theEvent;		GDHandle	gdh;	Boolean hasMode;	PixMapHandle xx;		if (DialogPresent)		return;	//	GetPort(&savePort);		ParamText(theText,0,0,0);	myProgDialog = GetNewDialog( (appearanceAvailable) ? 9501 : 9500 ,0L,(WindowPtr)-1);		SetPort(myProgDialog);	if (appearanceAvailable)	{		GetDItem(myProgDialog,2,&iType,(char***)&theProgressControl,&iRect);		SetCtlValue(theProgressControl,0);		DrawDialog(myProgDialog);	}	else	{				color.red = 56797;		color.green = 56797;		color.blue = 56797;		RGBBackColor(&color);		gdh = GetMainDevice();				ShowWindow(myProgDialog);		color.red = 0;		color.blue = 0;		color.green = 0;		RGBForeColor(&color);		GetDItem(myProgDialog,2,&iType,&iHndl,&iRect);		ShowDItem(myProgDialog,1);		ShowDItem(myProgDialog,2);		PenSize(1,1);		FrameRect(&iRect);		DrawDialog(myProgDialog);		color.red = 52428;		color.green = 52428;		color.blue = 65535;				GetDItem(myProgDialog,2,&iType,&iHndl,&iRect);		InsetRect(&iRect,1,1);		RGBForeColor(&color);		xx = ((**gdh).gdPMap);		if ((*xx)->pixelSize >1) /** if in color **/			FillRect(&iRect,&qd.black);		color.red = 0x0000;		color.green = 0x0000;		color.blue = 0x0000;		RGBForeColor(&color);	}	return;}void progressDispos(void){	if (DialogPresent)		return;//	SetPort(myProgDialog);	if (myProgDialog)		DisposDialog(myProgDialog);	myProgDialog = 0;//	SetPort(savePort);	return;}#include "SampleSearch.h"#include "Globals.h"DialogPtr myProgDialog;GrafPtr	savePort;Boolean progressIIDispN(short percentFull, short theValue);Boolean progressIIDispN(short percentFull, short theValue){	short itemHit;				/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	short diff;	WindowPtr	whichWindow;					/** for event handling **/	RGBColor	color;	EventRecord theEvent;	DialogPtr	whichDlog;	Rect	dragRect;	short	thePart;							/** for event handling **/	short theQuay;	Str255 theIntStr;		if (DialogPresent)		return;					if (percentFull >100)	 percentFull = 100;	dragRect = qd.screenBits.bounds;	if (appearanceAvailable)	{		GetDItem(myProgDialog,2,&iType,(char***)&theProgressControl,&iRect);		SetCtlValue(theProgressControl,percentFull);	}	else	{		GetDItem(myProgDialog,2,&iType,&iHndl,&iRect);		InsetRect(&iRect,1,1);		color.red = 17476;		color.green = 17476;		color.blue = 17476;		diff = iRect.right - iRect.left;		iRect.right = iRect.left + ((percentFull*diff)/100);		RGBForeColor(&color);		FillRect(&iRect,&qd.black);		color.red = 0x0000;		color.green = 0x0000;		color.blue = 0x0000;		RGBForeColor(&color);	}	NumToString((long)theValue,theIntStr);	GetDItem(myProgDialog,4,&iType,&iHndl,&iRect);	SetIText(iHndl,theIntStr);	if(GetNextEvent(everyEvent,&theEvent)) 	{		if (theEvent.what == mouseDown)		{			thePart = FindWindow (theEvent.where,&whichWindow);			if (thePart == inDrag)			{				if (whichWindow == myProgDialog)				DragWindow(myProgDialog, theEvent.where, &dragRect);				InvalRect(&myProgDialog->portRect);			}		}		if(IsDialogEvent(&theEvent)) 		{			if(DialogSelect(&theEvent,&whichDlog,&itemHit)) 			{				if (itemHit == 1)				{					progressDispos();					return true;				}			}		}		if (theEvent.what == keyDown)		{			theQuay = (theEvent.message) & keyCodeMask;			if ((theQuay == 0x2F00) && (theEvent.modifiers & cmdKey)) 			{					progressDispos();					return true;			}		}	}	return false;}Boolean progressIIDisp(short percentFull);Boolean progressIIDisp(short percentFull){		short diff;	RGBColor	color;	EventRecord theEvent;	short theQuay;	Rect theFillRect;	Rect theTextRect;	long totalSpan, rightSide;	PicHandle hPic;	Boolean drawCentre;			if (DialogPresent)		return;			if (percentFull >100)	 percentFull = 100;	 	 if (percentFull <1)	 	percentFull = 1;	 	 SetPort(myWindow);	 		 	totalSpan = (long)((myWindow->portRect.right-36) - 15L);	rightSide = (long)percentFull * (long)totalSpan / 100L;		if (rightSide < 1L )	{		rightSide = 1L;	}			SetRect(&theFillRect,15,myWindow->portRect.bottom-13,rightSide + 15,myWindow->portRect.bottom-2);				/********/ 	 		hPic = GetPicture(132);	DrawPicture(hPic,&theFillRect);		if (rightSide > 6)	{		drawCentre = true;	}	else	{		drawCentre = false;	}		if (drawCentre)	{		hPic = GetPicture(131);		theFillRect.left = rightSide + 15;		theFillRect.right = rightSide + 21;				DrawPicture(hPic,&theFillRect);	}	/*******/			if(WaitNextEvent(everyEvent,&theEvent,0,0)) 	{		if (theEvent.what == keyDown)		{			theQuay = (theEvent.message) & keyCodeMask;			if ((theQuay == 0x2F00) && (theEvent.modifiers & cmdKey)) 			{					progressDispos();					return true;			}		}	}	return false;}		Boolean xprogressIIDisp(short percentFull);	Boolean xprogressIIDisp(short percentFull){		short diff;	RGBColor	color;	EventRecord theEvent;	short theQuay;	Rect theFillRect;	Rect theTextRect;	long totalSpan, rightSide;		if (DialogPresent)		return;						if (percentFull >100)	 percentFull = 100;	 	 if (percentFull <1)	 	percentFull = 1;	 	 SetPort(myWindow);	 	 	totalSpan = (long)(myWindow->portRect.right-30) - (long)(myWindow->portRect.left+15);	rightSide = (long)percentFull * (long)totalSpan / 100L;			SetRect(&theFillRect,myWindow->portRect.left+15,myWindow->portRect.bottom-14,rightSide + 15,myWindow->portRect.bottom);		color.red = 0xFFFF;	color.blue = 0;	color.green = 0;	RGBForeColor(&color);		FillRect(&theFillRect,&qd.black);		color.red = 0;	color.blue = 0;	color.green = 0;	RGBForeColor(&color);				if(WaitNextEvent(everyEvent,&theEvent,0,0)) 	{		if (theEvent.what == keyDown)		{			theQuay = (theEvent.message) & keyCodeMask;			if ((theQuay == 0x2F00) && (theEvent.modifiers & cmdKey)) 			{					progressDispos();					return true;			}		}	}	return false;}void progressIICreate(Str255	theText);void progressIICreate(Str255	theText){		Rect theFillRect;	Rect theTextRect;	PicHandle hPic;	if (DialogPresent)		return;		SetRect(&theFillRect,15,myWindow->portRect.bottom-13,myWindow->portRect.right - 30,myWindow->portRect.bottom-2);				/********/ 	 		hPic = GetPicture(133);	DrawPicture(hPic,&theFillRect);			return;}void progressIIDispos(void);void progressIIDispos(void){		Rect theFillRect;	Rect theTextRect;	if (DialogPresent)		return;	 SetPort(myWindow);		SetRect(&theFillRect,15,myWindow->portRect.bottom-14,myWindow->portRect.right - 30,myWindow->portRect.bottom);				FillRect(&theFillRect,&qd.white);				return;}