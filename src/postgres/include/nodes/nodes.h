/*-------------------------------------------------------------------------
 *
 * nodes.h
 *	  Definitions for tagged nodes.
 *
 *
 * Portions Copyright (c) 1996-2022, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/nodes/nodes.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef NODES_H
#define NODES_H

/*
 * The first field of every node is NodeTag. Each node created (with makeNode)
 * will have one of the following tags as the value of its first field.
 *
 * Note that inserting or deleting node types changes the numbers of other
 * node types later in the list.  This is no problem during development, since
 * the node numbers are never stored on disk.  But don't do it in a released
 * branch, because that would represent an ABI break for extensions.
 */
typedef enum NodeTag
{
	T_Invalid = 0,

	/*
	 * TAGS FOR EXECUTOR NODES (execnodes.h)
	 */
	T_IndexInfo,
	T_ExprContext,
	T_ProjectionInfo,
	T_JunkFilter,
	T_OnConflictSetState,
	T_MergeActionState,
	T_ResultRelInfo,
	T_EState,
	T_TupleTableSlot,

	/*
	 * TAGS FOR PLAN NODES (plannodes.h)
	 */
	T_Plan,
	T_Result,
	T_ProjectSet,
	T_ModifyTable,
	T_Append,
	T_MergeAppend,
	T_RecursiveUnion,
	T_BitmapAnd,
	T_BitmapOr,
	T_Scan,
	T_SeqScan,
	T_SampleScan,
	T_IndexScan,
	T_IndexOnlyScan,
	T_BitmapIndexScan,
	T_BitmapHeapScan,
	T_TidScan,
	T_TidRangeScan,
	T_SubqueryScan,
	T_FunctionScan,
	T_ValuesScan,
	T_TableFuncScan,
	T_CteScan,
	T_NamedTuplestoreScan,
	T_WorkTableScan,
	T_ForeignScan,
	T_CustomScan,
	T_Join,
	T_NestLoop,
	T_MergeJoin,
	T_HashJoin,
	T_Material,
	T_Memoize,
	T_Sort,
	T_IncrementalSort,
	T_Group,
	T_Agg,
	T_WindowAgg,
	T_Unique,
	T_Gather,
	T_GatherMerge,
	T_Hash,
	T_SetOp,
	T_LockRows,
	T_Limit,
	/* these aren't subclasses of Plan: */
	T_NestLoopParam,
	T_PlanRowMark,
	T_PartitionPruneInfo,
	T_PartitionedRelPruneInfo,
	T_PartitionPruneStepOp,
	T_PartitionPruneStepCombine,
	T_PlanInvalItem,

	/*
	 * TAGS FOR PLAN STATE NODES (execnodes.h)
	 *
	 * These should correspond one-to-one with Plan node types.
	 */
	T_PlanState,
	T_ResultState,
	T_ProjectSetState,
	T_ModifyTableState,
	T_AppendState,
	T_MergeAppendState,
	T_RecursiveUnionState,
	T_BitmapAndState,
	T_BitmapOrState,
	T_ScanState,
	T_SeqScanState,
	T_SampleScanState,
	T_IndexScanState,
	T_IndexOnlyScanState,
	T_BitmapIndexScanState,
	T_BitmapHeapScanState,
	T_TidScanState,
	T_TidRangeScanState,
	T_SubqueryScanState,
	T_FunctionScanState,
	T_TableFuncScanState,
	T_ValuesScanState,
	T_CteScanState,
	T_NamedTuplestoreScanState,
	T_WorkTableScanState,
	T_ForeignScanState,
	T_CustomScanState,
	T_JoinState,
	T_NestLoopState,
	T_MergeJoinState,
	T_HashJoinState,
	T_MaterialState,
	T_MemoizeState,
	T_SortState,
	T_IncrementalSortState,
	T_GroupState,
	T_AggState,
	T_WindowAggState,
	T_UniqueState,
	T_GatherState,
	T_GatherMergeState,
	T_HashState,
	T_SetOpState,
	T_LockRowsState,
	T_LimitState,

	/*
	 * TAGS FOR PRIMITIVE NODES (primnodes.h)
	 */
	T_Alias,
	T_RangeVar,
	T_TableFunc,
	T_Var,
	T_Const,
	T_Param,
	T_Aggref,
	T_GroupingFunc,
	T_WindowFunc,
	T_SubscriptingRef,
	T_FuncExpr,
	T_NamedArgExpr,
	T_OpExpr,
	T_DistinctExpr,
	T_NullIfExpr,
	T_ScalarArrayOpExpr,
	T_BoolExpr,
	T_SubLink,
	T_SubPlan,
	T_AlternativeSubPlan,
	T_FieldSelect,
	T_FieldStore,
	T_RelabelType,
	T_CoerceViaIO,
	T_ArrayCoerceExpr,
	T_ConvertRowtypeExpr,
	T_CollateExpr,
	T_CaseExpr,
	T_CaseWhen,
	T_CaseTestExpr,
	T_ArrayExpr,
	T_RowExpr,
	T_RowCompareExpr,
	T_CoalesceExpr,
	T_MinMaxExpr,
	T_SQLValueFunction,
	T_XmlExpr,
	T_NullTest,
	T_BooleanTest,
	T_CoerceToDomain,
	T_CoerceToDomainValue,
	T_SetToDefault,
	T_CurrentOfExpr,
	T_NextValueExpr,
	T_InferenceElem,
	T_TargetEntry,
	T_RangeTblRef,
	T_JoinExpr,
	T_FromExpr,
	T_OnConflictExpr,
	T_IntoClause,

	/*
	 * TAGS FOR EXPRESSION STATE NODES (execnodes.h)
	 *
	 * ExprState represents the evaluation state for a whole expression tree.
	 * Most Expr-based plan nodes do not have a corresponding expression state
	 * node, they're fully handled within execExpr* - but sometimes the state
	 * needs to be shared with other parts of the executor, as for example
	 * with SubPlanState, which nodeSubplan.c has to modify.
	 */
	T_ExprState,
	T_WindowFuncExprState,
	T_SetExprState,
	T_SubPlanState,
	T_DomainConstraintState,

	/*
	 * TAGS FOR PLANNER NODES (pathnodes.h)
	 */
	T_PlannerInfo,
	T_PlannerGlobal,
	T_RelOptInfo,
	T_IndexOptInfo,
	T_ForeignKeyOptInfo,
	T_ParamPathInfo,
	T_Path,
	T_IndexPath,
	T_BitmapHeapPath,
	T_BitmapAndPath,
	T_BitmapOrPath,
	T_TidPath,
	T_TidRangePath,
	T_SubqueryScanPath,
	T_ForeignPath,
	T_CustomPath,
	T_NestPath,
	T_MergePath,
	T_HashPath,
	T_AppendPath,
	T_MergeAppendPath,
	T_GroupResultPath,
	T_MaterialPath,
	T_MemoizePath,
	T_UniquePath,
	T_GatherPath,
	T_GatherMergePath,
	T_ProjectionPath,
	T_ProjectSetPath,
	T_SortPath,
	T_IncrementalSortPath,
	T_GroupPath,
	T_UpperUniquePath,
	T_AggPath,
	T_GroupingSetsPath,
	T_MinMaxAggPath,
	T_WindowAggPath,
	T_SetOpPath,
	T_RecursiveUnionPath,
	T_LockRowsPath,
	T_ModifyTablePath,
	T_LimitPath,
	/* these aren't subclasses of Path: */
	T_EquivalenceClass,
	T_EquivalenceMember,
	T_PathKey,
	T_PathKeyInfo,
	T_PathTarget,
	T_RestrictInfo,
	T_IndexClause,
	T_PlaceHolderVar,
	T_SpecialJoinInfo,
	T_AppendRelInfo,
	T_RowIdentityVarInfo,
	T_PlaceHolderInfo,
	T_MinMaxAggInfo,
	T_PlannerParamItem,
	T_RollupData,
	T_GroupingSetData,
	T_StatisticExtInfo,
	T_MergeAction,

	/*
	 * TAGS FOR MEMORY NODES (memnodes.h)
	 */
	T_AllocSetContext,
	T_SlabContext,
	T_GenerationContext,

	/*
	 * TAGS FOR VALUE NODES (value.h)
	 */
	T_Integer,
	T_Float,
	T_Boolean,
	T_String,
	T_BitString,

	/*
	 * TAGS FOR LIST NODES (pg_list.h)
	 */
	T_List,
	T_IntList,
	T_OidList,

	/*
	 * TAGS FOR EXTENSIBLE NODES (extensible.h)
	 */
	T_ExtensibleNode,

	/*
	 * TAGS FOR STATEMENT NODES (mostly in parsenodes.h)
	 */
	T_RawStmt,
	T_Query,
	T_PlannedStmt,
	T_InsertStmt,
	T_DeleteStmt,
	T_UpdateStmt,
	T_MergeStmt,
	T_SelectStmt,
	T_ReturnStmt,
	T_PLAssignStmt,
	T_AlterTableStmt,
	T_AlterTableCmd,
	T_AlterDomainStmt,
	T_SetOperationStmt,
	T_GrantStmt,
	T_GrantRoleStmt,
	T_AlterDefaultPrivilegesStmt,
	T_ClosePortalStmt,
	T_ClusterStmt,
	T_CopyStmt,
	T_CreateStmt,
	T_DefineStmt,
	T_DropStmt,
	T_TruncateStmt,
	T_CommentStmt,
	T_FetchStmt,
	T_IndexStmt,
	T_CreateFunctionStmt,
	T_AlterFunctionStmt,
	T_DoStmt,
	T_RenameStmt,
	T_RuleStmt,
	T_NotifyStmt,
	T_ListenStmt,
	T_UnlistenStmt,
	T_TransactionStmt,
	T_ViewStmt,
	T_LoadStmt,
	T_CreateDomainStmt,
	T_CreatedbStmt,
	T_DropdbStmt,
	T_VacuumStmt,
	T_ExplainStmt,
	T_CreateTableAsStmt,
	T_CreateSeqStmt,
	T_AlterSeqStmt,
	T_VariableSetStmt,
	T_VariableShowStmt,
	T_DiscardStmt,
	T_CreateTrigStmt,
	T_CreatePLangStmt,
	T_CreateRoleStmt,
	T_AlterRoleStmt,
	T_DropRoleStmt,
	T_LockStmt,
	T_ConstraintsSetStmt,
	T_ReindexStmt,
	T_CheckPointStmt,
	T_CreateSchemaStmt,
	T_AlterDatabaseStmt,
	T_AlterDatabaseRefreshCollStmt,
	T_AlterDatabaseSetStmt,
	T_AlterRoleSetStmt,
	T_CreateConversionStmt,
	T_CreateCastStmt,
	T_CreateOpClassStmt,
	T_CreateOpFamilyStmt,
	T_AlterOpFamilyStmt,
	T_PrepareStmt,
	T_ExecuteStmt,
	T_DeallocateStmt,
	T_DeclareCursorStmt,
	T_CreateTableSpaceStmt,
	T_DropTableSpaceStmt,
	T_AlterObjectDependsStmt,
	T_AlterObjectSchemaStmt,
	T_AlterOwnerStmt,
	T_AlterOperatorStmt,
	T_AlterTypeStmt,
	T_DropOwnedStmt,
	T_ReassignOwnedStmt,
	T_CompositeTypeStmt,
	T_CreateEnumStmt,
	T_CreateRangeStmt,
	T_AlterEnumStmt,
	T_AlterTSDictionaryStmt,
	T_AlterTSConfigurationStmt,
	T_CreateFdwStmt,
	T_AlterFdwStmt,
	T_CreateForeignServerStmt,
	T_AlterForeignServerStmt,
	T_CreateUserMappingStmt,
	T_AlterUserMappingStmt,
	T_DropUserMappingStmt,
	T_AlterTableSpaceOptionsStmt,
	T_AlterTableMoveAllStmt,
	T_SecLabelStmt,
	T_CreateForeignTableStmt,
	T_ImportForeignSchemaStmt,
	T_CreateExtensionStmt,
	T_AlterExtensionStmt,
	T_AlterExtensionContentsStmt,
	T_CreateEventTrigStmt,
	T_AlterEventTrigStmt,
	T_RefreshMatViewStmt,
	T_ReplicaIdentityStmt,
	T_AlterSystemStmt,
	T_CreatePolicyStmt,
	T_AlterPolicyStmt,
	T_CreateTransformStmt,
	T_CreateAmStmt,
	T_CreatePublicationStmt,
	T_AlterPublicationStmt,
	T_CreateSubscriptionStmt,
	T_AlterSubscriptionStmt,
	T_DropSubscriptionStmt,
	T_CreateStatsStmt,
	T_AlterCollationStmt,
	T_CallStmt,
	T_AlterStatsStmt,

	/*
	 * TAGS FOR PARSE TREE NODES (parsenodes.h)
	 */
	T_A_Expr,
	T_ColumnRef,
	T_ParamRef,
	T_A_Const,
	T_FuncCall,
	T_A_Star,
	T_A_Indices,
	T_A_Indirection,
	T_A_ArrayExpr,
	T_ResTarget,
	T_MultiAssignRef,
	T_TypeCast,
	T_CollateClause,
	T_SortBy,
	T_WindowDef,
	T_RangeSubselect,
	T_RangeFunction,
	T_RangeTableSample,
	T_RangeTableFunc,
	T_RangeTableFuncCol,
	T_TypeName,
	T_ColumnDef,
	T_IndexElem,
	T_StatsElem,
	T_Constraint,
	T_DefElem,
	T_RangeTblEntry,
	T_RangeTblFunction,
	T_TableSampleClause,
	T_WithCheckOption,
	T_SortGroupClause,
	T_GroupingSet,
	T_WindowClause,
	T_ObjectWithArgs,
	T_AccessPriv,
	T_CreateOpClassItem,
	T_TableLikeClause,
	T_FunctionParameter,
	T_LockingClause,
	T_RowMarkClause,
	T_XmlSerialize,
	T_WithClause,
	T_InferClause,
	T_OnConflictClause,
	T_CTESearchClause,
	T_CTECycleClause,
	T_CommonTableExpr,
	T_MergeWhenClause,
	T_RoleSpec,
	T_TriggerTransition,
	T_PartitionElem,
	T_PartitionSpec,
	T_PartitionBoundSpec,
	T_PartitionRangeDatum,
	T_PartitionCmd,
	T_VacuumRelation,
	T_PublicationObjSpec,
	T_PublicationTable,

	/*
	 * TAGS FOR REPLICATION GRAMMAR PARSE NODES (replnodes.h)
	 */
	T_IdentifySystemCmd,
	T_BaseBackupCmd,
	T_CreateReplicationSlotCmd,
	T_DropReplicationSlotCmd,
	T_ReadReplicationSlotCmd,
	T_StartReplicationCmd,
	T_TimeLineHistoryCmd,

	/*
	 * TAGS FOR RANDOM OTHER STUFF
	 *
	 * These are objects that aren't part of parse/plan/execute node tree
	 * structures, but we give them NodeTags anyway for identification
	 * purposes (usually because they are involved in APIs where we want to
	 * pass multiple object types through the same pointer).
	 */
	T_TriggerData,				/* in commands/trigger.h */
	T_EventTriggerData,			/* in commands/event_trigger.h */
	T_ReturnSetInfo,			/* in nodes/execnodes.h */
	T_WindowObjectData,			/* private in nodeWindowAgg.c */
	T_TIDBitmap,				/* in nodes/tidbitmap.h */
	T_InlineCodeBlock,			/* in nodes/parsenodes.h */
	T_FdwRoutine,				/* in foreign/fdwapi.h */
	T_IndexAmRoutine,			/* in access/amapi.h */
	T_TableAmRoutine,			/* in access/tableam.h */
	T_TsmRoutine,				/* in access/tsmapi.h */
	T_ForeignKeyCacheInfo,		/* in utils/rel.h */
	T_CallContext,				/* in nodes/parsenodes.h */
	T_SupportRequestSimplify,	/* in nodes/supportnodes.h */
	T_SupportRequestSelectivity,	/* in nodes/supportnodes.h */
	T_SupportRequestCost,		/* in nodes/supportnodes.h */
	T_SupportRequestRows,		/* in nodes/supportnodes.h */
	T_SupportRequestIndexCondition, /* in nodes/supportnodes.h */
	T_SupportRequestWFuncMonotonic	/* in nodes/supportnodes.h */
} NodeTag;

