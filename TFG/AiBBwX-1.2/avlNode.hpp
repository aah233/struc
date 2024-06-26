/*
#include <concepts>

// Definir un concepto que requiere que el tipo tenga los operadores <, > y ==
template <typename T>
concept Comparable = requires(T a, T b) {
    {
        a < b
    } -> std::same_as<bool>;
    {
        a > b
    } -> std::same_as<bool>;
    {
        a == b
    } -> std::same_as<bool>;
};
Faltaria por compilar en c++20 con el boost y añadir template <Comparable KeyType, typename ValueType>
*/
#include <list>

template <typename KeyType, typename ValueType>
class AVLNode
{
public:
    ValueType value;
    KeyType key;
    AVLNode<KeyType, ValueType> *left;
    AVLNode<KeyType, ValueType> *right;
    int height;
    std::list<ValueType> dataList;

    AVLNode(KeyType key, ValueType value) : value(value), key(key), left(nullptr), right(nullptr), height(1) {}
};