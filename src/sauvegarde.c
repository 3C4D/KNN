#include <stdlib.h>
#include <stdio.h>
#include "points.h"
#include "erreur.h"

TabPts chargement_fichier(char *nom_fic){
  FILE *fic = NULL;
  TabPts tab_load;
  double *coord_temp = NULL;
  int i, j, classe, nb_pts, dimension, nbclasse;

  /*on essaye d'ouvrir le fichier dont le nom est en argument de la fonction*/
  fic = fopen(nom_fic, "r");
  if(fic == NULL){  /*si le fichier n'existe pas, on retourne une erreur*/
    erreur("Erreur, fichier introuvable dans la fonction chargement_fichier");
  }

  /*si la première ligne ne convient pas, on retourne une erreur*/
  if(fscanf(fic, "%d %d %d", &nb_pts, &dimension, &nbclasse) < 3){
    erreur("erreur, fichier mal formatté (premiere ligne)");
  }

  /*on crée le tableau de points et on charge les elements*/
  tab_load = creer_tab_pts(dimension);
  tab_load.nbclasse = nbclasse;

  /*on crée le tableau de points*/

  /*on alloue dynamiquement un tableau temporaire où seront chargées les
    coordonnées avant d'être insérées dans le point*/
  coord_temp = (double *)malloc(tab_load.dimension * sizeof(double));
  if(coord_temp == NULL){
    erreur("Erreur d'allocation dans la fonction chargement_fichier");
  }

  for(i = 0; i < nb_pts; i++){
    printf("%d\n", tab_load.taille);
    /*on essaye de saisir la classe du point, sinon on retourne une erreur*/
    if(fscanf(fic, "%d", &classe) != 1){
      erreur("erreur, fichier mal formatté (classe)");
    }

    /*on crée le point dans le tableau*/
    ajouter_point(&tab_load, creer_point(tab_load.dimension, classe));

    for(j = 0; j < tab_load.dimension; j++){
      /*on charge les coordonnées dans le tableau temporaire*/
      if(fscanf(fic, "%lf", &coord_temp[j]) != 1){
        erreur("erreur, fichier mal formatté (coordonnée)");
      }
    }
    /*on charge les coordonnées dans le point à l'aide du tableau*/
    ajouter_coord(&tab_load.tab[i], tab_load.dimension, coord_temp);
  }

  /*on libère le tableau temporaire*/
  free(coord_temp);
  return tab_load;
}

void save(TabPts tab_save, char *nom_fic){

}