#define nodeCase(c) case c: return #c

static inline char *tag_to_string(enum NodeTag tag)
{
    switch (tag) {
        nodeCase(T_Invalid);
        nodeCase(T_IndexInfo);
        nodeCase(T_ExprContext);
        nodeCase(T_ProjectionInfo);
        nodeCase(T_JunkFilter);
        nodeCase(T_OnConflictSetState);
        nodeCase(T_MergeActionState);
        nodeCase(T_ResultRelInfo);
        nodeCase(T_EState);
        nodeCase(T_TupleTableSlot);
        nodeCase(T_Plan);
        nodeCase(T_Result);
        nodeCase(T_ProjectSet);
        nodeCase(T_ModifyTable);
        nodeCase(T_Append);
        nodeCase(T_MergeAppend);
        nodeCase(T_RecursiveUnion);
        nodeCase(T_BitmapAnd);
        nodeCase(T_BitmapOr);
        nodeCase(T_Scan);
        nodeCase(T_SeqScan);
        nodeCase(T_SampleScan);
        nodeCase(T_IndexScan);
        nodeCase(T_IndexOnlyScan);
        nodeCase(T_BitmapIndexScan);
        nodeCase(T_BitmapHeapScan);
        nodeCase(T_TidScan);
        nodeCase(T_TidRangeScan);
        nodeCase(T_SubqueryScan);
        nodeCase(T_FunctionScan);
        nodeCase(T_ValuesScan);
        nodeCase(T_TableFuncScan);
        nodeCase(T_CteScan);
        nodeCase(T_NamedTuplestoreScan);
        nodeCase(T_WorkTableScan);
        nodeCase(T_ForeignScan);
        nodeCase(T_CustomScan);
        nodeCase(T_Join);
        nodeCase(T_NestLoop);
        nodeCase(T_MergeJoin);
        nodeCase(T_HashJoin);
        nodeCase(T_Material);
        nodeCase(T_Memoize);
        nodeCase(T_Sort);
        nodeCase(T_IncrementalSort);
        nodeCase(T_Group);
        nodeCase(T_Agg);
        nodeCase(T_WindowAgg);
        nodeCase(T_Unique);
        nodeCase(T_Gather);
        nodeCase(T_GatherMerge);
        nodeCase(T_Hash);
        nodeCase(T_SetOp);
        nodeCase(T_LockRows);
        nodeCase(T_Limit);
        nodeCase(T_NestLoopParam);
        nodeCase(T_PlanRowMark);
        nodeCase(T_PartitionPruneInfo);
        nodeCase(T_PartitionedRelPruneInfo);
        nodeCase(T_PartitionPruneStepOp);
        nodeCase(T_PartitionPruneStepCombine);
        nodeCase(T_PlanInvalItem);
        nodeCase(T_PlanState);
        nodeCase(T_ResultState);
        nodeCase(T_ProjectSetState);
        nodeCase(T_ModifyTableState);
        nodeCase(T_AppendState);
        nodeCase(T_MergeAppendState);
        nodeCase(T_RecursiveUnionState);
        nodeCase(T_BitmapAndState);
        nodeCase(T_BitmapOrState);
        nodeCase(T_ScanState);
        nodeCase(T_SeqScanState);
        nodeCase(T_SampleScanState);
        nodeCase(T_IndexScanState);
        nodeCase(T_IndexOnlyScanState);
        nodeCase(T_BitmapIndexScanState);
        nodeCase(T_BitmapHeapScanState);
        nodeCase(T_TidScanState);
        nodeCase(T_TidRangeScanState);
        nodeCase(T_SubqueryScanState);
        nodeCase(T_FunctionScanState);
        nodeCase(T_TableFuncScanState);
        nodeCase(T_ValuesScanState);
        nodeCase(T_CteScanState);
        nodeCase(T_NamedTuplestoreScanState);
        nodeCase(T_WorkTableScanState);
        nodeCase(T_ForeignScanState);
        nodeCase(T_CustomScanState);
        nodeCase(T_JoinState);
        nodeCase(T_NestLoopState);
        nodeCase(T_MergeJoinState);
        nodeCase(T_HashJoinState);
        nodeCase(T_MaterialState);
        nodeCase(T_MemoizeState);
        nodeCase(T_SortState);
        nodeCase(T_IncrementalSortState);
        nodeCase(T_GroupState);
        nodeCase(T_AggState);
        nodeCase(T_WindowAggState);
        nodeCase(T_UniqueState);
        nodeCase(T_GatherState);
        nodeCase(T_GatherMergeState);
        nodeCase(T_HashState);
        nodeCase(T_SetOpState);
        nodeCase(T_LockRowsState);
        nodeCase(T_LimitState);
        nodeCase(T_Alias);
        nodeCase(T_RangeVar);
        nodeCase(T_TableFunc);
        nodeCase(T_Var);
        nodeCase(T_Const);
        nodeCase(T_Param);
        nodeCase(T_Aggref);
        nodeCase(T_GroupingFunc);
        nodeCase(T_WindowFunc);
        nodeCase(T_SubscriptingRef);
        nodeCase(T_FuncExpr);
        nodeCase(T_NamedArgExpr);
        nodeCase(T_OpExpr);
        nodeCase(T_DistinctExpr);
        nodeCase(T_NullIfExpr);
        nodeCase(T_ScalarArrayOpExpr);
        nodeCase(T_BoolExpr);
        nodeCase(T_SubLink);
        nodeCase(T_SubPlan);
        nodeCase(T_AlternativeSubPlan);
        nodeCase(T_FieldSelect);
        nodeCase(T_FieldStore);
        nodeCase(T_RelabelType);
        nodeCase(T_CoerceViaIO);
        nodeCase(T_ArrayCoerceExpr);
        nodeCase(T_ConvertRowtypeExpr);
        nodeCase(T_CollateExpr);
        nodeCase(T_CaseExpr);
        nodeCase(T_CaseWhen);
        nodeCase(T_CaseTestExpr);
        nodeCase(T_ArrayExpr);
        nodeCase(T_RowExpr);
        nodeCase(T_RowCompareExpr);
        nodeCase(T_CoalesceExpr);
        nodeCase(T_MinMaxExpr);
        nodeCase(T_SQLValueFunction);
        nodeCase(T_XmlExpr);
        nodeCase(T_NullTest);
        nodeCase(T_BooleanTest);
        nodeCase(T_CoerceToDomain);
        nodeCase(T_CoerceToDomainValue);
        nodeCase(T_SetToDefault);
        nodeCase(T_CurrentOfExpr);
        nodeCase(T_NextValueExpr);
        nodeCase(T_InferenceElem);
        nodeCase(T_TargetEntry);
        nodeCase(T_RangeTblRef);
        nodeCase(T_JoinExpr);
        nodeCase(T_FromExpr);
        nodeCase(T_OnConflictExpr);
        nodeCase(T_IntoClause);
        nodeCase(T_ExprState);
        nodeCase(T_WindowFuncExprState);
        nodeCase(T_SetExprState);
        nodeCase(T_SubPlanState);
        nodeCase(T_DomainConstraintState);
        nodeCase(T_PlannerInfo);
        nodeCase(T_PlannerGlobal);
        nodeCase(T_RelOptInfo);
        nodeCase(T_IndexOptInfo);
        nodeCase(T_ForeignKeyOptInfo);
        nodeCase(T_ParamPathInfo);
        nodeCase(T_Path);
        nodeCase(T_IndexPath);
        nodeCase(T_BitmapHeapPath);
        nodeCase(T_BitmapAndPath);
        nodeCase(T_BitmapOrPath);
        nodeCase(T_TidPath);
        nodeCase(T_TidRangePath);
        nodeCase(T_SubqueryScanPath);
        nodeCase(T_ForeignPath);
        nodeCase(T_CustomPath);
        nodeCase(T_NestPath);
        nodeCase(T_MergePath);
        nodeCase(T_HashPath);
        nodeCase(T_AppendPath);
        nodeCase(T_MergeAppendPath);
        nodeCase(T_GroupResultPath);
        nodeCase(T_MaterialPath);
        nodeCase(T_MemoizePath);
        nodeCase(T_UniquePath);
        nodeCase(T_GatherPath);
        nodeCase(T_GatherMergePath);
        nodeCase(T_ProjectionPath);
        nodeCase(T_ProjectSetPath);
        nodeCase(T_SortPath);
        nodeCase(T_IncrementalSortPath);
        nodeCase(T_GroupPath);
        nodeCase(T_UpperUniquePath);
        nodeCase(T_AggPath);
        nodeCase(T_GroupingSetsPath);
        nodeCase(T_MinMaxAggPath);
        nodeCase(T_WindowAggPath);
        nodeCase(T_SetOpPath);
        nodeCase(T_RecursiveUnionPath);
        nodeCase(T_LockRowsPath);
        nodeCase(T_ModifyTablePath);
        nodeCase(T_LimitPath);
        nodeCase(T_EquivalenceClass);
        nodeCase(T_EquivalenceMember);
        nodeCase(T_PathKey);
        nodeCase(T_PathKeyInfo);
        nodeCase(T_PathTarget);
        nodeCase(T_RestrictInfo);
        nodeCase(T_IndexClause);
        nodeCase(T_PlaceHolderVar);
        nodeCase(T_SpecialJoinInfo);
        nodeCase(T_AppendRelInfo);
        nodeCase(T_RowIdentityVarInfo);
        nodeCase(T_PlaceHolderInfo);
        nodeCase(T_MinMaxAggInfo);
        nodeCase(T_PlannerParamItem);
        nodeCase(T_RollupData);
        nodeCase(T_GroupingSetData);
        nodeCase(T_StatisticExtInfo);
        nodeCase(T_MergeAction);
        nodeCase(T_AllocSetContext);
        nodeCase(T_SlabContext);
        nodeCase(T_GenerationContext);
        nodeCase(T_Integer);
        nodeCase(T_Float);
        nodeCase(T_Boolean);
        nodeCase(T_String);
        nodeCase(T_BitString);
        nodeCase(T_List);
        nodeCase(T_IntList);
        nodeCase(T_OidList);
        nodeCase(T_ExtensibleNode);
        nodeCase(T_RawStmt);
        nodeCase(T_Query);
        nodeCase(T_PlannedStmt);
        nodeCase(T_InsertStmt);
        nodeCase(T_DeleteStmt);
        nodeCase(T_UpdateStmt);
        nodeCase(T_MergeStmt);
        nodeCase(T_SelectStmt);
        nodeCase(T_ReturnStmt);
        nodeCase(T_PLAssignStmt);
        nodeCase(T_AlterTableStmt);
        nodeCase(T_AlterTableCmd);
        nodeCase(T_AlterDomainStmt);
        nodeCase(T_SetOperationStmt);
        nodeCase(T_GrantStmt);
        nodeCase(T_GrantRoleStmt);
        nodeCase(T_AlterDefaultPrivilegesStmt);
        nodeCase(T_ClosePortalStmt);
        nodeCase(T_ClusterStmt);
        nodeCase(T_CopyStmt);
        nodeCase(T_CreateStmt);
        nodeCase(T_DefineStmt);
        nodeCase(T_DropStmt);
        nodeCase(T_TruncateStmt);
        nodeCase(T_CommentStmt);
        nodeCase(T_FetchStmt);
        nodeCase(T_IndexStmt);
        nodeCase(T_CreateFunctionStmt);
        nodeCase(T_AlterFunctionStmt);
        nodeCase(T_DoStmt);
        nodeCase(T_RenameStmt);
        nodeCase(T_RuleStmt);
        nodeCase(T_NotifyStmt);
        nodeCase(T_ListenStmt);
        nodeCase(T_UnlistenStmt);
        nodeCase(T_TransactionStmt);
        nodeCase(T_ViewStmt);
        nodeCase(T_LoadStmt);
        nodeCase(T_CreateDomainStmt);
        nodeCase(T_CreatedbStmt);
        nodeCase(T_DropdbStmt);
        nodeCase(T_VacuumStmt);
        nodeCase(T_ExplainStmt);
        nodeCase(T_CreateTableAsStmt);
        nodeCase(T_CreateSeqStmt);
        nodeCase(T_AlterSeqStmt);
        nodeCase(T_VariableSetStmt);
        nodeCase(T_VariableShowStmt);
        nodeCase(T_DiscardStmt);
        nodeCase(T_CreateTrigStmt);
        nodeCase(T_CreatePLangStmt);
        nodeCase(T_CreateRoleStmt);
        nodeCase(T_AlterRoleStmt);
        nodeCase(T_DropRoleStmt);
        nodeCase(T_LockStmt);
        nodeCase(T_ConstraintsSetStmt);
        nodeCase(T_ReindexStmt);
        nodeCase(T_CheckPointStmt);
        nodeCase(T_CreateSchemaStmt);
        nodeCase(T_AlterDatabaseStmt);
        nodeCase(T_AlterDatabaseRefreshCollStmt);
        nodeCase(T_AlterDatabaseSetStmt);
        nodeCase(T_AlterRoleSetStmt);
        nodeCase(T_CreateConversionStmt);
        nodeCase(T_CreateCastStmt);
        nodeCase(T_CreateOpClassStmt);
        nodeCase(T_CreateOpFamilyStmt);
        nodeCase(T_AlterOpFamilyStmt);
        nodeCase(T_PrepareStmt);
        nodeCase(T_ExecuteStmt);
        nodeCase(T_DeallocateStmt);
        nodeCase(T_DeclareCursorStmt);
        nodeCase(T_CreateTableSpaceStmt);
        nodeCase(T_DropTableSpaceStmt);
        nodeCase(T_AlterObjectDependsStmt);
        nodeCase(T_AlterObjectSchemaStmt);
        nodeCase(T_AlterOwnerStmt);
        nodeCase(T_AlterOperatorStmt);
        nodeCase(T_AlterTypeStmt);
        nodeCase(T_DropOwnedStmt);
        nodeCase(T_ReassignOwnedStmt);
        nodeCase(T_CompositeTypeStmt);
        nodeCase(T_CreateEnumStmt);
        nodeCase(T_CreateRangeStmt);
        nodeCase(T_AlterEnumStmt);
        nodeCase(T_AlterTSDictionaryStmt);
        nodeCase(T_AlterTSConfigurationStmt);
        nodeCase(T_CreateFdwStmt);
        nodeCase(T_AlterFdwStmt);
        nodeCase(T_CreateForeignServerStmt);
        nodeCase(T_AlterForeignServerStmt);
        nodeCase(T_CreateUserMappingStmt);
        nodeCase(T_AlterUserMappingStmt);
        nodeCase(T_DropUserMappingStmt);
        nodeCase(T_AlterTableSpaceOptionsStmt);
        nodeCase(T_AlterTableMoveAllStmt);
        nodeCase(T_SecLabelStmt);
        nodeCase(T_CreateForeignTableStmt);
        nodeCase(T_ImportForeignSchemaStmt);
        nodeCase(T_CreateExtensionStmt);
        nodeCase(T_AlterExtensionStmt);
        nodeCase(T_AlterExtensionContentsStmt);
        nodeCase(T_CreateEventTrigStmt);
        nodeCase(T_AlterEventTrigStmt);
        nodeCase(T_RefreshMatViewStmt);
        nodeCase(T_ReplicaIdentityStmt);
        nodeCase(T_AlterSystemStmt);
        nodeCase(T_CreatePolicyStmt);
        nodeCase(T_AlterPolicyStmt);
        nodeCase(T_CreateTransformStmt);
        nodeCase(T_CreateAmStmt);
        nodeCase(T_CreatePublicationStmt);
        nodeCase(T_AlterPublicationStmt);
        nodeCase(T_CreateSubscriptionStmt);
        nodeCase(T_AlterSubscriptionStmt);
        nodeCase(T_DropSubscriptionStmt);
        nodeCase(T_CreateStatsStmt);
        nodeCase(T_AlterCollationStmt);
        nodeCase(T_CallStmt);
        nodeCase(T_AlterStatsStmt);
        nodeCase(T_A_Expr);
        nodeCase(T_ColumnRef);
        nodeCase(T_ParamRef);
        nodeCase(T_A_Const);
        nodeCase(T_FuncCall);
        nodeCase(T_A_Star);
        nodeCase(T_A_Indices);
        nodeCase(T_A_Indirection);
        nodeCase(T_A_ArrayExpr);
        nodeCase(T_ResTarget);
        nodeCase(T_MultiAssignRef);
        nodeCase(T_TypeCast);
        nodeCase(T_CollateClause);
        nodeCase(T_SortBy);
        nodeCase(T_WindowDef);
        nodeCase(T_RangeSubselect);
        nodeCase(T_RangeFunction);
        nodeCase(T_RangeTableSample);
        nodeCase(T_RangeTableFunc);
        nodeCase(T_RangeTableFuncCol);
        nodeCase(T_TypeName);
        nodeCase(T_ColumnDef);
        nodeCase(T_IndexElem);
        nodeCase(T_StatsElem);
        nodeCase(T_Constraint);
        nodeCase(T_DefElem);
        nodeCase(T_RangeTblEntry);
        nodeCase(T_RangeTblFunction);
        nodeCase(T_TableSampleClause);
        nodeCase(T_WithCheckOption);
        nodeCase(T_SortGroupClause);
        nodeCase(T_GroupingSet);
        nodeCase(T_WindowClause);
        nodeCase(T_ObjectWithArgs);
        nodeCase(T_AccessPriv);
        nodeCase(T_CreateOpClassItem);
        nodeCase(T_TableLikeClause);
        nodeCase(T_FunctionParameter);
        nodeCase(T_LockingClause);
        nodeCase(T_RowMarkClause);
        nodeCase(T_XmlSerialize);
        nodeCase(T_WithClause);
        nodeCase(T_InferClause);
        nodeCase(T_OnConflictClause);
        nodeCase(T_CTESearchClause);
        nodeCase(T_CTECycleClause);
        nodeCase(T_CommonTableExpr);
        nodeCase(T_MergeWhenClause);
        nodeCase(T_RoleSpec);
        nodeCase(T_TriggerTransition);
        nodeCase(T_PartitionElem);
        nodeCase(T_PartitionSpec);
        nodeCase(T_PartitionBoundSpec);
        nodeCase(T_PartitionRangeDatum);
        nodeCase(T_PartitionCmd);
        nodeCase(T_VacuumRelation);
        nodeCase(T_PublicationObjSpec);
        nodeCase(T_PublicationTable);
        nodeCase(T_IdentifySystemCmd);
        nodeCase(T_BaseBackupCmd);
        nodeCase(T_CreateReplicationSlotCmd);
        nodeCase(T_DropReplicationSlotCmd);
        nodeCase(T_ReadReplicationSlotCmd);
        nodeCase(T_StartReplicationCmd);
        nodeCase(T_TimeLineHistoryCmd);
        nodeCase(T_TriggerData);
        nodeCase(T_EventTriggerData);
        nodeCase(T_ReturnSetInfo);
        nodeCase(T_WindowObjectData);
        nodeCase(T_TIDBitmap);
        nodeCase(T_InlineCodeBlock);
        nodeCase(T_FdwRoutine);
        nodeCase(T_IndexAmRoutine);
        nodeCase(T_TableAmRoutine);
        nodeCase(T_TsmRoutine);
        nodeCase(T_ForeignKeyCacheInfo);
        nodeCase(T_CallContext);
        nodeCase(T_SupportRequestSimplify);
        nodeCase(T_SupportRequestSelectivity);
        nodeCase(T_SupportRequestCost);
        nodeCase(T_SupportRequestRows);
        nodeCase(T_SupportRequestIndexCondition);
        nodeCase(T_SupportRequestWFuncMonotonic);
    }

    return "Unknown";
}

