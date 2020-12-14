#include<iostream>
#include "ATree.h"
using namespace std;

int ATree::NodeHeight(Node* p) {
	int hl, hr;
	hl = p && p->lchild ? p->lchild->height : 0;
	hr = p && p->rchild ? p->rchild->height : 0;

	return hl > hr ? hl + 1 : hr + 1;
}

int ATree::BalanceFactor(Node* p) {
	int hl, hr;
	hl = p && p->lchild ? p->lchild->height : 0;
	hr = p && p->rchild ? p->rchild->height : 0;
	
	return hl - hr;
}

Node* ATree::LLRotation(Node* p) {
	Node* pl = p->lchild;
	Node* plr = pl->rchild;

	pl->rchild = p;
	p->lchild = plr;

	//update height
	p->height = NodeHeight(p);
	pl->height = NodeHeight(pl);

	if (p == root)
		root = pl;

	return pl;
}

Node* ATree::RRRotation(Node* p) {
	Node* pr = p->rchild;
	Node* prl = pr->lchild;

	pr->lchild = p;
	p->rchild = prl;

	//updating height
	p->height = NodeHeight(p);
	pr->height = NodeHeight(pr);

	if (p == root) {
		root = pr;
	}

	return pr;
}

Node *ATree::Rinsert(Node* t, int key) {
	Node* p;
	if (t == NULL) {
		p = new Node;
		p->data = key;
		p->height = 1;
		p->lchild = p->rchild = nullptr;
		return p;
	}
	if (key < t->data) {
		t->lchild = Rinsert(t->lchild, key);
	}
	else if (key > t->data) {
		t->rchild = Rinsert(t->rchild, key);
	}

	t->height = NodeHeight(t);

	if (BalanceFactor(t) == 2 && BalanceFactor(t->lchild) == 1) {
		return LLRotation(t);
	}

	return t;
}

int main() {
	ATree A;
	A.root = A.Rinsert(A.root, 30);
	A.root = A.Rinsert(A.root, 20);
	A.root = A.Rinsert(A.root, 25);
	A.root = A.Rinsert(A.root, 28);
	A.root = A.Rinsert(A.root, 10);
	A.root = A.Rinsert(A.root, 5);
	A.root = A.Rinsert(A.root, 15);
	A.root = A.Rinsert(A.root, 40);
	A.root = A.Rinsert(A.root, 50);
	A.root = A.Rinsert(A.root, 4);


	cout << "Ans : ";
	return 0;
}