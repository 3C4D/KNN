#include <stdlib.h>
#include <stdio.h>
#include "points.h"
#include "erreur.h"
#include "kppv.h"

int main(){
  TabPts tab, kppv;
  tab = creer_tab_pts();
  ajouter_point(&tab, creer_point(2, 4, 1));
  ajouter_point(&tab, creer_point(0, 7, 1));
  ajouter_point(&tab, creer_point(3, 6, 1));
  ajouter_point(&tab, creer_point(-1, 4, 1));

  afficher_tab_pts(tab);
  putchar('\n');
  kppv = trouver_kppv(tab, creer_point(1, 1, 1), 2);
  afficher_tab_pts(kppv);
  exit(0);
}
