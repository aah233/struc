/**
 * int argc is the count of the arguments
 * char *argv[] is the array of arguments
*/

#include <iostream>
#include <cstring>
#include "Controllers/Box.cpp"
int main(int argc, char const *argv[])
{
    //Create a instance of a Box 
    Box box;
    
    //If because have arguments 
    if(argc  > 1){
        std::cout << argv[1] << std::endl;
    }

    

    // Imprimir "Hola" por consola en C++
    std::cout << "Hola" << std::endl;

    // Resto del código
    return 0;
}

/*
 * Check if exist this argument in the array of arguments
*/
int ExistArg(char const *str_to_find, int narg, char **arg) {
  int i;
  for(i=0;i<narg;i++)
    if (    strlen(arg[i]) == strlen(str_to_find) 
        && strstr(arg[i],str_to_find)
       )
       return 1;
  return 0;
}

