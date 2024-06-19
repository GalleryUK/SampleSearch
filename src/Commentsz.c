#include "SampleSearch.h"#include "Globals.h"void zeditComment(FSSpec	theSelFile, short  index);short ifySCII(FSSpec mySpec);long findANNO(short localRefNum);Boolean zapAPPL(short localRefNum);long findAPPL(short localRefNum);Boolean zapANNO(short localRefNum);short SCFormat;Boolean SetFSSpecComment(FSSpec mySpec, Str255 theComment);Boolean GetFSSpecComment(FSSpec mySpec, StringPtr theComment);Boolean removeCommentFromChunkEnd(short localRefNum, long theFPos, OSType theType);Boolean addCommentToChunkEnd(short localRefNum, Str255 theComment, OSType theType);Boolean addAIFFCommentToChunkEnd(short localRefNum, Str255 theComment, OSType theType);Boolean isItTheLastChunk(short localRefNum, long theFPos);short identifySCII(FSSpec mySpec);void zeditComment(FSSpec	theSelFile, short  index){	short	myRefNum;	OSErr	iErr;	Handle	hRsrc,newCommentH;	Str255	myComment;	short	iCnt;	short itemHit;				/** for dialog enquiry **/	DialogPtr	myDlg;			/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	Cell	myCellCoords;	short	iRefNum,refNum;	Boolean askedOnce;	long	inOutCount;	OSType	myType;	FInfo	fndrInfo;	long	filpPos, AIFFpos, SCinpos, templong;	short z, thePresVRef;	short SCFormat;			if 	(!FInfolistInMem)	{			FInfoArrayPtr = totfindcounter;			//SetHandleSize(theFInfo,totfindcounter * sizeof(FInfo));			iErr = MemError();			if (iErr!=0)				genError("\pCould not expand FInfo in Filterlist");								checkHandleSize ((Handle)theFInfo,totfindcounter,sizeof(FInfo));											for (z=0;z<totfindcounter;z++)				{				iErr = FSpGetFInfo(&(*therealResults)[z],(*theFInfo)+z);			}				FInfolistInMem = true;	}		if (-(theSelFile.vRefNum)>maxVRef)	{		genError("\pYou cannot edit or view comments for ghosts");		return;	}		myType = ((*theFInfo)[index]).fdType;		iRefNum = CurResFile();			if (((*theFInfo)[index]).fdCreator == 'CARI')	{		iErr = GetFSSpecComment(theSelFile,(StringPtr)myComment);		 	if (!iErr)		 		return;		 	ParamText(myComment,0,0,0);			myDlg = GetNewDialog(1600,0L,(WindowPtr)-1);						SetPort (myDlg);		color.red = 56797;		color.green = 56797;		color.blue = 56797;		RGBBackColor(&color);			GetDItem(myDlg,3,&iType,&iHndl,&iRect);			SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);			GetDItem(myDlg,4,&iType,&iHndl,&iRect);			SetIText(iHndl,myComment);									ShowWindow(myDlg);			ModalDialog(xAlertFilter,&itemHit);			if (itemHit ==1)				{					GetDItem ( myDlg, 4, &iType, &iHndl, &iRect ); /** read data from textedit **/					GetIText ( iHndl, myComment );					if (DisplayComments)					{						SetPt(&myCellCoords,1,lCellCoords.v);						LSetCell(myComment+1,*myComment,myCellCoords,myList);					}									}			DisposDialog (myDlg);			iErr = SetFSSpecComment(theSelFile,myComment);			return;	}	switch (myType)	{	 case 'Sd2f':	 	myRefNum = FSpOpenResFile(&theSelFile,fsCurPerm);	 	if (myRefNum != -1)	 	{		 	hRsrc = Get1Resource('sdDD',1000);			if (!hRsrc)			{				hRsrc = Get1Resource('sdDD',900);				iErr = ResError();				if (iErr != 0)				{					genError("\pCan't get a comment");					CloseResFile(myRefNum);					UseResFile(iRefNum);					return;					}				DetachResource(hRsrc);				AddResource(hRsrc,'sdDD',1000,"\p");				iErr = ResError();				if (iErr != 0)				{					genError("\pCan't add a comment");					CloseResFile(myRefNum);					UseResFile(iRefNum);					return;					}			}						BlockMove((*hRsrc)+10,myComment,256L);			ParamText(myComment,0,0,0);			myDlg = GetNewDialog(1600,0L,(WindowPtr)-1);				SetPort (myDlg);			color.red = 56797;			color.green = 56797;			color.blue = 56797;			RGBBackColor(&color);			GetDItem(myDlg,3,&iType,&iHndl,&iRect);			SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);			GetDItem(myDlg,4,&iType,&iHndl,&iRect);			SetIText(iHndl,myComment);			if ((*therealResults)[(lCellCoords.v*DisplayedColumns)+lCellCoords.h*!DisplayComments].vRefNum>maxVRef)			{				HideDItem(myDlg,4);			}									ShowWindow(myDlg);			ModalDialog(xAlertFilter,&itemHit);			if (-((*therealResults)[(lCellCoords.v*DisplayedColumns)+lCellCoords.h*!DisplayComments].vRefNum)<=maxVRef)			{				if (itemHit ==1)				{					GetDItem ( myDlg, 4, &iType, &iHndl, &iRect ); /** read data from textedit **/					GetIText ( iHndl, myComment );					BlockMove(myComment,(*hRsrc)+10,*myComment+1L);						//BlockMove(myComment,*hRsrc,*myComment+1);					ChangedResource(hRsrc);					WriteResource(hRsrc);					if (DisplayComments)					{						SetPt(&myCellCoords,1,lCellCoords.v);						LSetCell(myComment+1,*myComment,myCellCoords,myList);					}									}			}			DisposDialog (myDlg);			//HUnlock(hRsrc);			ReleaseResource(hRsrc);				CloseResFile(myRefNum);			UseResFile(iRefNum);			iErr = ResError();			if (iErr!=0)				genError ("\pCan't close Resource file");		}	 break;	 	 case 'SFIL':		iErr = FSpOpenDF(&theSelFile,fsCurPerm,&refNum);		if (iErr!=0)		{			genError("\pCouldn't open file");			return;		}				iErr = SetFPos(refNum,1,764L);		inOutCount = 255L;		iErr = FSRead(refNum,&inOutCount,myComment);		//BlockMove((*hRsrc)+10,myComment,(*((*hRsrc)+10))+1L);		ParamText(myComment,0,0,0);		myDlg = GetNewDialog(1600,0L,(WindowPtr)-1);				SetPort (myDlg);	color.red = 56797;	color.green = 56797;	color.blue = 56797;	RGBBackColor(&color);		GetDItem(myDlg,3,&iType,&iHndl,&iRect);		SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);		GetDItem(myDlg,4,&iType,&iHndl,&iRect);		SetIText(iHndl,myComment);				if ((*therealResults)[(lCellCoords.v*DisplayedColumns)+lCellCoords.h*!DisplayComments].vRefNum>maxVRef)		{			HideDItem(myDlg,4);		}				ShowWindow(myDlg);		ModalDialog(xAlertFilter,&itemHit);		if (-((*therealResults)[(lCellCoords.v*DisplayedColumns)+lCellCoords.h*!DisplayComments].vRefNum)<=maxVRef)		{			if (itemHit ==1)			{				GetDItem ( myDlg, 4, &iType, &iHndl, &iRect ); /** read data from textedit **/				GetIText ( iHndl, myComment );				iErr = SetFPos(refNum,1,764L);				inOutCount = *myComment+1;				iErr = FSWrite(refNum,&inOutCount,myComment);				//BlockMove(myComment,(*hRsrc)+10,*myComment+1);					//BlockMove(myComment,*hRsrc,*myComment+1);				if (DisplayComments)				{					SetPt(&myCellCoords,1,lCellCoords.v);					LSetCell(myComment+1,*myComment,myCellCoords,myList);				}							}		}		DisposDialog (myDlg);		FSClose (refNum);		 break;	 	 case 'AIFF':		 iErr = FSpOpenDF(&theSelFile,fsCurPerm,&refNum);		if (iErr!=0)		{			genError("\pCouldn't open file");			return;		}		thePresVRef = -(theSelFile.vRefNum);		AIFFpos =  findAPPL(refNum);		if (AIFFpos)		{			iErr = SetFPos(refNum,1,AIFFpos+22L);			if (iErr!=0)				genError("\pCouldn't move file pointer");			inOutCount = 255L;			iErr = FSRead(refNum,&inOutCount,myComment);			if (iErr!=0)			{				if (iErr != -39)				{					genError("\pCouldn't read from file pointer");					iErr = FSClose(refNum);					break;				}			}		}		else		{		  *myComment = 0;		}						ParamText(myComment,0,0,0);		myDlg = GetNewDialog(1600,0L,(WindowPtr)-1);							SetPort (myDlg);	color.red = 56797;	color.green = 56797;	color.blue = 56797;	RGBBackColor(&color);		GetDItem(myDlg,3,&iType,&iHndl,&iRect);		SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);		GetDItem(myDlg,4,&iType,&iHndl,&iRect);		SetIText(iHndl,myComment);		if (thePresVRef>maxVRef)		{			HideDItem(myDlg,4);		}				ShowWindow(myDlg);		ModalDialog(xAlertFilter,&itemHit);		if (itemHit == 1)		{			GetDItem(myDlg,4,&iType,&iHndl,&iRect);			GetIText(iHndl,myComment);			DisposDialog(myDlg);			if (AIFFpos)			{					if(isItTheLastChunk(refNum, AIFFpos))				{					if(!removeCommentFromChunkEnd(refNum, AIFFpos,'APPL'))					{						genError ("\pProblem removing chunk");						iErr = FSClose(refNum);						break;					}					if (!addAIFFCommentToChunkEnd(refNum,myComment,'APPL'))					{						genError ("\pProblem adding new chunk");						iErr = FSClose(refNum);						break;					}				}				else				{					if (!zapAPPL(refNum))					{						genError ("\pProblem zapping APPL chunk");						iErr = FSClose(refNum);						break;					}					if (!addAIFFCommentToChunkEnd(refNum,myComment,'APPL'))					{						genError ("\pProblem adding new chunk");						iErr = FSClose(refNum);						break;					}					}			}			else			{				if (!addAIFFCommentToChunkEnd(refNum,myComment,'APPL'))				{					genError ("\pProblem adding new chunk");					iErr = FSClose(refNum);					break;				}			}					FSClose (refNum);				if (DisplayComments)			{				SetPt(&myCellCoords,1,lCellCoords.v);				LSetCell(myComment+1,*myComment,myCellCoords,myList);			}		}		else		{			DisposDialog(myDlg);			FSClose (refNum);		}	 break;	 	 case 'SCin': case 'MixD': case 'SCsi': case 'SCsd' : case 'SCss':	 		 	SCFormat = identifySCII(theSelFile);	 	if (SCFormat !=2)	 	{	 		genError("\pCan't Do SCI comments yet");	 		break;	 	}	 	iErr = FSpOpenDF(&theSelFile,fsCurPerm,&refNum);		if (iErr!=0)		{			genError("\pCouldn't open file");			return;		}		thePresVRef = -(theSelFile.vRefNum);		SCinpos =  findANNO(refNum);		if (SCinpos)		{			iErr = SetFPos(refNum,1,SCinpos+4L);			if (iErr!=0)				genError("\pCouldn't move file pointer");			inOutCount = 4L;			templong = 0L;			iErr = FSRead(refNum,&inOutCount,&templong);			if (iErr!=0)				genError("\pCouldn't read from file pointer");			inOutCount = templong;			if (inOutCount)			{				iErr = FSRead(refNum,&inOutCount,myComment);				if (iErr!=0)				{					genError("\pCouldn't read from file pointer");					iErr = FSClose(refNum);					break;				}			}			else			{			  *myComment = 0;			}			}		else		{		  *myComment = 0;		}					ParamText(myComment,0,0,0);		myDlg = GetNewDialog(1600,0L,(WindowPtr)-1);				SetPort (myDlg);	color.red = 56797;	color.green = 56797;	color.blue = 56797;	RGBBackColor(&color);		GetDItem(myDlg,3,&iType,&iHndl,&iRect);		SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);		GetDItem(myDlg,4,&iType,&iHndl,&iRect);		SetIText(iHndl,myComment);		if (thePresVRef>maxVRef)		{			HideDItem(myDlg,4);		}						ShowWindow(myDlg);		ModalDialog(xAlertFilter,&itemHit);		if (itemHit == 1)		{			GetDItem(myDlg,4,&iType,&iHndl,&iRect);			GetIText(iHndl,myComment);			DisposDialog (myDlg);			if (SCinpos)			{					if(isItTheLastChunk(refNum, SCinpos))				{					if(!removeCommentFromChunkEnd(refNum, SCinpos,'ANNO'))					{						genError ("\pProblem removing chunk");						iErr = FSClose(refNum);						break;					}					if (!addCommentToChunkEnd(refNum,myComment,'ANNO'))					{						genError ("\pProblem adding new chunk");						iErr = FSClose(refNum);						break;					}				}				else				{					if (!zapANNO(refNum))					{						genError ("\pProblem zapping ANNO chunk");						iErr = FSClose(refNum);						break;					}					if (!addCommentToChunkEnd(refNum,myComment,'ANNO'))					{						genError ("\pProblem adding new chunk");						iErr = FSClose(refNum);						break;					}					}			}			else			{				if (!addCommentToChunkEnd(refNum,myComment,'ANNO'))				{					genError ("\pProblem adding new chunk");					iErr = FSClose(refNum);					break;				}			}					FSClose (refNum);				if (DisplayComments)			{				SetPt(&myCellCoords,1,lCellCoords.v);				LSetCell(myComment+1,*myComment,myCellCoords,myList);			}		}		else		{			DisposDialog (myDlg);		}	 break;	 	 default:	 	iErr = GetFSSpecComment(theSelFile,(StringPtr)myComment);	 	if (!iErr)	 		return;	 	ParamText(myComment,0,0,0);		myDlg = GetNewDialog(1600,0L,(WindowPtr)-1);					SetPort (myDlg);	color.red = 56797;	color.green = 56797;	color.blue = 56797;	RGBBackColor(&color);		GetDItem(myDlg,3,&iType,&iHndl,&iRect);		SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);		GetDItem(myDlg,4,&iType,&iHndl,&iRect);		SetIText(iHndl,myComment);					ShowWindow(myDlg);		ModalDialog(xAlertFilter,&itemHit);		if (itemHit ==1)			{				GetDItem ( myDlg, 4, &iType, &iHndl, &iRect ); /** read data from textedit **/				GetIText ( iHndl, myComment );				if (DisplayComments)				{					SetPt(&myCellCoords,1,lCellCoords.v);					LSetCell(myComment+1,*myComment,myCellCoords,myList);				}							}		DisposDialog (myDlg);		iErr = SetFSSpecComment(theSelFile,myComment);	 break;	}	return;}short identifySCII(FSSpec mySpec){	short theFormat;	OSErr	iErr;	short refNum;	long inOutCount;	OSType	myChunk;		iErr = FSpOpenDF(&mySpec,fsCurPerm,&refNum);	if (iErr!=0)	{		return 1;	}	inOutCount = 4;	iErr = FSRead(refNum,&inOutCount,&myChunk);	if (myChunk!= 'FORM')	{		iErr = FSClose(refNum);		return 1;	}	else	{		iErr = FSClose(refNum);		return 2;	}	iErr = FSClose(refNum);	return 0;}Boolean SetFSSpecComment(FSSpec mySpec, Str255 theComment){	DTPBRec	myDtpbRec;	OSErr	iErr;	myDtpbRec.ioVRefNum = mySpec.vRefNum;	myDtpbRec.ioNamePtr = 0;	iErr = PBDTGetPath(&myDtpbRec);	if (iErr != 0 )	{		if (iErr == -123)		{			genError("\pCan't access comments on removeable volumes of less than 2MB");			return false;		}		//genError("\pProblem finding Desktop file");		return false;	}		myDtpbRec.ioNamePtr	= mySpec.name;	myDtpbRec.ioDTBuffer = (Ptr)theComment+1;	myDtpbRec.ioDTReqCount = *theComment;	myDtpbRec.ioDirID = mySpec.parID;		iErr = PBDTSetComment(&myDtpbRec,false);	if (iErr != 0 )	{		if (iErr == -123)		{			genError ("\pCan't access comments for removeable volumes of less than 2MB");			return;		}		genError("\pProblem setting comment in desktop file");		return false;	}	return true;}Boolean GetFSSpecComment(FSSpec mySpec, StringPtr theComment){	DTPBRec	myDtpbRec;	OSErr	iErr;	myDtpbRec.ioVRefNum = mySpec.vRefNum;	myDtpbRec.ioNamePtr = 0;	if (-(myDtpbRec.ioVRefNum)<=maxVRef)	{		iErr = PBDTGetPath(&myDtpbRec);		if (iErr != 0)		{			if (iErr == -123)				return; 							SysBeep(5);						//genError("\pProblem finding Desktop file");			return false;		}				myDtpbRec.ioNamePtr	= mySpec.name;		myDtpbRec.ioDTBuffer = (Ptr)theComment+1;		myDtpbRec.ioDirID = mySpec.parID;				iErr = PBDTGetComment(&myDtpbRec,false);		if (iErr != 0 && iErr!= -5012)		{			//genError("\pProblem getting comment in desktop file");			return false;		}				*theComment = myDtpbRec.ioDTActCount;		if (iErr == -50120)			*theComment = 0;		return true;	}	else	{		*theComment = 0;	}}/**********/Boolean isItTheLastChunk(short localRefNum, long theFPos){	OSErr	iErr;	long theChunkLen;	long inOutCount;	OSType	filpType;	iErr = SetFPos(localRefNum,1,theFPos+4L);	if(iErr!=0)	{		genError ("\pProblem getting to start of chunk");		return false;	}	inOutCount = 4;	iErr = FSRead(localRefNum,&inOutCount,&theChunkLen);	if(iErr!=0)	{		genError ("\pProblem reading chunk size");		return false;	}	iErr = SetFPos(localRefNum,3,theChunkLen);	if(iErr!=0)	{		genError ("\pProblem getting to the end of the chunk");		return false;	}	inOutCount = 1;	iErr = FSRead(localRefNum,&inOutCount,&theChunkLen);	if(iErr != eofErr)	{		return false;	}	return true;}Boolean addCommentToChunkEnd(short localRefNum, Str255 theComment, OSType theType){	OSErr	iErr;	long theFileLength;	long theChunkLen;	long inOutCount;	OSType	theChunkID = theType;			iErr = SetFPos(localRefNum,1,4L);	if(iErr!=0)	{		genError ("\pProblem getting to start of file");		return false;	}	inOutCount = 4;	iErr = FSRead(localRefNum,&inOutCount,&theFileLength);	if(iErr != 0)	{		genError ("\pCan't read FORM size");		return false;	}	iErr = SetFPos(localRefNum,2,0L);	if(iErr!=0)	{		genError ("\pProblem getting to end of file");		return false;	}	theChunkLen = (*theComment)+1;	inOutCount = 4;	iErr = FSWrite(localRefNum,&inOutCount,&theChunkID);	if(iErr != 0)	{		genError ("\pCan't write Comment chunk header");		return false;	}	inOutCount = 4;	iErr = FSWrite(localRefNum,&inOutCount,&theChunkLen);	if(iErr != 0)	{		genError ("\pCan't write Comment chunk chunk size");		return false;	}	inOutCount = theChunkLen;	iErr = FSWrite(localRefNum,&inOutCount,theComment);	if(iErr != 0)	{		genError ("\pCan't write Comment chunk Comment");		return false;	}	iErr = SetFPos(localRefNum,1,4L);	if(iErr!=0)	{		genError ("\pProblem getting back to FORM size at start of file");		return false;	}	inOutCount = 4;	theFileLength += (8 + theChunkLen);	iErr = FSWrite(localRefNum,&inOutCount,&theFileLength);	if(iErr != 0)	{		genError ("\pCan't write FORM size");		return false;	}	return true;}Boolean addAIFFCommentToChunkEnd(short localRefNum, Str255 theComment, OSType theType){	OSErr	iErr;	long theFileLength;	long theChunkLen;	long inOutCount;	OSType	theChunkID = theType;	OSType theSpecType;	Handle zzZZRes;	long filePos;		iErr = SetFPos(localRefNum,1,4L);	if(iErr!=0)	{		genError ("\pProblem getting to start of file");		return false;	}	inOutCount = 4;	iErr = FSRead(localRefNum,&inOutCount,&theFileLength);	if(iErr != 0)	{		genError ("\pCan't read FORM size");		return false;	}	iErr = SetFPos(localRefNum,2,0L);	if(iErr!=0)	{		genError ("\pProblem getting to end of file");		return false;	}		iErr = GetFPos(localRefNum,&filePos);		theChunkLen = 424;		zzZZRes = Get1Resource('zzZZ',128);	if (!zzZZRes)	{		genError ("\pCan't load zzZZ res");		return false;	}		inOutCount = theChunkLen + 8;	iErr = FSWrite(localRefNum,&inOutCount,*zzZZRes);	if(iErr != 0)	{		genError ("\pCan't write zzZZRes");		return false;	}		iErr = SetFPos(localRefNum,1,filePos +22L);	if(iErr != 0)	{		genError ("\pCan't locate to comment");		return false;	}	inOutCount = *theComment +1;	iErr = FSWrite(localRefNum,&inOutCount,theComment);	if(iErr != 0)	{		genError ("\pCan't write Comment chunk Comment");		return false;	}		iErr = SetFPos(localRefNum,1,4L);	if(iErr!=0)	{		genError ("\pProblem getting back to FORM size at start of file");		return false;	}	inOutCount = 4;	theFileLength += (8 + theChunkLen);	iErr = FSWrite(localRefNum,&inOutCount,&theFileLength);	if(iErr != 0)	{		genError ("\pCan't write FORM size");		return false;	}	return true;}Boolean removeCommentFromChunkEnd(short localRefNum, long theFPos, OSType theType){	OSErr	iErr;	long theFileLength;	long theChunkLen;	long inOutCount;	OSType	theChunkID = theType;			iErr = SetFPos(localRefNum,1,4L);	if(iErr!=0)	{		genError ("\pProblem getting to start of file");		return false;	}	inOutCount = 4;	iErr = FSRead(localRefNum,&inOutCount,&theFileLength);	if(iErr != 0)	{		genError ("\pCan't read FORM size");		return false;	}	iErr = SetFPos(localRefNum,1,theFPos+4L);	if(iErr!=0)	{		genError ("\pProblem getting to the Comment chunk");		return false;	}	inOutCount = 4;	iErr = FSRead(localRefNum,&inOutCount,&theChunkLen);	if(iErr != 0)	{		genError ("\pCan't read the Comment size");		return false;	}		iErr = SetFPos(localRefNum,1,4L);	if(iErr!=0)	{		genError ("\pProblem getting back to FORM size at start of file");		return false;	}	inOutCount = 4;	theFileLength -= (8 + theChunkLen);	iErr = FSWrite(localRefNum,&inOutCount,&theFileLength);	if(iErr != 0)	{		genError ("\pCan't write FORM size");		return false;	}		iErr = SetEOF(localRefNum,theFileLength+8);	if (iErr != 0)	{		genError ("\pProblem setting EOF size");		return false;	}	return true;}Boolean zapANNO(short localRefNum){	OSErr	iErr;	Handle	myTempStore;	long inOutCount;	long lOffset;	OSType	filpType = 'ANNO';	myTempStore = NewHandle(500);	if (!myTempStore)		return 0;	//MoveHHi(myTempStore);	iErr = SetFPos(localRefNum,1,0L);	if (iErr!=0)		return 0;	inOutCount = 490;	iErr = FSRead(localRefNum,&inOutCount,*myTempStore);	if (iErr!=0 && iErr !=eofErr)	{		DisposHandle(myTempStore);		return false;	}	lOffset = Munger(myTempStore,0,&filpType,4,nil,0);	if (lOffset >= 0)	{		iErr = SetFPos(localRefNum,1,lOffset);		inOutCount=1;		**myTempStore='z';		iErr = FSWrite(localRefNum,&inOutCount,*myTempStore);		DisposHandle(myTempStore);		return true;	}	else	{		DisposHandle(myTempStore);		return false;	}}Boolean zapAPPL(short localRefNum){	OSErr	iErr;	Handle	myTempStore;	long inOutCount;	long lOffset;	OSType	filpType = 'APPL';	myTempStore = NewHandle(500);	if (!myTempStore)		return 0;	//MoveHHi(myTempStore);	iErr = SetFPos(localRefNum,1,0L);	if (iErr!=0)		return 0;	inOutCount = 490;	iErr = FSRead(localRefNum,&inOutCount,*myTempStore);	if (iErr!=0 && iErr !=eofErr)	{		DisposHandle(myTempStore);		return false;	}	lOffset = Munger(myTempStore,0,&filpType,4,nil,0);	if (lOffset >= 0)	{				iErr = SetFPos(localRefNum,1,lOffset+1L);		/*inOutCount=1;		**myTempStore='z';		iErr = FSWrite(localRefNum,&inOutCount,*myTempStore);*/				iErr = SetFPos(localRefNum,3,7L);		inOutCount=3;		iErr = FSRead(localRefNum,&inOutCount,*myTempStore);		if (*(*myTempStore)=='S' && *((*myTempStore)+1)=='d' && *((*myTempStore)+2)=='2')		{			iErr = SetFPos(localRefNum,3,-3L);			inOutCount=1;			**myTempStore='z';			iErr = FSWrite(localRefNum,&inOutCount,*myTempStore);			iErr = SetFPos(localRefNum,1,lOffset);			inOutCount=1;			**myTempStore='z';			iErr = FSWrite(localRefNum,&inOutCount,*myTempStore);		}		DisposHandle(myTempStore);		return true;	}	else	{		DisposHandle(myTempStore);		return false;	}}