/*
 * The first field of a node of any type is guaranteed to be the NodeTag.
 * Hence the type of any node can be gotten by casting it to Node. Declaring
 * a variable to be of Node * (instead of void *) can also facilitate
 * debugging.
 */
typedef struct Node
{
	NodeTag		type;
} Node;

#define nodeTag(nodeptr)		(((const Node*)(nodeptr))->type)

/*
 * newNode -
 *	  create a new node of the specified size and tag the node with the
 *	  specified tag.
 *
 * !WARNING!: Avoid using newNode directly. You should be using the
 *	  macro makeNode.  eg. to create a Query node, use makeNode(Query)
 *
 * Note: the size argument should always be a compile-time constant, so the
 * apparent risk of multiple evaluation doesn't matter in practice.
 */
#ifdef __GNUC__

/* With GCC, we can use a compound statement within an expression */
#define newNode(size, tag) \
({	Node   *_result; \
	AssertMacro((size) >= sizeof(Node));		/* need the tag, at least */ \
	_result = (Node *) palloc0fast(size); \
	_result->type = (tag); \
	_result; \
})
#else

/*
 *	There is no way to dereference the palloc'ed pointer to assign the
 *	tag, and also return the pointer itself, so we need a holder variable.
 *	Fortunately, this macro isn't recursive so we just define
 *	a global variable for this purpose.
 */
