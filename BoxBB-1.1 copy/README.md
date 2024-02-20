#Objetivo creacion de un box generico para introducir en un arbol generico 

1. Ver como podemos convertir los metodos en las nuevas instancias 
2. Ver que metodos realmente necesitamos del BOX y del arbol, ya que esos metodos tenemos que convertirlos a c++
3. Claro ver en los metodos que cajan son las que entratian, ya que es le propio objeto lo que se necesita 

#Pasos que se estan siguiendo: 
1. Creacion del template 
2. Creacion de la clase heredada
3. Creacion del arbol con el template 


#Una de las opciones, puede ser crear el arbol de 0, que quizar sea mas rapido y eficiente



#Esta tecnica pone que es la que nos permitiria, obtener un objeto generico, pero asegurtando que ese objeto generico sea 
#herencia del template 
técnica SFINAE (Substitution Failure Is Not An Error) 

Creacion de esto:
----------------
template<typename T>
concept IsBox = std::is_base_of<BOX<typename T::FunctionType, typename T::Ts...>, T>::value;

y luego se comprueba en la instancia,aunque yo creo que si ponemos el generico, ya directamente da error si no tiene ese atributo
el generico 