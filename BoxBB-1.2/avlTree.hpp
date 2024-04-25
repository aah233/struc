#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <memory>
#include "avlNode.hpp"
#include <algorithm> // Para std::max

template <typename KeyType, typename ValueType>
class AVLTree
{
public:
    AVLNode<KeyType, ValueType> *root;

    // Constructor
    AVLTree(KeyType key, ValueType value);

    // Destructor
    ~AVLTree();
    // Métodos públicos
    AVLNode<KeyType, ValueType> *getRoot();
    AVLNode<KeyType, ValueType> *insert(AVLNode<KeyType, ValueType> *node, KeyType key, ValueType value);
    int getHeight(AVLNode<KeyType, ValueType> *node);
    void updateHeight(AVLNode<KeyType, ValueType> *node);
    int getBalance(AVLNode<KeyType, ValueType> *node);
    AVLNode<KeyType, ValueType> *rotateRight(AVLNode<KeyType, ValueType> *y);
    AVLNode<KeyType, ValueType> *rotateLeft(AVLNode<KeyType, ValueType> *x);

private:
    void deleteSubtree(AVLNode<KeyType, ValueType> *node);
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
// Método para obtener la altura de un nodo
template <typename KeyType, typename ValueType>
int AVLTree<KeyType, ValueType>::getHeight(AVLNode<KeyType, ValueType> *node)
{
    if (!node)
        return 0;
    return node->height;
}

/********************************************************************/
// Método para actualizar la altura de un nodo
template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::updateHeight(AVLNode<KeyType, ValueType> *node)
{
    if (node)
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

/********************************************************************/
// Método para calcular el factor de balance de un nodo
template <typename KeyType, typename ValueType>
int AVLTree<KeyType, ValueType>::getBalance(AVLNode<KeyType, ValueType> *node)
{
    if (!node)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

/********************************************************************/
// Rotaciones para el balanceo del árbol
template <typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::rotateRight(AVLNode<KeyType, ValueType> *y)
{
    AVLNode<KeyType, ValueType> *x = y->left;
    AVLNode<KeyType, ValueType> *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x; // nueva raíz
}

/********************************************************************/
template <typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::rotateLeft(AVLNode<KeyType, ValueType> *x)
{
    AVLNode<KeyType, ValueType> *y = x->right;
    AVLNode<KeyType, ValueType> *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y; // nueva raíz
}
/********************************************************************/
template <typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::insert(AVLNode<KeyType, ValueType> *node, KeyType key, ValueType value)
{
    // 1. Insertar el nodo como en un BST
    if (!node)
        return new AVLNode<KeyType, ValueType>(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else // Claves duplicadas no se permiten en el AVL por ahora
        return node;

    // 2. Actualizar la altura de este nodo ancestro
    updateHeight(node);

    // 3. Obtener el factor de balance para verificar si este nodo se desequilibró
    int balance = getBalance(node);

    // Rotaciones para balancear el árbol
    // Caso izquierda-izquierda
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Caso derecha-derecha
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Caso izquierda-derecha
    if (balance > 1 && key > node->left->key)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Caso derecha-izquierda
    if (balance < -1 && key < node->right->key)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Retorna el nodo (sin cambios)
    return node;
}

/********************************************************************/

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::deleteSubtree(AVLNode<KeyType, ValueType> *node)
{
    if (node != nullptr)
    {
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }
}

/********************************************************************/
template <typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>::~AVLTree()
{
    deleteSubtree(root);
}

#endif