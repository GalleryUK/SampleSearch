/*	*** THIS FILE GENERATED AUTOMATICALLY -- DO NOT MODIFY ***	Copyright �1994-95 Opcode Systems, Inc.*/#if USESROUTINEDESCRIPTORSenum {	uppOMSNModalProcInfo = kPascalStackBased					| RESULT_SIZE(0)							/* pascal void          */					| STACK_ROUTINE_PARAMETER(1, kFourByteCode)	/* EventRecord *evt     */};typedef UniversalProcPtr OMSNModalProcUPP;#define NewOMSNModalProc(userRoutine)	\		(OMSNModalProcUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppOMSNModalProcInfo, GetCurrentISA())#define CallOMSNModalProc(userRoutine, evt)	\		CallUniversalProc((UniversalProcPtr)(userRoutine), uppOMSNModalProcInfo, (evt))#elsetypedef OMSNModalProc OMSNModalProcUPP;#define NewOMSNModalProc(userRoutine)	\		(OMSNModalProcUPP)(userRoutine)#define CallOMSNModalProc(userRoutine, evt)	\		(*(userRoutine))((evt))#endif#if USESROUTINEDESCRIPTORSenum {	uppOMSNameMenuChangeProcInfo = kPascalStackBased					| RESULT_SIZE(0)							/* pascal void          */					| STACK_ROUTINE_PARAMETER(1, kFourByteCode)	/* OMSNameMenu menu     */					| STACK_ROUTINE_PARAMETER(2, kFourByteCode)	/* long refCon          */					| STACK_ROUTINE_PARAMETER(3, kTwoByteCode)	/* short newChoice      */};typedef UniversalProcPtr OMSNameMenuChangeProcUPP;#define NewOMSNameMenuChangeProc(userRoutine)	\		(OMSNameMenuChangeProcUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppOMSNameMenuChangeProcInfo, GetCurrentISA())#define CallOMSNameMenuChangeProc(userRoutine, menu, refCon, newChoice)	\		CallUniversalProc((UniversalProcPtr)(userRoutine), uppOMSNameMenuChangeProcInfo, (menu), (refCon), (newChoice))#elsetypedef OMSNameMenuChangeProc OMSNameMenuChangeProcUPP;#define NewOMSNameMenuChangeProc(userRoutine)	\		(OMSNameMenuChangeProcUPP)(userRoutine)#define CallOMSNameMenuChangeProc(userRoutine, menu, refCon, newChoice)	\		(*(userRoutine))((menu), (refCon), (newChoice))#endif