extern PGDLLIMPORT Node *newNodeMacroHolder;

#define newNode(size, tag) \
( \
	AssertMacro((size) >= sizeof(Node)),		/* need the tag, at least */ \
	newNodeMacroHolder = (Node *) palloc0fast(size), \
	newNodeMacroHolder->type = (tag), \
	newNodeMacroHolder \
)
#endif							/* __GNUC__ */


#define makeNode(_type_)		((_type_ *) newNode(sizeof(_type_),T_##_type_))
#define NodeSetTag(nodeptr,t)	(((Node*)(nodeptr))->type = (t))

#define IsA(nodeptr,_type_)		(nodeTag(nodeptr) == T_##_type_)

/*
 * castNode(type, ptr) casts ptr to "type *", and if assertions are enabled,
 * verifies that the node has the appropriate type (using its nodeTag()).
 *
 * Use an inline function when assertions are enabled, to avoid multiple
 * evaluations of the ptr argument (which could e.g. be a function call).
 */
//#ifdef USE_ASSERT_CHECKING
//static inline Node *
//castNodeImpl(NodeTag type, void *ptr)
//{
//	Assert(ptr == NULL || nodeTag(ptr) == type);
//	return (Node *) ptr;
//}
//#define castNode(_type_, nodeptr) ((_type_ *) castNodeImpl(T_##_type_, nodeptr))
//#else
//#define castNode(_type_, nodeptr) ((_type_ *) (nodeptr))
//#endif							/* USE_ASSERT_CHECKING */

