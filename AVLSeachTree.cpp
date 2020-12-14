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

Node* ATree::LRRotation(Node* p) {
	Node* pl = p->lchild;
	Node* plr = pl->rchild;
	
	Node* plrr = plr->rchild;
	Node* plrl = plr->lchild;

	plr->lchild = pl;
	plr->rchild = p;
	p->lchild = plrr;
	pl->rchild = plrl;

	//updating Height
	p->height = NodeHeight(p);
	pl->height = NodeHeight(pl);
	plr->height = NodeHeight(plr);

	if (root == p) {
		root = plr;
	}

	return plr;
}

Node* ATree::RLRotation(Node* p) {
	Node* pr = p->rchild;
	Node* prl = pr->lchild;

	Node* prlr = prl->rchild;
	Node* prll = prl->lchild;

	prl->lchild = p;
	prl->rchild = pr;
	p->rchild = prll;
	pr->lchild = prlr;

	//updating Height
	p->height = NodeHeight(p);
	pr->height = NodeHeight(pr);
	prl->height = NodeHeight(prl);

	if (root == p) {
		root = prl;
	}

	return prl;
}

Node* ATree::Rinsert(Node* t, int key) {
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
	else if (BalanceFactor(t) == -2 && BalanceFactor(t->rchild) == -1){
		return RRRotation(t);
	}
	else if (BalanceFactor(t) == 2 && BalanceFactor(t->lchild) == -1) {
		return LRRotation(t);
	}
	else if (BalanceFactor(t) == -2 && BalanceFactor(t->rchild) == -1) {
		return RRRotation(t);
	}

	return t;
}

void ATree::Inorder(Node* p) {
	if (p) {
		Inorder(p->lchild);
		cout << p->data << " ";
		Inorder(p->rchild);
	}
}

int main() {
	int ch;
	cout << "######## Welcome to AVL Tree Data Structure ###########" << endl;
	ATree B;
	do {
		cout << "\nEnter the Operation, you want to perform on the binary tree " << endl;
		cout << "[1] - Insert an Element" << endl;
		cout << "[2] - Display Inorder" << endl;
		cout << "[0] - Quit" << endl;
		cout << "\nEnter your choice : ";
		cin >> ch;

		if (ch == 1) {

			int key;
			cout << "\nEnter the key, you want to insert in the Binary Search Tree : ";
			cin >> key;
			B.root = B.Rinsert(B.root, key);
			cout << "\nInserted Successfully" << endl;
		}
		else if (ch == 2) {
			cout << "\nINORDER : ";
			B.Inorder(B.root);
			cout << endl;
		}
		else if (ch == 0) {
			cout << "\nThanks for using the Application" << endl;
		}
		else {
			cout << "\nInvalid Choice, Enter again!" << endl;
		}

	} while (ch != 0);
	
	return 0;
}