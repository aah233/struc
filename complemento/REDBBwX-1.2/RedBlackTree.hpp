#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <memory>
#include <algorithm>
#include <iostream>
#include <list>
#include "iutils.hpp"

// Definición de los colores del nodo
enum Color
{
    RED,
    BLACK
};

// Nodo del árbol rojo-negro
template <typename KeyType, typename ValueType>
struct RBNode
{
    KeyType key;
    std::list<ValueType> dataList;
    Color color;
    std::shared_ptr<RBNode> left;
    std::shared_ptr<RBNode> right;
    std::shared_ptr<RBNode> parent;

    RBNode(KeyType k, ValueType value) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr)
    {
        dataList.push_back(value);
    }
};

// Comparador genérico para cualquier tipo
template <typename T>
struct Comparator
{
    static bool equals(const T &a, const T &b)
    {
        return a == b;
    }
    static bool less(const T &a, const T &b)
    {
        return a < b;
    }
    static bool lessEquals(const T &a, const T &b)
    {
        return a <= b;
    }
    static bool greater(const T &a, const T &b)
    {
        return a > b;
    }
    static bool greaterEquals(const T &a, const T &b)
    {
        return a >= b;
    }
};

// Especialización del comparador para el tipo itv
template <>
struct Comparator<itv>
{
    static bool equals(const itv &a, const itv &b)
    {
        return iEQ(a, b);
    }
    static bool less(const itv &a, const itv &b)
    {
        return iLT(a, b);
    }
    static bool lessEquals(const itv &a, const itv &b)
    {
        return iLE(a, b);
    }
    static bool greater(const itv &a, const itv &b)
    {
        return iGT(a, b);
    }
    static bool greaterEquals(const itv &a, const itv &b)
    {
        return iGE(a, b);
    }
};

// Clase RedBlackTree
template <typename KeyType, typename ValueType>
class RedBlackTree
{
public:
    std::shared_ptr<RBNode<KeyType, ValueType>> root;

    // Constructor
    RedBlackTree();
    // Destructor
    ~RedBlackTree();
    // Métodos públicos
    void insert(KeyType key, ValueType value);
    ValueType getMin();
    bool isEmpty();
    void removeLowerThan(KeyType key);
    void removeGreaterThan(KeyType key);
    void checkOrderTree();

private:
    void insertFix(std::shared_ptr<RBNode<KeyType, ValueType>> node);
    void leftRotate(std::shared_ptr<RBNode<KeyType, ValueType>> x);
    void rightRotate(std::shared_ptr<RBNode<KeyType, ValueType>> x);
    std::shared_ptr<RBNode<KeyType, ValueType>> getMinNode(std::shared_ptr<RBNode<KeyType, ValueType>> node);
    void removeLowerThanRecursive(std::shared_ptr<RBNode<KeyType, ValueType>> node, KeyType key);
    void removeGreaterThanRecursive(std::shared_ptr<RBNode<KeyType, ValueType>> node, KeyType key);
    void checkOrderNodeTree(std::shared_ptr<RBNode<KeyType, ValueType>> node, KeyType &prevKey, bool &first);
};

// Implementación de RedBlackTree
template <typename KeyType, typename ValueType>
RedBlackTree<KeyType, ValueType>::RedBlackTree() : root(nullptr) {}

template <typename KeyType, typename ValueType>
RedBlackTree<KeyType, ValueType>::~RedBlackTree()
{
    root.reset();
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::insert(KeyType key, ValueType value)
{
    auto newNode = std::make_shared<RBNode<KeyType, ValueType>>(key, value);
    if (!root)
    {
        root = newNode;
        root->color = BLACK;
    }
    else
    {
        std::shared_ptr<RBNode<KeyType, ValueType>> parent = nullptr;
        std::shared_ptr<RBNode<KeyType, ValueType>> current = root;
        while (current)
        {
            parent = current;
            if (Comparator<KeyType>::less(key, current->key))
            {
                current = current->left;
            }
            else if (Comparator<KeyType>::greater(key, current->key))
            {
                current = current->right;
            }
            else
            {
                current->dataList.push_back(value);
                return;
            }
        }
        newNode->parent = parent;
        if (Comparator<KeyType>::less(key, parent->key))
        {
            parent->left = newNode;
        }
        else
        {
            parent->right = newNode;
        }
        insertFix(newNode);
    }
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::insertFix(std::shared_ptr<RBNode<KeyType, ValueType>> node)
{
    while (node->parent && node->parent->color == RED)
    {
        if (node->parent == node->parent->parent->left)
        {
            auto uncle = node->parent->parent->right;
            if (uncle && uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(node->parent->parent);
            }
        }
        else
        {
            auto uncle = node->parent->parent->left;
            if (uncle && uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::leftRotate(std::shared_ptr<RBNode<KeyType, ValueType>> x)
{
    auto y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::rightRotate(std::shared_ptr<RBNode<KeyType, ValueType>> x)
{
    auto y = x->left;
    x->left = y->right;
    if (y->right)
        y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

template <typename KeyType, typename ValueType>
ValueType RedBlackTree<KeyType, ValueType>::getMin()
{
    auto minNode = getMinNode(root);
    if (!minNode)
        return nullptr;

    if (!minNode->dataList.empty())
    {
        ValueType minValue = minNode->dataList.front();
        minNode->dataList.pop_front();
        return minValue;
    }
    return nullptr;
}

template <typename KeyType, typename ValueType>
std::shared_ptr<RBNode<KeyType, ValueType>> RedBlackTree<KeyType, ValueType>::getMinNode(std::shared_ptr<RBNode<KeyType, ValueType>> node)
{
    while (node && node->left)
        node = node->left;
    return node;
}

template <typename KeyType, typename ValueType>
bool RedBlackTree<KeyType, ValueType>::isEmpty()
{
    return !root;
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::removeLowerThan(KeyType key)
{
    removeLowerThanRecursive(root, key);
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::removeLowerThanRecursive(std::shared_ptr<RBNode<KeyType, ValueType>> node, KeyType key)
{
    if (!node)
        return;
    if (Comparator<KeyType>::less(node->key, key))
    {
        removeLowerThanRecursive(node->right, key);
        node->left.reset();
    }
    else
    {
        removeLowerThanRecursive(node->left, key);
    }
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::removeGreaterThan(KeyType key)
{
    removeGreaterThanRecursive(root, key);
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::removeGreaterThanRecursive(std::shared_ptr<RBNode<KeyType, ValueType>> node, KeyType key)
{
    if (!node)
        return;
    if (Comparator<KeyType>::greaterEquals(node->key, key))
    {
        removeGreaterThanRecursive(node->left, key);
        node->right.reset();
    }
    else
    {
        removeGreaterThanRecursive(node->right, key);
    }
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::checkOrderTree()
{
    if (isEmpty())
        return;
    KeyType prevKey;
    bool first = true;
    checkOrderNodeTree(root, prevKey, first);
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::checkOrderNodeTree(std::shared_ptr<RBNode<KeyType, ValueType>> node, KeyType &prevKey, bool &first)
{
    if (!node)
        return;
    checkOrderNodeTree(node->left, prevKey, first);
    if (first)
    {
        prevKey = node->key;
        first = false;
    }
    else
    {
        if (Comparator<KeyType>::greater(prevKey, node->key))
        {
            std::cout << "Error: " << prevKey << " > " << node->key << std::endl;
        }
        prevKey = node->key;
    }
    checkOrderNodeTree(node->right, prevKey, first);
}

#endif // RED_BLACK_TREE_HPP
