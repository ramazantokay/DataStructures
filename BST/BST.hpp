#ifndef BST_HPP
#define BST_HPP

#include <iostream>

#include "BSTNode.hpp"

template <class T>
class BST {
public: 
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot();
    void insert(const T &data);
    void remove(const T &data);
    BSTNode<T> *find(const T &data);
    void printInorder();
    BST<T> &operator=(const BST<T> &rhs);

private: 
    void printInorder(BSTNode<T> *node);
    BSTNode<T>* insertNode(BSTNode<T> *node, const T &data);
    BSTNode<T>* removeAllNodes(BSTNode<T> *node);
    BSTNode<T>* removeNode(BSTNode<T> *node, const T &data);
    BSTNode<T>* findNode(BSTNode<T> *node, const T &data);
    BSTNode<T>* findMax(BSTNode<T>* node);
    BSTNode<T>* findMin(BSTNode<T>* node);
    void CopyConstructor(BSTNode<T> *&n1, BSTNode<T> *n2);

private: 
    BSTNode<T> *root;
};

#endif //BST_HPP

template <class T>
BST<T>::BST() {
   
    root =NULL;
}

template <class T>
BST<T>::BST(const BST<T> &obj) {
  
    if (obj.root ==NULL)
    {
        root = NULL;
    }
    else
    {
        CopyConstructor(root, obj.root);
    }
}


template <class T>
BST<T>::~BST() {

    root = removeAllNodes(root);
}


template <class T>
BSTNode<T> *BST<T>::getRoot() {
    return root != NULL ? root : NULL;
}

template <class T>
void BST<T>::insert(const T &data) {
    root = insertNode(root, data);  
  
}

template <class T>
void BST<T>::remove(const T &data) {
    root = removeNode(root, data);
}

template <class T>
BSTNode<T> *BST<T>::find(const T &data) {
    return findNode(root, data);
}

template <class T>
void BST<T>::printInorder() {

    if (root == NULL) {
        std::cout << "{}" << std::endl;
    } else {
        std::cout << "{" << std::endl;
        printInorder(root);
        std::cout << std::endl << "}" << std::endl;
    }
}

template <class T>
void BST<T>::printInorder(BSTNode<T> *node) {

    if (node == NULL)
        return;

    printInorder(node->left);
    if (node->left) {
        std::cout << "," << std::endl;
    }
    std::cout << "\t" << node->data;
    if (node->right) {
        std::cout << "," << std::endl;
    }
    printInorder(node->right);
}

template <class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    /* TODO */
    if (this!=&rhs)
    {
        removeAllNodes(root);
        CopyConstructor(root, rhs.root);
    }
    return *this;
    
}

//HELPER FUNCTIONS
template <class T>
BSTNode<T>* BST<T>::insertNode(BSTNode<T> *node, const T &data)
{
    if  (node == NULL)
    {
        node = new BSTNode<T>(data, NULL, NULL);
    }
    
    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    
    return node;
}

template <class T>
BSTNode<T>* BST<T>::removeAllNodes(BSTNode<T> *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    else
    {
        removeAllNodes(node->left);
        removeAllNodes(node->right);
        delete node;
    }
    return NULL;
}

template <class T>
BSTNode<T> *BST<T>::removeNode(BSTNode<T> *node, const T &data)
{
    BSTNode<T> *temp;
    if (node ==NULL)
        return NULL;
    else if (data < node->data)
        node->left=removeNode(node->left, data);    
    else if (data > node->data)
        node->right = removeNode(node->right, data);
    else if (node->right && node->left)
    {
        temp = findMin(node->right);
        node->data = temp->data;
        node->right= removeNode(node->right, node->data);
    }
    else
    {
        temp = node;
        if (node->left ==NULL)
            node = node->right;
        else if(node->right ==NULL)
            node = node->left;
        delete temp;

    }
    return node;
    
}

template <class T>
BSTNode<T> *BST<T>::findNode(BSTNode<T> *node, const T &data)
{
    if (node ==NULL)
        return NULL;
    else if(data > node->data)
        return findNode(node->right, data);
    else if(data < node->data)
        return findNode(node->left, data);
    else
        return node;
   
}

template <class T>
BSTNode<T>* BST<T>::findMax(BSTNode<T>* node)
{
    if (node==NULL)
        return NULL;
    else if (node->right ==NULL)
        return node;
    else
        return findMax(node->right);
    
}

template <class T>
BSTNode<T>* BST<T>::findMin(BSTNode<T>* node)
{
    if (node == NULL)
        return NULL;
    else if (node->left==NULL)
        return node;
    else
        return findMin(node->left);
    
    
}

template <class T>
void BST<T>::CopyConstructor(BSTNode<T> *&n1, BSTNode<T> *n2)
{
    if (n2 !=NULL)
    {
        n1 = new BSTNode<T>(n2->data, NULL, NULL);
        CopyConstructor(n1->left, n2->left);
        CopyConstructor(n1->right, n2->right);
    }
    else
    {
        n1 = NULL;
    }
    
    
}