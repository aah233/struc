# Trabajo final de Grado y Complemento 

## Nomenclaturas:
- **AVL**: Árbol Binario de búsqueda balanceado.
- **AVL-T**: Árbol Binario de búsqueda balanceado con templates.
- **AOGI**: Algoritmo intervalar .
- **AOGI-M**: Algoritmo intervalar implementado con multiset. 
- **AOGI-MI**: Algoritmo intervalar implementado con multi_index.

## Objetivo TFG:
Tener una versión C++ con templates para el almacenamiento en AVL ordenado por una clave (límite **inferior** de la función objetivo), donde cada nodo se almacenan los elementos con la misma clave. Para los elementos con la misma clave:
  - En el código actual se almacenan en una lista FIFO.
  - Se puede usar otro árbol binario ordenado por menor límite **superior** de la función objetivo.
  - En caso de que haya dos elementos con los mismos dos límites se puede usar una lista.

## Objetivo TFC:
Comparativa de nuestra versión AVL-T, con las estructuras estándar disponibles en C++. Para su uso su comparación se han seleccionado multiset y multi_index. 


## Observaciones:

Creo que necesitarás que el elemento que se instancie en el template sea una clase que tenga sobrecargados algunos operadores.

## Directorios:
- TFG/AiBoBBwX-1.2: Versión del AVL-T.
- TFC/AiBoBBwX-1.2-M : Versión del AOGI con el uso de multiset.
- TFC/AiBoBBwX-1.2-MI: Versión del AOGI con el multi_index. 

## Necesitarás
1. **make**
2. **Compilador g++**
3. **tk** (para la salida gráfica)
4. **kv** (paquete C++ con Aritmética de Intervalos). Este usa:
   - **boost-devel**

