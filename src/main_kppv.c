/* Fichier principal correspondant à l'executable kppv */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "interface.h"
#include "points.h"
#include "erreur.h"
#include "kppv.h"
#include "sauvegarde.h"
#include "arbre.h"
#include "generation.h"
#include "recherche.h"

int main(int argc, char **argv){
  /*
  TabPts kppv;
  TabPts tab;
  TabPts essai;
  arbre_kd arbre = creer_arbre_vide();
  point p = creer_point(2, 5);
  point *pt;
  int i;
  double coord[2] = {-1.0, 0.9};

  ajouter_coord(&p, 2, coord);

  */
  // putchar('\n');
  // afficher_tab_pts(tab);
  // putchar('\n');
  // printf("%d %d\n", tab.taille, tab.taille_max);



  // arbre = creer_arbre_kd(&tab);
  // afficher_arbre_bis(arbre);
  srand(time(NULL));
  lancer_interface();
  /*
  arbre = insere(arbre, &pt);
  printf("######## Insertion ########################################\n");
  afficher_arbre_bis(arbre);
  afficher_pt(*(arbre->racine), tab.dimension);
  afficher_pt(*(arbre->fils_g->racine), tab.dimension);
  afficher_pt(*(arbre->fils_d->racine), tab.dimension);
  afficher_pt(*(arbre->fils_g->fils_g->racine), tab.dimension);
  afficher_pt(*(arbre->fils_g->fils_d->racine), tab.dimension);
  afficher_tab_pts(tab);


  if(argc < 2){
    erreur("Usage : kppv <entier> [<nom_fic> | <entier K>]");
  }

  srand(time(NULL));
  */
  // if((argv[1][0]-'0') == 1){
  //   tab = chargement_fichier(argv[2]);
  //   putchar('\n');
  //   afficher_tab_pts(tab);
  //   putchar('\n');
  //   pt = plus_lointain(tab.tab[0], tab);
  //   afficher_pt(*pt, 2);

  //   printf("######## POINTS ########\n");
  //   for(i = 0; i < 6; i++){
  //     printf("%f\n", calc_distance(tab.tab[0], tab.tab[i], 2));
  //   }
  // }
  // if((argv[1][0]-'0') == 2){
  //   // à completer
  // }
  exit(0);
}
