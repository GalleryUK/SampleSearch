/*Create new file and resforkifSave entire memory contents or selected out to fileSave just FSSpecs of selected or entire to Ffile, Save just FInfo's of selected or entire to FfileSave current oREFs,Save current OVOlsadd selected to Ffile\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/open existing file and resforkLoad entire memory contentsLoad just FSSpecs, Load just FInfosLoad oREFs,Load and resolve OVolsMerge in new FSSpecs and FInfos and oVOLS and oREFS and resolve.*/OSErr renameTabAuto(short tabNum, Str31 theName);#include "SampleSearch.h"#include "Globals.h"#include "prefs.h"extern newPrefsRec theNewPrefs;extern FSSpec theApplSpec;Boolean MemToFSSpec(FSSpec mySpec, Boolean justSelected, Boolean askForSpec, Boolean toFaves, Boolean toClipboard);Boolean MemToFSSpec(FSSpec mySpec, Boolean justSelected, Boolean askForSpec, Boolean toFaves, Boolean toClipboard){	short z,x;	short refNum,iRefNum;	StandardFileReply	theReply;	short selectedCounter;	Cell theCell;	short theindex;	long inOutCount,numberOfEntries, currentPos;	Handle	volumeName[499],volumeRef[499];	extern FSSpec	faveFSpec, faveISpec;	OSErr	iErr;	OSType theType = 'SFlf';		if 	(!FInfolistInMem)	/** make FINfo array if necessary */	{		FInfoArrayPtr = totfindcounter;		iErr = MemError();		if (iErr != 0)			genError("\pCan't resize theFInfo in save list");						checkHandleSize ((Handle)theFInfo,totfindcounter,sizeof(FInfo));					for (z=0;z<totfindcounter;z++)			{			iErr = FSpGetFInfo(&(*therealResults)[z],(*theFInfo)+z);		}			FInfolistInMem = true;	}		if (askForSpec)	/** query filename **/	{		StandardPutFile("\pEnter name for file","\pSampleFinderFile",&theReply);		if (!theReply.sfGood)		{			return false;		}		if (theReply.sfReplacing)		{			iErr = FSpDelete(&theReply.sfFile);			if (iErr!=0)			{				genError ("\pCould not overwrite file");				return false;			}		}		BlockMove (&theReply.sfFile,&mySpec,70L);				renameTabAuto(theNewPrefs.whichTab, mySpec.name);	}		if (toClipboard)	{		iErr = FSMakeFSSpec(theApplSpec.vRefNum,theApplSpec.parID,"\pSFClipboard",&mySpec);		iErr = FSpDelete(&mySpec);		theType = 'SFcb';	}		if (!toFaves)	 /** normal save not faves list **/	{				iErr = FSpCreate(&mySpec,'MgAl',theType,0);		if (iErr!=0)		{			genError ("\pCan't create new file");			return false;		}				iErr = FSpOpenDF(&mySpec,fsWrPerm,&refNum);		if (iErr!=0)		{			genError ("\pCan't open the new file");			return false;		}				if (justSelected)	/** just save highlightes items **/		{			numberOfEntries = 0L;			inOutCount = 4L;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}						SetPt( &theCell, 0,0 );		/* start at top of list  */			while ( LGetSelect( TRUE, &theCell, myList) ) 			{				if (theCell.h == 1 && DisplayedColumns == 1)				{					LNextCell( TRUE, TRUE, &theCell, myList );					break;				}				theindex = (theCell.v * DisplayedColumns) + (theCell.h * (DisplayedColumns != 1));				inOutCount = 70L;				iErr = FSWrite(refNum,&inOutCount,&((*therealResults)[theindex]));				if (iErr!=0)				{					genError ("\pProblem writing data to file");					return false;				}				numberOfEntries ++;				LNextCell( TRUE, TRUE, &theCell, myList ); 	/* advance to next */			}						iErr = GetFPos(refNum,&currentPos);			iErr = SetFPos(refNum,1,0L);			inOutCount = 4L;			numberOfEntries = numberOfEntries*70L;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}						iErr = SetFPos(refNum,1,currentPos);			numberOfEntries = 0L;			inOutCount = 4L;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}			SetPt( &theCell, 0,0 );		/* start at top of list  */			while ( LGetSelect( TRUE, &theCell, myList) ) 			{				if (theCell.h == 1 && DisplayedColumns == 1)				{					LNextCell( TRUE, TRUE, &theCell, myList );					break;				}				theindex = (theCell.v * DisplayedColumns) + (theCell.h * (DisplayedColumns != 1));				inOutCount = 16L;				iErr = FSWrite(refNum,&inOutCount,&((*theFInfo)[theindex]));				if (iErr!=0)				{					genError ("\pProblem writing data to file");					return false;				}				numberOfEntries ++;				LNextCell( TRUE, TRUE, &theCell, myList ); 	/* advance to next */			}				iErr = SetFPos(refNum,1,currentPos);			inOutCount = 4L;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}		}		else   /** if save all **/		{			inOutCount = 4L;			numberOfEntries = totfindcounter * 70L;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}			inOutCount = totfindcounter * 70L;			iErr = FSWrite(refNum,&inOutCount,*therealResults);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}			inOutCount = 4L;			numberOfEntries = totfindcounter;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}			inOutCount = totfindcounter * 16L;			iErr = FSWrite(refNum,&inOutCount,*theFInfo);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}			}		FSClose (refNum);		FSpCreateResFile(&mySpec,'MgAl',theType,0);	/** add OVOLS and OREFS**/		iRefNum = CurResFile();		refNum = FSpOpenResFile(&mySpec,fsCurPerm);		if (!refNum)		{			genError ("\pProblem opening resource fork");			return false;		}		for (z=1; z<=volumearrayptr;z++)	/** mounted vols **/		{			volumeName[z] = NewHandle(63);			if (!volumeName[z])			{				genError ("\pMemory Allocation Failed");				UseResFile(iRefNum);				return false;			}			volumeRef[z] = NewHandle(2);			if (!volumeRef[z])			{				genError ("\pMemory Allocation Failed");				UseResFile(iRefNum);				return false;			}			BlockMove (volName[z],*(volumeName[z]),28L);						AddResource(volumeName[z],'oVOL',z,"\pVolume Name");			iErr = ResError();			if (iErr != 0)			{				genError ("\pCan't create resource");				UseResFile(iRefNum);				return false;			}			**(volumeRef[z]) = volumes[z];			AddResource(volumeRef[z] ,'oREF',z,"\pVRefNum reference");			iErr = ResError();			if (iErr != 0)			{				genError ("\pCan't create resource");				UseResFile(iRefNum);				return false;			}		}/** ghost vols **/		for (z=volumearrayptr+1; z<=fvolumearrayptr;z++)			{			volumeName[z] = NewHandle(63);			if (!volumeName[z])			{				genError ("\pMemory Allocation Failed");				UseResFile(iRefNum);				return false;			}			volumeRef[z] = NewHandle(2);			if (!volumeRef[z])			{				genError ("\pMemory Allocation Failed");				return false;			}			BlockMove (fvolName[z],*(volumeName[z]),28L);			AddResource(volumeName[z],'oVOL',z,"\pVolume Name");			iErr = ResError();			if (iErr != 0)			{				genError ("\pCan't create resource");				UseResFile(iRefNum);				return false;			}			**(volumeRef[z]) = fvolumes[z];			AddResource(volumeRef[z] ,'oREF',z,"\pVRefNum reference");			iErr = ResError();			if (iErr != 0)			{				genError ("\pCan't create resource");				UseResFile(iRefNum);				return false;			}		}		CloseResFile(refNum);		UseResFile(iRefNum);	/*	for (z=1;z<=fvolumearrayptr;z++)		{			ReleaseResource(volumeRef[z]);			//DisposHandle (volumeRef[z]);							ReleaseResource(volumeName[z]);			//DisposHandle (volumeName[z]);		}*/	}	else	/** to faves files **/	{		iErr = FSpDelete(&faveFSpec);		iErr = FSpCreate(&faveFSpec,'MgAl','SFfl',0);		if (iErr!=0)		{			genError ("\pCan't create new faves file");			return false;		}		iErr = FSpOpenDF(&faveFSpec,fsWrPerm,&refNum);		if (iErr!=0)		{			genError ("\pCan't open the new file");			return false;		}				if (justSelected)		{			numberOfEntries = 0L;			inOutCount = 4L;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}						SetPt( &theCell, 0,0 );		/* start at top of list  */			while ( LGetSelect( TRUE, &theCell, myList) ) 			{				if (theCell.h == 1 && DisplayedColumns == 1)				{					LNextCell( TRUE, TRUE, &theCell, myList );					break;				}				theindex = (theCell.v * DisplayedColumns) + (theCell.h * (DisplayedColumns != 1));				inOutCount = 70L;				iErr = FSWrite(refNum,&inOutCount,&((*therealResults)[theindex]));				if (iErr!=0)				{					genError ("\pProblem writing data to file");					return false;				}				numberOfEntries ++;				LNextCell( TRUE, TRUE, &theCell, myList ); 	/* advance to next */			}						iErr = SetFPos(refNum,1,0L);			inOutCount = 4L;			numberOfEntries = numberOfEntries*70L;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}		}		else   /** if save all **/		{			inOutCount = 4L;			numberOfEntries = totfindcounter * 70L;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}			inOutCount = totfindcounter * 70L;			iErr = FSWrite(refNum,&inOutCount,*therealResults);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}		}		FSClose (refNum);		/*******************/		iErr = FSpDelete(&faveISpec);		iErr = FSpCreate(&faveISpec,'MgAl','SFfl',0);		if (iErr!=0)		{			genError ("\pCan't create new faves file");			return false;		}		iErr = FSpOpenDF(&faveISpec,fsCurPerm,&refNum);		if (iErr!=0)		{			genError ("\pCan't open the new file");			return false;		}				if (justSelected)		{			numberOfEntries = 0L;			inOutCount = 4L;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}						SetPt( &theCell, 0,0 );		/* start at top of list  */			while ( LGetSelect( TRUE, &theCell, myList) ) 			{				if (theCell.h == 1 && DisplayedColumns == 1)				{					LNextCell( TRUE, TRUE, &theCell, myList );					break;				}				theindex = (theCell.v * DisplayedColumns) + (theCell.h * (DisplayedColumns != 1));				inOutCount = 16L;				iErr = FSWrite(refNum,&inOutCount,&((*theFInfo)[theindex]));				if (iErr!=0)				{					genError ("\pProblem writing data to file");					return false;				}				numberOfEntries ++;				LNextCell( TRUE, TRUE, &theCell, myList ); 	/* advance to next */			}						iErr = SetFPos(refNum,1,0L);			inOutCount = 4L;			numberOfEntries = numberOfEntries;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}		}		else   /** if save all **/		{			inOutCount = 4L;			numberOfEntries = totfindcounter;			iErr = FSWrite(refNum,&inOutCount,&numberOfEntries);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}			inOutCount = totfindcounter * 16L;			iErr = FSWrite(refNum,&inOutCount,*theFInfo);			if (iErr!=0)			{				genError ("\pProblem writing data to file");				return false;			}		}		FSClose (refNum);	/*********************************************************************/			FSpCreateResFile(&faveFSpec,'MgAl','SFfl',0);		iRefNum =CurResFile();		refNum = FSpOpenResFile(&faveFSpec,fsCurPerm);		if (!refNum)		{			genError ("\pProblem opening resource fork");			return false;		}		for (z=1; z<=volumearrayptr;z++)		{			volumeName[z] = NewHandle(63);			if (!volumeName[z])			{				genError ("\pMemory Allocation Failed");				UseResFile(iRefNum);				return false;			}			volumeRef[z] = NewHandle(2);			if (!volumeRef[z])			{				genError ("\pMemory Allocation Failed");				UseResFile(iRefNum);				return false;			}			BlockMove (volName[z],*(volumeName[z]),28L);			**(volumeRef[z]) = volumes[z];			AddResource(volumeName[z],'oVOL',z,"\pVolume Name");			iErr = ResError();			if (iErr != 0)			{				genError ("\pCan't create resource");				UseResFile(iRefNum);				return false;			}			AddResource(volumeRef[z] ,'oREF',z,"\pVRefNum reference");			iErr = ResError();			if (iErr != 0)			{				genError ("\pCan't create resource");				UseResFile(iRefNum);				return false;			}		}		for (z=volumearrayptr+1; z<=fvolumearrayptr;z++)		{			volumeName[z] = NewHandle(63);			if (!volumeName[z])			{				genError ("\pMemory Allocation Failed");				UseResFile(iRefNum);				return false;			}			volumeRef[z] = NewHandle(2);			if (!volumeRef[z])			{				genError ("\pMemory Allocation Failed");				UseResFile(iRefNum);				return false;			}			BlockMove (fvolName[z],*(volumeName[z]),28L);			**(volumeRef[z]) = fvolumes[z];			AddResource(volumeName[z],'oVOL',z,"\pVolume Name");			iErr = ResError();			if (iErr != 0)			{				genError ("\pCan't create resource");				UseResFile(iRefNum);				return false;			}			AddResource(volumeRef[z] ,'oREF',z,"\pVRefNum reference");			iErr = ResError();			if (iErr != 0)			{				genError ("\pCan't create resource");				UseResFile(iRefNum);				return false;			}		}		CloseResFile(refNum);		UseResFile(iRefNum);		for (z=1;z<=fvolumearrayptr;z++)		{			ReleaseResource(volumeRef[z]);			//DisposHandle (volumeRef[z]);							ReleaseResource(volumeRef[z]);			//DisposHandle (volumeName[z]);		}	}}	