static inline Node *
castNodeImpl(NodeTag type, void *ptr)
{
    if (ptr != NULL && nodeTag(ptr) != type)
        elog(ERROR, "deparse: expected node type: %s, actual: %s", tag_to_string(type), tag_to_string(nodeTag(ptr)));

	return (Node *) ptr;
}
#define castNode(_type_, nodeptr) ((_type_ *) castNodeImpl(T_##_type_, nodeptr))


/* ----------------------------------------------------------------
 *					  extern declarations follow
 * ----------------------------------------------------------------
 */

/*
 * nodes/{outfuncs.c,print.c}
 */
struct Bitmapset;				/* not to include bitmapset.h here */
struct StringInfoData;			/* not to include stringinfo.h here */

extern void outNode(struct StringInfoData *str, const void *obj);
extern void outToken(struct StringInfoData *str, const char *s);
extern void outBitmapset(struct StringInfoData *str,
						 const struct Bitmapset *bms);
extern void outDatum(struct StringInfoData *str, uintptr_t value,
					 int typlen, bool typbyval);
extern char *nodeToString(const void *obj);
extern char *bmsToString(const struct Bitmapset *bms);

/*
 * nodes/{readfuncs.c,read.c}
 */
extern void *stringToNode(const char *str);
#ifdef WRITE_READ_PARSE_PLAN_TREES
extern void *stringToNodeWithLocations(const char *str);
#endif
extern struct Bitmapset *readBitmapset(void);
extern uintptr_t readDatum(bool typbyval);
extern bool *readBoolCols(int numCols);
extern int *readIntCols(int numCols);
extern Oid *readOidCols(int numCols);
extern int16 *readAttrNumberCols(int numCols);

