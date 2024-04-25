#include "avlTree.hpp"
#include <iostream>

// Función para imprimir el árbol en preorden junto con la altura y el balance de cada nodo
template <typename KeyType, typename ValueType>
void printTree(AVLNode<KeyType, ValueType> *node, AVLTree<KeyType, ValueType> &tree, int depth = 0)
{
    if (node != nullptr)
    {
        if (node->left != nullptr)
            printTree(node->left, tree, depth + 4);
        std::cout << std::string(depth, ' ') << "Key: " << node->key << ", Value: " << node->value;
        std::cout << ", Height: " << tree.getHeight(node);
        std::cout << ", Balance: " << tree.getBalance(node) << std::endl;
        if (node->right != nullptr)
            printTree(node->right, tree, depth + 4);
    }
    else
    {
        std::cout << "Node padre" << std::endl;
        std::cout << std::string(depth, ' ') << "Key: " << node->key << ", Value: " << node->value;
        std::cout << ", Height: " << tree.getHeight(node);
        std::cout << ", Balance: " << tree.getBalance(node) << std::endl;
    }
}

int main()
{
    AVLTree<int, std::string> *tree = new AVLTree<int, std::string>(0, "root");
    std::cout << "Root: " << tree->getRoot()->key << std::endl;
    printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 0, "zero");
    printTree(tree->getRoot(), *tree);
    // Inserta varios elementos en el árbol
    tree->insert(tree->getRoot(), 1, "one");
    printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), -1, "minus one");
    printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 2, "two");
    printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), -2, "minus two");
    printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 3, "three");
    printTree(tree->getRoot(), *tree);

    // Imprime el árbol
    std::cout << "AVL Tree:" << std::endl;
    printTree(tree->getRoot(), *tree);

    // Destruye el árbol
    delete tree;
    std::cout << "Árbol eliminado, comenzando prueba 2:" << std::endl;

    // Recrear el árbol
    tree = new AVLTree<int, std::string>(0, "root");
    std::cout << "Root: " << tree->getRoot()->key << std::endl;
    printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 0, "zero");
    printTree(tree->getRoot(), *tree);
    // Inserta varios elementos en el árbol
    tree->insert(tree->getRoot(), 2, "one");
    printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), -2, "minus one");
    printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 1, "two");
    printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), -1, "minus two");
    printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 3, "three");
    printTree(tree->getRoot(), *tree);

    // Imprime el árbol
    std::cout << "AVL Tree:" << std::endl;
    printTree(tree->getRoot(), *tree);

    // Destruye el árbol de nuevo
    delete tree;
    return 0;
}
// 0,2,-2,1,-1,3