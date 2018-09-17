/*
 * Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
 *
 * Simple integer keys and basic operations
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 *
 */

#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <queue>
using namespace std;

/*
 *  Node datastructure for single tree node
 */ 
template <class T>
struct Node {
	T data;
	Node *left; //do we need to use class T here?
	Node *right;
};


/*
 * Binary Search Tree (BST) class implementation
 */
template <class T>
class BST {

//***********************************PRIVATE*********************************
    private:
    Node<T> *root;

    ///PRIVATE ADD FUNCTION (DONE)
    void add_p(Node<T> *current, T val)
    {
        if (current->data > val) //less than new value (left branch)
            {
                if (!current->left) //nothing on the left branch
                {
                    //Node<T> *n = new Node<T>; //create new node
                    current->left = new Node<T>; //set child node equal to new node (value included)
                    current->left->data = val;   
                    current->left->right = NULL;
                    current->left->left = NULL;
                }
                else
                {
                    add_p(current->left, val); //something there, recursively check
                }    
            }
            else
            {
                if (!current->right) //nothing on the right branch
                {
                    //Node<T> *n = new Node<T>; //create new node
                    current->right = new Node<T>; //set child node equal to new node (value included)
                    current->right->data = val;
                    current->right->right = NULL;
                    current->right->left = NULL;    
                }
                else
                {
                    add_p(current->right, val); //something there, recursively check
                }
            }
    }


    ///PRIVATE HEIGHT FUNCTION (DONE)
    int height_p(Node<T> *root)
    {
        if (!root)
        {
            return 0;
        }
        else
        {   
            return (1 + max(height_p(root->left), height_p(root->right)));
        }
    }


    ///PRIVATE PREORDER FUNCTION (DONE)
    void preOrder_p(Node<T> *current)
    {
        if (current == NULL) //if tree is empty
        {
            //cout << " [!] Tree is Empty!" << endl; //not necessarily (recursion)
            return;
        }
        else
        {
            cout << current->data << " "; //print data (assuming node is not null)

            preOrder_p(current->left);
            preOrder_p(current->right);
        }

    }

//************************************PUBLIC***********************************
    public:

    BST()
    {
        root = NULL;
    }


    ///PUBLIC ADD FUNCTION (DONE)
    void add(T val)
    {
			//cout << " [!] BST::add currently unimplemented." << endl;

            if (root)
            {
                this->add_p(root, val);
            }
            else //if there is no root (empty tree)
            {
                root = new Node<T>;
                root->data = val; //set root equal to new node (value included)
                root->left = NULL;
                root->right = NULL;
            }
            
    }


    ///PUBLIC PRINT FUNCTION[S] (DONE)
    void print()
    {
			this->printPreOrder();
    }

    void printPreOrder() /// [FIXED] NEED TO FIGURE OUT HOW TO DO THIS WITHOUT ANY PARAMETERS
    {
        //cout << " [!] BST::printPreOrder currently unimplemented." << endl;
        preOrder_p(this->root); //sends over to private function
    }



    ///PUBLIC NODE COUNTER (WAS THIS FOR HELPING WITH HEIGHT FUNCTION?)
    int nodesCount()
    {
   
    }



    ///PUBLIC TREE HEIGHT CALC (DONE)
    int height() // [FIXED] HOW DO I DO THIS WITHOUT ANY PARAMETERS
    {

      return height_p(this->root); //sends over to private function
    }
};

#endif
