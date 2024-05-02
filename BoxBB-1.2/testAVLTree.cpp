#include "avlTree.hpp"
#include <iostream>

// Función para imprimir el árbol en preorden junto con la altura y el balance de cada nodo
template <typename KeyType, typename ValueType>
void printTree(AVLNode<KeyType, ValueType> *node, AVLTree<KeyType, ValueType> &tree, int depth = 0, std::string prefix = "")
{
    if (node == nullptr)
    {
        std::cout << std::string(depth, ' ') << prefix << "Null" << std::endl;
        return;
    }

    // Imprimir el nodo actual
    std::cout << std::string(depth, ' ') << prefix << "Key: " << node->key
              << ", Value: " << node->value
              << ", Height: " << tree.getHeight(node)
              << ", Balance: " << tree.getBalance(node) << std::endl;

    // Llamar recursivamente para el hijo izquierdo y derecho
    printTree(node->left, tree, depth + 4, "L-> ");
    printTree(node->right, tree, depth + 4, "R-> ");
}

int main()
{
    // Recrear el árbol
    AVLTree<int, std::string> *tree = new AVLTree<int, std::string>(1, "root");
    std::cout << "Root: " << tree->getRoot()->key << std::endl;
    printTree(tree->getRoot(), *tree);
    std::cout << "=================================================:" << std::endl;

    tree->insert(2, "dos"); // Actualizado para usar solo clave y valor
    printTree(tree->getRoot(), *tree);
    std::cout << "=================================================:" << std::endl;

    tree->insert(3, "tres"); // Actualizado para usar solo clave y valor
    printTree(tree->getRoot(), *tree);
    std::cout << "=================================================:" << std::endl;
    tree->insert(4, "cuatro"); // Actualizado para usar solo clave y valor
    printTree(tree->getRoot(), *tree);
    std::cout << "=================================================:" << std::endl;
    tree->insert(5, "cinco"); // Actualizado para usar solo clave y valor
    printTree(tree->getRoot(), *tree);
    std::cout << "=================================================:" << std::endl;
    // get min
    tree->insert(0, "cero"); // Actualizado para usar solo clave y valor
    printTree(tree->getRoot(), *tree);
    std::cout << "=================================================:" << std::endl;
    tree->insert(6, "seis"); // Actualizado para usar solo clave y valor
    printTree(tree->getRoot(), *tree);
    std::cout << "=================================================:" << std::endl;
    tree->insert(-1, "siete"); // Actualizado para usar solo clave y valor
    printTree(tree->getRoot(), *tree);
    // std::cout << "Min: " << tree->getMin()->key << std::endl;
    // printTree(tree->getRoot(), *tree);
    delete tree;
    return 0;
}
