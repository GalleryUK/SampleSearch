#include "SampleSearch.h"#include "Globals.h"void mergeFile(FSSpec theMergeSource);void xmergeLists(void);void mergeLists(void){	StandardFileReply	mySFReply;	SFTypeList	myTypes;	myTypes[0] = 'SFlf';	StandardGetFile(0,1,myTypes,&mySFReply);	if (mySFReply.sfGood)	{	  	mergeFile(mySFReply.sfFile);	}}void xmergeLists(void){StandardFileReply	mySFReply;SFTypeList	myTypes;short 	myRefNum;long	myInOutCounter;Size	TempmyInOutCounter;short preservedtotfindcounter;short z;short iCnt;Handle hRsrc;short iRefNum;short preservefvolumearrayptr;OSErr	iErr;long totfindlen;preservefvolumearrayptr = fvolumearrayptr;preservedtotfindcounter = totfindcounter;myTypes[0] = 'SFlf';	StandardGetFile(0,1,myTypes,&mySFReply);	if (mySFReply.sfGood)	{	  	iErr = HOpen(mySFReply.sfFile.vRefNum,mySFReply.sfFile.parID,mySFReply.sfFile.name,2,&myRefNum);		if (!iErr)		{			totfindlen = 4L;			iErr = FSRead(myRefNum,&totfindlen,&myInOutCounter);		/** read # of FSSpec entries **/			iErr = SetFPos(myRefNum,1,myInOutCounter+4L);				/** set to FInfo entries pointer	**/			iErr = FSRead(myRefNum,&totfindlen,&TempmyInOutCounter);		/** read no of Finfo's 	**/			//SetHandleSize(theFInfo,(totfindcounter *16L) + TempmyInOutCounter*16L);			iErr = MemError();			if (iErr != 0)			{				genError("\pNot enough memory to expand list");				iErr = FSClose(myRefNum);				return;			}						iErr = SetFPos(myRefNum,1,4L);								/** set file to start of FSSpecs **/			if (totfindcounter + (myInOutCounter/70L) >= kMaxMatches)			{				TempmyInOutCounter = (kMaxMatches - totfindcounter) * 70L;				genError("\pCan not append entire new list");				iErr = FSRead(myRefNum,&TempmyInOutCounter,(*therealResults)+totfindcounter);				if (iErr!=0)					genError("\pCould not read new data");				totfindcounter += (TempmyInOutCounter/70L);			}			else			{				iErr = FSRead(myRefNum,&myInOutCounter,(*therealResults)+totfindcounter);				if (iErr!=0)					genError("\pCould not read new data");				totfindcounter += (myInOutCounter/70L);			}			/** expand (*therealResults) to fit new file add **/						iErr = SetFPos(myRefNum,1,myInOutCounter+8L);			totfindlen = (totfindcounter-preservedtotfindcounter) *16L;			/** set it to read the same no as FSSpecs **/			iErr = FSRead(myRefNum,&totfindlen,(*theFInfo)+preservedtotfindcounter);		/** read no of Finfo's 	**/			if (iErr!=0)					genError("\pCould not use read new data");			FInfoArrayPtr = totfindcounter; 			iErr = FSClose(myRefNum);						iRefNum = CurResFile();											myRefNum = HOpenResFile(mySFReply.sfFile.vRefNum,mySFReply.sfFile.parID,mySFReply.sfFile.name,fsCurPerm);			UseResFile(myRefNum);			iErr = ResError();			if (iErr!=0)					genError("\pCould not use new resource file as current");			iCnt = CountResources('oVOL');			for (z=1;z<=iCnt;z++)			{				hRsrc = Get1Resource('oVOL',z);				if (!hRsrc)					genError("\pCouldn't get 1 resource oVOL");				HLock (hRsrc);				BlockMove(*hRsrc,fvolName[fvolumearrayptr+1],28L);				HUnlock (hRsrc);				fvolumes[fvolumearrayptr+1] = -(fvolumearrayptr+1);				fvolumearrayptr ++;							}			for (z = preservedtotfindcounter;z<totfindcounter;z++)			{			//	(*therealResults)[z].vRefNum -= preservefvolumearrayptr;			(*therealResults)[z].vRefNum -= maxVRef;							}						reFound = true;			CloseResFile(myRefNum);			UseResFile(iRefNum);			resolveOVols();					}		}}