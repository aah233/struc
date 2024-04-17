#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <memory>
#include "avlNode.hpp"

template <typename KeyType, typename ValueType>
class AVLTree
{
public:
    AVLNode<KeyType, ValueType> *root;
    // Constructor
    AVLTree(KeyType key, ValueType value);
    AVLNode<KeyType, ValueType> *getRoot();
    // Destructor
    ~AVLTree();
};

// Definitions of the AVLTree member functions
template <typename KeyType, typename ValueType>

AVLTree<KeyType, ValueType>::AVLTree(KeyType key, ValueType value)
{
    root = new AVLNode<KeyType, ValueType>(key, value);
}

/********************************************************************/
template <typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::getRoot()
{
    return root;
}

/********************************************************************/
template <typename KeyType, typename ValueType>

AVLTree<KeyType, ValueType>::~AVLTree()
{
    delete root;
}

#endif
