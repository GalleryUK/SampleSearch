#include "SampleSearch.h"#include "Globals.h"short identifySCII(FSSpec mySpec);extern Boolean DblBuffAudition;void SDIPlay(FSSpec mySpec, short playFreq);void SDIIPlay(FSSpec mySpec, short playFreq);void AIFFtoSnd(FSSpec mySpec,short playFreq);void Audition(FSSpec mySpec, short playFreq);Boolean pleaseStop(void);#define kNoSCIIData -5typedef struct resolveRec {Str27	driveName;long	dirID;Str31	fileName;OSType	type;Boolean	found;} resRec, *resRecPtr;OSErr  getNumOfEntries (FSSpec	mySpec);void	getSCIIfile(FSSpec	mySpec,short	index,resRecPtr myRec);Boolean rRectoFSSpec(resRecPtr myResRecPtr, FSSpecPtr mySpecPtr);extern short arrowPressed;void SC2InstPlay(FSSpec mySpec);void SC2InstPlay(FSSpec mySpec){		FInfo ** myInstanceTypeH;	FSSpec ** myInstanceH;	Ptr	myInstancePtr;	Ptr	myInstanceTypePtr;	resRecPtr	 nullRec;	resRec myTempRec;	long inst,samp,instTot,sampTot;	long	memSize, memtypeSize;	short 	arrayPointer = 0;	StandardFileReply	reply;	OSErr  iErr;	short	itemHit, refNum;	FInfo	fndrInfo;	long	fileLength;	long inOutCount;	FSSpec	myTempSpec;	short iRefNum, myRefNum;	short z;	Handle hString;	short dispFar;	short dispFarSeg;	FSSpec	myPSpec;	FSSpec	myInstSpec;	Str31	theDefName;	Str31	resText = "\p resolved";				if (-(mySpec.vRefNum) > (maxVRef))	{		genError("\pCan't audition a ghost instrument");		return;	}	if (identifySCII(mySpec) != 2)	{		return;	}	instTot = 1;	myInstanceH = (FSSpec **)NewHandle(70L);				/** make mem **/	memSize = 70L;	if (!myInstanceH)	{		genError ("\pNot enough memory to allocate Handle");		return;	}	myInstanceTypeH = (FInfo **)NewHandle(16L);				/** make mem **/	memtypeSize = 16L;	if (!myInstanceTypeH)	{		genError ("\pNot enough memory to allocate type Handle");		DisposHandle((Handle)myInstanceH);		return;	}		progressCreate("\pAuditioning Instrument");		inst = 1;	   				myTempRec.found = 1;	BlockMove (volName[-(mySpec.vRefNum)],myTempRec.driveName,26L);	myTempRec.dirID = mySpec.parID;	BlockMove (mySpec.name,myTempRec.fileName,32L);		iErr = FSpGetFInfo(&mySpec,&fndrInfo);	myTempRec.type = fndrInfo.fdType; 	iErr = rRectoFSSpec(&myTempRec, &myTempSpec);	/** make it into an FSSpec **/	if (!iErr && (myTempSpec.vRefNum == 0))	{		long theLast;		 FlashMenuBar(0);		 	Delay(10,(unsigned long *)&theLast);		 FlashMenuBar(0);		// SysBeep(5);	}	else	{		memSize += 70L;						SetHandleSize((Handle)myInstanceH, memSize);		iErr = MemError();		if (iErr!=0)		{			genError ("\pNot enough memory to resize pointer");			DisposHandle((Handle)myInstanceH);			DisposHandle((Handle)myInstanceTypeH);			progressDispos();			return;		}		memtypeSize += 16L;						SetHandleSize((Handle)myInstanceTypeH, memtypeSize);		iErr = MemError();		if (iErr!=0)		{			genError ("\pNot enough memory to resize type pointer");			DisposHandle((Handle)myInstanceH);			DisposHandle((Handle)myInstanceTypeH);			progressDispos();			return;		}		iErr = FSpGetFInfo(&myTempSpec,&fndrInfo);		if (iErr!=0)		{			genError("\pProblem getting FInfo");			progressDispos();			DisposHandle((Handle)myInstanceH);			DisposHandle((Handle)myInstanceTypeH);			return;		}			sampTot = getNumOfEntries (myTempSpec);			/** find out how many samples it has **/				if (sampTot == kNoSCIIData)		{			progressDispos();			DisposHandle((Handle)myInstanceH);			DisposHandle((Handle)myInstanceTypeH);			genError ("\pCant Resolve SampleCell I files, only SampleCell II files");			return;		}					memSize += (long)(70L*(long)(sampTot+1));						SetHandleSize((Handle)myInstanceH,memSize);		iErr = MemError();		if (iErr!=0)		{			DisposHandle((Handle)myInstanceH);			DisposHandle((Handle)myInstanceTypeH);			progressDispos();			genError ("\pNot enough memory to resize pointer");			return;		}					memtypeSize += (long)(16L*(long)(sampTot+1));						SetHandleSize((Handle)myInstanceTypeH,memtypeSize);		iErr = MemError();		if (iErr!=0)		{			DisposHandle((Handle)myInstanceH);			DisposHandle((Handle)myInstanceTypeH);			genError ("\pNot enough memory to resize type pointer");			progressDispos();			return;		}			dispFar = 0;		dispFarSeg = 105;		if (progressDisp(dispFar))		{			DisposHandle((Handle)myInstanceH);			DisposHandle((Handle)myInstanceTypeH);			return;		}		BlockMove (&myTempSpec,&myInstSpec,70L);		if (!sampTot)		{			progressDispos();			DisposHandle((Handle)myInstanceH);			DisposHandle((Handle)myInstanceTypeH);			return;		}		for (samp = 0;samp < sampTot;samp ++)		{			if(progressDisp(samp*100 / sampTot))			{				DisposHandle((Handle)myInstanceH);				DisposHandle((Handle)myInstanceTypeH);				return;			}			getSCIIfile(myInstSpec,samp, &myTempRec);		/** get a name from inst **/			if (!(myTempRec.found))			{				genError ("\pA problem occurred getting a sample name");				progressDispos();				DisposHandle((Handle)myInstanceH);				DisposHandle((Handle)myInstanceTypeH);				return;			}			iErr = rRectoFSSpec(&myTempRec, &myTempSpec);	/** make it into an FSSpec **/			if (!iErr && (myTempSpec.vRefNum == -999))			{				progressDispos();				DisposHandle((Handle)myInstanceH);				DisposHandle((Handle)myInstanceTypeH);				return;			}			if (!iErr && (myTempSpec.vRefNum == 0))			{				SysBeep(5);			}			if (iErr && !pleaseStop())			{							Audition(myTempSpec, 0x3C);			}					}	}	progressDispos();	DisposHandle((Handle)myInstanceH);	DisposHandle((Handle)myInstanceTypeH);}