/*
 * nodes/copyfuncs.c
 */
extern void *copyObjectImpl(const void *obj);

/* cast result back to argument type, if supported by compiler */
#ifdef HAVE_TYPEOF
#define copyObject(obj) ((typeof(obj)) copyObjectImpl(obj))
#else
#define copyObject(obj) copyObjectImpl(obj)
#endif

/*
 * nodes/equalfuncs.c
 */
extern bool equal(const void *a, const void *b);


/*
 * Typedefs for identifying qualifier selectivities and plan costs as such.
 * These are just plain "double"s, but declaring a variable as Selectivity
 * or Cost makes the intent more obvious.
 *
 * These could have gone into plannodes.h or some such, but many files
 * depend on them...
 */
typedef double Selectivity;		/* fraction of tuples a qualifier will pass */
typedef double Cost;			/* execution cost (in page-access units) */
typedef double Cardinality;		/* (estimated) number of rows or other integer
								 * count */


/*
 * CmdType -
 *	  enums for type of operation represented by a Query or PlannedStmt
 *
 * This is needed in both parsenodes.h and plannodes.h, so put it here...
 */
typedef enum CmdType
{
	CMD_UNKNOWN,
	CMD_SELECT,					/* select stmt */
	CMD_UPDATE,					/* update stmt */
	CMD_INSERT,					/* insert stmt */
	CMD_DELETE,					/* delete stmt */
	CMD_MERGE,					/* merge stmt */
	CMD_UTILITY,				/* cmds like create, destroy, copy, vacuum,
								 * etc. */
	CMD_NOTHING					/* dummy command for instead nothing rules
								 * with qual */
} CmdType;


