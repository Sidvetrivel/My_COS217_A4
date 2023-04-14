/*--------------------------------------------------------------------*/
/* nodeDT.h                                                           */
/* Author: Julian & Sid                                               */
/*--------------------------------------------------------------------*/

#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <stddef.h>
#include "a4def.h"
#include "path.h"


/* A Node_T is a node in a File Tree */
typedef struct node *Node_T;

/*
  Creates a new node in the File Tree, with path oPPath and
  parent oNParent. Depending on if it is a file or directory (based off
  the paramter isFile), the function will set respective parameters. If
  it is a file, the parameters pvContents and length are set. Otherwise
  the other parameters are used to set the values for the directory
  node. Returns an int SUCCESS status and sets *poNResult
  to be the new node if successful. Otherwise, sets *poNResult to NULL
  and returns status:
  * MEMORY_ERROR if memory could not be allocated to complete request
  * CONFLICTING_PATH if oNParent's path is not an ancestor of oPPath
  * NO_SUCH_PATH if oPPath is of depth 0
                 or oNParent's path is not oPPath's direct parent
                 or oNParent is NULL but oPPath is not of depth 1
  * ALREADY_IN_TREE if oNParent already has a child with this path
*/
int Node_new(Path_T oPPath, Node_T oNParent, Node_T *poNResult,
 boolean isFile, void *pvContents, size_t length);

/*
  Destroys and frees all memory allocated for the subtree rooted at
  oNNode, i.e., deletes this node and all its descendents. Returns the
  number of nodes deleted.
*/
size_t Node_free(Node_T oNNode);

/* Returns the path object representing oNNode's absolute path. */
Path_T Node_getPath(Node_T oNNode);

/*
  Returns TRUE if oNParent has a child with path oPPath. Returns
  FALSE if it does not.

  If oNParent has such a child, stores in *pulChildID the child's
  identifier (as used in Node_getChild). If oNParent does not have
  such a child, stores in *pulChildID the identifier that such a
  child _would_ have if inserted. Returns NOT_A_DIRECTORY if oNNode 
  is a file. 
*/
boolean Node_hasChild(Node_T oNParent, Path_T oPPath,
                         size_t *pulChildID);

/* Returns the number of children that oNParent has or NOT_A_DIRECTORY 
   if oNNode is a file 
*/
size_t Node_getNumChildren(Node_T oNParent);

/*
  Returns an int SUCCESS status and sets *poNResult to be the child
  node of oNParent with identifier ulChildID, if one exists.
  Otherwise, sets *poNResult to NULL and returns status:
  * NO_SUCH_PATH if ulChildID is not a valid child for oNParent
  * NOT_A_DIRECTORY if oNNode is a file
*/
int Node_getChild(Node_T oNParent, size_t ulChildID,
                  Node_T *poNResult);

/*
  Returns a the parent node of oNNode.
  Returns NULL if oNNode is the root and thus has no parent.
*/
Node_T Node_getParent(Node_T oNNode);

/*
  Compares oNFirst and oNSecond lexicographically based on their paths.
  Returns <0, 0, or >0 if onFirst is "less than", "equal to", or
  "greater than" oNSecond, respectively.
*/
int Node_compare(Node_T oNFirst, Node_T oNSecond);

/* Inputs a node and returns its contents if its a file 
  * NOT_A_FILE if oNNode is a directory */
void *Node_returnContents(Node_T oNNode);

/* Replaces the contents and its length of oNNode with pvNewContents
  and ulNewLength then return the old contents as a void pointer. 
  Function returns NULL if oNNode is a directory */
void* Node_replaceContents(Node_T oNNode, void *pvNewContents,
                           size_t ulNewLength);

/* Inputs a node and checks if it is a file */
boolean Node_isFile(Node_T oNNode);

/* Inputs a node and returns the length of its concents if its
  a file. Function returns NOT_A_FILE if oNNode is a directory */
size_t Node_contentsLength(Node_T oNNode);

/*
  Returns a string representation for oNNode, or NULL if
  there is an allocation error.

  Allocates memory for the returned string, which is then owned by
  the caller!
*/
char *Node_toString(Node_T oNNode);

#endif