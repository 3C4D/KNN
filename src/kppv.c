#include "points.h"
#include "erreur.h"

TabPts trouver_kppv(TabPts tab_pts, point pt, int k){
  TabPts kppv = creer_tab_pts(tab_pts.dimension, tab_pts.nbclasse);
  int i, j;

  if(k <= 0){
    erreur("k doit être supérieur à 0 dans la fonction trouver_kppv");
  }

  for(i = 0; i < tab_pts.taille; i++){
    /*on remplit le tableau tant que sa taille est inférieure à k*/
    if(kppv.taille < k){
      ajouter_point(&kppv, tab_pts.tab[i]);
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
      if(j < kppv.taille){                    /*si un point est plus éloigné :*/
        supprimer_point(&kppv, j);            /* - on le supprime*/
        ajouter_point(&kppv, tab_pts.tab[i]); /* - on ajoute le point actuel*/
      }
    }
  }
  return kppv;
}
