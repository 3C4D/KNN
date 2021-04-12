/* Fichier source contenant les  fonctions concernant les kppv à savoir */
/* trouver les kppv et trouver la classe d'un point par rapport à ses kppv */

#include <stdlib.h>
#include <stdio.h>
#include "points.h"
#include "erreur.h"
#include "arbre.h"

/* Renvoie le tableau des k plus proches voisins */
TabPts trouver_kppv_tab(TabPts tab_pts, point pt, int k){
  TabPts kppv = creer_tab_pts(tab_pts.dimension, tab_pts.nbclasse);
  int i, j;

  if(k <= 0){
    erreur("Erreur, k doit être supérieur à 0 dans la fonction trouver_kppv");
  }
  if(k > tab_pts.taille-1){
    erreur("Erreur, k doit être inférieur à n-1 dans la fonction trouver_kppv");
  }

  for(i = 0; i < tab_pts.taille; i++){
    /*on remplit le tableau tant que sa taille est inférieure à k*/
    if(kppv.taille < k){
      ajouter_point(
        &kppv,
        creer_point(kppv.dimension, tab_pts.tab[i].classe)
      );
      /*on ajoute les coordonnées dans le point du tableau kppv*/
      ajouter_coord(&kppv.tab[i], kppv.dimension, tab_pts.tab[i].coord);
    }
   /*sinon on remplace le premier point plus éloigné de pt que le point actuel*/
    else{
      j = 0;
      /*on trouve l'index du premier point le plus proche (s'il existe)*/
      while(j < kppv.taille
        && calc_distance(kppv.tab[j], pt, tab_pts.dimension)
        < calc_distance(tab_pts.tab[i], pt, tab_pts.dimension)
      ){
        j++;
      }
      if(j < kppv.taille){                  /*si un point est plus éloigné :*/
        supprimer_point(&kppv, j);          /* - on le supprime*/
                                            /* - on ajoute le point actuel*/
        ajouter_point(
          &kppv,
          creer_point(kppv.dimension, tab_pts.tab[i].classe)
        );
        /*on ajoute les coordonnées dans le point du tableau kppv*/
        ajouter_coord(&kppv.tab[kppv.taille-1],
                      kppv.dimension,
                      tab_pts.tab[i].coord
                    );
      }
    }
  }
  return kppv;
}

/* Permet de trouver la classe d'un point par rapport à ses kppv */
int trouver_classe_kppv_tab(TabPts tab, point pt, int k){
  TabPts kppv;
  int classe, i;

  /*calcul des kppv*/
  kppv = trouver_kppv_tab(tab, pt, k);

  /*calcul de la classe majoritaire parmi les kppv*/
  classe = classe_majoritaire(kppv);

  /*libération de la mémoire du tableau kppv*/
  for(i = 0; i < kppv.taille; i++){
    free(kppv.tab[i].coord);
  }
  free(kppv.tab);

  /*on renvoie la classe du point par rapport à ses kppv*/
  return classe;
}
