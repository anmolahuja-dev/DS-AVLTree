#pragma once
#include "Node.h"
class ATree
{
public:
	Node* root;
	ATree() { root = nullptr; }

    int NodeHeight(Node* p);
    int BalanceFactor(Node* p);
    Node* InPre(Node*);
    Node* InSucc(Node*);
  
    Node* LLRotation(Node* p);
    Node* RRRotation(Node* p);
    Node* LRRotation(Node* p);
    Node* RLRotation(Node* p);

    // Insert
    Node* Rinsert(Node* p, int key);

    // Traversal
    void Inorder(Node* p);

    //delete
    Node* Delete(Node* p, int key);

    void deleteNodes(Node* t);
    ~ATree() { deleteNodes(root); }
        
};

