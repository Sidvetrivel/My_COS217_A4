/*--------------------------------------------------------------------*/
/* checkerDT.c                                                        */
/* Author:                                                            */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "checkerDT.h"
#include "dynarray.h"
#include "path.h"



/* see checkerDT.h for specification */
boolean CheckerDT_Node_isValid(Node_T oNNode) {
   Node_T oNParent;
   Path_T oPNPath;
   Path_T oPPPath;

   size_t ucIndex;
   size_t numChildren;


   /* Sample check: a NULL pointer is not a valid node */
   if(oNNode == NULL) {
      fprintf(stderr, "A node is a NULL pointer\n");
      return FALSE;
   }

   /* Sample check: parent's path must be the longest possible
      proper prefix of the node's path */
   oNParent = Node_getParent(oNNode);
   if(oNParent != NULL) {
      oPNPath = Node_getPath(oNNode);
      oPPPath = Node_getPath(oNParent);

      if(Path_getSharedPrefixDepth(oPNPath, oPPPath) !=
         Path_getDepth(oPNPath) - 1) {
         fprintf(stderr, "P-C nodes don't have P-C paths: (%s) (%s)\n",
                 Path_getPathname(oPPPath), Path_getPathname(oPNPath));
         return FALSE;
      }
   }

   /* Checks if there are any duplicate paths between the children
   of a node and ensures typographical order is maintained between
   all children of a node */ 
   numChildren = Node_getNumChildren(oNNode);
   for(ucIndex = 1; ucIndex < numChildren; ucIndex++)
         {
            /*compares 2 successive nodes at a time*/
            Node_T currNode = NULL;
            Node_T nextNode = NULL;
            Path_T currNodepath;
            Path_T nextNodepath;
            int currStatus;

            currStatus = Node_getChild(oNNode, ucIndex-1, &currNode);
            /*checks if child exists*/
            if(currStatus != SUCCESS){
               fprintf(stderr, "child does not exist\n");
               return FALSE;
            }

            int nextStatus = Node_getChild(oNNode, ucIndex, &nextNode);
            /*checks if child exists*/
            if(nextStatus != SUCCESS){
               fprintf(stderr, "child does not exist\n");
               return FALSE;
            }

            currNodepath = Node_getPath(currNode);
            nextNodepath = Node_getPath(nextNode);

            /*checks if there are duplicate paths between 2 nodes*/
            if(Path_comparePath(currNodepath, nextNodepath) == 0){
               fprintf(stderr, "File tree has duplicate paths\n");
               return FALSE;
            }

            /*checks for correct lexigraphic order between 2 nodes*/
            if(Path_comparePath(currNodepath, nextNodepath) > 0){
               fprintf(stderr, "File tree has paths that are out of order\n");
               return FALSE;
            }
         }


   return TRUE;
}

/*
   Performs a pre-order traversal of the tree rooted at oNNode.
   Returns FALSE if a broken invariant is found and
   returns TRUE otherwise.

   You may want to change this function's return type or
   parameter list to facilitate constructing your checks.
   If you do, you should update this function comment.
*/
static boolean CheckerDT_treeCheck(Node_T oNNode) {
   size_t ulIndex;
   size_t index;

   if(oNNode!= NULL) {

      /* Sample check on each node: node must be valid */
      /* If not, pass that failure back up immediately */
      if(!CheckerDT_Node_isValid(oNNode))
         return FALSE;

      /* Recur on every child of oNNode */
      for(ulIndex = 0; ulIndex < Node_getNumChildren(oNNode); ulIndex++)
      {
         Node_T oNChild = NULL;

         int iStatus = Node_getChild(oNNode, ulIndex, &oNChild);

         if(iStatus != SUCCESS) {
            fprintf(stderr, "getNumChildren claims more children than getChild returns\n");
            return FALSE;
         }

         /* if recurring down one subtree results in a failed check
            farther down, passes the failure back up immediately */
         if(!CheckerDT_treeCheck(oNChild))
            return FALSE;
      }
   }
   return TRUE;
}

/* see checkerDT.h for specification */
boolean CheckerDT_isValid(boolean bIsInitialized, Node_T oNRoot,
                          size_t ulCount) {

   /* Sample check on a top-level data structure invariant:
      if the DT is not initialized, its count should be 0. */
   if(!bIsInitialized)
      if(ulCount != 0) {
         fprintf(stderr, "Not initialized, but count is not 0\n");
         return FALSE;
      }



   /* Now checks invariants recursively at each node from the root. */
   return CheckerDT_treeCheck(oNRoot);
}
