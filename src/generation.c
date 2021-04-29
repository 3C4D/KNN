/* Fichier source contenant les fonctions relatives à la */
/* génération de fichiers de tests */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "points.h"
#include "erreur.h"
#include "sauvegarde.h"

/* Permet de générer un point */
point generation_pt_alea(int dimension, int nbclasse){
  point pt_alea;
  int i;

  pt_alea = creer_point(dimension, nbclasse); /* On crée un point */

  pt_alea.coord = (double *)malloc(dimension * sizeof(double));
  /* On alloue le tableau de coordonnes */
  if(pt_alea.coord == NULL){  /* Vérification de l'allocation */
    erreur("Erreur d'allocation dans la fonction generation_tableau_alea");
  }

  pt_alea.classe = (rand()%nbclasse)+1; /* Classe tirée au hasard */
  for(i = 0; i < dimension; i++){
    /* On tire au hasard ses coordonnées */
    pt_alea.coord[i] = (-1000000 + rand()%2000000) / 1000000.0;
  }

  return pt_alea;
}

/* Permet de générer un tableau de point aléatoire */
TabPts *generation_tableau_alea(int nbpoint, int dimension, int nbclasse){
  TabPts *tab_tmp = creer_tab_pts(dimension, nbclasse);
  int i;

  /* On insère des points aléatoires */
  for(i = 0; i < nbpoint; i++){
    /* On ajoute un point aléatoire dans le tableau */
    ajouter_point(tab_tmp, generation_pt_alea(dimension, nbclasse));
  }

  return tab_tmp; /* On retourne le tableau obtenu */
}

/* Permet de générer un fichier de points aléatoire */
void generation_fichier(int nb_point, int dimension, int nbclasse, char *fic){
  FILE *new = NULL;
  int i, j;

  /* On vérifie que le fichier n'existe pas */
  /* Cela permet de ne pas ecraser par mégarde un fichier source par exemple */
  if(!verif_nom_fic(fic)){
    erreur("Erreur, mauvaise extension ou fichier, generation_fichier");
  }

  /* On vérifie que le fichier est bien créé */
  if((new = fopen(fic, "w")) == NULL){
    erreur("Erreur, fonction de generation, échec d'ouverture de fichier'");
  }

  /* On imprime la première ligne qui contient les informations essentielles */
  fprintf(new, "%d %d %d\n", nb_point, dimension, nbclasse);

  /* On met le nombre de point demandé */
  for(i = 0; i < nb_point; i++){
    fprintf(new, "%d ", (rand()%nbclasse)+1); /* Classe tirée au hasard */
    for(j = 0; j < dimension-1; j++){         /* de même pour les coordonnées */
      fprintf(new, "%f ", (-1000000 + rand()%2000000) / 1000000.0);
    }
    fprintf(new, "%f\n", (-1000000 + rand()%2000000) / 1000000.0);
  }

  fclose(new); /* On ferme le fichier */
}
