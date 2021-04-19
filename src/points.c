/* Fichier source contenant les fonctions relatives à la manipulation de */
/* points et de tableaux de point */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "points.h"
#include "erreur.h"

/* Permet de créer un point d'une classe donnée */
point creer_point(int dimension, int classe){
  point pt;
  pt.classe = classe;       /* Mise en place de la classe */
  pt.dimension = dimension; /* Mise en place de la dimension */
  return pt;                /* On retourne le point */
}

/* Ajoute les coordonnées contenues dans un tableau dans un point */
void ajouter_coord(point *pt, int dimension, double *coord){
  int i;

  /*on alloue un espace mémoire correspondant au nombre de dimensions*/
  pt->coord = (double *)malloc(dimension * sizeof(double));
  /*vérification de l'allocation*/
  if(pt->coord == NULL){
    erreur("Erreur d'allocation dans la fonction creer_tab_pts");
  }

  for(i = 0; i < dimension; i++){ /*on met les coordonnées dans le point*/
    pt->coord[i] = coord[i];
  }
}

/* Permet de calculer la distance euclidienne entre deux points */
double calc_distance(point p1, point p2, int dimension){
  int i;
  double somme = 0;
  for(i = 0; i < dimension; i++){
    somme += (p1.coord[i] - p2.coord[i]) * (p1.coord[i] - p2.coord[i]);
  }
  return sqrt(somme);
}

/* Permet d'ajouter un point au tableau de points */
TabPts *creer_tab_pts(int dimension, int nbclasse){
  TabPts *tab;
  tab = (TabPts *)malloc(sizeof(TabPts));
  /*on alloue un espace mémoire pour pouvoir utiliser realloc*/
  tab->tab = (point *)malloc(16*sizeof(point));
  tab->taille_max = 16;
  /*vérification de l'allocation*/
  if(tab->tab == NULL){
    erreur("Erreur d'allocation dans la fonction creer_tab_pts");
  }
  /*le tableau ne comporte pas d'élements, sa taille est donc 0*/
  tab->taille = 0;
  /*on insère les champs dans les emplacements correspondants*/
  tab->dimension = dimension;
  tab->nbclasse = nbclasse;
  return tab;
}

void detruire_tab_pts(TabPts *tab){
  int i;
  /*libération de la mémoire du tableau tab*/
  if(tab != NULL){
    for(i = 0; i < tab->taille; i++){
      free(tab->tab[i].coord);
    }
    free(tab->tab);
    free(tab);
  }
}

void tab_pts_maj_nb_classe(int classe, TabPts *tab){
  if (classe > tab->nbclasse){
    tab->nbclasse = classe;
  }
}

/* Permet d'ajouter un point au tableau de points */
void ajouter_point(TabPts *tab_pts, point pt){
  /*on realloue le tableau en ajoutant 10 cases si le tableau est plein*/
  if(tab_pts->taille == tab_pts->taille_max){
    tab_pts->taille_max += 16;
    tab_pts->tab = (point *)realloc(
      tab_pts->tab,
      (tab_pts->taille+16)*sizeof(point)
    );
  }
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

  free(tab_pts->tab[index].coord);

  for(i = index; i < tab_pts->taille; i++){ /*On décale les élements afin*/
    tab_pts->tab[i] = tab_pts->tab[i+1];     /*d'écraser l'élement à supprimer*/
  }

  tab_pts->taille -= 1;       /*on décremente la taille du tableau*/
}

/* Affiche un point */
void afficher_pt(point pt, int dimension){
  int i;
  putchar('(');
  for(i = 0; i < dimension-1; i++){
    printf("%lf, ", pt.coord[i]);
  }
  printf("%lf) classe : %d\n", pt.coord[dimension-1], pt.classe);
}

/* Affiche un tableau de points */
void afficher_tab_pts(TabPts tab_pts){
  int i;
  for(i = 0; i < tab_pts.taille; i++){
    afficher_pt(tab_pts.tab[i], tab_pts.dimension);
  }
}

/* Retourne la classe la plus présente dans un tableau de points */
int classe_majoritaire(TabPts tab){
  int *eff_classe, i, max = 0, val_max = 0;

  /*on alloue à un tableau autant de cases que le tableau possède de classes*/
  /*ce tableau repertoriera l'effectif des classes dans le tableau*/
  eff_classe = (int *)calloc(0, tab.nbclasse * sizeof(int));
  /*on vérifie l'allocation*/
  if(eff_classe == NULL){
    erreur("Erreur d'allocation dans la fonction classe_majoritaire");
  }

  /*ici on part du postulat que si il y a 5 classes, les classes vont de
    1 à 5*/
  for(i = 0; i < tab.taille; i++){
    eff_classe[tab.tab[i].classe-1]++;
  }

  /*on calcule l'effectif maximal*/
  for(i = 0; i < tab.nbclasse; i++){
    /*si l'effectif est supérieur au max, on remplace le max*/
    if(eff_classe[i] > val_max){
      val_max = eff_classe[i];
      max = i+1;
    }
    /*si il y a égalité, on choisit au hasard un des deux nombre*/
    if(val_max != 0 && val_max == eff_classe[i]){
      if(rand()%2 == 0){
        val_max = eff_classe[i];
        max = i+1;
      }
    }
  }

  /*on retourne la classe maximale*/
  return max;
}

/* Trie une liste de points récursivement */
void tri_tab(point *tab, int premier, int dernier, int axe){
  point pivot = tab[premier];   /* On fixe le pivot */
  int pos = premier;            /* La position actuelle est celle du premier */
  int i;

  if(premier < dernier){        /* si il reste des élements à traiter */
    for(i = premier; i < dernier; i++){ /* Pour tous ces élements : */
      if(tab[i].coord[axe] < pivot.coord[axe]){ /* Si le pivot est inférieur */
        tab[pos] = tab[i];          /* Le point pos devient le point i */
        pos++;                      /* On incrémente la position */
        tab[i] = tab[pos];          /* Le point i devient le point pos */
        tab[pos] = pivot;           /* Le point pos devient le pivot */
      }
    }
    /* On rappelle la fonction sur les élements précedant le pivot */
    tri_tab(tab, premier, pos, axe);
    /* On rappelle la fonction sur les élements suivants le pivot */
    tri_tab(tab, pos+1, dernier, axe);
  }
}

/* Renvoie le point d'un tableau de points le plus éloigné d'un point p */
point *plus_lointain(point p, TabPts tab){
  int i, victime = 0;
  if(tab.taille == 0){  /* Erreur si le tableau est vide */
    erreur("Erreur tableau vide dans la fonction plus_lointain()");
  }
  for(i = 0; i < tab.taille; i++){  /* On cherche la victime */
    if(calc_distance(tab.tab[i], p, p.dimension)
    > calc_distance(tab.tab[victime], p, p.dimension)){
      victime = i;
    }
  }
  return &tab.tab[victime]; /* On renvoie un pointeur sur la victime */
}
