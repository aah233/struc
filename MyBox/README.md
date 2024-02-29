1. Implementar con el inputouput coger los parametros  y  usar el initBox

##Compilar el proyecto:
  1. g++ -o compilado  main.cpp
  2. ./name arg1 arg2 ...

##Cosas del new y direcciones de memoria

En C++, cuando creas una instancia de una clase con un puntero como miembro, la memoria para ese puntero generalmente se asigna en el propio objeto. No necesitas usar new explícitamente en este caso, ya que el puntero se gestionará automáticamente cuando el objeto se destruya.

En otras palabras, si la vida útil del objeto Box o Generic está contenida dentro de una función o un bloque de código, y no estás usando new para asignar memoria dinámicamente, la memoria se manejará automáticamente cuando la variable salga de alcance.

Sin embargo, si decides asignar memoria dinámicamente usando new en algún momento, entonces sería responsabilidad tuya liberar esa memoria utilizando delete para evitar posibles fugas de memoria.


##Muy buena documentacion de Templates 
https://learn.microsoft.com/es-es/cpp/cpp/templates-cpp?view=msvc-170