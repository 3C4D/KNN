#include "points.h"
#include "erreur.h"

TabPts trouver_kppv(TabPts tab_pts, point pt, int k){
  TabPts kppv = creer_tab_pts();
  int i, j;

  if(k <= 0){
    erreur("k doit être supérieur à 0 dans la fonction trouver_kppv");
  }

  for(i = 0; i < tab_pts.taille; i++){
    if(kppv.taille < k){
      ajouter_point(&kppv, tab_pts.tab[i]);
    }
    else{
      j = 0;
      while(j < kppv.taille && calc_distance(kppv.tab[j], pt) < calc_distance(tab_pts.tab[i], pt)){
        j++;
      }
      supprimer_point(&kppv, j);
      ajouter_point(&kppv, tab_pts.tab[i]);
    }
  }
  return kppv;
}
