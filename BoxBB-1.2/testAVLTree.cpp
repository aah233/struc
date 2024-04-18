#include "avlTree.hpp"
#include <iostream>

// Función para imprimir el árbol en preorden junto con la altura y el balance de cada nodo
template <typename KeyType, typename ValueType>
void printTree(AVLNode<KeyType, ValueType> *node, AVLTree<KeyType, ValueType> &tree, int depth = 0)
{
    if (node != nullptr)
    {
        std::cout << std::string(depth, ' ') << "Key: " << node->key << ", Value: " << node->value;
        std::cout << ", Height: " << tree.getHeight(node);
        std::cout << ", Balance: " << tree.getBalance(node) << std::endl;

        printTree(node->left, tree, depth + 4);
        printTree(node->right, tree, depth + 4);
    }
}

int main()
{
    AVLTree<int, std::string> tree(0, "root"); // Asumiendo que el árbol tiene un constructor que toma una clave y valor inicial

    // Inserta varios elementos en el árbol
    tree.insert(tree.getRoot(), 1, "one");
    tree.insert(tree.getRoot(), -1, "minus one");
    tree.insert(tree.getRoot(), 2, "two");
    tree.insert(tree.getRoot(), -2, "minus two");
    tree.insert(tree.getRoot(), 3, "three");

    // Imprime el árbol
    std::cout << "AVL Tree:" << std::endl;
    printTree(tree.getRoot(), tree);

    return 0;
}
