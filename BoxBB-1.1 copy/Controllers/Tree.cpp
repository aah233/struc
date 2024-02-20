template<typename F, typename... Ts>
class BinaryTreeNode {
//esto seria el nodo que se va a utilizar en el arbol, que deberia tiene el Box
public:
    BOX<F, Ts...>* data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode(BOX<F, Ts...>* value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename F, typename... Ts>
class BinaryTree {
    private:
        //Y este seria el nodo 
        BinaryTreeNode<F, Ts...>* root;

    public:
        BinaryTree() : root(nullptr) {} //constructor

        void insert(BOX<F, Ts...>* value) {
            //aqui iria el metodo para insertar por ejemplo 
        }
};