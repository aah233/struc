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
    // Los prefijos 'L-> ' y 'R-> ' indican si el nodo es izquierdo o derecho
    printTree(node->left, tree, depth + 4, "L-> ");
    printTree(node->right, tree, depth + 4, "R-> ");
}

int main()
{
    AVLTree<int, std::string> *tree = new AVLTree<int, std::string>(0, "root");
    std::cout << "Root: " << tree->getRoot()->key << std::endl;
    // printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 0, "zero");
    // printTree(tree->getRoot(), *tree);
    //  Inserta varios elementos en el árbol
    tree->insert(tree->getRoot(), 1, "one");
    // printTree(tree->getRoot(), *tree);
    //  imprimir contenido lista
    std::cout << "Contenido de la lista: " << std::endl;
    for (std::string i : tree->getRoot()->dataList)
    {
        std::cout << i << std::endl;
    }
    tree->insert(tree->getRoot(), -1, "minus one");
    // printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 2, "two");
    // printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), -2, "minus two");
    // printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 3, "three");
    // //printTree(tree->getRoot(), *tree);

    // Imprime el árbol
    std::cout << "AVL Tree:" << std::endl;
    printTree(tree->getRoot(), *tree);

    // Destruye el árbol
    delete tree;
    std::cout << "Árbol eliminado, comenzando prueba 2:" << std::endl;

    // Recrear el árbol
    tree = new AVLTree<int, std::string>(0, "root");
    std::cout << "Root: " << tree->getRoot()->key << std::endl;
    // printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 0, "zero");
    // printTree(tree->getRoot(), *tree);
    //  Inserta varios elementos en el árbol
    tree->insert(tree->getRoot(), 2, "one");
    // printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), -2, "minus one");
    // printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 1, "two");
    // printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), -1, "minus two");
    // printTree(tree->getRoot(), *tree);
    tree->insert(tree->getRoot(), 3, "three");
    // printTree(tree->getRoot(), *tree);

    // Imprime el árbol
    std::cout << "AVL Tree:" << std::endl;
    printTree(tree->getRoot(), *tree);
    //  Devuelve el nodo minimo
    std::cout << "Nodo minimo: " << tree->getMin()->key << std::endl;
    printTree(tree->getRoot(), *tree);
    //   Destruye el árbol de nuevo
    delete tree;
    return 0;
}