#include <stdlib.h>
#include <stdio.h>

void erreur(char *error){
  perror(error);
  exit(-1);
}
