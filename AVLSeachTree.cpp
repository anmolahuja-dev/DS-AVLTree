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

void ATree::deleteNodes(Node* t) {
	if (t) {
		deleteNodes(t->lchild);
		delete t;
		deleteNodes(t->rchild);
	}
}

Node* ATree::InPre(Node* p) {
	while (p && p->rchild != nullptr) {
		p = p->rchild;
	}
	return p;
}

Node* ATree::InSucc(Node* p) {
	while (p && p->lchild != nullptr) {
		p = p->lchild;
	}
	return p;
}

Node* ATree::Delete(Node* p, int key) {
	Node* q;
	if (p == nullptr) {
		return nullptr;
	}
	if (p->lchild == nullptr && p->rchild == nullptr) {
		if (p == nullptr) {
			root = nullptr;
		}
		delete p;
		return nullptr;
	}
	if (key < p->data) {
		p->lchild = Delete(p->lchild, key);
	}
	else if (key > p->data) {
		p->rchild = Delete(p->rchild, key);
	}
	else {
		if (NodeHeight(p->lchild) < NodeHeight(p->rchild)) {
			q = InPre(p->lchild);
			p->data = q->data;
			p->lchild = Delete(p->lchild, q->data);
		}
		else {
			q = InSucc(p->rchild);
			p->data = q->data;
			p->rchild = Delete(p->rchild, q->data);
		}
	}


	// Update height
	p->height = NodeHeight(p);

	// Balance Factor and Rotation
	if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) {  // L1 Rotation
		return LLRotation(p);
	}
	else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1) {  // L-1 Rotation
		return LRRotation(p);
	}
	else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1) {  // R-1 Rotation
		return RRRotation(p);
	}
	else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1) {  // R1 Rotation
		return RLRotation(p);
	}
	else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 0) {  // L0 Rotation
		return LLRotation(p);
	}
	else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 0) {  // R0 Rotation
		return RRRotation(p);
	}
	return p;

}

int main() {
	int ch;
	cout << "######## Welcome to AVL Tree Data Structure ###########" << endl;
	ATree B;
	do {
		cout << "\nEnter the Operation, you want to perform on the binary tree " << endl;
		cout << "[1] - Insert an Element" << endl;
		cout << "[2] - Display Inorder" << endl;
		cout << "[3] - Delete a Node" << endl;
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
		else if (ch == 3) {
			int key;
			cout << "\nEnter the key, you want to delete from the Binary Search Tree : ";
			cin >> key;

			B.Delete(B.root, key);
			cout << "Deleted Successfully! " << endl;
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