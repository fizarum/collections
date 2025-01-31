#ifndef TREE_H
#define TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "array.h"
#include "types.h"

#define TREE_INDEX_NONE UINT16_MAX

typedef struct TreeNode_t TreeNode_t;
typedef struct Tree_t Tree_t;

typedef void(TreeIterator)(TreeNode_t* node);
typedef void(TreeNodeChangeCallback)(TreeNode_t* node);

Tree_t* Tree_Create();
void Tree_Destroy(Tree_t* tree, TreeNodeChangeCallback callback);

_u16 Tree_AddNodeById(Tree_t* tree, const _u16 branchId, const bool addAsLeaf);
_u16 Tree_AddNode(Tree_t* tree, TreeNode_t* branch, const bool addAsLeaf);
void Tree_RemoveNode(Tree_t* tree, const _u16 nodeId);
bool Tree_SetNodeData(const Tree_t* tree, const _u16 nodeId, void* data);

TreeNode_t* Tree_FindNode(const Tree_t* tree, const _u16 id);
TreeNode_t* Tree_GetRoot(Tree_t* tree);
void Tree_Foreach(Tree_t* tree, TreeIterator iterator);

// tree node api
TreeNode_t* TreeNode_Create(_u16 id, _u8 maxNodes);
void TreeNode_Destroy(TreeNode_t* node, TreeNodeChangeCallback callback);

_u16 TreeNode_GetId(TreeNode_t* node);
void* TreeNode_GetData(TreeNode_t* node);
bool TreeNode_IsLeaf(const TreeNode_t* node);
bool TreeNode_HasNoChildren(const TreeNode_t* node);
TreeNode_t* TreeNode_GetParent(const TreeNode_t* node);
Array_t* TreeNode_GetChildren(const TreeNode_t* node);
void TreeNode_Foreach(TreeNode_t* node, TreeIterator iterator);

#ifdef __cplusplus
}
#endif

#endif  // TREE_H