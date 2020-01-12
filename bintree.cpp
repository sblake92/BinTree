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

#include "bintree.h"

using namespace std;

/* Constructors */
// Empty
BinTree::BinTree()
{
  root = NULL;
}

/*---------------Copy Constructor ----------------------------
Description: function to copy values of one tree to create another
preconditions: Incoming source is a completed tree.
postconditons: new tree is same as passed in tree
Special Algorithms: uses recursive function copy()
--------------------------------------------------------------*/
BinTree::BinTree(const BinTree &source)
{
  copy(root, source.root);
}

/*---------------Copy ----------------------------
Description: Recursive copy constructor helper. First checks if incoming is Empty
then allocates new memory for a new node as well as its data and recursively
deep copies from the incoming BS
preconditions: copy constructor called to create new tree
postconditons: new tree is same as passed in tree
Special Algorithms: recusion calls for left and right nodes
--------------------------------------------------------------*/
void BinTree::copy(Node *&newNode, Node *oldNode) const
{
    if(oldNode == NULL)
    {
      newNode = NULL;
    }
    else
    {
      newNode = new Node;
      NodeData *n = new NodeData(*oldNode->data);
      newNode->data = n;
      copy(newNode->left, oldNode->left);
      copy(newNode->right, oldNode->right);
    }
}

/* Deconstructor */
BinTree::~BinTree()
{
  makeEmpty();
}

/* checks if tree is empty by looking at the root */
bool BinTree::isEmpty() const
{
  return root == NULL;
}

/*---------------makeEmpty ----------------------------
Description: uses recursive function to deallocate memory and delete trees
preconditions: tree is full of data values
postconditons: tree memory is completely deallocated
Special Algorithms: uses recursive functin deleteTree()
--------------------------------------------------------------*/
void BinTree::makeEmpty()
{
  deleteTree(root);
}

/* Recursively goes through tree deleting each node and deallocating memory */
void BinTree::deleteTree(Node *&tree)
{
  if(tree != NULL)
  {
    deleteTree(tree->left); //traverse left subtree
    deleteTree(tree->right); //traverse right subtree
    delete tree->data; //deletes data
    tree->data = NULL;
    delete tree; //deletes node
    tree = NULL;
  }
}

/*---------------getHeight ----------------------------
Description: first of 3 functions which recursively checks height
preconditions: tree is a valid BinTree
postconditons: the height of the desired node is given as an int
Special Algorithms: uses 2 recursive functions. One to find the location
of the node, the second to find its height from the furthest subtree
--------------------------------------------------------------*/
int BinTree::getHeight(const NodeData &data) const
{
  return heightHelper(root, data);
}

/* recursive funtion to find location of desired node */
int BinTree::heightHelper(Node *n, const NodeData &data) const
{
  if(n == NULL) // if root is null, return 0
  {
    return 0;
  }
  if(data == *n->data) // if root is the requested data then find its height
  {
    return findHeight(n);
  }
  else
  {
    int lCount = heightHelper(n->left, data); // look down the left subtree
    int rCount = heightHelper(n->right, data); // search right subtree
    return max(lCount, rCount); // return whichever is subtree is larger
  }
}

/* recursive function that finds desired nodes height from the furthest leaf
in its subtree */
int BinTree::findHeight(Node *loc) const
{
    if(loc == NULL) // base case to end recursive call
    {
      return 0;
    }
    else
    { /* returns greater value between the left and right subtrees of the subtree*/
      return 1 + max(findHeight(loc->left), findHeight(loc->right));
    }
}

/*--------------- Assignment ----------------------------
Description: sets one tree equal to another and creates a deep Copy
preconditions: 2 trees have been created
postconditons: both trees are the same
Special Algorithms: uses copy() function. Similar to copy constructor
--------------------------------------------------------------*/
BinTree &BinTree::operator=(const BinTree &bt)
{
  if(*this == bt) // if already equal return original
  {
    return *this;
  }
  else
  {
    makeEmpty(); // empty current tree
    copy(root, bt.root); // create deep copy using recursive function
    return *this;
  }
}

/*--------------- Print function ----------------------------
Description: prints out the tree in Inorder
precondions: none
postconditons: tree remains same
Special Algorithms: uses recursive inorderHelper() function
--------------------------------------------------------------*/
ostream& operator<<(ostream &out, const BinTree &bt)
{
    bt.inorderHelper(bt.root);
    out << " " << endl;
    return out;
}

/* recursively prints out data in order */
void BinTree::inorderHelper(Node *curr) const
{
  if(curr != NULL)
  {
    inorderHelper(curr->left);
    cout << *curr->data;
    inorderHelper(curr->right);
  }
}

/*---------------Equality ----------------------------
Description: checks if 2 trees are equal to one another
precondions: none
postconditons: tree remains same
Special Algorithms: uses eCheck() recursive funciton to test
equality
--------------------------------------------------------------*/
bool BinTree::operator==(const BinTree &bt) const
{
  if(root == NULL && bt.root == NULL) // if both are NULL automatically return true
  {
    return true;
  }
  else
  {
    return eCheck(root, bt.root); // recursive function to check
  }
}

