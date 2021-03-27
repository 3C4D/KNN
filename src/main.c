#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "points.h"
#include "erreur.h"
#include "kppv.h"
#include "sauvegarde.h"

int main(){
  TabPts kppv;
  TabPts tab;
  TabPts essai;

  srand(time(NULL));

  tab = chargement_fichier("test");

  afficher_tab_pts(tab);

  putchar('\n');

  kppv = trouver_kppv(tab, tab.tab[1], 2);
  afficher_tab_pts(kppv);

  putchar('\n');

  afficher_tab_pts(tab);
  sauvegarde_fichier(tab, "test_save");
  essai = chargement_fichier("test_save");

  putchar('\n');

  printf("%d\n", trouver_classe_kppv(tab, tab.tab[0], 4));
  afficher_tab_pts(essai);
  exit(0);
}
