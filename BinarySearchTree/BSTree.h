#pragma once
#include <iostream>
using namespace std;
#include <cmath>
#include "SafeArray.h"
template <class T>
class BSTree
{
public:
	BSTree();//- constructor to initialize class data
	~BSTree();//- free up any resources acquired
	void insert(const T& d);//- insert an element into the tree
	bool search(const T& d);//- search for an element in the tree
	bool remove(const T& d);//- remove an element from the tree
	int size();
	void printInOrder();//- print the items in ascending order
	void printPreorder();//- print the items in preorder fashion
	void printPostOrder();//- print the items in postorder fashion
	T findMax();//- return the maximum value in the tree
	T findMin();//- return the minimum value in the tree
	int heightOfTree();//- return the height of the tree
	double percentLeaf();//- return the percentage of nodes that are leaf nodes
	double percentInterior();//- return the percentage of nodes that are interior nodes
	void printInTreeForm();//- print the tree in tree form
private:
	int numNodes;
	struct Node
	{
		Node* right;
		Node* left;
		T data;
		int heightLeft;
		int heightRight;
	};
	void insertHelper(Node*& p_node, const T& elem);
	void postOrderHelper(Node* p_node);
	void preOrderHelper(Node* p_node);
	void inOrderHelper(Node* p_node);
	void destructorHelper(Node* p_node);
	bool searchHelper(Node* p_node, T val);
	bool removeHelper(Node*& p_node, T val);
	void percentLeafHelper(Node* p_node);
	void percentInteriorHelper(Node* p_node);
	void balanceLeft(Node*& p_node);
	void balanceRight(Node*& p_node);
	bool isBalanced(Node* p_node);
	int setHeightHelper(Node* p_node);
	void findPositionHelper(Node* p_node, int posInArray, SafeArray<Node*>& arr);
	Node* root;
	int numLeaf;
	int numInteriors;
};

template <class T>
BSTree <T> :: BSTree()
{
	//sets default values to variables
	numNodes = 0;
	numInteriors = 0;
	numLeaf = 0;
	root = NULL;
}

template <class T>
BSTree <T>:: ~BSTree()
{
	destructorHelper(root);
}

template <class T>
void BSTree <T>:: destructorHelper(Node* p_node)
{
	//if p_node is not null it will recurse down the tree and begin deleting the tree upwards
	if(p_node != 0)
	{
		destructorHelper(p_node -> left);
		destructorHelper(p_node -> right);
		delete p_node;
		numNodes--;
	}
}

template <class T>
bool BSTree <T>:: search(const T& d)
{
	return searchHelper(root, d);	
}

template <class T>
bool BSTree <T>:: searchHelper(Node* p_node, T val)
{
	//will return true if the data is found in the tree and false if it is not
	if( p_node -> data == val)
	{
		return true;
	}
	else if(p_node -> right == 0 && p_node -> left == 0)
	{
		return false;
	}
	else if(p_node -> data < val)
	{
		return searchHelper(p_node -> right, val);
	}
	else
	{
		return searchHelper(p_node -> left, val);
	}
}

template <class T>
bool BSTree <T>:: remove(const T& d)
{
	return removeHelper(root, d);
}

template <class T>
int BSTree <T>:: size()
{
	return numNodes;
}

template<class T>
void BSTree <T>:: printPreorder()
{
	preOrderHelper(root);
}

template <class T>
void BSTree <T>:: preOrderHelper(Node* p_node)
{
	//will return things in right, left, process ordering
	if(p_node != 0)
	{
		preOrderHelper(p_node -> right);
		preOrderHelper(p_node -> left);
		cout << p_node -> data << endl;
	}
}

template <class T>
void BSTree <T>:: printPostOrder()
{
	postOrderHelper(root);
}

template <class T>
T BSTree <T>:: findMax()
{
	//will iterate and search to the right of the tree to find the largest value
	Node* p_max = root;
	while(p_max-> right != 0)
	{
		p_max = p_max->right;
	}
	return p_max -> data;
}

template <class T>
T BSTree <T>:: findMin()
{
	//will iterate and search to the  left of the tree to find the smallest value
	Node* p_min = root;
	while(p_min-> left != 0)
	{
		p_min = p_min->left;
	}
	return p_min -> data;
}

template <class T>
int BSTree <T>:: heightOfTree()
{
	//will search and compare the height right and the left right as searching down the tree.
	if(numNodes > 0)
	{
		if(root -> heightRight > root -> heightLeft)
		{
			return root -> heightRight + 1;
		}
		else
		{
			return root -> heightLeft + 1;
		}
	}
	else 
	{
		return 0;
	}
}

template <class T>
double BSTree <T>:: percentLeaf()
{
	numInteriors = 0;
	numLeaf = 0;
	percentLeafHelper(root);
	return ((double)numLeaf / (double) numNodes);
}

