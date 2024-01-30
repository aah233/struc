#include <stdio.h>
#include <string.h>
#include "argshand.h"

/*----------------------------------------------------------------------------*/
/**
 * @brief Busca una cadena de texto en un arreglo de argumentos y devuelve el siguiente argumento.
 * 
 * @param str_to_find Cadena de texto a buscar.
 * @param narg Cantidad de argumentos en el arreglo.
 * @param arg Arreglo de argumentos.
 * @return Puntero al siguiente argumento si se encuentra la cadena de texto, NULL si no se encuentra.
 */

char *GetArg(char const *str_to_find, int narg, char **arg) {
  int i;
  for(i=0;i<narg;i++)                
    if (    strlen(arg[i]) == strlen(str_to_find)
       && strstr(arg[i],str_to_find)
       ) 
       return arg[i+1];          
  return NULL;           
}


/*----------------------------------------------------------------------------*/
/* Return 1 if the string 'str_to_find' is in the command line 'arg'          */
/*----------------------------------------------------------------------------*/

int ExistArg(char const *str_to_find, int narg, char **arg) {
  int i;
  for(i=0;i<narg;i++)
    if (    strlen(arg[i]) == strlen(str_to_find) 
        && strstr(arg[i],str_to_find)
       )
       return 1;
  return 0;
}

/*----------------------------------------------------------------------------*//*----------------------------------------------------------------------------*/