/*
 * JoinType -
 *	  enums for types of relation joins
 *
 * JoinType determines the exact semantics of joining two relations using
 * a matching qualification.  For example, it tells what to do with a tuple
 * that has no match in the other relation.
 *
 * This is needed in both parsenodes.h and plannodes.h, so put it here...
 */
typedef enum JoinType
{
	/*
	 * The canonical kinds of joins according to the SQL JOIN syntax. Only
	 * these codes can appear in parser output (e.g., JoinExpr nodes).
	 */
	JOIN_INNER,					/* matching tuple pairs only */
	JOIN_LEFT,					/* pairs + unmatched LHS tuples */
	JOIN_FULL,					/* pairs + unmatched LHS + unmatched RHS */
	JOIN_RIGHT,					/* pairs + unmatched RHS tuples */

	/*
	 * Semijoins and anti-semijoins (as defined in relational theory) do not
	 * appear in the SQL JOIN syntax, but there are standard idioms for
	 * representing them (e.g., using EXISTS).  The planner recognizes these
	 * cases and converts them to joins.  So the planner and executor must
	 * support these codes.  NOTE: in JOIN_SEMI output, it is unspecified
	 * which matching RHS row is joined to.  In JOIN_ANTI output, the row is
	 * guaranteed to be null-extended.
	 */
	JOIN_SEMI,					/* 1 copy of each LHS row that has match(es) */
	JOIN_ANTI,					/* 1 copy of each LHS row that has no match */

	/*
	 * These codes are used internally in the planner, but are not supported
	 * by the executor (nor, indeed, by most of the planner).
	 */
	JOIN_UNIQUE_OUTER,			/* LHS path must be made unique */
	JOIN_UNIQUE_INNER			/* RHS path must be made unique */

	/*
	 * We might need additional join types someday.
	 */
} JoinType;