template <class T>
double BSTree <T>:: percentInterior()
{
	numInteriors = 0;
	numLeaf = 0;
	percentInteriorHelper(root);
	return((double) numInteriors / (double) numNodes);
}

template <class T>
void BSTree <T>:: percentLeafHelper(Node* p_node)
{
	//will calculate the percentage of leaves in the tree
	if(p_node != 0)
	{
		//if you get to the bottom of the tree at any point it will add to the counter of leaves
		percentLeafHelper(p_node -> left);
		if(p_node -> right == 0 && p_node -> left == 0)
		{
			numLeaf++;
		}
		percentLeafHelper(p_node -> right);
	}
}

template <class T>
void BSTree <T>:: percentInteriorHelper(Node* p_node)
{
	//will keep track of the number of non leaf nodes in the tree
	if(p_node != 0)
	{
		//anytime that it is not at a bottom point of the tree it will add to the counter of interiors
		percentInteriorHelper(p_node -> left);
		if(!(p_node -> right == 0 && p_node -> left == 0))
		{
			numInteriors++;
		}
		percentInteriorHelper(p_node -> right);
	}
}

template <class T>
void BSTree <T>:: printInTreeForm()
{
	if(heightOfTree() > 0)
	{
		//creates the size of the array based tree
		int y = heightOfTree();
		int treeSize = ((int)(pow(2.0, (double) heightOfTree()) - 1.0)); 
		SafeArray <Node*> tree(treeSize);

		//initialize all node pointers in array to null
		for(unsigned int i = 0; i < tree.size(); i++)
		{
			tree[i] = NULL;
		}
	
		//set the nodes to the array
		findPositionHelper(root, 0, tree);

		double currRow = 0.0;
		//this will begin printing in tree form
		for(unsigned int i = 0; i < tree.size(); i++)
		{
			//if the node is not null it will print the data
			if(tree[i] != NULL)
			{
				if(i == 0)
				{
					//this makes leading spaces
					for(int j = 0; j < ((int)pow(2.0, ((double)heightOfTree() - 1) - currRow) - 1); j++)
					{
						cout << "  ";
					}
				}
				//check if 1 digit
				if(tree[i] -> data / 10 < 1)
				{
					cout << " ";
				}
				cout << tree[i] -> data;

				//this makes spaces between values
				for(int k = 0; k < ((int)pow(2.0, (double)heightOfTree() - currRow) - 1); k++)
				{
					cout << "  ";
				}
				//this will keep track of the row of the tree that we are on and end the lines.
				if(i == 0 || i == ((int) pow(2.0, (currRow + 1)) - 2))
				{
					cout << endl;
					currRow = currRow + 1;
					//this makes leading spaces
					for(int j = 0; j < ((int)pow(2.0, (double)heightOfTree() - 1 - currRow) - 1); j++)
					{
						cout << "  ";
					}
				}
			}
			else
			{
				cout << "XX";
				//this makes spaces between values
				for(int k = 0; k < ((int)pow(2.0, (double)heightOfTree() - currRow) - 1); k++)
				{
					cout << "  ";
				}
			}
		}
	}
	else
	{
		cout << "There is no longer a tree." << endl;
	}
}

template <class T>
void BSTree <T>:: insert(const T& d)
{
	insertHelper(root, d);	
}

template <class T>
void BSTree <T>::insertHelper(Node*& p_node, const T& elem)
{
	//bool retVal = false;
	//will add a new node
	if(p_node == 0)
	{
		p_node = new Node;
		p_node -> right = 0;
		p_node -> left = 0;
		p_node -> heightRight = 0;
		p_node -> heightLeft = 0;
		p_node -> data = elem;
		numNodes++;
		setHeightHelper(root);
	}
	else 
	{
		//will mean that the elem is less than the data found and will search to the left of the tree
		if(elem <= p_node -> data)
		{
			insertHelper(p_node -> left, elem);
			
			//this will balance the tree
			if(!isBalanced(p_node))
			{
				balanceLeft(p_node);
				setHeightHelper(root);
				if(!isBalanced(p_node))
				{
					balanceLeft(p_node ->right);
					balanceRight(p_node);
					setHeightHelper(root);
				}
			}
			
		}
		else
		{
			insertHelper(p_node -> right, elem);
			//this will balance the tree
			if(!isBalanced(p_node))
			{
				balanceRight(p_node);
				//will reset the heights after being balanced
				setHeightHelper(root);
				if(!isBalanced(p_node))
				{
					balanceRight(p_node -> left);
					balanceLeft(p_node);
					//will reset the heights after being balanced
					setHeightHelper(root);
				}
			}
		}
	}
	//return retVal;
}

