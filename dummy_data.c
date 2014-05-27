/*
 * The dummy Foreign Data Wrapper allows you 
 * to test foreign data wrappers. 
 */

#include "postgres.h"
#include "nodes/pg_list.h"
#include "catalog/pg_foreign_server.h"
#include "catalog/pg_foreign_table.h"
//#include "commands/defrem.h"
#include "foreign/fdwapi.h"
#include "foreign/foreign.h"
//#include "funcapi.h"
//#include "lib/stringinfo.h"
//#include "nodes/relation.h"
//#include "utils/builtins.h"
//#include "catalog/pg_type.h"
//#include "utils/syscache.h"
//#include "access/relscan.h"
//#include "nodes/makefuncs.h"
//#include "nodes/bitmapset.h"

//######################
#include "commands/explain.h"
#include "optimizer/paths.h"
#include "optimizer/pathnode.h"
#include "optimizer/planmain.h"
/*
#include "optimizer/restrictinfo.h"
#include "optimizer/clauses.h"
#include "optimizer/var.h"
#include "access/reloptions.h"
#include "access/relscan.h"
#include "access/sysattr.h"
#include "access/xact.h"
#include "nodes/makefuncs.h"
#include "catalog/pg_type.h"
#include "utils/memutils.h"
#include "utils/rel.h"
*/
#include "parser/parsetree.h"

PG_MODULE_MAGIC;

extern Datum dummy_handler(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(dummy_handler);

void		_PG_init(void);
void		_PG_fini(void);

/*
 * FDW functions declarations
 */

static void dummyGetForeignRelSize(PlannerInfo *root,
						   RelOptInfo *baserel,
						   Oid foreigntableid);
static void dummyGetForeignPaths(PlannerInfo *root,
						 RelOptInfo *baserel,
						 Oid foreigntableid);
static ForeignScan *dummyGetForeignPlan(PlannerInfo *root,
						RelOptInfo *baserel,
						Oid foreigntableid,
						ForeignPath *best_path,
						List *tlist,
						List *scan_clauses);
static void dummyExplainForeignScan(ForeignScanState *node,
							ExplainState *es);
static void dummyBeginForeignScan(ForeignScanState *node, int eflags);
static TupleTableSlot *dummyIterateForeignScan(ForeignScanState *node);
static void dummyReScanForeignScan(ForeignScanState *node);
static void dummyEndForeignScan(ForeignScanState *node);

void _PG_init() 
{
}

void _PG_fini()
{
}

Datum dummy_handler(PG_FUNCTION_ARGS)
{
	FdwRoutine *fdw_routine = makeNode(FdwRoutine);

	fdw_routine->GetForeignRelSize = dummyGetForeignRelSize;
	fdw_routine->GetForeignPaths = dummyGetForeignPaths;
	fdw_routine->GetForeignPlan = dummyGetForeignPlan;
	fdw_routine->ExplainForeignScan = dummyExplainForeignScan;

	fdw_routine->BeginForeignScan = dummyBeginForeignScan;
	fdw_routine->IterateForeignScan = dummyIterateForeignScan;
	fdw_routine->ReScanForeignScan = dummyReScanForeignScan;
	fdw_routine->EndForeignScan = dummyEndForeignScan;

	PG_RETURN_POINTER(fdw_routine);
}

/*
 * GetForeignRelSize
 *		set relation size estimates for a foreign table
 */
static void
dummyGetForeignRelSize(PlannerInfo *root,
						   RelOptInfo *baserel,
						   Oid foreigntableid)
{
		baserel-> rows = 0;
}

/*
 * GetForeignPaths
 *		create access path for a scan on the foreign table
 */
static void
dummyGetForeignPaths(PlannerInfo *root,
						 RelOptInfo *baserel,
						 Oid foreigntableid)
{
	Path	   *path;
	path = (Path *) create_foreignscan_path(root, baserel,
						baserel->rows,
						10,
						0,
						NIL,	
						NULL,	
						NULL);
  add_path(baserel, path);
}

/*
 * GetForeignPlan
 *	create a ForeignScan plan node 
 */
static ForeignScan *
dummyGetForeignPlan(PlannerInfo *root,
						RelOptInfo *baserel,
						Oid foreigntableid,
						ForeignPath *best_path,
						List *tlist,
						List *scan_clauses)
{
//	Index		scan_relid = baserel->relid;
	return make_foreignscan(tlist,
			scan_clauses,
			baserel->relid,
			scan_clauses,		
			NULL);
}

/*
 * ExplainForeignScan
 *   no extra info explain plan
 */
static void
dummyExplainForeignScan(ForeignScanState *node, ExplainState *es)
{
}

/*
 * BeginForeignScan
 *   called during executor startup. perform any initialization 
 *   needed, but not start the actual scan. 
 */
static void
dummyBeginForeignScan(ForeignScanState *node, int eflags)
{
}


/*
 * IterateForeignScan
 *		Retrieve next row from the result set, or clear tuple slot to indicate
 *		EOF.
 *   Fetch one row from the foreign source, returning it in a tuple table slot 
 *    (the node's ScanTupleSlot should be used for this purpose). 
 *  Return NULL if no more rows are available. 
 */
static TupleTableSlot *
dummyIterateForeignScan(ForeignScanState *node)
{
	return NULL;
}

/*
 * ReScanForeignScan
 *		Restart the scan from the beginning
 */
static void
dummyReScanForeignScan(ForeignScanState *node)
{
}

/*
 *EndForeignScan
 *	End the scan and release resources. 
 */
static void
dummyEndForeignScan(ForeignScanState *node)
{
}

