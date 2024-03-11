# struc

## Objetivo:
Tener una versión C++ con templates para el almacenamiento en árbol binario balanceado ordenado por una clave (límite **inferior** de la función objetivo), donde cada nodo se almacenan los elementos con la misma clave. Para los elementos con la misma clave:
  - En el código actual se almacenan en una lista FIFO.
  - Se puede usar otro árbol binario ordenado por menor límite **superior** de la función objetivo.
  - En caso de que haya dos elementos con los mismos dos límites se puede usar una lista.

## Observaciones:

Creo que necesitarás que el elemento que se instancie en el template sea una clase que tenga sobrecargados algunos operadores.

## Directorios:
- BoxBB-1.1: Versión actual en C y C++.
- kv-0.4.51: Librería kv que se ha modificado para evitar warnnings de compilación.
- Example-1.0: Intento de tener todo en C++. Usa c-xsc otra librería de Aritmética de Intervalos diferente a kv. Puede servir para las clase Box, pero es un código C++ muy antiguo.

## Necesitaras:
1. make
2. compilador g++
3. tk (salida gráfica)
4. kv (paquete C++ con Aritmética de Intervalos). Este usa:
  - boost-devel

El kv-0.4.51 debe tener un enlace simbólico en tu HOME:
  - cd [enter]
  - ~ $> ln -s [donde este]/kv-0.4.51 kv



paso 2 
coger alfa -d , y while hasta que no sea mejor que alfa 
pintar por pantalla, salida gráfica
tfl 