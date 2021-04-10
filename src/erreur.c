/* Fichier source contenant la fonction erreur() */

#include <stdlib.h>
#include <stdio.h>

/* Fonction renvoyant une erreur et arrêtant le pogramme */
void erreur(char *error){
  perror(error);
  exit(-1);
}
