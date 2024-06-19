#include "SampleSearch.h"#include "Globals.h"extern FSSpec theApplSpec;extern long GhostsDirID;#include "undoStuff.h"OSErr cleanUpSnapshot (FSSpec theSnapshot);long countFilesOn(short driveNumber);#define SFSaveDisk 	0x00000214#define CurDirStore 0x00000398pascal	OSErr	myPBCatSearchSyncCompat(CSParamPtr paramBlock);void checkList(void);Boolean MemToFSSpec(FSSpec mySpec, Boolean justSelected, Boolean askForSpec, Boolean toFaves, Boolean toClipboard);void NewvolumeSnapshot(void){short itemHit;				/** for dialog enquiry **/DialogPtr	myDlg;			/** for dialog enquiry **/Handle	iHndl;				/** for dialog enquiry **/Rect	iRect;				/** for dialog enquiry **/short	iType;				/** for dialog enquiry **/short z;MenuHandle	hRsrc;short catIndexNo;HFileParam	pb;Str255 theNameStr;OSErr	iErr;long	theCount= 4L;long	theFInfoCount;short iRefNum;StringHandle	hString[499];HVolumeParam	Fpb;Str255	theName,theTempVol;FSSpec	theBackUpSpec;Handle vRef[499];FSSpec	theDriveSpec;short wdRefNum,theVolRef;	pascal	OSErr	PBCatSearchSyncCompat(CSParamPtr paramBlock);pascal	OSErr	myPBCatSearchSyncCompat(CSParamPtr paramBlock);		char *occur;	Str255 Cstring,substring,volumeName;short menuVRefs[99];short menuitem = 1;FInfoArrayPtr = 0;snapFileLen = 0L;gogetvolref();hRsrc = GetMenu(1010);hRsrc = (MenuHandle)GetResource('MENU',1010);for (z=1;z<=volumearrayptr;z++)			/*** set up loop to go through all registered drives **/	{		makeStr255 (volName[z], theTempVol);		doTheSlashAnalysis(theTempVol);		if (*theTempVol)		{			menuVRefs[menuitem] = volumes[z];			menuitem++;				AppendMenu(hRsrc,theTempVol);			iErr = ResError();			 BlockMove (volName[z],Cstring,28L);			  PtoCstr (Cstring);		 	 makeStr255("\pAudio CD",substring);		 	 PtoCstr (substring);		 	 occur = strstr((const char *)Cstring,(const char *)substring);		 	 if (occur)			/*if (EqualString(volName[z],"\pAudio CD 1",true,true))*/			{				DisableItem(hRsrc,z);			}		}	}	ParamText("\pSelect mounted volume to make snapshot of:",0,0,0);	myDlg = GetNewDialog(6015,0L,(WindowPtr)-1);	SetPort(myDlg);		color.red = 56797;		color.green = 56797;		color.blue =56797;		RGBBackColor(&color);	GetDItem(myDlg,3,&iType,&iHndl,&iRect);	SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);	ShowWindow(myDlg);	ModalDialog(xAlertFilter,&itemHit);	GetDItem(myDlg,5,&iType,&iHndl,&iRect);  			/** get handle etc of popup **/	iCtlValue = GetCtlValue((ControlHandle)iHndl); 	GetItem(hRsrc,iCtlValue,volumeName); 	DisposDialog (myDlg);	iErr = OpenWD(theApplSpec.vRefNum,GhostsDirID,0,&wdRefNum);		BlockMove (&GhostsDirID,(Ptr)CurDirStore,4L);	theVolRef = -(theApplSpec.vRefNum);	BlockMove (&theVolRef,(Ptr)SFSaveDisk,2L);			if (itemHit == 1)		{			StandardPutFile("\pEnter Location and Name for Snapshot",volumeName,&snapReply);			if (snapReply.sfGood)			{					if (snapReply.sfReplacing)					iErr = FSpDelete(&snapReply.sfFile);				ParamText(volumeName/*volName[iCtlValue]*/,0,0,0);				myDlg = GetNewDialog(1800,0L,(WindowPtr)-1);					SetPort (myDlg);					color.red = 56797;					color.green = 56797;					color.blue = 56797;					RGBBackColor(&color);				GetDItem(myDlg,3,&iType,&iHndl,&iRect);				SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);				ShowWindow(myDlg);				ModalDialog(xAlertFilter,&itemHit);				if (itemHit == 2)					{						DisposDialog (myDlg);						return;					}				watchcursor(true);				iErr = FSMakeFSSpec(theApplSpec.vRefNum,theApplSpec.parID,"\pSFTempBackupFile",&theBackUpSpec);				if (iErr != -43)					iErr = FSpDelete(&theBackUpSpec);				MemToFSSpec(theBackUpSpec, false, false, false,false);								//saveFSList(&theBackUpSpec);				if (snapReply.sfReplacing)					iErr = FSpDelete(&snapReply.sfFile);				iErr = FSpCreate(&snapReply.sfFile,'MgAl','SFlf',snapReply.sfScript);					if (iErr !=0)				{					genError("\pCould not create new file");					DisposDialog (myDlg);					return;				}				iErr = FSpOpenDF(&snapReply.sfFile,fsCurPerm,&snapRefNum);				if (iErr !=0)				{					genError("\pCould not open new file");					DisposDialog (myDlg);					return;				}							/* count files on disk */				Fpb.ioVFilCnt = countFilesOn(menuVRefs[iCtlValue]);		/*		*theName = 0;				Fpb.ioNamePtr = theName;				Fpb.ioVolIndex = 0;				Fpb.ioCompletion = 0;				Fpb.ioVRefNum = menuVRefs[iCtlValue]; //volumes[iCtlValue]				iErr = PBHGetVInfo((HParamBlockRec *)&Fpb,false);				if (iErr !=0)				{					genError("\pCould not get info about volume");					iErr = FSClose(snapRefNum);					DisposDialog (myDlg);					return;				}*/								if (!Fpb.ioVFilCnt)				{					genError ("\pSampleSearch cannot make a snapshot of this volume since it is not a std filing system");					iErr = FSClose(snapRefNum);					DisposDialog (myDlg);					return; 				}				SetHandleSize((Handle)theFInfo,(Fpb.ioVFilCnt+10L) * sizeof(FInfo));				iErr = MemError();				if (iErr !=0)					{						genError("\pCould not expand theFInfo - allocate more memory");						iErr = FSClose(snapRefNum);						DisposDialog (myDlg);						return;					}				SetHandleSize((Handle)therealResults,(Fpb.ioVFilCnt+10L) * sizeof(FSSpec));				iErr = MemError();				if (iErr !=0)					{						genError("\pCould not expand therealResults - allocate more memory");						iErr = FSClose(snapRefNum);						DisposDialog (myDlg);						return;					}				SetHandleSize((Handle)gTheResults,(Fpb.ioVFilCnt+10L) * sizeof(FSSpec));				iErr = MemError();				if (iErr !=0)					{						genError("\pCould not expand gTheResults - allocate more memory");						iErr = FSClose(snapRefNum);						DisposDialog (myDlg);						return;					}												NewSnapshot( menuVRefs[iCtlValue]/*volumes[iCtlValue]*/,Fpb.ioVFilCnt+5L);								theFInfoCount = snapFileLen;				 snapFileLen = snapFileLen * 70L;								iErr = SetFPos(snapRefNum,1,0L);								iErr = FSWrite(snapRefNum,&theCount,&snapFileLen);		/** write FSSPEC len **/				if (iErr !=0)				{					genError("\pCould not write FSSpec len to new file");				}								iErr = FSWrite(snapRefNum,&snapFileLen,*therealResults);	/** write FSSpec data **/				if (iErr !=0)				{					genError("\pCould not write FSSpec data to new file");				}								iErr = FSWrite(snapRefNum,&theCount,&theFInfoCount);	/** write FInfo len (not data length - * 16) **/				if (iErr !=0)				{					genError("\pCould not write FINfo len to new file");				}								theFInfoCount = theFInfoCount*sizeof(FInfo);			 					iErr = FSWrite(snapRefNum,&theFInfoCount,*theFInfo);	/** write FInfo data **/				if (iErr !=0)				{					genError("\pCould not write FInfo data to new file");				}									iErr = FSClose(snapRefNum);								gogetvolref();				iRefNum = CurResFile();					HCreateResFile(snapReply.sfFile.vRefNum,snapReply.sfFile.parID,snapReply.sfFile.name);				iErr = ResError();				if (iErr !=0)				{					genError("\pCould not create new res fork");				}				snapRefNum = HOpenResFile(snapReply.sfFile.vRefNum,snapReply.sfFile.parID,snapReply.sfFile.name,fsCurPerm);				if (snapRefNum == -1)					genError("\pCould not open new fork");				UseResFile(snapRefNum);				iErr = ResError();				if (iErr !=0)				{					genError("\pCould not use new res fork");				}				for (z=1;z<=volumearrayptr;z++)				{				//z = -(snapReply.sfFile.vRefNum);					hString[z] = (StringHandle)NewHandle(256);					//MoveHHi(hString[z]);					HLock ((Handle)hString[z]);					BlockMove(volName[z],*hString[z],28L);					AddResource((Handle)hString[z],'oVOL',z,"\pVolume Name for list");					iErr = ResError();					if (iErr !=0)					{						genError("\pCould not add new oVOL resource");					}					HUnlock ((Handle)hString[z]);					vRef[z] = NewHandle (2);					//MoveHHi(vRef[z]);					**vRef[z] = volumes[z];					AddResource(vRef[z],'oREF',z,"\pVRefNum for List");					iErr = ResError();					if (iErr!=0)					{						genError ("\pCan't add new oREF resource");					}					//myDriveSpec.vRefNum = volumes(z);					//myDriveSpec.parID = 2; /** root directory **/									}				CloseResFile(snapRefNum);				for (z=1;z<=volumearrayptr;z++)				{					ReleaseResource((Handle)hString[z]);					ReleaseResource(vRef[z]);					//DisposHandle (vRef[z]);					//DisposHandle (hString[z]);				}				DisposDialog (myDlg);				UseResFile(iRefNum);				iErr = ResError();				if (iErr !=0)				{					genError("\pCould not use new old fork");				}				watchcursor(false);				cleanUpSnapshot (snapReply.sfFile);			}					}		else		{		}		openFSList(theBackUpSpec);		checkList();		gogetvolref();		resolveOVols();iErr = FSpDelete(&theBackUpSpec);/*if (iErr != 0)	genError ("\pCan't Delete temp file");*/return;}OSErr cleanUpSnapshot (FSSpec theSnapshot);OSErr cleanUpSnapshot (FSSpec theSnapshot){	Boolean refNumUsed[400];	short refNumTranslation[400];	short txlateCount;	short z;	short refNum;	long inOutCount,myInOutCounter,filePos;	FSSpec *specData;	long numFiles;	short numGhosts;	OSErr iErr;	short highestVRef,lowestVRef;	for (z=0;z<199;z++)	{		refNumUsed[z] = false;		refNumTranslation[z] = 0;	}		iErr = FSpOpenDF(&theSnapshot,fsWrPerm,&refNum);	if (!iErr)	{		inOutCount = 4;		iErr = FSRead(refNum,&inOutCount,&myInOutCounter);		/** length of FSSpec data **/		specData = (FSSpec * )NewPtrClear (myInOutCounter);		if (specData)		{			numFiles = myInOutCounter / sizeof(FSSpec);			iErr = FSRead(refNum,&myInOutCounter,specData);			for (z=0;z<numFiles;z++)			{				short myS;				myS = ((short)(specData[z].vRefNum));				refNumUsed[-myS] = true;			}/* refNumUsed[zero] should also read false */			highestVRef = 199;			lowestVRef = 0;			txlateCount = -1;			for (z=0;z<199;z++)			{				if (refNumUsed[z])				{					if (lowestVRef == 0)					{						lowestVRef = z;					}					highestVRef = z;					if (refNumTranslation[z] == 0)					{						refNumTranslation[z] = txlateCount;						txlateCount--;					}				}			}		 /* from here we should have a table to renumber vrefs */			for (z=0;z<numFiles;z++)			{				short myS = ((short)(specData[z].vRefNum));				specData[z].vRefNum = refNumTranslation[-myS];			}			iErr = SetFPos(refNum,fsFromStart,4L);			iErr = FSWrite(refNum,&myInOutCounter,specData);			DisposPtr((Ptr)specData);			FSClose(refNum);			/* now clean up the Ovols */			if (true)			{				short snapRefNum;				short iCnt,z;				Handle hRsrc, vRsrc;				short iRefNum;				short currentRef;				short oldmaxVRef = maxVRef;				short ** theORef[200];				Handle theOVol[200];				short thisRef;				short idxRez;				short oREFCnt;				iRefNum = CurResFile();			/** preserve current resource file **/								snapRefNum = FSpOpenResFile(&theSnapshot,fsWrPerm);	/** open resource fork of specified ghost **/				if (snapRefNum)				{								UseResFile(snapRefNum);							oREFCnt = Count1Resources('oREF');					idxRez = 1;					for (z=1;z<= oREFCnt;z++)					{						short thisRef;						theORef[z] = (short **)(GetIndResource('oREF',idxRez));						theOVol[z] = GetIndResource('oVOL',idxRez);						if (theORef[z])						{							short debugDhrtl;							thisRef = (*(short *)(*(theORef[z])));							debugDhrtl = thisRef;									thisRef = (thisRef >> 8) | 0xFF00;							if (refNumTranslation[-thisRef] == 0)							{								RmveResource((Handle)theORef[z]);								RmveResource(theOVol[z]);							}							else							{								short newShort = refNumTranslation[-thisRef];								newShort = (newShort << 8) | 0x00FF;								*(short *)(*(theORef[z])) = newShort;								SetResInfo((Handle)theORef[z],idxRez,"\pVRefNum for List");								ChangedResource((Handle)theORef[z]);								WriteResource((Handle)theORef[z]);								SetResInfo(theOVol[z],idxRez,"\pVolume Name for list");								ChangedResource(theOVol[z]);								WriteResource(theOVol[z]);								idxRez++;							}						}					}					CloseResFile(snapRefNum);					UseResFile(iRefNum);				}			}		}	}}void NewSnapshot(short driveNum,long	numFiles){	short z;	Boolean sdone;	OSErr	iErr;	//	HLock((Handle)gTheResults);	snapFileLen = 0;	gPb.csParam.ioVRefNum = driveNum;		/** select relevant volume **/				gPb.csParam.ioCompletion = nil;  				/** no completion routine **/	gPb.csParam.ioNamePtr = nil;   			 		/** no volume name;  use vRefNum **/	gPb.csParam.ioMatchPtr = (*gTheResults);  			/** points to results buffer **/	gPb.csParam.ioReqMatchCount = numFiles;   	/** number of matches **/		gPb.csParam.ioSearchBits = fsSBFlAttrib;								gPb.csParam.ioSearchInfo1 = &gSpec1;   			/** points to first criteria set **/	gPb.csParam.ioSearchInfo2 = &gSpec2;  			/** points to second criteria set **/	gPb.csParam.ioSearchTime = 0;              	/** don't time out on searches **/	gPb.csParam.ioCatPosition.initialize = 0;   	/** set catalog position hint to 0  **/	gPb.csParam.ioOptBuffer = gBuffer;    			/** point to search cache  **/	gPb.csParam.ioOptBufSize  = kOptBufferSize;		/** size of search cache **/	gSpec1.hFileInfo.ioFlAttrib = 0x00;      		/** clear bit 4 to ask for files **/	gSpec2.hFileInfo.ioFlAttrib  = 0x10;  			 /** set mask for bit 4 **/																		watchcursor(TRUE);					/** display watch **/			progressCreate("\pMaking a Ghost Snapshot");			do 			{				gErr = myPBCatSearchSyncCompat((CSParam *)&gPb);	/** get some files returns error 0 (noErr) if it returns without finishing **/				sdone = (gErr == eofErr); 		/**  eofErr returned when all done **/								if ((gPb.csParam.ioActMatchCount != 0) && ((gErr == noErr) || sdone))  /** ioActMatchCount contains the number of matches for this pass  **/				{										BlockMove((*gTheResults),&(*therealResults)[snapFileLen],gPb.csParam.ioActMatchCount*70L);					snapFileLen += gPb.csParam.ioActMatchCount;				}				if (progressDisp((snapFileLen *100) / numFiles))				{				//	HUnlock((Handle)gTheResults);					return;				}								} while (!sdone); 			totfindcounter = snapFileLen;						checkHandleSize ((Handle)theFInfo,totfindcounter,sizeof(FInfo));									for (z=0;z<totfindcounter;z++)				{				iErr = FSpGetFInfo(&(*therealResults)[z],&(*theFInfo)[z]);			}						watchcursor(FALSE);				progressDispos();		//HUnlock((Handle)gTheResults);			SetHandleSize((Handle)theFInfo,2480 * sizeof(FInfo));			iErr = MemError();			if (iErr !=0)			{				genError("\pCould not expand theFInfo - allocate more memory");								return;			}								return;}		void saveForUndo (void);void saveForUndo (void){	OSErr	iErr;	FSSpec theBackUpSpec;	watchcursor(true);		iErr = FSMakeFSSpec(theApplSpec.vRefNum,theApplSpec.parID,"\pSFTempUndoFile",&theBackUpSpec);	if (iErr != -43)		iErr = FSpDelete(&theBackUpSpec);	MemToFSSpec(theBackUpSpec, false, false, false,false);	EnableItem(GetMHandle(129),1);	undoFolderSearch = folderSearch;	watchcursor(FALSE);			lastOperation = kListUndo;	backUpAudioValid = false;		return;}void loadUndoFile(void);void loadUndoFile(void){	OSErr	iErr;	FSSpec theBackUpSpec;		iErr = FSMakeFSSpec(theApplSpec.vRefNum,theApplSpec.parID,"\pSFTempUndoFile",&theBackUpSpec);	if (iErr == -43)	{		SysBeep(5);		return;	}	openFSList(theBackUpSpec);	//checkList();	//gogetvolref();	//resolveOVols();	reFound = true;	DisableItem(GetMHandle(129),1);	lastOperation = kNoUndo;	return;}pascal	OSErr	PBCatSearchSyncCompat(CSParamPtr paramBlock);/* need to provide a ptr to an FSSpec array  */long countFilesOn(short driveNumber){//	HParamBlockRec RPb; 				/** parameter block for PBCatSearch **/	CSParam RPb;  	FSSpec * theFiles;	short z;	CInfoPBRec gSpec1; 					/** search criteria, part 1 **/ 	CInfoPBRec gSpec2; 	OSErr	gErr,iErr;	short q;	FInfo fndrInfo;	char *occur;	Str255 Cstring,substring;	long numsofar = 0;	Ptr	gBuffer;	GrafPtr savePort;	Str255 driveName = "\p";	Boolean nameSearch;	Str255 myFileName = "\p";	GetPort(&savePort);			theFiles = (FSSpec *)NewPtrClear(sizeof(FSSpec) * 1000L);	if (!theFiles)	{		genError("\pCannot allocate memory for theFiles");		return false;	}	numsofar = 0;			gogetvolref();		gBuffer = NewPtr(32768L);			/** search cache  **/	if (!gBuffer)	{		genError("\pCannot allocate memory for gBuffer");		DisposPtr((Ptr)theFiles);		return false;	}		nameSearch = false;	volumearrayptr = 1;	volumes[1] = driveNumber;	q=0;	if (true)		{		for (z=1;z<=volumearrayptr;z++)			/*** set up loop to go through all registered drives **/		{		//	Spincursor(1);			if (true)			{				memset(&gSpec1,0,sizeof(CInfoPBRec));				memset(&gSpec2,0,sizeof(CInfoPBRec));								RPb.ioVRefNum = volumes[z];		/** select relevant volume **/								RPb.ioCompletion = nil;  				/** no completion routine **/				RPb.ioNamePtr = driveName;   			 		/** no volume name;  use vRefNum **/				RPb.ioMatchPtr = theFiles;  			/** points to results buffer **/				RPb.ioReqMatchCount = 900;   	/** number of matches **/														/** search for name + file or directory + file TYPE  **/														RPb.ioSearchBits = ((nameSearch) ? fsSBPartialName : 0) /*+ fsSBFlAttrib*/ + fsSBFlFndrInfo;														RPb.ioSearchInfo1 = &gSpec1;   			/** points to first criteria set **/				RPb.ioSearchInfo2 = &gSpec2;  			/** points to second criteria set **/				RPb.ioSearchTime = 0;              	/** don't time out on searches **/				RPb.ioCatPosition.initialize = 0;   	/** set catalog position hint to 0  **/				RPb.ioOptBuffer = gBuffer;    			/** point to search cache  **/				RPb.ioOptBufSize  = 32768L;		/** size of search cache **/							RPb.ioSearchInfo1->hFileInfo.ioNamePtr = myFileName;   		/** point to string to find **/				RPb.ioSearchInfo1->hFileInfo.ioFlAttrib = 0x00;      		/** clear bit 4 to ask for files **/						RPb.ioSearchInfo1->hFileInfo.ioFlFndrInfo.fdType = 0xFFFFFFFF;									RPb.ioSearchInfo1->hFileInfo.ioFlFndrInfo.fdCreator = 0;								RPb.ioSearchInfo2->hFileInfo.ioNamePtr = nil;   			/** check for mask set to nil **/				RPb.ioSearchInfo2->hFileInfo.ioFlAttrib  = 0x10;  			 /** set mask for bit 4 **/					RPb.ioSearchInfo2->hFileInfo.ioFlFndrInfo.fdType = 0;   //searchMask;  							RPb.ioSearchInfo2->hFileInfo.ioFlFndrInfo.fdCreator = 0;																RPb.ioSearchInfo2->hFileInfo.ioFlFndrInfo.fdFlags = 0x0000;					RPb.ioSearchInfo2->hFileInfo.ioFlFndrInfo.fdFldr = 0;											do				{					RPb.ioMatchPtr = theFiles;  			/** points to results buffer **/					RPb.ioReqMatchCount = 900;  					gErr = PBCatSearchSyncCompat((CSParam *)&RPb);	/** get some files returns error 0 (noErr) if it returns without finishing **/					numsofar += RPb.ioActMatchCount;				} while (gErr == 0);			}		}		q++;	}herey:		DisposPtr((Ptr)gBuffer);	DisposPtr((Ptr)theFiles);	return numsofar;}