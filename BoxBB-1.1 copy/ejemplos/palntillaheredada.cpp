// Clase de plantilla genérica
template<class T>
class Base {
public:
    T value;

    Base(T value) : value(value) {}

    T getValue() {
        return value;
    }
};

// Clase derivada que hereda de la clase de plantilla genérica
class Derived : public Base<int> {
public:
    Derived(int value) : Base(value) {}

    void printValue() {
        std::cout << "Value: " << getValue() << std::endl;
    }
};