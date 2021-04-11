/* Fichier source contenant les fonctions relatives à la */
/* génération de fichiers de tests */

#include <stdlib.h>
#include <stdio.h>
#include "erreur.h"

void generation_fichier(int nb_point, int dimension, int nbclasse, char *nom_fic){
  FILE *fic = NULL;
  int i, j;

  /* On vérifie que le fichier n'existe pas */
  /* Cela permet de ne pas ecraser par mégarde un fichier source par exemple */
  if((fic = fopen(nom_fic, "r")) != NULL){
    erreur("Erreur, fonction de generation, le fichier existe surement déjà");
  }

  /* On vérifie que le fichier est bien créé */
  if((fic = fopen(nom_fic, "w")) == NULL){
    erreur("Erreur, fonction de generation, échec d'ouverture de fichier'");
  }

  /* On imprime la première ligne qui contient les informations essentielles */
  fprintf(fic, "%d %d %d\n", nb_point, dimension, nbclasse);

  /* On met le nombre de point demandé */
  for(i = 0; i < nb_point; i++){
    fprintf(fic, "%d ", (rand()%nbclasse)+1); /* Classe tirée au hasard */
    for(j = 0; j < dimension-1; j++){         /* de même pour les coordonnées */
      fprintf(fic, "%f ", (-1000000 + rand()%2000000) / 1000000.0);
    }
    fprintf(fic, "%f\n", (rand()%1000000)/1000000.0);
  }

  fclose(fic); /* On ferme le fichier */
}