bool BinTree::eCheck(Node *left, Node *right) const
{
  if(left == NULL && right == NULL) // checks if both are null first and returns true if so
  {
    return true;
  }
  if(left == NULL || right == NULL) // if one is null and the other isnt, return false
  {
    return false;
  }
  if(*left->data == *right->data && //if the data is equal and both children are null return true
    (left->left == NULL && right->left == NULL) &&
    (left->right == NULL && right->right == NULL))
    {
      return true;
    }
    else
    { //otherwise keep the data the same, then recursively check the left and right subtrees
      return (*left->data == *right->data &&
        eCheck(left->left, right->left) &&
        eCheck(left->right, right->right));
    }
}

/* inverse of equality */
bool BinTree::operator!=(const BinTree &bt) const
{
  return !(*this == bt);
}

/*---------------Insert ----------------------------
Description: iteratively inserts node in order positions. left < root < right
preconditions: tree has been created and data being input is valid
postconditons: tree has node added in proper position
--------------------------------------------------------------*/
bool BinTree::insert(NodeData *item)
{
  Node *node = new Node; // allocate new memory for a node
  node->data = item;
  node->left = NULL;
  node->right = NULL;

  if(root == NULL) // if root is empty, insert as root
  {
    root = node;
  }
  else
  {
    Node *current = root;
    while(true)
    {
      if(*item == *current->data) // if is equal to data, deallocate memory for
      {                           // created node and return false
        delete node;
        node = NULL;
        return false;
      }
      else if(*item < *current->data) // if it is less than root, traverse left
      {                               // subtree to find location to insert
        if (current->left == NULL)
        {
          current->left = node;
          break;
        }
        else
        {
          current = current->left;
        }
      }
      else // if it is greater than the root, traverse the right subtree to find
      {     // location to insert node
        if(current->right == NULL)
        {
          current->right = node;
          break;
        }
        else
        {
          current = current->right;
        }
      }
    }
  }
  return true;
}

/*---------------Retrieve ----------------------------
Description: searches for node with desired data and returns if found
preconditions: none
postconditons: tree remains same and node is returned if found
Special Algorithms: recursive retHelp() function used to check for data
--------------------------------------------------------------*/
bool BinTree::retrieve(const NodeData &item, NodeData *&key) const
{
  retHelp(item, key, root);
  if(key != NULL)
  {
    return true;
  }
  return false;
}

/*recursively looks for the desired data and returns it if found */
bool BinTree::retHelp(const NodeData &item, NodeData *&key, Node *curr) const
{
  if(curr == NULL) // if root is null then return false
  {
    key = NULL;
    return false;
  }
  if(item == *curr->data) // base case, if found assign key to the value and return true
  {
    key = curr->data;
    return true;
  }
  else if(item < *curr->data) //if the desired value is less than node, traverse
  {                     // left subtree to find item
    retHelp(item, key, curr->left);
  }
  else if (item > *curr->data) // otherwise traverse right subtree
    {
      retHelp(item, key, curr->right);
    }
  else // if it is not found return false
  {
    return false;
  }
}

/*-------------- BST to Array ----------------------------
Description: takes values from tree and creates an array
preconditions: BinTree has values to be transfered to an array
postconditons: array is filled and tree is deleted to avoid mem leak
Special Algorithms: recursive toArrHelp() used
--------------------------------------------------------------*/
void BinTree::bstreeToArray(NodeData* arr[])
{
  toArrHelp(root, arr);
  makeEmpty();
}

// recursively searches left and right sub trees and places nodes at proper
// array index
int BinTree::toArrHelp(Node *curr, NodeData *temp[])
{
  int left; // this will be left postion index
  int right; // right postion index
  if(curr == NULL)
  {
    return 0;
  }
  left = toArrHelp(curr->left, temp); // sets the left
  NodeData *test; // creates NodeData
  test = curr->data; // set data equal to passed in node->data
  curr->data = NULL; // set pointer to null of passed in node
  *(left + temp) = test; // passed in array points ot created NodeData
  test = NULL; // set created NodeData to Null
  right = toArrHelp(curr->right, (temp + 1 + left)); // set right postion
  return ((right + left) + 1); // return postion
}

/*-------------- Array to BST ----------------------------
Description: takes values from array and creates a BST
preconditions: array has values to be transferred to tree
postconditons: BST is created using data in array
Special Algorithms: recursive toTreeHelp() used
--------------------------------------------------------------*/
void BinTree::arrayToBSTree(NodeData* arr[])
{
  makeEmpty(); // first empty current BST
  int high = 0;
  for(int i = 0; i < 100; i++) // assignment instructions provide max array size
  {
    if(arr[i] != NULL) // find out how many index are being used
    {
      high++; // total number of used index
    }
    else
    {
      arr[i]= NULL;
    }
  }
  toTreeHelp(root, arr, 0, high-1); // recursive function to set tree
}
/*-------------- BST to Array ----------------------------
Special Algorithms: uses insert() to create tree from data
--------------------------------------------------------------*/
void BinTree::toTreeHelp(Node *curr, NodeData *temp[], int low, int high)
{
  if(low > high) // Base case, end of array
  {
    curr = NULL;
  }
  else
  {
    int root = (low + high) / 2; // root is item in middle of array
    NodeData *test;
    test = temp[root]; // creates root of tree
    temp[root] = NULL; // sets index of root to  null

    insert(test); // insert root

    toTreeHelp(curr, temp, low, root - 1); // recursively set left side of tree
    toTreeHelp(curr, temp, root + 1, high); // recursively set right side of tree
  }
}
//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}
