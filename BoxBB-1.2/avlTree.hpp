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
    void insert(KeyType key, ValueType value);
    AVLNode<KeyType, ValueType> *getMin();
    AVLNode<KeyType, ValueType> *getMax();
    int getHeight(AVLNode<KeyType, ValueType> *node);
    void updateHeight(AVLNode<KeyType, ValueType> *node);
    int getBalance(AVLNode<KeyType, ValueType> *node);
    AVLNode<KeyType, ValueType> *rotateRight(AVLNode<KeyType, ValueType> *y);
    AVLNode<KeyType, ValueType> *rotateLeft(AVLNode<KeyType, ValueType> *x);

private:
    AVLNode<KeyType, ValueType> *insertRecursive(AVLNode<KeyType, ValueType> *node, KeyType key, ValueType value);
    void deleteSubtree(AVLNode<KeyType, ValueType> *node);
    AVLNode<KeyType, ValueType> *balance(AVLNode<KeyType, ValueType> *node);
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
void AVLTree<KeyType, ValueType>::insert(KeyType key, ValueType value)
{
    root = insertRecursive(root, key, value);
}
/********************************************************************/
template <typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::insertRecursive(AVLNode<KeyType, ValueType> *node, KeyType key, ValueType value)
{
    if (node == nullptr)
        return new AVLNode<KeyType, ValueType>(key, value);

    if (key < node->key)
        node->left = insertRecursive(node->left, key, value);
    else if (key > node->key)
        node->right = insertRecursive(node->right, key, value);
    else if (key == node->key)
    {
        if (node->dataList.size() == 0)
        {
            node->dataList.push_back(node->value);
        }
        node->dataList.push_back(value);
        return node;
    }

    updateHeight(node);
    return balance(node);
}

/********************************************************************/
template <typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::balance(AVLNode<KeyType, ValueType> *node)
{
    if (node == nullptr)
        return nullptr;

    updateHeight(node);
    int balance = getBalance(node);

    // Caso Izquierda-Izquierda (Left-Left)
    if (balance > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);

    // Caso Izquierda-Derecha (Left-Right)
    if (balance > 1 && getBalance(node->left) < 0)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Caso Derecha-Derecha (Right-Right)
    if (balance < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);

    // Caso Derecha-Izquierda (Right-Left)
    if (balance < -1 && getBalance(node->right) > 0)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

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
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::getMin()
{
    if (!root)
    {
        return nullptr;
    }

    AVLNode<KeyType, ValueType> *current = root;
    AVLNode<KeyType, ValueType> *parent = nullptr;

    // Encontrar el nodo mínimo
    while (current->left)
    {
        parent = current;
        current = current->left;
    }

    //   Ahora 'current' es el nodo con la clave mínima
    if (!current->dataList.empty())
    {
        ValueType minValue = current->dataList.front();                 // Obtener el valor del frente de la lista
        current->dataList.pop_front();                                  // Eliminar el valor del frente de la lista
        return new AVLNode<KeyType, ValueType>(current->key, minValue); // Devolver el valor
    }

    // Si current tiene un hijo derecho, debemos reemplazar current con este hijo
    AVLNode<KeyType, ValueType> *replacement = current->right;
    if (parent)
    {
        parent->left = replacement; // Reemplaza el nodo mínimo con su hijo derecho
    }
    else
    {
        root = replacement; // El mínimo era la raíz
    }

    // Rebalancear desde la raíz
    root = balance(root);

    current->left = current->right = nullptr;
    return current;
}

/********************************************************************/
template <typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::getMax()
{
}

/********************************************************************/
template <typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>::~AVLTree()
{
    deleteSubtree(root);
}

#endif