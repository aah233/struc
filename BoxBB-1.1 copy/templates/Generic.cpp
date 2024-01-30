// member_function_templates1.cpp

//Con esto podemos obligar a tener una F y una G y despues infinitos Ts, que son los que queramos
template<int F,int G, class... Ts> 

class GenericForm {
   // Definimos los atributos de la clase
    int value = F; // F es un valor entero en tiempo de compilación
    int value2 = G; // G es un valor entero en tiempo de compilación

    /**Creacion de las clases */
    public:
        DivideForm() {  //Aqui estaria bien meter el divide box, para que se pueda dividir un generico 
            std::cout << "MyForm" << std::endl;
        }

};




/**
 * Como instanciamos la clase, ejemplo de uso  
**/
int main() {
    GenericForm<10,10, double> myObject; // F es 10, Ts contiene int y double
    myObject.DivideForm(); // Imprime "MyForm"
}