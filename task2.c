#include <stdlib.h>
#include <stdio.h>

#define red (0)
#define black (1)

struct rbTree{
  struct rbNode* root;
  struct rbNode* nil;
};

struct rbNode {
    int key;
    int color;
    struct rbNode* lChild;
    struct rbNode* rChild;
    struct rbNode* parent;
};

void printTree(struct TreeNode *root);
struct rbNode* newNode(int key, struct rbTree* tree);
void insert(struct rbNode * nodeToInsert, struct rbTree * tree);
int isLeftChild(struct rbNode* node);
struct rbNode* getUncle(struct rbNode* node);
void rightRotate(struct rbTree* tree, struct rbNode* node);
void rbFixup(struct rbTree* tree, struct rbNode** insertedNode);
void rbInsert(int key, struct rbTree** tree);
void printTreeRecursive(struct TreeNode *root);

int int main() {
  /* code */
  return 0;
}

struct rbNode* newNode(int key, struct rbTree* tree){
  struct rbNode *nodeToInsert = malloc(sizeof(struct rbNode));
  nodeToInsert->key = key;
  nodeToInsert->color=red;
  nodeToInsert->lChild = (*tree)->nil;
  nodeToInsert->rChild = (*tree)->nil;
  nodeToInsert->parent = (*tree)->nil;
}

void insert(struct rbNode * nodeToInsert, struct rbTree * tree) {
    struct rbNode *oneDelayed = (tree)->nil;
    struct rbNode *insertPlace = (tree)->root;
    while (insertPlace != (tree)->nil) {
        oneDelayed = insertPlace;
        if (insertPlace->key < nodeToInsert->key)
            insertPlace = insertPlace->rChild;
        else
            insertPlace = insertPlace->lChild;
    }
    if (oneDelayed == (tree)->nil)
        (tree)->root = nodeToInsert;
    else if (oneDelayed->key < nodeToInsert->key)
        oneDelayed->rChild = nodeToInsert;
    else
        oneDelayed->lChild = nodeToInsert;
}

int isLeftChild(struct rbNode* node){
  return(node->parent->parent->lChild== node?1:0);
}

struct rbNode* getUncle(struct rbNode* node){
  if (isLeftChild(node->parent)) {
    return node->parent-parent->rChild;
  }else{
    return node->parent->parent->lChild;
  }
}

void rightRotate(struct rbTree* tree, struct rbNode* node) {
  struct rbNode* newParent = node->lChild;
  int isNodeLeftChild = isLeftChild(node);
  newParent->parent= node->parent;
  node->lChild = newParent->rChild;
  if (isNodeLeftChild) {
    node->parent->lChild = newParent;
  }else{
    node->parent->rChild = newParent;
  }
  node->parent = newParent;

  node->lChild->parent = node;
  newParent->rChild = node;
}

void rbFixup(struct rbTree* tree, struct rbNode** insertedNode){
  if ((*insertedNode)== (tree)->root) {
    (*insertedNode)->color = black;
    return;
  }else if ((*insertedNode)->parent->color== black) {
    return;
  }
  if (isLeftChild(getUncle(insertedNode))) {
    //normal case
    if (getUncle(insertedNode)->color == red) {
      // case 1
    }else if (!isLeftChild(insertedNode)) {
      // case 2
    }else{
      // case 3
      (*insertedNode)->parent->color = black;
      (*insertedNode)->parent->paren->color = red;
      //rightRotate
    }
  }
}

void rbInsert(int key, struct rbTree** tree) {
  struct rbNode* node = newNode(key, tree);
  insert(node, tree);
  rbFixup(tree , node);
}

void printTreeRecursive(struct TreeNode *root) {
    if (root == NULL)
        return;
    if (root->lChild != NULL) {
        printf("  %d -- %d\n", root->key, root->lChild->key);
        printTreeRecursive(root->lChild);
    }
    if(root->rChild != NULL) {
        printf("  %d -- %d\n", root->key, root->rChild->key);
        printTreeRecursive(root->rChild);
    }
}

void printTree(struct TreeNode *root) {
    printf("graph g {\n");
    printTreeRecursive(root);
    printf("}\n");
}