/*
 * OUTER joins are those for which pushed-down quals must behave differently
 * from the join's own quals.  This is in fact everything except INNER and
 * SEMI joins.  However, this macro must also exclude the JOIN_UNIQUE symbols
 * since those are temporary proxies for what will eventually be an INNER
 * join.
 *
 * Note: semijoins are a hybrid case, but we choose to treat them as not
 * being outer joins.  This is okay principally because the SQL syntax makes
 * it impossible to have a pushed-down qual that refers to the inner relation
 * of a semijoin; so there is no strong need to distinguish join quals from
 * pushed-down quals.  This is convenient because for almost all purposes,
 * quals attached to a semijoin can be treated the same as innerjoin quals.
 */
#define IS_OUTER_JOIN(jointype) \
	(((1 << (jointype)) & \
	  ((1 << JOIN_LEFT) | \
	   (1 << JOIN_FULL) | \
	   (1 << JOIN_RIGHT) | \
	   (1 << JOIN_ANTI))) != 0)

/*
 * AggStrategy -
 *	  overall execution strategies for Agg plan nodes
 *
 * This is needed in both pathnodes.h and plannodes.h, so put it here...
 */
typedef enum AggStrategy
{
	AGG_PLAIN,					/* simple agg across all input rows */
	AGG_SORTED,					/* grouped agg, input must be sorted */
	AGG_HASHED,					/* grouped agg, use internal hashtable */
	AGG_MIXED					/* grouped agg, hash and sort both used */
} AggStrategy;

/*
 * AggSplit -
 *	  splitting (partial aggregation) modes for Agg plan nodes
 *
 * This is needed in both pathnodes.h and plannodes.h, so put it here...
 */

/* Primitive options supported by nodeAgg.c: */
#define AGGSPLITOP_COMBINE		0x01	/* substitute combinefn for transfn */
#define AGGSPLITOP_SKIPFINAL	0x02	/* skip finalfn, return state as-is */
#define AGGSPLITOP_SERIALIZE	0x04	/* apply serialfn to output */
#define AGGSPLITOP_DESERIALIZE	0x08	/* apply deserialfn to input */

/* Supported operating modes (i.e., useful combinations of these options): */
typedef enum AggSplit
{
	/* Basic, non-split aggregation: */
	AGGSPLIT_SIMPLE = 0,
	/* Initial phase of partial aggregation, with serialization: */
	AGGSPLIT_INITIAL_SERIAL = AGGSPLITOP_SKIPFINAL | AGGSPLITOP_SERIALIZE,
	/* Final phase of partial aggregation, with deserialization: */
	AGGSPLIT_FINAL_DESERIAL = AGGSPLITOP_COMBINE | AGGSPLITOP_DESERIALIZE
} AggSplit;

/* Test whether an AggSplit value selects each primitive option: */
#define DO_AGGSPLIT_COMBINE(as)		(((as) & AGGSPLITOP_COMBINE) != 0)
#define DO_AGGSPLIT_SKIPFINAL(as)	(((as) & AGGSPLITOP_SKIPFINAL) != 0)
#define DO_AGGSPLIT_SERIALIZE(as)	(((as) & AGGSPLITOP_SERIALIZE) != 0)
#define DO_AGGSPLIT_DESERIALIZE(as) (((as) & AGGSPLITOP_DESERIALIZE) != 0)

/*
 * SetOpCmd and SetOpStrategy -
 *	  overall semantics and execution strategies for SetOp plan nodes
 *
 * This is needed in both pathnodes.h and plannodes.h, so put it here...
 */
typedef enum SetOpCmd
{
	SETOPCMD_INTERSECT,
	SETOPCMD_INTERSECT_ALL,
	SETOPCMD_EXCEPT,
	SETOPCMD_EXCEPT_ALL
} SetOpCmd;

typedef enum SetOpStrategy
{
	SETOP_SORTED,				/* input must be sorted */
	SETOP_HASHED				/* use internal hashtable */
} SetOpStrategy;

/*
 * OnConflictAction -
 *	  "ON CONFLICT" clause type of query
 *
 * This is needed in both parsenodes.h and plannodes.h, so put it here...
 */
typedef enum OnConflictAction
{
	ONCONFLICT_NONE,			/* No "ON CONFLICT" clause */
	ONCONFLICT_NOTHING,			/* ON CONFLICT ... DO NOTHING */
	ONCONFLICT_UPDATE			/* ON CONFLICT ... DO UPDATE */
} OnConflictAction;

/*
 * LimitOption -
 *	LIMIT option of query
 *
 * This is needed in both parsenodes.h and plannodes.h, so put it here...
 */
typedef enum LimitOption
{
	LIMIT_OPTION_DEFAULT,		/* No limit present */
	LIMIT_OPTION_COUNT,			/* FETCH FIRST... ONLY */
	LIMIT_OPTION_WITH_TIES,		/* FETCH FIRST... WITH TIES */
} LimitOption;

#endif							/* NODES_H */
