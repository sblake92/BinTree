/* BinTree
-------------------------------------------------------
 Scott Blake CSS 343
 8 July 2019
 15 July 2019
-------------------------------------------------------------------------------
Purpose:
This program builds a Binary Search Tree using a given nodedata
file. Has standard BST functions as well as can change back and forth from
an array to a BST
----------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/

#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include "nodedata.h"

using namespace std;

class BinTree {				// you add class/method comments and assumptions
	friend ostream& operator<<(ostream &out, const BinTree &bt);

public:
	BinTree();								// constructor
	BinTree(const BinTree &);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty
	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true
	int getHeight (const NodeData &) const;
	BinTree& operator=(const BinTree &);
	bool operator==(const BinTree &) const;
	bool operator!=(const BinTree &) const;
	bool insert(NodeData*);
	bool retrieve(const NodeData &, NodeData* &) const;
	void bstreeToArray(NodeData* []);
	void arrayToBSTree(NodeData* []);
	void displaySideways() const;			// provided below, displays the tree sideways


private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

// utility functions
void deleteTree(Node *&tree);
void copy(Node *&newNode, Node *oldNode) const; // recursive function to create deep copy
int heightHelper(Node *, const NodeData &data) const; // finds node location recursively for getHeight
int findHeight(Node*) const; // recursively finds height from furthest leaf
bool eCheck(Node *, Node *) const; // recursively checks equality
bool retHelp(const NodeData &, NodeData *&, Node *) const; // recursive helper for retrieve
int toArrHelp(Node *, NodeData *[]); // recursive helper for toArray funciton
void toTreeHelp(Node *, NodeData *[], int, int); // recursive helper for toTree function
void inorderHelper(Node *curr) const; // recursive helper to ostream prints in order
void sideways(Node*, int) const;			// provided below, helper for displaySideways()

};
#endif
