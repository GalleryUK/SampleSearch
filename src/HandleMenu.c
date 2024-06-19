#include <Gestalt.h>#include <Movies.h>#include <QuickTimeComponents.h>#include "SampleSearch.h"#include "tabs.h"#include  "furphul_premiere.h"#include "newPremiere.h"#include "prefs.h"#include "overViews.h"#include "undoStuff.h"#include "autoReplace.h"extern newPrefsRec theNewPrefs;void cleanUpRes(void);extern FSSpec theApplSpec;FSSpec vblSpec;void SDIIReverseMany(void);void RemoveNameCharsMany(void);void SDIIAddSilenceMany(void);void setConvertDest(void);#include "Globals.h"void renameMany(void);#include "Folders.h"void PrefsPage(void);extern Handle premMen;void scriptedAddAsk(void);OSErr showSelectionSize(void);void stripComments(void);void CDImportII (void);void showCommentinWin(short mode, Cell theCell);void SaveAsTabFave(short whichList);void LoadFaves(void);OSErr SDIIOrigTimesToUserTimesMany(void);void textToComments(void);OSErr generateDatabaseText(void);void paramSort(void);void deselectIfMoreThanOneRegion(void);OSErr transferRegionsIntoProToolsMany(void);Boolean scanList(Str255	theDrive);void setBringIntoProToolsDefaults (void);extern Boolean plusMode;void readSampleSearchLog (void);Boolean divertLoadBulk;void windowUpdate(void);void eraseAllTabs(void);OSErr SDIITileRegionsIntoPTMany(void);OSErr cleanUpSnapshot (FSSpec theSnapshot);void transferProToolsManySpot(void);void playMoviesMainMany(void);void SDIIReverseMany(void);extern Boolean optionKeyHeld;void transferProToolsMany(Boolean sendRegions);extern Boolean divertIt;void selectScripted(void);void makeFaveSpecs(void);void SDIIProcessMany(void);void playIMAWAVMany(void);void IMAWAV2SDIIMany(void);void SDII2IMAWAVMany(void);OSErr SDII16To24Many(void);Boolean DrawInfoBox (FSSpec mySpec, short index);void SDIIScriptedConcat(void);pascal	OSErr	myPBCatSearchSyncCompat(CSParamPtr paramBlock);pascal	OSErr	PBCatSearchSyncCompat(CSParamPtr paramBlock);void	OMSmain(void);extern OSType  myeventFileType;    //	'APPL'extern OSType  myeventCreatorType;   //'WILD'extern unsigned long myEventID;	//kAEOpenDocumentsextern unsigned long myEventClass;  //kCoreEventClass		void RecoverSDIIMany(void);Boolean deFragMany(void);void TrashSDDDMany(void);void captureSelectionToFile(Boolean writeTemp);void selectTab(short tt);Boolean markersRegionsMany(void);void SDIItoPCRawMany(void);void SDIItoSNDMany(void);extern Boolean goingToFind;void ChangeSRInfoMany(void);void saveNewPrefs (void);void GeffenToSDIIMany(void);void AFM_MakePremiereMenus(void);void RemoveVBL(void);void ChangeFInfoMany(void);Boolean checkReference(short	indexToSpec);void appendToCommentMany(void);void PCRAWToSDIIMany(void);void mainPrint(void);void autoCropMany(void);Boolean premiereProcessMany(short plugInNum);void normaliseMany(void);void MultiGet(void);Boolean ConvertMany(void);Boolean CompositeSDII(void);void SDIIAIFF3ChToMonoMany(void);void ResolveMany(void);void SDIItoPCSampleVisionMany(void);void SDII16to8Many(void);void SDIITrimEndMany(void);void SDIIMonoToStereoMany(void);Boolean editFile(void);void topTailMany(void);void RenameScripted(void);void doRichardsThing(void);Boolean CustomRecording (void);Boolean refindItemMany(void);void OutputListToFile(void);Boolean threshProcessMany(void);Boolean exportRegionsMany(void);Boolean recordPage(void);Boolean WAVtoSDIIMany(void);void SFAddToList(void);OSErr ShowSelection(FSSpec theDoc);void deleteMany(void);void archiveMany(void);extern Boolean divertIt;extern Boolean dontQuery;void saveForUndo (void);void loadUndoFile(void);extern Boolean SkipList;void divertLoadSelect(void);void selectAllItems(void);Boolean resolvePTMany(void);extern Boolean displayTypes;void OpenManyinFinder(void);void pasteSelection(void);void OpenMany(void);void AuditionMany(short playFreq);void copySelectedToFile(void);void cutSelection(void);void updateOptions(void);void setOptionDefaults(short * myMenus);void getOptionDefaults(short * myMenus);extern short globPlay;OSType AddToFileTypesDialog(StringPtr theMenuString);void OpenInFinder(FSSpec mySpec);void archiveList(void);void zeditComment(FSSpec	theSelFile, short  index);short isPressed(unsigned short k );void ExamineSCII(FSSpec theSelFile, short selectedFile);Boolean	resolveDawn (FSSpec theSpec);extern short DispMenuCheck;extern Boolean DblBuffAudition;extern Boolean autoSustain;Boolean resolveBank (FSSpec mySpec, short index);Boolean resolveInst (FSSpec mySpec, short index);void AddToFaves(FSSpec	mySpec, short index);void prefsDialog(void);void appendNameMany(void);void AddToFileTypeMenu(void);void removeItemFromList(short index);extern FSSpec	faveFSpec, faveISpec;void SaveAsFave(void);Boolean	YesNo (Str255	myText);Boolean MemToFSSpec(FSSpec mySpec, Boolean justSelected, Boolean askForSpec, Boolean toFaves, Boolean toClipboard);extern Boolean folderSearch;void exportMovie(void);typedef struct RegionRec {long	RegionID;long	StartFrame;long	StopFrame;long	SynchFrame;long 	TimeStampMS;long 	TimeStampLS;Str31	RegionName;} RegionRec, *RegionRecPtr;Boolean SoundManagerPlaySD2 (FSSpec mySpec, short playFreq, RegionRec theRegion, Boolean playAll);Boolean CopyrightMany (void);#include "convertFormat.h"OSErr SDIIOrigTimesToUserTimesMany(void);OSErr SDIIUserTimesToOrigTimesMany(void);OSErr SDIIUserTimesToOrigTimeExchangeMany(void);void HandleMenu (long mSelect){	short 		DMmenu;	short			menuID = HiWord(mSelect);	short			menuItem = LoWord(mSelect);	RegionRec	myRecRgn;	Str255		name;	GrafPtr		savePort;	WindowPeek	frontWindow;	MenuHandle apMenu;	MenuHandle hMenu;	short markChar;	Cell	myCellCoords;	FInfo	fndrInfo;	OSErr	iErr;	StandardFileReply	mySFReply;			Str255 fdFldrMemberStr,fdFldrGroupStr;	long fdFldrMember;	long fdFldrGroup;	div_t	fdDiv;	short itemHit;				/** for dialog enquiry **/	DialogPtr	myDlg;			/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	short 	myRefNum;	long	myInOutCounter;	SFTypeList	myTypes;	long	totfindlen;	Handle	hRsrc,newCommentH;	Str255	myComment;	short	iCnt,z;	Handle hString[16];	Handle	myhString;	HFileParam	pb;	Str255	temName;	short myshort;	short iRefNum;	Point myPoint;	long theFInfoCount;	FSSpec appSpec,docSpec;	FSSpec	myAliasSpec= {0,0,"\p"};	Str255	myAliasName;	AliasHandle	aliasH;	short	 selectedFile;	FSSpec	theSelFile;	unsigned short aliasFileLength;	SFTypeList mytypeList;	StandardFileReply	reply;	Boolean modif;	Cell theCell;	short theindex;	FSSpec theBackUpSpec;	long response;				mytypeList[0] = 'APPL';	HiliteMenu(0);	divertIt = false;		theSelFile = ((*therealResults)[(lCellCoords.v*DisplayedColumns)+lCellCoords.h*!DisplayComments]);	selectedFile = (lCellCoords.v*DisplayedColumns)+lCellCoords.h*!DisplayComments;	apMenu = GetMHandle(132);	switch (menuID)	{	  case	132:  /* APPLE MENU */	  if (menuItem == 1)	  	{	  		ident();	  	}	  	  if (menuItem > 1)	    {			GetPort(&savePort);			GetItem(apMenu, menuItem, name);			OpenDeskAcc(name);			SetPort(savePort);	    }	  break;	  	  case	136: /*recording */	  switch (menuItem)		{		  case 1:		  			  	{			  	if (Gestalt(gestaltQuickTime, &response)) 				{					genError ("\pThis function requires QuickTime 1.6.1 and Sound Manager 3.0");					break;				}				iErr = EnterMovies();				if (iErr) return;				CDImportII ();				//exportMovie();				ExitMovies();			}		  break;				 case 2:		  	CustomRecording ();		  break;			  		  case 4:			normaliseMany();		  break;					case 5:			autoCropMany();			//topTailMany();		 break;				}	  break;	  	  case 138:   /* convert menu */	  	switch (menuItem)	  	{	  		case 1:	  			setConvertDest();	  		break;	  			  		case 3:				ConvertMany();  /* aiff to sd2 */	  		break;	  		case 4:	  			SDIItoAIFFMany();	  		break;	  		case 6:	  			AIFFtoQuickTimeMany();	  		break;	  		case 7:	  			QuickTimetoAIFFMany();	  		break;	  		case 9:	  			SDIItoPCRawMany();	  		break;	  		case 10:	  			SDIItoPCSampleVisionMany();	  		break;	  			  		case 12:	  			SDIItoWavMany();	  		break;	  			  		case 13:	  			WAVtoSDIIMany();	  		break;	  			  		case 15:	  			SDIIStereoToMonoMany();	  		break;	  			  		case 16:	  			SDIIMonoToStereoMany();	  		break;	  			  		case 18:	  			SDII16to8Many();	  		break;	  			  		case 19:	  			SDIIAddSilenceMany();	  		break;	  			  		case 20:	  			PCRAWToSDIIMany();	  		break;	  		case 21:	  			SDIItoSNDMany();	  		break;	  		case 23:	  			markersRegionsMany();	  		break;	  			  		case 24:	  			RecoverSDIIMany();	  		break;	  			  		case 25:	  			deFragMany();	  		break;	  			  		case 26:	  			SDIITrimEndMany();	  		break;	  			  		/*case 27:	  			AFM_MakePremiereMenus();			break;*/						case 28:				SDIIAIFF3ChToMonoMany();			break;									case 30:				SDIIReverseMany();			break;						case 32:				IMAWAV2SDIIMany();			break;						case 33:				SDII2IMAWAVMany();			break;				  		/*case 22:	  			TrashSDDDMany();	  		break;*/	  			  		case 35:	  			GeffenToSDIIMany();	  		break;			case 36:				SDII16To24Many();			break;	//	  	case 36:	//  			SDIIProcessMany(); /* new SR COnvertor */	//  		break;	  	}	  	  break;	  	  case	128:    /** file menu **/		switch (menuItem)		{		  case 1:   /** new item **/		  	totfindcounter = 0;		  	reFound = true;		  	SkipList = true;		  	folderSearch = false;			break;					  case	2:   /** open item **/		   if (true)		  	{		  		SFTypeList	myTypes;		  		StandardFileReply theReply;		  		myTypes[0] = 'SFlf';		  		StandardGetFile(0,1,myTypes,&theReply);		  		openFSList(theReply.sfFile);		  		checkList();				gogetvolref();				resolveOVols();		  	} 		  	//openList();		  	folderSearch = false;			break;  				  					  case	3:  /** close item **/			if ((frontWindow = (WindowPeek) FrontWindow()) != 0L)			{				if (!theNewPrefs.tabLocked[theNewPrefs.whichTab])					SaveAsTabFave(theNewPrefs.whichTab);				done = true;				break;			}  			if (frontWindow->windowKind < 0)			  CloseDeskAcc(frontWindow->windowKind);			break;					case 4:   /** save item **/					MemToFSSpec(myAliasSpec,false,true, false, false);						//saveList();					break;				  	  		case 6: 			AddToFileTypeMenu();		break;				case 7: 			OutputListToFile();		break;				case 8: 			scriptedAddAsk();		break;				case 11: 			mainPrint();		break;						 case 13:  /*** quit item **/		    HUnlock (volHdl);			DisposHandle (volHdl);			FSMakeFSSpec(theApplSpec.vRefNum,theApplSpec.parID,"\pSFTempUndoFile",&theBackUpSpec);			FSpDelete(&theBackUpSpec);			FSMakeFSSpec(theApplSpec.vRefNum,theApplSpec.parID,"\pSFTempBackupFile",&theBackUpSpec);				FSpDelete(&theBackUpSpec);				cleanUpRes();			//RemoveVBL();			saveNewPrefs ();			if (!theNewPrefs.tabLocked[theNewPrefs.whichTab])				SaveAsTabFave(theNewPrefs.whichTab);			ExitToShell();			break;		 }		break;	  	case	130:    /** faves menu **/		switch (menuItem)		{			case	1:				if (folderSearch)				{					genError("\pSorry, folders cannot be entered into the favourite list");					break;				}				watchcursor(true);				SetPt( &theCell, 0,0 );		/* start at top of list  */				while ( LGetSelect( TRUE, &theCell, myList) ) 				{					theindex = (theCell.v * DisplayedColumns) + (theCell.h * (DisplayedColumns != 1));					AddToFaves(((*therealResults)[theindex]), theindex);					LNextCell( TRUE, TRUE, &theCell, myList ); 	/* advance to next */				}				watchcursor(false);			break;	  				  						case	3: 				folderSearch = false;				saveForUndo();				LoadFaves();			break;							case 6: /** erase faves **/				if (YesNo ("\pAre you sure you want to erase your favourite list ?"))				{					iErr = FSpDelete(&faveFSpec);					if (iErr != 0)						genError ("\pCan't Delete FSpec file");					iErr = FSpDelete(&faveISpec);					if (iErr != 0)						genError ("\pCan't Delete ISpec file");					makeFaveSpecs();				}			break;					  		  		case 4: 	  			if (folderSearch)				{					genError("\pSorry, folders cannot be saved into the favourite list");					break;				}	  			MemToFSSpec(myAliasSpec,false,false,true, false);			break;		}		break;			  case	129:  /** edit menu **/		if (SystemEdit(menuItem-1))		{			break;		}		DMmenu = menuItem;		switch (DMmenu)		{			case 1:   /*****UNDO*****/				/*switch (lastOperation)				{					case kNoUndo:										break;										case kOverviewUndo:						if (!backUpAudioValid)							break;												// check the backup still exists 												if(!EqualString(whatTheBUAudioIsOf.name,theDisplayedFile.name,true,true)) 						{							// the undo file is not the currently displayed one 							makeStr255 ("\pThe last undo relates to the file called ",tempStr);							concatStrings(tempStr,whatTheBUAudioIsOf.name,"\p");							concatStrings(tempStr,"\pBut you are currently editing ","\p. ");							concatStrings(tempStr,theDisplayedFile.name,"\p");							concatStrings(tempStr,"\pShall I undo the operation on the old file anyway ?","\p. ");							if (!YesNo (tempStr))							{								 break;							}						}												if (!FSpExchangeFiles(&whatTheBUAudioIsOf,&theBackUpAudioFile))						{							iErr = FSpDelete(&whatTheBUAudioIsOf);						}					break;														case kListUndo:										*/											loadUndoFile();												/*BlockMove((*theUndoResults),(*therealResults),oldFindCounter*70);*/												fChanged = false;								DisableItem(GetMHandle(129),1);						reFound = true;						folderSearch = undoFolderSearch;									/*	break;					}*/							break;						case 3:				/*****save for undo*****/				saveForUndo ();				oldFindCounter = totfindcounter;																undoFolderSearch = folderSearch;					EnableItem(GetMHandle(129),1);									/** enable undo menu item **/								/***********/				watchcursor(true);							MemToFSSpec(myAliasSpec,true,false,false, true);				cutSelection();				watchcursor(false);			break;						case 4:  /**copy**/				watchcursor(true);				MemToFSSpec(myAliasSpec,true,false,false, true);								watchcursor(false);			break;						case 5:  /**paste**/				/*****save for undo*****/				oldFindCounter = totfindcounter;							/** preserve for undo **/								 saveForUndo ();					undoFolderSearch = folderSearch;					EnableItem(GetMHandle(129),1);									/** enable undo menu item **/								/***********/				watchcursor(true);				pasteSelection();						watchcursor(false);			break;						case 6:  /**clear**/				/*****save for undo*****/				oldFindCounter = totfindcounter;							/** preserve for undo **/				undoFolderSearch = folderSearch;				/***********/				watchcursor(true);				saveForUndo ();				cutSelection();				watchcursor(false);			break;			case 8:				selectAllItems();			break;			case 10:				PrefsPage();				reFound = true;			break;		}		break;			 	case 137: /** item menu **/		DMmenu = menuItem;		switch (DMmenu)		{			case 1:	/** audition. make this item auto disable, enable on file type selected **/		 			AuditionMany(globPlay);								/******/			break;							case 2:	/** launch **/					optionKeyHeld = false;					OpenMany();								/********/			break;						case 4:				renameMany();			//	RenameItem(theSelFile,selectedFile);			break;						case 5:					deleteMany();			break;						case 7:					DrawInfoBox ((*therealResults)[selectedFile], selectedFile);			break;						case 8:				editCategory();			break;						case 10:				OpenManyinFinder();			break;						case 11:				if (!folderSearch)				{					archiveList(); /* this is Copy/Move */				}				else				{					genError ("\pYou cannot archive folders");				}			break;						case 13:						{				MultiGet();			}				break;						case 14:				CopyrightMany();				break;						case 16:				appendNameMany();			break;						case 17:				appendToCommentMany();			break;						case 19:				if (Gestalt(gestaltQuickTime, &response)) 				{					genError ("\pThis function requires QuickTime");					break;				}		 		playMoviesMainMany();				//OMSmain();		 					break;						case 20:				ChangeFInfoMany();			break;						case 21:				RemoveNameCharsMany();			break;						case 22:				ChangeSRInfoMany();			break;						case 24:				refindItemMany();			break;						case 25:				RenameScripted();			break;						case 26:				replaceFilesFromFolder ();			break;						case 27:				selectScripted();			break;			case 29:				textToComments();			break;			case 30:				stripComments();			break;			case 31:				showSelectionSize();			break;		}		break;		case	133: /** LIST menu **/		DMmenu = menuItem;		switch (DMmenu)		{			case 1:				if (!theNewPrefs.tabLocked[theNewPrefs.whichTab])					SaveAsTabFave(theNewPrefs.whichTab);				done = true;				goingToFind = true;			break;						case 2:				totfindcounter = NewSearchAgain();			break;						case 4:				mergeLists();			break;						case 5:				AlphaSort();				reFound = true;			break;						case 7:				PurgeList ();				reFound = true;			break;						case 9:				generateDatabaseText();			break;		}		break;		case	134: /** view menu **/		DMmenu = menuItem;		switch (DMmenu)		{			case 1:				squashColumns = !squashColumns;				CheckItem(GetMHandle(134), 1, squashColumns);				updateOptions();			break;						case 2: /* display comments ***/				modif = false;				myshort = isPressed(0x38);		/** 3b 3a 37 **/					if(myshort)				{					DispMode = 4;					modif = true;				}									myshort = isPressed(0x3B);		/** 3b 3a 37 **/					if(myshort)				{					DispMode = 3;					modif = true;				}									myshort = isPressed(0x3A);		/** 3b 3a 37 **/					if(myshort)				{					DispMode = 2;					modif = true;				}								myshort = isPressed(0x37);		/** 3b 3a 37 **/					if(myshort)				{					DispMode = 1;					modif = true;				}										reFound = true;				if (modif == false) 				{					DispMode = DispMenuCheck;					itemHit = 1;					if ((totfindcounter > 30 && !DisplayComments && DispMode == 0) || (totfindcounter > 100 && !DisplayComments && DispMode != 0))	/** too many to display comments **/					{						//itemHit = dAlert (4567,0);					}					DisplayComments = !DisplayComments;					CheckItem(GetMHandle(134), 2, DisplayComments);					DisplayedColumns = (3 * !DisplayComments )+ 1;					updateOptions();					}			break;			case 14:				paramSort();				reFound = true;			break;			case 16:				readSampleSearchLog ();			break;			case 4:case 5:case 6:case 7:case 8:case 9:case 10: case 11:case 12:				for (z=4;z<=11;z++)				{					CheckItem(GetMHandle(134),z,false);				}								CheckItem(GetMHandle(134),DMmenu,true);				switch(DMmenu)				{					case 4:						DispMenuCheck = 0;					break;					case 5:						myshort = isPressed(0x3A);		/** 3b 3a 37 **/							if(myshort)						{							displayTypes = false;						}						else						{							displayTypes = true;						}						DispMenuCheck = 2;					break;					case 6:						DispMenuCheck = 3;					break;					case 7:						DispMenuCheck = 4;					break;					case 8:						DispMenuCheck = 5;					break;					case 9:						DispMenuCheck = 6;					break;					case 10:						DispMenuCheck = 7;					break;									case 11:						DispMenuCheck = 8;					break;					case 12:						DispMenuCheck = 9;					break;				}				if (DisplayComments)				{					reFound = true;					DispMode = DispMenuCheck;				}				if (!DisplayComments)				{					itemHit = 1;					if ((totfindcounter > 30 && !DisplayComments && DispMode == 0) || (totfindcounter > 100 && !DisplayComments && DispMode != 0))	/** too many to display comments **/					{					}						DisplayComments = !DisplayComments;						CheckItem(GetMHandle(134), 2, DisplayComments);						DisplayedColumns = (3 * !DisplayComments )+ 1;						reFound = true;						DispMode = DispMenuCheck;					}			break;		}		break;						case 139: /* tabs menu */			DMmenu = menuItem;			switch (DMmenu)			{				case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:case 10:					selectTab(DMmenu - 1);				break;								case 11:									break;								case 12:					eraseAllTabs();				break;			}		break;						case	135: /** SPECIAL menu **/			DMmenu = menuItem;			switch (DMmenu)			{			case 1:				NewvolumeSnapshot();				break;					case 3: /** divert load **/				myshort = isPressed(0x3A);							if(myshort)				{	  				StandardGetFile(0,1,mytypeList,&reply);	  				if (reply.sfGood)	  				{		  					BlockMove(&(reply.sfFile),&divertSpec,70L);						setDivertAppSpec(reply.sfFile);						iErr = FSpGetFInfo(&(reply.sfFile),&fndrInfo);		  				myhString = (Handle)GetString(998);						BlockMove(&(fndrInfo.fdCreator),(*myhString)+1,4L);						ChangedResource(myhString);						WriteResource(myhString);						divertDocCreator = fndrInfo.fdCreator;					}					windowUpdate();	  				break;	  			}	  			else	  			{					divertSamples = !divertSamples;					CheckItem(GetMHandle(135), 3, divertSamples);					updateOptions();					if (divertSamples && (divertSpec.vRefNum== 0)) /** not yet selected **/					{						genError ("\pPlease select the switch launch application");						StandardGetFile(0,1,mytypeList,&reply);						if (reply.sfGood)		  				{							BlockMove(&(reply.sfFile),&divertSpec,70L);							setDivertAppSpec(reply.sfFile);							iErr = FSpGetFInfo(&(reply.sfFile),&fndrInfo);		  					myhString = (Handle)GetString(998);							BlockMove(&(fndrInfo.fdCreator),(*myhString)+1,4L);							ChangedResource(myhString);							WriteResource(myhString);							divertDocCreator = fndrInfo.fdCreator;						}						}					if (divertSamples)						OpenSelection (divertSpec);					windowUpdate();					break;					}							case 4: /** choose divert load app **/				divertLoadSelect();				windowUpdate();			break;						case 6:				ExamineSCII(theSelFile, selectedFile);			break;						case 7:				ResolveMany();				/*if ((-(theSelFile.vRefNum)) > maxVRef)				{					genError ("\pCan't resolve a ghost");					break;				}								iErr = FSpGetFInfo(&theSelFile,&fndrInfo);				if (iErr!=0)				{					genError ("\pProblem getting info for that file");					break;				}				if (fndrInfo.fdType == 'MixD')					resolveBank (theSelFile, selectedFile);				if (fndrInfo.fdType == 'SCin' || fndrInfo.fdType == 'SCsi'|| fndrInfo.fdType == 'SCsd'|| fndrInfo.fdType == 'SCss')					resolveInst (theSelFile, selectedFile);				if (fndrInfo.fdType == 'CR02')					resolveDawn (theSelFile);*/			break;			case 8:				archiveMany();			break;			case 10:				theNewPrefs.modernDblBufferAudition = !theNewPrefs.modernDblBufferAudition;				CheckItem(GetMHandle(135), 10, theNewPrefs.modernDblBufferAudition);				updateOptions();			break;			case 11:				autoSustain = !autoSustain;				CheckItem(GetMHandle(135), 11, autoSustain);				updateOptions();			break;						case 13:				dontQuery = !dontQuery;				CheckItem(GetMHandle(135), 13, dontQuery);				updateOptions();			break;						case 15:				exportRegionsMany();			break;						case 16:				threshProcessMany();			break;						case 17:				editFile();			break;						case 18:				resolvePTMany();			break;						case 20:				CompositeSDII();			break;				case 21:				transferProToolsMany(false);				//done = true;			break;							case 22:				setBringIntoProToolsDefaults();				//done = true;			break;					case 23:				transferProToolsManySpot();			break;				case 24:				transferProToolsMany(true);			break;				case 26:				createSDIIOverviewMany();			break;						case 27:				SDIIScriptedConcat();			break;					case 28:				SDIIOrigTimesToUserTimesMany();			break;					case 29:				SDIIUserTimesToOrigTimesMany();			break;					case 30:				SDIIUserTimesToOrigTimeExchangeMany();			break;						case 32:				SDIITileRegionsIntoPTMany();			break;			case 33:				deselectIfMoreThanOneRegion();			break;		}		break;			case 10: /* premiere menu */		premiereProcessMany(menuItem);		//InvalRect(&qd.screenBits.bounds);		reFound = true;	break;	}	SetPort (myWindow);}	extern PremierePlugInPtr		pPlugIns;void AFM_MakePremiereMenus(void);Handle premMen;extern short totalPremierePlugIns;void DrawMenus (void){	Handle	mendy, plusMenu;	MenuHandle onemenu;	MenuHandle	hMenu;	short z;		AFM_MakePremiereMenus();	mendy=GetNewMBar(1000);		SetMenuBar (mendy);			apMenu = GetMHandle (130);	onemenu= GetMHandle (132);	AddResMenu (onemenu, 'DRVR');		premMen = (Handle)GetMenu(10);	for (z=0;z<totalPremierePlugIns;z++)	{			AppendMenu((MenuHandle)premMen,pPlugIns[z].filespec.name);		}	InsertMenu((MenuHandle)premMen, -1);		DrawMenuBar();	CheckItem(GetMHandle(134), 1, true);	//DisableItem((GetMHandle(130)),10);	//DisableItem((GetMHandle(130)),11);	DisableItem((undoMenuH = GetMHandle(129)),1);	//DisableItem((GetMHandle(128)),5);	//DisableItem((GetMHandle(128)),6);	CheckItem(GetMHandle(134), 4, true);		if (!plusMode)	{		plusMenu = (Handle)GetMHandle (137);		DelMenuItem((MenuHandle)plusMenu,25);		plusMenu = (Handle)GetMHandle (138);		DisableItem((MenuHandle)plusMenu,13);	}}/***********************************************************************//**** *  AdjustMenus() * *	Enable or disable the items in the Edit menu if a DA window *	comes up or goes away. Our application doesn't do anything with *	the Edit menu. * ****/void AdjustMenus(void){	register WindowPeek wp = (WindowPeek) FrontWindow();	short kind = wp ? wp->windowKind : 0;	Boolean DA = kind < 0;	}short isPressed(unsigned short k )// k =  any keyboard scan code, 0-127{	unsigned char km[16];GetKeys( ( long *) km);	return ( ( km[k>>3] >> (k & 7) ) & 1);}void OpenManyinFinder(void){	Cell theCell;	short theindex;		SetPt( &theCell, 0,0 );		/* start at top of list  */	while ( LGetSelect( TRUE, &theCell, myList) ) 	{		theindex = (theCell.v * DisplayedColumns) + (theCell.h * (DisplayedColumns != 1));		OpenInFinder(((*therealResults)[theindex]));		LNextCell( TRUE, TRUE, &theCell, myList ); 	/* advance to next */	}}void deleteMany(void){	Cell theCell;	short theindex;	short itemHit;				/** for dialog enquiry **/	DialogPtr	myDlg;			/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	myDlg = GetNewDialog(8997,0L,(WindowPtr)-1);		SetPort (myDlg);	color.red = 56797;	color.green = 56797;	color.blue = 56797;	RGBBackColor(&color);	GetDItem(myDlg,3,&iType,&iHndl,&iRect);	SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);	ShowWindow(myDlg);	ModalDialog(xAlertFilter,&itemHit);	DisposDialog(myDlg);	if (itemHit == 2)	{		watchcursor(true);		SetPt( &theCell, 0,0 );		/* start at top of list  */		while ( LGetSelect( TRUE, &theCell, myList) ) 		{			theindex = (theCell.v * DisplayedColumns) + (theCell.h * (DisplayedColumns != 1));			if (DeleteItem((*therealResults)[theindex]))				LSetSelect(false,theCell,myList);			LNextCell( TRUE, TRUE, &theCell, myList ); 	/* advance to next */		}		cutSelection();		watchcursor(false);		reFound = true;	}}void renameMany(void){	short theindex;	Cell firstSelection;	short numSelected = 0;	Cell theCell;	FInfo fndrInfo;			firstSelection.h = -1;		SetPt( &theCell, 0,0 );		/* start at top of list  */		while ( LGetSelect( TRUE, &theCell, myList) ) 		{			if (firstSelection.h == -1)			{				firstSelection = theCell;			} 			theindex = (theCell.v * DisplayedColumns) + (theCell.h * (DisplayedColumns != 1));				if (RenameItem((*therealResults)[theindex],theindex))			{				break;			}			LSetCell((*therealResults)[theindex].name+1,*(*therealResults)[theindex].name,theCell,myList);			LSetSelect(false,theCell,myList);						if (DisplayedColumns != 1)			{				LNextCell( TRUE, TRUE, &theCell, myList ); 	/* advance to next - non column view */			}			else			{				LNextCell( false, TRUE, &theCell, myList ); 	/* advance to next - column view */			}			numSelected++;						showCommentinWin(kFirstSelected,nullCell);		}				if (numSelected == 1)		{			LSetSelect(true,firstSelection,myList);		}		//reFound = true;}void OpenInFinder(FSSpec mySpec){	Str255  myTempString = "\p";	CInfoPBRec	Zpb;	DirInfo	*dZpb=(DirInfo *)&Zpb;	long theNewParent;	FSSpec	folderSpec;	OSErr	iErr;	Boolean presDiv;	short theVolRef;		BlockMove (&mySpec,&vblSpec,70L);		/*theVolRef = -(mySpec.vRefNum);	BlockMove (&theVolRef,&SFSaveDisk,2L);*/		*myTempString = 0;	dZpb->ioCompletion = 0;	dZpb->ioVRefNum = mySpec.vRefNum;	dZpb->ioNamePtr = myTempString;	dZpb->ioFDirIndex = -1;	dZpb->ioDrDirID = mySpec.parID;	iErr = PBGetCatInfo(&Zpb,false);	if (iErr!=0)		genErrorN("\pCannot get info for that file",(long)iErr);	theNewParent = dZpb->ioDrParID;	iErr = FSMakeFSSpec(mySpec.vRefNum,theNewParent,myTempString,&folderSpec);		presDiv = divertSamples;	divertSamples = false;	ShowSelection(folderSpec);	divertSamples = presDiv;	return;}void AddToFileTypeMenu(void){	StandardFileReply	reply;	OSType	theNewType;	short itemHit;				/** for dialog enquiry **/	DialogPtr	myDlg;			/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	Str255	newMenuText, newMenuType;	Handle hRsrc;	Handle hSRsrc;	Handle hString;	short iItemCnt;		/*genError ("\pSelect an example of the file type");	StandardGetFile(0,-1,0,&reply);	if (!reply.sfGood)		return;			theNewType = reply.sfType;	myDlg = GetNewDialog ( 11001, 0L,(WindowPtr)-1);			SetPort (myDlg);	color.red = 56797;	color.green = 56797;	color.blue = 56797;	RGBBackColor(&color);			ShowWindow(myDlg);	ModalDialog((ProcPtr)AlertFilter,&itemHit);	if (itemHit ==2)		return;	GetDItem ( myDlg, 3, &iType, &iHndl, &iRect );	GetIText ( iHndl, newMenuText );		DisposDialog (myDlg);	*/		theNewType = AddToFileTypesDialog((StringPtr)newMenuText);	if (!theNewType || !(*newMenuText))		return;	//hRsrc = GetIndResource('MENU',5000);		hRsrc = (Handle)GetMenu(5000);	if (!hRsrc)	{		genError ("\pCan't get resource");		return;	}	AppendMenu((MenuHandle)hRsrc,newMenuText);	ChangedResource(hRsrc);	WriteResource(hRsrc);	iItemCnt = CountMItems((MenuHandle)hRsrc);		BlockMove(&theNewType,newMenuType+1,4L);	*newMenuType = 4;	hString = (Handle)NewString(newMenuType);	AddResource(hString,'STR ',iItemCnt+999,"\pUser addition to menu");	ChangedResource(hString);	WriteResource(hString);	return;}OSType AddToFileTypesDialog(StringPtr theMenuString){	short itemHit;				/** for dialog enquiry **/	DialogPtr	myDlg;			/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Rect	iRect;				/** for dialog enquiry **/	short	iType;				/** for dialog enquiry **/	Str255 textStr;	OSType theRetType;	StandardFileReply	reply;	FInfo fndrInfo;	OSErr	iErr;	myDlg = GetNewDialog(11300,0L,(WindowPtr)-1);		SetPort (myDlg);	color.red = 56797;	color.green = 56797;	color.blue = 56797;	RGBBackColor(&color);	GetDItem(myDlg,3,&iType,&iHndl,&iRect);	SetDItem(myDlg,3,iType,(Handle)NewUserItemProc(MyItemProc),&iRect);	ShowWindow(myDlg);		do	{		ModalDialog(xAlertFilter,&itemHit);		if (itemHit == 5)		{			StandardGetFile(0,-1,0,&reply);			if (reply.sfGood)			{				iErr = FSpGetFInfo(&(reply.sfFile),&fndrInfo);				if (iErr != 0)					genError ("\pCan't get file info");				BlockMove(&(fndrInfo.fdType), textStr + 1, 4L);				*textStr = 4;				GetDItem(myDlg,4,&iType,&iHndl,&iRect);				SetIText(iHndl,textStr);			}		}	}while (itemHit == 5);		if (itemHit == 2)	{		DisposDialog(myDlg);		return 0;	}	if (itemHit == 1)	{		GetDItem(myDlg,4,&iType,&iHndl,&iRect);		GetIText(iHndl,textStr);		BlockMove (textStr +1, &theRetType,4L );		if (!(*textStr))		{			theRetType = 0;		}		GetDItem(myDlg,7,&iType,&iHndl,&iRect);		GetIText(iHndl,theMenuString);		DisposDialog(myDlg); 		return theRetType;	}			DisposDialog(myDlg);}void updateOptions(void){	short	theOptions[6];		theOptions[0] = (short)squashColumns;	theOptions[1] = (short)DisplayComments;	theOptions[2] = (short)divertSamples;	theOptions[3] = (short)DblBuffAudition;	theOptions[4] = (short)autoSustain;	theOptions[5] = (short)dontQuery;			setOptionDefaults(theOptions);}Boolean refindItem(FSSpecPtr mySpecPtr, FInfo fndrInfo);Boolean refindItem(FSSpecPtr mySpecPtr, FInfo fndrInfo){	HParamBlockRec RPb; 				/** parameter block for PBCatSearch **/	short z;	FSSpec	theResolveSpec[2];	OSErr	gErr,iErr;	short q;	short fTypes;	char *occur;	Str255 Cstring,substring;	gogetvolref();		for (z=1;z<=volumearrayptr;z++)			/*** set up loop to go through all registered drives **/	{		 BlockMove (volName[z],Cstring,*(volName[z])+1);		  PtoCstr (Cstring);		  makeStr255("\pAudio CD",substring);		  PtoCstr (substring);		  occur = strstr((const char *)Cstring,(const char *)substring);		if (!(*volName[z]))		{			occur = (Ptr)1;		}		  if (!occur)		   {		    if (!scanList(volName[z]))			{			  				RPb.csParam.ioVRefNum = volumes[z];		/** select relevant volume **/								RPb.csParam.ioCompletion = nil;  				/** no completion routine **/				RPb.csParam.ioNamePtr = nil;   			 		/** no volume name;  use vRefNum **/				RPb.csParam.ioMatchPtr = &theResolveSpec[0];  			/** points to results buffer **/				RPb.csParam.ioReqMatchCount = 1;   	/** number of matches **/														/** search for name + file or directory + file TYPE  **/				RPb.csParam.ioSearchBits = fsSBFullName + fsSBFlAttrib + fsSBFlFndrInfo;														RPb.csParam.ioSearchInfo1 = &gSpec1;   			/** points to first criteria set **/				RPb.csParam.ioSearchInfo2 = &gSpec2;  			/** points to second criteria set **/				RPb.csParam.ioSearchTime = 0;              	/** don't time out on searches **/				RPb.csParam.ioCatPosition.initialize = 0;   	/** set catalog position hint to 0  **/				RPb.csParam.ioOptBuffer = gBuffer;    			/** point to search cache  **/				RPb.csParam.ioOptBufSize  = kOptBufferSize;		/** size of search cache **/							gSpec1.hFileInfo.ioNamePtr = mySpecPtr->name;   		/** point to string to find **/				gSpec1.hFileInfo.ioFlAttrib = 0x00;      		/** clear bit 4 to ask for files **/						BlockMove (&fndrInfo,&gSpec1.hFileInfo.ioFlFndrInfo,16L);												gSpec2.hFileInfo.ioNamePtr = nil;   			/** check for mask set to nil **/				gSpec2.hFileInfo.ioFlAttrib  = 0x10;  			 /** set mask for bit 4 **/				gSpec2.hFileInfo.ioFlFndrInfo.fdType = 0xFFFFFFFF;   //searchMask;  				gSpec2.hFileInfo.ioFlFndrInfo.fdCreator = 0xFFFFFFFF;											watchcursor(TRUE);					/** display watch **/					do 					{						gErr = myPBCatSearchSyncCompat((CSParam *)&RPb);	/** get some files returns error 0 (noErr) if it returns without finishing **/							} while ( RPb.csParam.ioActMatchCount == 0 && gErr == 0);					if ( RPb.csParam.ioActMatchCount > 0)					goto herey;															/** display arrow **/		    }		  }		}			herey:	watchcursor(FALSE);	if ( RPb.csParam.ioActMatchCount == 0)	{		SysBeep(5);		return false;	}	else	{			if ( RPb.csParam.ioActMatchCount > 0)		{			BlockMove(&(theResolveSpec[0]),mySpecPtr,70L); 			return true;		}	}	return true;}Boolean refindItemMany(void){	Cell theCell;	short theindex;	watchcursor(true);	SetPt( &theCell, 0,0 );		/* start at top of list  */	while ( LGetSelect( TRUE, &theCell, myList) ) 	{		theindex = (theCell.v * DisplayedColumns) + (theCell.h * (DisplayedColumns != 1));		refindItem(&((*therealResults)[theindex]),(*theFInfo)[theindex]);		LNextCell( TRUE, TRUE, &theCell, myList ); 	/* advance to next */	}	watchcursor(false);}OSErr sendMultipleEvent(void);FSSpec theSpecs[60];short theNumberOfSpecs;Boolean isSample;void doRichardsThing(void){	Cell theCell;	short theindex;	FInfo fndrInfo;	OSType Fiyltype[3];	OSErr myErr;	short z;			numTypesToSearch = 2;	Fiyltype[0] = 'AIFF';	Fiyltype[1] = 'SFIL';	Fiyltype[2] = 'Sd2f';	isSample = false;		/******** here *********/		theNumberOfSpecs = 0;	watchcursor(true);	SetPt( &theCell, 0,0 );		/* start at top of list  */	while ( LGetSelect( TRUE, &theCell, myList) ) 	{		theindex = (theCell.v * DisplayedColumns) + (theCell.h * (DisplayedColumns != 1));		if (checkReference (theindex))		{			theSpecs[theNumberOfSpecs] = (*therealResults)[theindex];			theNumberOfSpecs ++;			FSpGetFInfo(&(*therealResults)[theindex],&fndrInfo);			for (z =0 ;z<=numTypesToSearch;z++)			{				if (fndrInfo.fdType == Fiyltype[z])				{					isSample = true;				}			}		}		LNextCell( TRUE, TRUE, &theCell, myList ); 	/* advance to next */	}	sendMultipleEvent();	watchcursor(false);}OSErr xOpenSelection(FSSpec theDoc);OSErr sendMultipleEvent(void){	AppleEvent	aeEvent;	/* the event to create*/	AEDesc	myAddressDesc;	/* descriptors for the */	AEDesc	aeDirDesc[60];	AEDesc	listElem;	AEDesc	fileList;		/*our list*/	FSSpec	dirSpec;	AliasHandle	fileAlias[60];		/* alias of the file itself*/	AliasHandle	theAliasH[60];	ProcessSerialNumber process;	/* the finder's psn*/	OSErr		myErr;				/* duh*/	FSSpec	mySpec;	FInfo	fndrInfo;	Boolean	CreatorChanged;	OSType	preserveCreator;		short z;	CInfoPBRec	pb;	StandardFileReply	reply;	short temprefNum;	OSErr	iErr;	short switchCount;	char	myChar;	long	theParID;	EventRecord	theEvent;	short itemHit;				/** for dialog enquiry **/	DialogPtr	myDlg;			/** for dialog enquiry **/	Handle	iHndl;				/** for dialog enquiry **/	Handle  myHand;	Rect	iRect;				/** for dialog enquiry **/	Rect	myRect;	short	iType;				/** for dialog enquiry **/	short p;		if ((divertSamples && isSample) || optionKeyHeld || divertIt)	{		myeventFileType = 'APPL';		myeventCreatorType = divertDocCreator;		myEventID = kAEOpenDocuments;		myEventClass = kCoreEventClass;	}	else	{		for (p = 0;p<theNumberOfSpecs;p++)		{			xOpenSelection(theSpecs[p]);		}		return;	}	if(FindAProcess(myeventFileType,myeventCreatorType,&process))	{			genError ("\pProcess not found");			return;	}	myErr = AECreateDesc(typeProcessSerialNumber,(Ptr) &process,sizeof(process), &myAddressDesc);	if(myErr)		{		genError("\pAppleEvent error");		return;	}	myErr = AECreateAppleEvent (myEventClass, myEventID,&myAddressDesc, kAutoGenerateReturnID, kAnyTransactionID,&aeEvent);	if(myErr)	{		genError("\pAppleEvent error");		return;	}	if(myErr=AECreateList(nil,0,false,&fileList))	{		genError("\pAppleEvent error");		return;	}		for (p=0;p<theNumberOfSpecs;p++)	{		NewAlias(nil,&theSpecs[p],&fileAlias[p]);			theAliasH[p] = fileAlias[p];				HLock((Handle)theAliasH[p]);			AECreateDesc(typeAlias, (Ptr) *theAliasH[p], GetHandleSize((Handle) theAliasH[p]), &aeDirDesc[p]);		HUnlock((Handle)theAliasH[p]);				myErr = AEPutDesc (&fileList, 1+p, &aeDirDesc[p]);		}	if(myErr = AEPutParamDesc(&aeEvent,keyDirectObject,&fileList))			return myErr;		myErr = AEDisposeDesc(&fileList);  /* ????? */	myErr = AESend(&aeEvent, nil,kAENoReply+kAEAlwaysInteract+kAECanSwitchLayer,kAEHighPriority, kAEDefaultTimeout, nil, nil);	AEDisposeDesc(&aeEvent);}