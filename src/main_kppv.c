/* Fichier principal correspondant à l'executable kppv */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "points.h"
#include "erreur.h"
#include "kppv.h"
#include "sauvegarde.h"
#include "arbre.h"
#include "generation.h"

int main(){

  TabPts kppv;
  TabPts tab;
  TabPts essai;
  arbre_kd arbre = creer_arbre_vide();

  srand(time(NULL));

  tab = chargement_fichier("test");

  putchar('\n');
  afficher_tab_pts(tab);
  putchar('\n');


  arbre = creer_arbre_kd(&tab);
  afficher_arbre_bis(arbre);
  /*
  afficher_pt(*(arbre->racine), tab.dimension);
  afficher_pt(*(arbre->fils_g->racine), tab.dimension);
  afficher_pt(*(arbre->fils_d->racine), tab.dimension);
  afficher_pt(*(arbre->fils_g->fils_g->racine), tab.dimension);
  afficher_pt(*(arbre->fils_g->fils_d->racine), tab.dimension);
  afficher_tab_pts(tab);

  kppv = trouver_kppv(tab, tab.tab[231], 500);
  afficher_tab_pts(kppv);

  putchar('\n');

  afficher_tab_pts(tab);
  sauvegarde_fichier(tab, "test_save");
  essai = chargement_fichier("test_save");

  putchar('\n');

  printf("%d\n", trouver_classe_kppv(tab, tab.tab[0], 4));
  afficher_tab_pts(essai);
  arbre = creer_arbre(&tab.tab[2], creer_arbre(&tab.tab[5],
  creer_noeud(&tab.tab[21]), creer_arbre_vide()), creer_noeud(&tab.tab[8]));
  afficher_pt(*(arbre->racine), tab.dimension);

  afficher_pt(tab.tab[2], tab.dimension);
  afficher_pt(tab.tab[5], tab.dimension);
  afficher_pt(tab.tab[8], tab.dimension);
  printf("suppression\n");
  detruire_arbre(arbre);
  afficher_pt(tab.tab[2], tab.dimension);
  afficher_pt(tab.tab[5], tab.dimension);
  afficher_pt(tab.tab[8], tab.dimension);
  afficher_pt(*(arbre->racine), tab.dimension);
  */

  exit(0);
}
