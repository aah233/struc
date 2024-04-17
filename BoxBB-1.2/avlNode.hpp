
template <typename KeyType, typename ValueType>
class AVLNode
{
public:
    ValueType value;
    AVLNode<KeyType, ValueType> *left;
    AVLNode<KeyType, ValueType> *right;
    int height;
    KeyType key;
    std::list<ValueType> dataList;

    AVLNode(KeyType key, ValueType value) : value(value), key(key), left(nullptr), right(nullptr), height(1) {}
};