template <class T>
bool BSTree <T>:: isBalanced(Node* p_node)
{
	//will check if it is balanced at the p_node passed in
	if(p_node -> heightRight - p_node -> heightLeft > 1 || p_node -> heightRight - p_node -> heightLeft < -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template <class T>
void BSTree <T>:: printInOrder()
{
	inOrderHelper(root);
}

template <class T>
void BSTree <T>:: inOrderHelper(Node* p_node)
{
	if(p_node != 0)
	{
		inOrderHelper(p_node -> left);
		cout << p_node -> data << endl;
		inOrderHelper(p_node -> right);
	}
}
template <class T>
void BSTree <T>:: postOrderHelper(Node* p_node)
{
	if(p_node != 0)
	{
		postOrderHelper(p_node -> left);
		postOrderHelper(p_node -> right);
		cout << p_node -> data;
	}
}

template <class T>
bool BSTree <T>::removeHelper(Node*& p_node, T val)
{ 
	bool retVal = false;
	if(p_node != 0)
	{
		if(p_node -> data == val)
		{
			//if it is not a null pointer and the data desired matches the p_node data this happpens
			retVal = true;
			if(p_node -> right == 0 && p_node -> left == 0)
			{
				delete p_node;
				p_node = 0;
				numNodes--;
			}
			else if(p_node -> right == 0 && p_node -> left != 0)
			{
				Node* p_delete = p_node;
				p_node = p_node -> left;
				delete p_delete;
				numNodes--;
			}
			else if(p_node -> left == 0 && p_node -> right != 0)
			{
				Node* p_delete = p_node;
				p_node = p_node -> right;
				delete p_delete;
				numNodes--;
			}
			else
			{
				//go left and find the largest number
				Node* p_left = p_node->left;
				while(p_left-> right != 0)
				{
					p_left = p_left->right;
				}

				//replace the node that we are trying to remove's data w/ the largest value on the left
				p_node->data = p_left -> data;

				//call removeHelper & pass in the left node and largest value
				removeHelper(p_node -> left, p_node -> data);
			}
			//will reset the heights after any remove happens in the tree
			setHeightHelper(root);
		}
		else if(p_node ->data <= val)
		{

			retVal = removeHelper(p_node -> right, val);
			//rebalance and recalculate the height of the tree
			if(!isBalanced(p_node))
			{
				balanceLeft(p_node);
				//will reset the heights after being balanced
				setHeightHelper(root);
				if(!isBalanced(p_node))
				{
					balanceRight(p_node -> left);
					balanceLeft(p_node);
					//will reset the heights after being balanced
					setHeightHelper(root);
				}
			}
		}
		else
		{
			retVal = removeHelper(p_node -> left, val);	
			//will recalculate the height of the tree and will balance any unbalanced tree
			if(!isBalanced(p_node))
			{
				balanceRight(p_node);
				setHeightHelper(root);
				if(!isBalanced(p_node))
				{
					balanceLeft(p_node ->right);
					balanceRight(p_node);
					setHeightHelper(root);
				}
			}
		} 
	}

	return retVal;
}

template <class T>
void BSTree <T>:: balanceLeft(Node*& p_node)
{
	if(p_node != 0)
	{
		Node* p_curr = p_node;
		Node* p_newRoot = p_curr -> left;
		Node* p_newRootsRight = p_newRoot -> right;
		p_newRoot -> right = p_curr;
		p_curr -> left = p_newRootsRight;
		p_node = p_newRoot;
	}
}

template <class T> 
void BSTree <T>:: balanceRight(Node*& p_node)
{
	if(p_node != 0)
	{
		Node* p_curr = p_node;
		Node* p_newRoot = p_curr -> right;
		Node* p_newRootsLeft = p_newRoot -> left;
		p_newRoot -> left = p_curr;
		p_curr -> right = p_newRootsLeft;
		p_node = p_newRoot;
	}
}

template <class T> 
int BSTree <T>:: setHeightHelper(Node* p_node)
{
	//will be used to reset the heights when they are altered by inserting or removing from the tree.
	if(p_node !=0)
	{
		p_node -> heightLeft = setHeightHelper(p_node -> left) + 1;
		p_node -> heightRight = setHeightHelper(p_node -> right) + 1;
		
		if(p_node -> heightLeft >= p_node -> heightRight)
		{
			return p_node -> heightLeft;
		}
		else
		{
			return p_node -> heightRight;
		}
	}
	else
	{
		return -1;
	}
}

template <class T> 
void BSTree <T>:: findPositionHelper(Node* p_node, int posInArray, SafeArray <Node*>& arr)
{
	if(p_node != 0)
	{
		arr[posInArray] = p_node;
		findPositionHelper(p_node -> left, (2 * posInArray) + 1, arr);
		findPositionHelper(p_node -> right, (2 * posInArray) + 2, arr);
	}
}
