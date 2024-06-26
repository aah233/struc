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
    AVLTree() = default;
    // Destructor
    ~AVLTree();
    // Métodos públicos
    AVLNode<KeyType, ValueType> *getRoot();
    void insert(KeyType key, ValueType value);
    ValueType getMin();
    AVLNode<KeyType, ValueType> *getMax();
    int getHeight(AVLNode<KeyType, ValueType> *node);
    void updateHeight(AVLNode<KeyType, ValueType> *node);
    int getBalance(AVLNode<KeyType, ValueType> *node);
    AVLNode<KeyType, ValueType> *rotateRight(AVLNode<KeyType, ValueType> *y);
    AVLNode<KeyType, ValueType> *rotateLeft(AVLNode<KeyType, ValueType> *x);
    bool isEmpty();
    void removeLowerThan(KeyType key);
    void removeGreaterThan(KeyType key);
    void checkOrderTree(AVLTree<KeyType, ValueType> &tree);

private:
    AVLNode<KeyType, ValueType> *insertRecursive(AVLNode<KeyType, ValueType> *node, KeyType key, ValueType value);
    void deleteSubtree(AVLNode<KeyType, ValueType> *node);
    AVLNode<KeyType, ValueType> *balance(AVLNode<KeyType, ValueType> *node);
    AVLNode<KeyType, ValueType> *removeLowerThanRecursive(AVLNode<KeyType, ValueType> *node, KeyType key);
    AVLNode<KeyType, ValueType> *removeGreaterThanRecursive(AVLNode<KeyType, ValueType> *node, KeyType key);
    void checkOrderNodeTree(AVLNode<KeyType, ValueType> *node, KeyType &prevKey, bool &first);
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
ValueType AVLTree<KeyType, ValueType>::getMin()
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
        ValueType minValue = current->dataList.front(); // Obtener el valor del frente de la lista
        current->dataList.pop_front();                  // Eliminar el valor del frente de la lista

        return minValue; // Devolver el valor
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
    return current->value;
}
/********************************************************************/
template <typename KeyType, typename ValueType>
bool AVLTree<KeyType, ValueType>::isEmpty()
{
    return root == nullptr;
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

/********************************************************************/
// Método público para eliminar todos los nodos con claves menores a un valor dado
template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::removeLowerThan(KeyType key)
{
    root = removeLowerThanRecursive(root, key);
}

/********************************************************************/
// Método privado recursivo para eliminar nodos
template <typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::removeLowerThanRecursive(AVLNode<KeyType, ValueType> *node, KeyType key)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->key < key)
    {
        AVLNode<KeyType, ValueType> *rightSubtree = removeLowerThanRecursive(node->right, key); // procesar primero el subárbol derecho
        deleteSubtree(node->left);                                                              // eliminar subárbol izquierdo seguro
        delete node;                                                                            // eliminar el nodo actual seguro
        return rightSubtree;                                                                    // devolver el subárbol derecho procesado
    }
    else
    {
        node->left = removeLowerThanRecursive(node->left, key); // procesar subárbol izquierdo
    }

    updateHeight(node);   // actualizar altura del nodo actual
    return balance(node); // balancear y devolver el nodo actual
}
/********************************************************************/
template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::removeGreaterThan(KeyType key)
{
    root = removeGreaterThanRecursive(root, key);
}
/********************************************************************/
template <typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::removeGreaterThanRecursive(AVLNode<KeyType, ValueType> *node, KeyType key)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    // Si la clave del nodo es mayor que la clave especificada, eliminar este nodo y todo su subárbol derecho
    if (node->key >= key)
    {
        AVLNode<KeyType, ValueType> *leftSubtree = removeGreaterThanRecursive(node->left, key); // procesar primero el subárbol izquierdo
        deleteSubtree(node->right);                                                             // eliminar subárbol derecho seguro
        delete node;                                                                            // eliminar el nodo actual seguro
        return leftSubtree;                                                                     // devolver el subárbol izquierdo procesado
    }
    else
    {
        // Si la clave del nodo es menor o igual, solo procesar el subárbol derecho
        node->right = removeGreaterThanRecursive(node->right, key); // procesar subárbol derecho
    }

    updateHeight(node);   // actualizar altura del nodo actual
    return balance(node); // balancear y devolver el nodo actual
}

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::checkOrderTree(AVLTree<KeyType, ValueType> &tree)
{

    // Nodo raiz
    if (tree.isEmpty())
        return;

    AVLNode<KeyType, ValueType> *node = tree.getRoot();
    if (node->left == nullptr && node->right == nullptr)
        return;

    KeyType prevKey;
    bool first = true;
    checkOrderNodeTree(node, prevKey, first);
}

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::checkOrderNodeTree(AVLNode<KeyType, ValueType> *node, KeyType &prevKey, bool &first)
{
    if (node == nullptr)
        return;

    checkOrderNodeTree(node->left, prevKey, first);

    if (first)
    {
        prevKey = node->key;
        first = false;
    }
    else
    {
        if (prevKey > node->key)
        {
            std::cout << "Error: " << prevKey << " > " << node->key << std::endl;
        }
        prevKey = node->key;
    }

    checkOrderNodeTree(node->right, prevKey, first);
}

#endif