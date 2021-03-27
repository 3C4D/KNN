#include <stdlib.h>
#include <stdio.h>
#include "points.h"
#include "erreur.h"
#include "kppv.h"
#include "sauvegarde.h"

int main(){
  TabPts kppv;
  TabPts tab;

  printf("%d\n", tab.taille);
  tab = chargement_fichier("test");
  printf("%d\n", tab.taille);

  afficher_tab_pts(tab);
  printf("bonjour\n");
  putchar('\n');
  kppv = trouver_kppv(tab, tab.tab[1], 2);
  afficher_tab_pts(kppv);
  exit(0);
}
