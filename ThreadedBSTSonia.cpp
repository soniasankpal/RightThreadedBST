/* C++ program to convert a Binary Tree to
	Threaded Tree */
#include <bits/stdc++.h>
#include <iostream>
#include <ostream>
using namespace std;

typedef int T;
typedef int KEY;
struct Elem {
	KEY key;
	T data;
	Elem *left;
	Elem *right;
	bool rightThread; //normal right child link or a threadlink
};
Elem *_root; // a dummy root sentinel
int _size;

Elem *createThreaded(Elem *root)
{
	// Base cases : Tree is empty or has single
	//			 Elem
	if (root == NULL)
		return NULL;
	if (root->left == NULL &&
		root->right == NULL)
		return root;

	// Find predecessor if it exists
	if (root->left != NULL)
	{
		// Find predecessor of root (Rightmost
		// child in left subtree)
		Elem* l = createThreaded(root->left);

		// Link a thread from predecessor to
		// root.
		l->right = root;
		l->rightThread = true;
	}

	// If current Elem is rightmost child
	if (root->right == NULL)
		return root;

	// Recur for right subtree.
	return createThreaded(root->right);
}

Elem *leftMost(Elem *root)
{
	while (root != NULL && root->left != NULL)
		root = root->left;
	return root;
}



// A utility function to create a new Elem
Elem *newElem(KEY key,T data)
{
	Elem *temp = new Elem;
	temp->left = temp->right = NULL;
	temp->key = key;
	temp->data = data;
	return temp;
}

// helper method for print tree
void inorder(ostream& out, Elem *root)
{
    //out = cout;
    if (root == NULL) return;

	// Find the leftmost Elem in Binary Tree
	Elem *cur = leftMost(root);

	while (cur != NULL)
	{
		out <<cur->key << " - "<< cur->data << " || ";

		// If this Elem is a thread Elem, then go to
		// inorder successor
		if (cur->rightThread)
			cur = cur->right;

		else // Else go to the leftmost child in right subtree
			cur = leftMost(cur->right);
	}
}

bool insert(Elem *& root, const KEY &key, const T &data)
{
   
	Elem *newNode = newElem(key,data);
	Elem *current=root;
	Elem* parent =NULL;
	while(true)
	{
	    //cout<<"check1";
		parent=current;
		//left subtree
		if(key < current->key)
		{
			current=current->left;
			if(current==NULL)
			{
				parent->left=newNode;
				newNode->right=parent;
				newNode->rightThread=true;
				return true;
			}
		}
		//right subtree
		else
		{
		   // cout<<"check2";
			if(current->rightThread==false)
			{
				current=current->right;
				if(current==NULL)
				{
					parent->right=newNode;
					return true;
				}
			}
			//cout<<"check3";
			Elem* temp=current->right;
			current->right=newNode;
			newNode->right=temp;
			newNode->rightThread=true;
			return true;
		}
	}
	
}

void destructCode(Elem * node)
{
    if (node == NULL) return;

    /* first delete both subtrees */
    destructCode(node->left);
    destructCode(node->right);

    /* then delete the node */
    cout << "\n Deleting node: " << node->key <<"+"<< node->data;
    delete (node);
	node=NULL;
}

void printTree(ostream& out, int level, Elem *root)
{

    if (root == NULL)
        return;

    if (level == 1) {

            out <<root->key << " - "<< root->data << " || ";

    }
    else if (level > 1) {
        printTree(cout,level - 1,root->left);
        printTree(cout,level - 1,root->right);
    }
}

// Driver program to test above functions
int main()
{
	Elem *root = newElem(1,1);
	root->left = newElem(2,2);
	root->right = newElem(3,3);
	root->left->left = newElem(4,4);
	root->left->right = newElem(5,5);
	root->right->right = newElem(7,7);
	insert(root,10,10);
	insert(root,15,15);

	createThreaded(root);

	cout << "Inorder traversal of created threaded tree is\n";
	inorder(cout,root);
	int level;
	cout<<"\nenter level number?";
	cin>>level;
	cout<<" printing tree Level wise : \n";
	printTree(cout,level,root);
	cout<<"\n delete tree: \n";
	destructCode(root);
	//root=NULL;


	return 0;
}
