//
// Name: Aaron Barlow
// Date: 3/29/2016
// Description: Header file that encapsulates the
// templated tree class with its public and private methods.
//

#pragma once
using namespace std;

// Declare a templated tree class
template<class T>
class Tree {
public:
   Tree(); // constructor
   ~Tree(); // destructor
   Tree<T>* get_root(); // public method to access root
   Tree<T>* get_left(); // public method to access left child
   Tree<T>* get_right(); // public method to access right child
   T get_data(); // public method to access data
   void insert(T data, bool (*cp)(T, T));
   T* search(Tree* node, T d, bool (*eq)( T, T ), int num_searches);
private:
   T data; // Generic data
   Tree* root; // Root (base node)
   Tree* left; // Left child
   Tree* right; // Right child
   void remove(Tree* node); // Helper for destructing all nodes
};


//
// get_root
// Returns the root
//
template<class T>
Tree<T>* Tree<T>::get_root() {
   return root;
}

//
// get_left
// Returns the left child
//
template<class T>
Tree<T>* Tree<T>::get_left() {
   return left;
}

//
// get_right
// Returns the right child
//
template<class T>
Tree<T>* Tree<T>::get_right() {
   return right;
}

//
// get_data
// Returns the templated data
//
template<class T>
T Tree<T>::get_data() {
   return data;
}


//
// Constructor for Tree
// Explicitly sets the left and right node to null
//
template<class T>
Tree<T>::Tree() {
   left = right = NULL;
}

//
// Destructor
// Call the remove method to remove all nodes attached to root and including root
//
template<class T>
Tree<T>::~Tree() {
   remove(root);
}

//
// remove
// Recursively call remove on node to
// delete the nodes from left to right.
//
template<class T>
void Tree<T>::remove(Tree* node) {
   // Ensure the current node exists
   if(node == NULL) return;
   if(node->left != NULL) remove(node->left);
   if(node->right != NULL)remove(node->right);
   // Deallocate node
   delete node;
}

//
// insert
// Given a templated data and a function pointer for the comparison
// of the data, set the first inserted data equal to root.
// If the data is not root, then find it's order by comparing data with
// the function pointer and place it in the location in which it is
// alphebetically ordered against other nodes.
//
template<class T>
void Tree<T>::insert( T data, bool (*cp)(T, T)) {
   // When the element is the first in the tree
   if( root == NULL ) {
      // Create a new tree and set it to root
      root = new Tree<T>;
      root->data = data;
      root->left = root->right = NULL;
   } else { // Not the first element in the tree
      Tree *current = root;
      bool inserted = false;
      
      // Search the tree to identify the alphebetically correct location to place the data
      do {
         // Use the function pointer to compare the current node's data against the new data
         if ( cp(current->data, data) ) {
            // When the current tree node does not exist
            if ( current->left == NULL ) {
               // Create a new node with the data
               current->left = new Tree<T>;
               current->left->data = data;
               inserted = true;
            } else { // The left node already exists
               // Set current to the left node
               current = current->left;
            }
         } else { // Date is greater than current node's data
            // When the curent node does not exist
            if ( current->right == NULL ) {
               // Create a new tree node with the data
               current->right = new Tree<T>;
               current->right->data = data;
               inserted = true;
            } else { // The right node already exists
               // Set current to the right node
               current = current->right;
            }
         }
      // Continue to search the tree until the appropriate
      // position is identified and the tree node is inserted
      } while( !inserted );
   }
   
}

//
// search
// Recursively searches through the tree until the given data matches
// The node's data and recursively goes back up to base and return
// a pointer to the data. Also, print the number of nodes that were traversed.
// If the data is never found in the tree, return a null pointer.
//
template<class T>
T* Tree<T>::search(Tree* node, T d, bool (*eq)( T, T ), int num_searches) {
   // Ensure node exists
   if(node == NULL) return NULL;
   
   // Determine if node's data is equal to given data using the given function pointer
   if( eq(node->data, d) ) {
      // Print the data and number of nodes traversed to find the data
      cout << num_searches << " nodes were traversed to find the data." << endl;
      return &node->data;
   } else { // Node's data is not equal to the given data
      T* outcome = NULL;
      // When left node exists
      if( node->left != NULL ) {
         // Call this function and get the outcome
         outcome = search( node->left, d, eq, num_searches++ );
         if(outcome != NULL) return outcome;
      }
      
      // When right node exists
      if( node->right != NULL ) {
         // Call this function and get the outcome
         outcome = search( node->right, d, eq, num_searches++ );
         if(outcome != NULL) return outcome;
      }
      // Either return null because we could not
      // find the data or return the data found.
      return outcome;
   }
}

