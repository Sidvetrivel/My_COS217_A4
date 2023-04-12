/*--------------------------------------------------------------------*/
/* checkerDT.h                                                        */
/* Author: Christopher Moretti                                        */
/*--------------------------------------------------------------------*/

#ifndef CHECKER_INCLUDED
#define CHECKER_INCLUDED

#include "nodeDT.h"


/*
   Returns TRUE if oNNode represents a directory entry
   in a valid state, or FALSE otherwise. Prints explanation
   to stderr in the latter case. isValid also checks if the children 
   of oNNode have any duplicate paths and prints FALSE if a duplicate 
   path is found and otherwise prints TRUE. isValid checks if all 
   children of oNNode are within the dynarray in lexigraphic order and 
   returns FALSE if there is a misordering found and TRUE otherwise.
*/
boolean CheckerDT_Node_isValid(Node_T oNNode);

/*
   Returns TRUE if the hierarchy is in a valid state or FALSE
   otherwise.  Prints explanation to stderr in the latter case.
   The data structure's validity is based on a boolean
   bIsInitialized indicating whether the DT is in an initialized
   state, a Node_T oNRoot representing the root of the hierarchy, and
   a size_t ulCount representing the total number of directories in
   the hierarchy.
*/
boolean CheckerDT_isValid(boolean bIsInitialized,
                          Node_T oNRoot,
                          size_t ulCount);

#endif
