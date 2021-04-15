#include <stdlib.h>
#include <stdio.h>

void erreur(char *error){
  perror(error);
  exit(-1);
}

void verif_alloc(void *ptr){
  if (ptr == NULL) {
    erreur("Erreur: Échec de l'allocation");
  }
}
