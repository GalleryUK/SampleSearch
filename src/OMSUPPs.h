/*	*** THIS FILE GENERATED AUTOMATICALLY -- DO NOT MODIFY ***	Copyright �1994-95 Opcode Systems, Inc.*/#if USESROUTINEDESCRIPTORSenum {	uppOMSAsyncCompletionInfo = kPascalStackBased					| RESULT_SIZE(0)							/* pascal void          */					| STACK_ROUTINE_PARAMETER(1, kFourByteCode)	/* OMSAsyncWriteReq *req */};typedef UniversalProcPtr OMSAsyncCompletionUPP;#define NewOMSAsyncCompletion(userRoutine)	\		(OMSAsyncCompletionUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppOMSAsyncCompletionInfo, GetCurrentISA())#define CallOMSAsyncCompletion(userRoutine, req)	\		CallUniversalProc((UniversalProcPtr)(userRoutine), uppOMSAsyncCompletionInfo, (req))#elsetypedef OMSAsyncCompletion OMSAsyncCompletionUPP;#define NewOMSAsyncCompletion(userRoutine)	\		(OMSAsyncCompletionUPP)(userRoutine)#define CallOMSAsyncCompletion(userRoutine, req)	\		(*(userRoutine))((req))#endif#if USESROUTINEDESCRIPTORSenum {	uppOMSAppHookInfo = kPascalStackBased					| RESULT_SIZE(0)							/* pascal void          */					| STACK_ROUTINE_PARAMETER(1, kFourByteCode)	/* OMSAppHookMsg *packet */					| STACK_ROUTINE_PARAMETER(2, kFourByteCode)	/* long appHookRefCon   */};typedef UniversalProcPtr OMSAppHookUPP;#define NewOMSAppHook(userRoutine)	\		(OMSAppHookUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppOMSAppHookInfo, GetCurrentISA())#define CallOMSAppHook(userRoutine, packet, appHookRefCon)	\		CallUniversalProc((UniversalProcPtr)(userRoutine), uppOMSAppHookInfo, (packet), (appHookRefCon))#elsetypedef OMSAppHook OMSAppHookUPP;#define NewOMSAppHook(userRoutine)	\		(OMSAppHookUPP)(userRoutine)#define CallOMSAppHook(userRoutine, packet, appHookRefCon)	\		(*(userRoutine))((packet), (appHookRefCon))#endif#if USESROUTINEDESCRIPTORSenum {	uppOMSReadHookInfo = kPascalStackBased					| RESULT_SIZE(0)							/* pascal void          */					| STACK_ROUTINE_PARAMETER(1, kFourByteCode)	/* OMSPacket *packet    */					| STACK_ROUTINE_PARAMETER(2, kFourByteCode)	/* long readHookRefCon  */};typedef UniversalProcPtr OMSReadHookUPP;#define NewOMSReadHook(userRoutine)	\		(OMSReadHookUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppOMSReadHookInfo, GetCurrentISA())#define CallOMSReadHook(userRoutine, packet, readHookRefCon)	\		CallUniversalProc((UniversalProcPtr)(userRoutine), uppOMSReadHookInfo, (packet), (readHookRefCon))#elsetypedef OMSReadHook OMSReadHookUPP;#define NewOMSReadHook(userRoutine)	\		(OMSReadHookUPP)(userRoutine)#define CallOMSReadHook(userRoutine, packet, readHookRefCon)	\		(*(userRoutine))((packet), (readHookRefCon))#endif#if USESROUTINEDESCRIPTORSenum {	uppOMSReadHook2Info = kPascalStackBased					| RESULT_SIZE(0)							/* pascal void          */					| STACK_ROUTINE_PARAMETER(1, kFourByteCode)	/* OMSMIDIPacket *packet */					| STACK_ROUTINE_PARAMETER(2, kFourByteCode)	/* long readHookRefCon  */};typedef UniversalProcPtr OMSReadHook2UPP;#define NewOMSReadHook2(userRoutine)	\		(OMSReadHook2UPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppOMSReadHook2Info, GetCurrentISA())#define CallOMSReadHook2(userRoutine, packet, readHookRefCon)	\		CallUniversalProc((UniversalProcPtr)(userRoutine), uppOMSReadHook2Info, (packet), (readHookRefCon))#elsetypedef OMSReadHook2 OMSReadHook2UPP;#define NewOMSReadHook2(userRoutine)	\		(OMSReadHook2UPP)(userRoutine)#define CallOMSReadHook2(userRoutine, packet, readHookRefCon)	\		(*(userRoutine))((packet), (readHookRefCon))#endif#if USESROUTINEDESCRIPTORSenum {	uppOMSNodeFilterProcInfo = kPascalStackBased					| RESULT_SIZE(kOneByteCode)					/* pascal OMSBool       */					| STACK_ROUTINE_PARAMETER(1, kFourByteCode)	/* OMSNodeInfoRec *info */};typedef UniversalProcPtr OMSNodeFilterProcUPP;#define NewOMSNodeFilterProc(userRoutine)	\		(OMSNodeFilterProcUPP)NewRoutineDescriptor((ProcPtr)(userRoutine), uppOMSNodeFilterProcInfo, GetCurrentISA())#define CallOMSNodeFilterProc(userRoutine, info)	\		(OMSBool)CallUniversalProc((UniversalProcPtr)(userRoutine), uppOMSNodeFilterProcInfo, (info))#elsetypedef OMSNodeFilterProc OMSNodeFilterProcUPP;#define NewOMSNodeFilterProc(userRoutine)	\		(OMSNodeFilterProcUPP)(userRoutine)#define CallOMSNodeFilterProc(userRoutine, info)	\		(*(userRoutine))((info))#endif