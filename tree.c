#include "tree.h"

#include <stdlib.h>

#include "array.h"

#define TREE_MAX_CHILDREN 8

typedef struct TreeNode_t {
  _u16 id;
  void* data;

  TreeNode_t* parent;
  Array_t* nodes;
} TreeNode_t;

typedef struct Tree_t {
  TreeNode_t* root;
  _u8 maxChildrenPerNode;
  _u16 nextNodeId;
} Tree_t;

static _u16 Tree_GetNextId(Tree_t* tree);

TreeNode_t* TreeNode_Create(_u16 id, _u8 maxNodes);
void TreeNode_Destroy(TreeNode_t* node);

bool TreeNode_AddChild(TreeNode_t* node, TreeNode_t* child);
static bool TreeNode_SetData(TreeNode_t* node, void* data);
static void TreeNode_Find(TreeNode_t* node, TreeNode_t** result, const _u16 id);
static void _TreeNode_Destroy(const TreeNode_t* root, TreeNode_t* node);

Tree_t* Tree_Create() {
  Tree_t* tree = (Tree_t*)malloc(sizeof(Tree_t));
  if (tree == NULL) {
    return NULL;
  }

  tree->nextNodeId = 0;
  tree->maxChildrenPerNode = TREE_MAX_CHILDREN;
  tree->root = TreeNode_Create(tree->nextNodeId, tree->maxChildrenPerNode);

  return tree;
}

void Tree_Destroy(Tree_t* tree) {
  TreeNode_Destroy(tree->root);

  free(tree);
}

_u16 Tree_AddNodeById(Tree_t* tree, const _u16 branchId, const bool addAsLeaf) {
  TreeNode_t* branch = Tree_FindNode(tree, branchId);

  return Tree_AddNode(tree, branch, addAsLeaf);
}

_u16 Tree_AddNode(Tree_t* tree, TreeNode_t* branch, const bool addAsLeaf) {
  if (branch == NULL || TreeNode_IsLeaf(branch)) {
    return TREE_INDEX_NONE;
  }

  _u16 id = Tree_GetNextId(tree);
  TreeNode_t* node = addAsLeaf == true
                         ? TreeNode_Create(id, 0)
                         : TreeNode_Create(id, tree->maxChildrenPerNode);

  if (node == NULL) {
    return TREE_INDEX_NONE;
  }

  return TreeNode_AddChild(branch, node) == true ? id : TREE_INDEX_NONE;
}

void Tree_RemoveNode(Tree_t* tree, const _u16 nodeId) {
  TreeNode_t* branch = Tree_FindNode(tree, nodeId);

  if (branch != NULL) {
    TreeNode_Destroy(branch);
  }
}

bool Tree_SetNodeData(const Tree_t* tree, const _u16 nodeId, void* data) {
  TreeNode_t* node = Tree_FindNode(tree, nodeId);
  if (node != NULL) {
    return TreeNode_SetData(node, data);
  }
  return false;
}

TreeNode_t* Tree_FindNode(const Tree_t* tree, const _u16 id) {
  TreeNode_t* result = NULL;
  if (id != TREE_INDEX_NONE) {
    TreeNode_Find(tree->root, &result, id);
  }

  return result;
}

TreeNode_t* Tree_GetRoot(Tree_t* tree) { return tree->root; }

void Tree_Foreach(Tree_t* tree, TreeIterator iterator) {
  TreeNode_t* root = Tree_GetRoot(tree);

  TreeNode_Foreach(root, iterator);
}

_u16 TreeNode_GetId(TreeNode_t* node) { return node->id; }

void* TreeNode_GetData(TreeNode_t* node) { return node->data; }

bool TreeNode_IsLeaf(const TreeNode_t* node) { return node->nodes == NULL; }

bool TreeNode_HasNoChildren(const TreeNode_t* node) {
  return node->nodes == NULL || ArrayIsEmpty(node->nodes);
}

TreeNode_t* TreeNode_GetParent(const TreeNode_t* node) { return node->parent; }

void TreeNode_Foreach(TreeNode_t* node, TreeIterator iterator) {
    iterator(node);

    if (TreeNode_HasNoChildren(node) == false) {
        for (_u8 index = 0; index < ArraySize(node->nodes); index++) {
            TreeNode_t* child = ArrayValueAt(node->nodes, index);
            TreeNode_Foreach(child, iterator);
        }
    }
}

// private part

static _u16 Tree_GetNextId(Tree_t* tree) {
  tree->nextNodeId++;
  return tree->nextNodeId;
}

bool TreeNode_AddChild(TreeNode_t* node, TreeNode_t* child) {
  if (node == NULL || child == NULL) {
    return false;
  }

  if (TreeNode_IsLeaf(node) == true) {
    return false;
  }

  child->parent = node;

  return ArrayAdd(node->nodes, child);
}

TreeNode_t* TreeNode_Create(_u16 id, _u8 maxNodes) {
  TreeNode_t* node = (TreeNode_t*)malloc(sizeof(TreeNode_t));

  if (node == NULL) {
    return NULL;
  }

  node->id = id;
  node->parent = NULL;
  node->data = NULL;
  if (maxNodes > 0) {
    node->nodes = ArrayCreate(maxNodes);
  } else {
    node->nodes = NULL;
  }

  return node;
}

void TreeNode_Destroy(TreeNode_t* node) { _TreeNode_Destroy(node, node); }

static void _TreeNode_Destroy(const TreeNode_t* root, TreeNode_t* node) {
  // there are three cases:
  // 1. if node root and no children - free node & exit
  // 2. if node has no children - free node and call _TreeNode_Destroy with its
  // parent
  // 3. if node has children - call _TreeNode_Destroy for every child
  if (TreeNode_HasNoChildren(node) == true) {
    bool isRoot = node->id == root->id;
    TreeNode_t* parent = TreeNode_GetParent(node);

    node->data = NULL;
    node->parent = NULL;
    ArrayDestroy(node->nodes);
    node->nodes = NULL;
    free(node);

    // case 1
    if (isRoot == true) {
      return;
    }
    // case 2
    else {
      _TreeNode_Destroy(root, parent);
    }
  } else {
    // case 3
    _u16 index = ArrayLastIndex(node->nodes);
    TreeNode_t* childNode = ArrayValueAt(node->nodes, index);

    ArrayRemoveIndex(node->nodes, index);
    _TreeNode_Destroy(root, childNode);
  }
}

static void TreeNode_Find(TreeNode_t* node, TreeNode_t** result,
                          const _u16 id) {
  if (node->id == id) {
    *result = node;
    return;
  }

  for (_u8 index = 0; index < ArraySize(node->nodes); index++) {
    TreeNode_t* child = ArrayValueAt(node->nodes, index);
    TreeNode_Find(child, result, id);
  }
}

static bool TreeNode_SetData(TreeNode_t* node, void* data) {
  if (node == NULL || data == NULL) {
    return false;
  }

  node->data = data;
  return true;
}