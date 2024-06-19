#include <Sound.h>#include <StandardFile.h>#include <Files.h>#include <stdlib.h>#include <string.h>#include <AppleEvents.h>#include <Aliases.h>#include <Processes.h>#include <stdio.h>#define kTotalSize	20000#define kAsync	true#define	kQuietNow	true#define	defScreenWid	550#define kFinderSig	'FNDR'#define kAEFinderEvents	'FNDR'#define kSystemType	'MACS'#define kAEOpenSelection	'sope'#define keySelection	'fsel'#define listFont	geneva //systemFont#define listFontHeight	14 //16#define listFontSize	9  //12#define haveAUX() 0#define Demomode false#define demolimit	2#define kMaxMatches 2475           /** find up to n matches **/#define kOptBufferSize 16384    	/** use a 16k search cache for speed **//********************************* Function Prototypes **************************/pascal Boolean AlertFilter (DialogPtr theDialog, EventRecord *theEvent,short *itemHit);void concatStrings(StringPtr sourceA,StringPtr sourceB,Str255 theSeperator);void genErrorN(Str255 myText,long Errno);void getConvertDest(void);Boolean getSDIIData (FSSpec mySpec, long* theRate, short* theWordSize, Boolean* stereo, long* theBytes);Boolean	YesNo (Str255	myText);short isPressed(unsigned short k );Boolean addFileToList(FSSpec mySpec);void checkList(void);void makeStr255(Str255 theString, StringPtr thePtr);short dAlert(short dnum,Ptr theFilt);void ShowPath (FSSpec mySpec, Point myPoint);void genError(Str255	myErrStr);Boolean checkReference(short);OSErr FindAProcess(OSType, OSType, ProcessSerialNumber*);OSErr OpenSelection(FSSpec theDoc);void gogetoldrefs(FSSpec myFSSpec, Boolean appendList);void FindAll(long,short);short NewSearchAgain(void);void DoIt(HFileInfo *pb, long myDrDir);void volumeSnapshot(void);void editComment(void);void AlphaSort(void);void zipitup(void);void Audition(FSSpec mySpec, short playFreq);void bringToDesk(FSSpec mySpec);void watchcursor(Boolean seting);			/** function display watch / arrow **/void SetupForFirstTime(void);				/** initialise search variables   **/Boolean getsearchstring(Boolean);					/** dialog for find ? **/void DrawList(void);						/** draw file list **/void searcher(void);						/** search through catalog **/void InitStuff(void);						/** init toolbox **/void gogetvolref(void);						/** make list of mounted volumes for search **/void handleEvents(void);					/** handle list drawn by DrawList **/void LaunchAnApplication (FSSpec	mySpec);void DoError (OSErr myErr);short AddGhosts(void);pascal void MyItemProc(WindowPtr theDlg,short theItem); short PopDialog(void);pascal short xDlgHook(short item,DialogPtr theDlg,Ptr userData);pascal void MyItemProc(WindowPtr theDlg,short theItem);void DrawMenus(void);void plsound(void);void HandleMenu (long mSelect);void PathNameFromDirID(long dirID, short vRefNum, StringPtr fullPathName);void pstrcat(StringPtr dst, StringPtr src);void pstrinsert(StringPtr dst, StringPtr src);void AdjustMenus(void);short SearchAgain(void);void configPopup(void);void ident(void);pascal short  cmp1stChar( Byte *cellPtr, Byte *testPtr, short cellLen,short testLen );void mergeLists(void);void resolveOVols(void);FSSpec	getAppSpec(void);OSErr DoLaunch(FSSpec	*appspec, FSSpec	*filspec);void openList(void);void saveList(void);void editCategory (void);void resolveOVols(void);void allocateHandles(void);void removefvolume(short thefVol);void NewvolumeSnapshot(void);void NewSnapshot(short driveNum,long	numFiles);OSErr RenameItem(FSSpec theDoc, short theselected);OSErr DeleteItem(FSSpec theDoc);void PurgeList(void);void MakeAliasOnDesk(FSSpecPtr	mySpec, short indy);long findFILP(short localRefNum);void ExamineSCII(FSSpec theSelFile, short theIndex);short FgetVRefNum(Str255);void DialogList(FSSpec theSelFile);void genErrorN(Str255 myText,long Errno);void burnData(FSSpec theSelFile,short myUpdated);void burnSData(FSSpec theSelFile,short myUpdated);short openPrefFile(void);FSSpec	getDivertAppSpec(void);void setDivertAppSpec(FSSpec	theDAppSpec);Boolean progressDisp(short percentFull);void progressCreate(Str255	theText);void progressDispos(void);void writeLog(Ptr theLogTextPtr);void writeLogS(Str255 theLogText);void saveFSList(FSSpec mySpec);void openFSList(FSSpec mySpec);void checkHandleSize (Handle theHandle,long arraySize,long cellSize);void doTheSlashAnalysis(StringPtr theTempVol);//void myLSetCell(Ptr theData, short dataLength, Cell theCell, ListHandle myList);