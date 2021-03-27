#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "points.h"
#include "erreur.h"

/* Permet de créer une structure point en prenant les composantes de cette
   structure en paramètre*/
point creer_point(double x, double y, int classe){
  point pt;
  pt.x = x;
  pt.y = y;
  pt.classe = classe;
  return pt;
}

/* Permet de calculer la distance euclidienne entre deux points */
double calc_distance(point p1, point p2){
  return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

/* Permet d'ajouter un point au tableau de points */
TabPts creer_tab_pts(){
  TabPts tab;
  /*on alloue un espace mémoire pour pouvoir utiliser realloc*/
  tab.tab = (point *)malloc(0);
  /*vérification de l'allocation*/
  if(tab.tab == NULL){
    erreur("Erreur d'allocation dans la fonction creer_tab_pts");
  }
  /*le tableau ne comporte pas d'élements, sa taille est donc 0*/
  tab.taille = 0;
  return tab;
}

/* Permet d'ajouter un point au tableau de points */
void ajouter_point(TabPts *tab_pts, point pt){
  /*on realloue le tableau en ajoutant une case*/
  tab_pts->tab = (point *)realloc(
    tab_pts->tab,
    (tab_pts->taille+1)*sizeof(point)
  );
  /*vérification de l'allocation*/
  if(tab_pts->tab == NULL){
    erreur("Erreur d'allocation dans la fonction ajouter_point");
  }

  tab_pts->tab[tab_pts->taille] = pt; /*on place le point dans la case*/
  tab_pts->taille += 1;               /*on incrémente la taille du tableau*/
}

/* Permet de supprimer un point du tableau de points dont on connait l'index */
void supprimer_point(TabPts *tab_pts, int index){
  int i;
  for(i = index; i < tab_pts->taille; i++){ /*On décale les élements afin*/
    tab_pts->tab[i] = tab_pts->tab[i+1];     /*d'écraser l'élement à supprimer*/
  }

  tab_pts->tab = (point *)realloc(      /*on diminue la taille du tableau de 1*/
    tab_pts->tab,
    (tab_pts->taille-1) * sizeof(point)
  );
  /*vérification de l'allocation*/
  if(tab_pts->tab == NULL){
    erreur("Erreur d'allocation dans la fonction supprimer_point");
  }

  tab_pts->taille -= 1;       /*on décremente la taille du tableau*/
}

/* Affiche un point */
void afficher_pt(point pt){
  printf("(%f, %f), classe : %d\n", pt.x, pt.y, pt.classe);
}

/* Affiche un tableau de points */
void afficher_tab_pts(TabPts tab_pts){
  int i;
  for(i = 0; i < tab_pts.taille; i++){
    afficher_pt(tab_pts.tab[i]);
  }
}
