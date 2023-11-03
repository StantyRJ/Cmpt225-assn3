/*
 * BST.cpp
 * 
 * Description: Binary Search Tree data collection ADT class.
 *              Link-based implementation.
 *              Duplicated elements are not allowed.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Inspired from our textbook
 * Date of last modification: Oct. 2023
 */
 
#include "BST.h"
#include "WordPair.h"
#include <iostream>

using std::cout;
using std::endl;

// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one we will use to mark this assignment - will not know about them
// since we will use these public method prototypes to create our test driver.

/* Constructors and destructor */

   // Default constructor
   BST::BST() { }            

   // Copy constructor
   BST::BST(const BST & aBST) {
      root = copyR(aBST.root);
      elementCount = aBST.elementCount;
   }

   BSTNode * BST::copyR(BSTNode * theirCurrent)
   {
      if(theirCurrent == nullptr)
         return nullptr;

      BSTNode * copyNode = new BSTNode;
      copyNode->element = theirCurrent->element;
      copyNode->left = copyR(theirCurrent->left);
      copyNode->right = copyR(theirCurrent->right); 

      
      return copyNode;     
   }

   // Destructor 
   BST::~BST() {
      deleteR(root);
   }   

   void BST::deleteR(BSTNode * current)      
   {
      if(current == nullptr)
         return;

      deleteR(current->left);

      deleteR(current->right);  

      delete current;
      return;
         
   }
   
   
/* Getters and setters */

   // Description: Returns the number of elements currently stored in the binary search tree.   
   // Time efficiency: O(1)   
   unsigned int BST::getElementCount() const {     
      return elementCount;
   }
   

/* BST Operations */

   // Description: Inserts an element into the binary search tree.
   //              This is a wrapper method which calls the recursive insertR( ).
   // Precondition: "newElement" does not already exist in the binary search tree.
   // Exception: Throws the exception "UnableToInsertException" when newElement 
   //            cannot be inserted because the "new" operator failed. 
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the binary search tree.
   // Time efficiency: O(log2 n)   
   void BST::insert(WordPair & newElement) {
      BSTNode * newNode = new BSTNode(newElement,nullptr,nullptr);
      if(newNode)
      {
         if(root != nullptr)
         {
            bool i = insertR(newNode,root);
            if(!i)
               throw UnableToInsertException("failed to insert");
            else
               elementCount++;
         }
         else
            root = newNode;
      }
      else
      {
         throw UnableToInsertException("new failed");
      }	  
   } 

   // Description: Recursive insertion into a binary search tree.
   //              Returns true when "anElement" has been successfully inserted into the 
   //              binary search tree. Otherwise, returns false.
   bool BST::insertR(BSTNode * newBSTNode, BSTNode * current) {  
      bool inserted = false;
      if(current->element == newBSTNode->element)
      {
         return false;
      }
      else if(current->element > newBSTNode->element)
      {
         if(current->left != nullptr)
            inserted = insertR(newBSTNode,current->left);
         else 
         {
            current->left = newBSTNode;
            return true;
         }
      }
      else
      {
         if(current->right != nullptr)
            inserted = insertR(newBSTNode,current->right);
         else 
         {
            current->right = newBSTNode;
            return true;
         }
      }
      return inserted;
   }

   
   // Description: Retrieves "targetElement" from the binary search tree.
   //           This is a wrapper method which calls the recursive retrieveR( ).
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Exception: Throws (propagates) the exception "ElementDoesNotExistException" 
   //            thrown from the retrieveR(...)
   //            if "targetElement" is not in the binary search tree.
   // Time efficiency: O(log2 n)
   WordPair& BST::retrieve(WordPair & targetElement) const {
      
     if (elementCount == 0)  
        throw EmptyDataCollectionException("Binary search tree is empty.");
	
     WordPair& translated = retrieveR(targetElement, root);
	 
     return translated;
   }

   // Description: Recursive retrieval from a binary search tree.
   // Exception: Throws the exception "ElementDoesNotExistException" 
   //            if "targetElement" is not found in the binary search tree.
   WordPair& BST::retrieveR(WordPair & targetElement, BSTNode * current) const {

	  if(current->element == targetElement)
     {
         return current->element;
     }
     else if(current->element < targetElement)
     {
         if(current->right != nullptr)
            retrieveR(targetElement,current->right);
         else
         {
            throw ElementDoesNotExistException("target element not found inside BST");
         }
     }
      else if(current->element > targetElement)
     {
         if(current->left != nullptr)
            retrieveR(targetElement,current->left);
         else
         {
            throw ElementDoesNotExistException("target element not found inside BST");
         }
     }
      throw ElementDoesNotExistException("Element not found");
   } 
         
   
   // Description: Traverses the binary search tree in order.
   //           This is a wrapper method which calls the recursive traverseInOrderR( ).
   //           The action to be done on each element during the traverse is the function "visit".
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //         if the binary search tree is empty.
   // Time efficiency: O(n)     
   void BST::traverseInOrder(void visit(WordPair &)) const {
     
     if (elementCount == 0)  
       throw EmptyDataCollectionException("Binary search tree is empty.");

     traverseInOrderR(visit, root);
     
     return;
   }

   // Description: Recursive in order traversal of a binary search tree.   
   void BST::traverseInOrderR(void visit(WordPair &), BSTNode* current) const { 
      if(current == nullptr)
         return;

      traverseInOrderR(visit, current->left);
      traverseInOrderR(visit, current->right);

      visit(current->element);
      return;
   }
