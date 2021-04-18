#include <stdlib.h>
#include <stdio.h>

/* Renvoie un message d'erreur sur stderr */
void err_log(char *error){
  fprintf(stderr, "Erreur, %s", error);
}

/* Renvoie un message d'erreur sur stderr et interrompt le programme */
void erreur(char *error){
  perror(error);
  exit(-1);
}

/* Vérifie une allocation (jamais utilisée) */
void verif_alloc(void *ptr){
  if (ptr == NULL) {
    erreur("Erreur: Échec de l'allocation");
  }
}
