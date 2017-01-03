#include "BinarySearchTree.hpp"
#include <iostream>
#include <stack>

using namespace std;

typedef BinarySearchTree::DataType DataType;

BinarySearchTree::Node::Node(DataType newval)
{
	val = newval;
	left = NULL;
	right = NULL;
    
}

BinarySearchTree::BinarySearchTree()
{
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
	
	if (root_ != NULL) {
	stack<Node*> mystack;
	
	mystack.push(root_);
		
	while (!mystack.empty()) {
	Node* visitor = mystack.top();
	mystack.pop();
	if (visitor->right != NULL) {
		mystack.push(visitor->right);
		}
		if (visitor->left != NULL) {
			mystack.push(visitor->left);
		}
	delete visitor;
	}
	}
}

void BinarySearchTree::eraseData()
{
	
	if (root_ != NULL) {
	stack<Node*> mystack;
	
	mystack.push(root_);
		
	while (!mystack.empty()) {
	Node* visitor = mystack.top();
	mystack.pop();
	if (visitor->right != NULL) {
		mystack.push(visitor->right);
		}
		if (visitor->left != NULL) {
			mystack.push(visitor->left);
		}
	delete visitor;
	}
	}
}



bool BinarySearchTree::insert(DataType val)
{
	Node* insertNode = new Node(val);
	Node* visitor = root_;
	Node* temp = root_;
	
	if (visitor == NULL) {
		root_ = insertNode;
		size_ = 1;
		return true;
	}
	
	while (visitor != NULL) {
		temp = visitor;
		if (visitor->val == val) {
			return false;
		}
		if (val > visitor->val) {
			visitor = visitor->right;
		} else {
			visitor = visitor->left;
		}
	}
	
	if (val > temp->val) {
		temp->right = insertNode;
		size_++;
		return true;
	} else {
		temp->left = insertNode;
		size_++;
		return true;
	}
    
}

int getNumChildren(BinarySearchTree::Node* N) {
	if (N->left == NULL && N->right == NULL) {
		return 0;
	} else if (N->left == NULL || N->right == NULL) {
		return 1;
	} else {
		return 2;
	}
}

bool BinarySearchTree::remove(DataType val)
{
	if (root_ == NULL) {
		return false;
	} else if(!exists(val)) {
    	return false;
    } else {
    	
    	Node** visitor = &root_;
    	
    	while ((*visitor)->val != val) {
    		
    		if (val > (*visitor)->val) {
    			visitor = &(*visitor)->right;
    		} else {
    			visitor = &(*visitor)->left;
    		}
    	}
    	
    	//cout << "Parent: " << parent->val << " , Visitor: " << visitor->val << ". Parent Children: " << getNumChildren(parent) << ". Visitor Children: " << getNumChildren(visitor) << endl;
    	
    	if (getNumChildren(*visitor) == 0) {
			(*visitor) = NULL;
    		delete (*visitor);
    		size_--;
    		return true;
    	}
    	
    	
    	if (getNumChildren(*visitor) == 1) {
    			Node* todelete = (*visitor);
				if ((*visitor)->left == NULL) {
					(*visitor) = (*visitor)->right;
				} else {
					(*visitor) = (*visitor)->left;
				}
			delete todelete;
			size_--;
			return true;
    	}
    	
    	if (getNumChildren(*visitor) == 2) { // When it has two children
    		
    		Node** visitor2 = &(*visitor)->right; // Pointer to the pointer
    		while ((*visitor2)->left != NULL) { // Traverse the Tree to the min of the right tree
    			visitor2 = &(*visitor2)->left;
    		}
    		Node* tomove = (*visitor2); // Specify the node to move
    		Node* todelete = (*visitor); // Specify the node to delete
    		(*visitor2) = (*visitor2)->right; // The pointer (Which is a dereference of the pointer to a pointer) now points to the node's right sub tree
    		tomove->left = (*visitor)->left; // The node we are moving (min of the right subtree)'s left subtree is now the deleted node's left subtree
    		tomove->right = (*visitor)->right; // Same deal as above with the right subtree
    		(*visitor) = tomove; // The pointer to the todelete node now points to our node that we are moving
    		delete todelete; // Delete the pointer 
    		size_--; // Make the size smaller
    		return true;
    	}
    	
    	
    }
}

bool BinarySearchTree::exists(DataType val) const
{
   
   
   
   
    if (size_==0) {
    	return false;
    } else {
    	Node* visitor = root_;
    	
    	while (visitor != NULL) {
    		if (val == visitor->val) {
    			return true;
    		}
    		if (val > visitor->val) {
    			visitor = visitor->right;
    		} else {
    			visitor = visitor->left;
    		}
    }
	return false;		
    }
}

DataType BinarySearchTree::min() const
{
    if (root_ == NULL) {
    	return 0;
    } else {
    	Node* visitor = root_;
    	
    	while (visitor->left != NULL) {
    		visitor = visitor->left;
    	}
    	
    	return visitor->val;
    }
}

DataType BinarySearchTree::max() const
{
    if (root_ == NULL) {
    	return 0;
    } else {
    	Node* visitor = root_;
    	
    	while (visitor->right != NULL) {
    		visitor = visitor->right;
    	}
    	
    	return visitor->val;
    }
}


unsigned int BinarySearchTree::size() const
{
	if (root_== NULL) {
		return 0;
	} else {
		stack<Node*> mystack;
		
		mystack.push(root_);
		
		int counter = 0;
		
		while (!mystack.empty()) {
			Node* visitor = mystack.top();
			mystack.pop();
			counter++;
			if (visitor->left != NULL) {
				mystack.push(visitor->left);
			}
			if (visitor->right != NULL) {
				mystack.push(visitor->right);
			}
		}
		
		return counter;
	}
}

unsigned int BinarySearchTree::depth() const
{
	if (root_ == NULL) {
		return 0;
	} else {
    getNodeDepth(root_);
	}
}


void BinarySearchTree::print() const{
    
    if (size_ == 0) {
    	std::cout << "|---Tree Is Empty---|" << std::endl;
    } else {
    	std::cout << "---Printing In Prefix Order---" << std::endl;
    	stack<Node*> mystack;
		mystack.push(root_);
		while (!mystack.empty()) {
			Node* visitor = mystack.top();
			mystack.pop();
			cout << "Node with value: " << visitor->val << " Has depth: " << getNodeDepth(visitor) << endl;
			if (visitor->right != NULL) {
				mystack.push(visitor->right);
			}
			if (visitor->left != NULL) {
				mystack.push(visitor->left);
			}
		}
    	
    	std::cout << "---End of Tree---" << std::endl;
    }
}




int BinarySearchTree::getNodeDepth(Node* n) const
{
	if (n == NULL) {
		return 0;
	} else if (n->right == NULL && n->left == NULL) {
		return 0;
	} else {
		int a = getNodeDepth(n->left);
		int b = getNodeDepth(n->right);
		//cout << "-D-Node value: " << n->val << " A: " << a << "  And B:" << b <<"-D-";
		if (a >= b) {
			//cout << " , Choosing A" << endl;
			return a+1;
		} else {
			//cout << " , Choosing B" << endl;
			return b+1;
		}
	}
}
