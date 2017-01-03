#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

// Defines a pointer-based binary search tree. The tree is always traversed by
// starting at the root node, then following its children.
// This tree does not have to be balanced.
class BinarySearchTree
{
  friend class BinarySearchTreeTest;

public:
  // Can be seen externally as BST::DataType
	typedef int BSTDataType; 
  
public:
  struct Node {
    // Constructor. Sets the left and right children to NULL, and initializes val.
    Node(BSTDataType newval);
    
    BSTDataType val;  // value of the node
    Node* left;    // left child
    Node* right;   // right child
  };
  
public:
  // Default constructor.
  BinarySearchTree();
  // Destructor.
  ~BinarySearchTree();
  
  // Inserts value "val" into the tree. Returns false if failed (i.e., "val"
  // already exists in the tree), and true otherwise.
  bool insert(BSTDataType val);
  // Removes the node with value "val" from the tree. Returns true if successful,
  // false otherwise.
  bool remove(BSTDataType val);
  
  void eraseData();
  
  // Returns true if a node with value "val" exists in the tree; false otherwise.
  bool exists(BSTDataType val) const;
  // Returns the minimum value of the tree. You can assume that this function
  // will never be called on an empty tree.
  BSTDataType minFunction() const;
  // Returns the maximum value of the tree. You can assume that this function
  // will never be called on an empty tree.
  BSTDataType maxFunction() const;
  // Returns the number of nodes in the tree.
  unsigned int size() const;
  // Returns the maximum depth of the tree. A tree with only the root node has a
  // depth of 0. You can assume that this function will never be called on an 
  // empty tree.
  unsigned int depth() const;
  
  // You can print the tree in which ever manner you like, however methods such
  // as in-order, level-order, etc. might be the most useful for debugging
  // purposes.
  void print() const;
  
private:
  // Optional function.
  // Recursively get the maximum depth from a given node. Call on root_ first.
  // This might be of great value to you in depth().
  int getNodeDepth(Node* n) const;
  
private:
  // Pointer to the root node.
  Node* root_;
  // Number of nodes in the tree.
  unsigned int size_;

private:
  // Override copy constructor and assignment operator in private so we can't
  // use them.
  BinarySearchTree(const BinarySearchTree& other) {}
  BinarySearchTree& operator=(const BinarySearchTree& other) {}
};

#endif  //BINARY_SEARCH_TREE_HPP
