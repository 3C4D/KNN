/* Fichier source contenant les fonctions relatives aux arbres */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "erreur.h"
#include "arbre.h"

/* Permet de renvoyer un arbre vide */
arbre_kd creer_arbre_vide(){
  return NULL;    /* L'arbre vide correspond à la valeur NULL */
}

/* Permet de déterminer si un arbre est vide */
int est_vide_arbre_kd(arbre_kd arbre){
  return (arbre == NULL);   /* Un arbre est vide si il équivaut à NULL */
}

/* Permet de creer un noeud à partir de sa racine (ie un point) */
arbre_kd creer_noeud(point *pt){
  arbre_kd arbre = creer_arbre_vide();    /* Crée un noeud vide */

  arbre = (Noeud *)malloc(sizeof(Noeud)); /* Allocation du noeud */
  if(arbre == creer_arbre_vide()){        /* Vérification de l'allocation */
    erreur("Erreur d'allocation dans la fonction creer_noeud");
  }

  arbre->racine = pt;                     /* Insertion de la valeur du noeud */
  arbre->fils_g = creer_arbre_vide();     /* Met à vide le fils gauche */
  arbre->fils_d = creer_arbre_vide();     /* Met à vide le fils droit*/
  return arbre;                           /* On retourne le noeud obtenu */
}

/* Permet de creer un arbre à partir de sa racine et de ses fils*/
arbre_kd creer_arbre(point *pt, arbre_kd fils_gauche, arbre_kd fils_droit){
  arbre_kd arbre = creer_noeud(pt);       /* Création du noeud */

  arbre->fils_g = fils_gauche;            /* Insertion du fils gauche */
  arbre->fils_d = fils_droit;             /* Insertion du fils droit */

  return arbre;                           /* On retrourne l'arbre */
}

/* Permet de renvoyer la racine */
point *racine(arbre_kd arbre){
  return arbre->racine;
}

/* Permet de renvoyer le fils gauche */
arbre_kd renvoyer_fils_gauche(arbre_kd arbre){
  return arbre->fils_g;         /* On renvoie le fils droit */
}

/* Permet de renvoyer le fils droit */
arbre_kd renvoyer_fils_droit(arbre_kd arbre){
  return arbre->fils_d;         /* On renvoie le fils droit */
}

/* Permet d'insérer le fils gauche d'un arbre */
arbre_kd inserer_fils_gauche(arbre_kd arbre, arbre_kd fils_gauche){
  arbre->fils_g = fils_gauche;  /* On Insère le fils gauche */
  return arbre;                 /* On retourne l'arbre */
}

/* Permet d'insérer le fils droit d'un arbre */
arbre_kd inserer_fils_droit(arbre_kd arbre, arbre_kd fils_droit){
  arbre->fils_d = fils_droit;   /* On Insère le fils droit */
  return arbre;                 /* On retourne l'arbre */
}

/* Permet de déterminer si un noeud est une feuille */
int est_feuille(arbre_kd arbre){
  if(est_vide_arbre_kd(arbre)){  /* Si le noeud est vide il y a une erreur */
    erreur("Erreur, arbre vide passé en paramètre, fonction est_feuille");
  }
  /* Si les deux fils sont vides le noeud est une feuille */
  if(est_vide_arbre_kd(arbre->fils_g) && est_vide_arbre_kd(arbre->fils_d)){

  }
  return 0;           /* Sinon le noeud n'est pas une feuille */
}

/* Permet de détruire un arbre */
void detruire_arbre(arbre_kd arbre){
  if(est_feuille(arbre)){ /* Si l'arbre est une feuille on le libère */
    free(arbre);
  }
  else{     /* Sinon on libère ses fils non vides */
    /* On libère le fils gauche si il n'est pas vide */
    if(!est_vide_arbre_kd(renvoyer_fils_gauche(arbre))){
      detruire_arbre(renvoyer_fils_gauche(arbre));
    }
    /* On libère le fils droit si il n'est pas vide */
    if(!est_vide_arbre_kd(renvoyer_fils_droit(arbre))){
      detruire_arbre(renvoyer_fils_droit(arbre));
    }
    free(arbre);    /* Enfin on libère l'arbre lui-même */
  }
}

/* Fonction auxiliaire récursive permettant de construire un arbre kd */
/* à partir d'un tableau de point */
arbre_kd creer_arbre_kd_aux(TabPts *tab, int debut, int fin, int prof, int axe){
  int mediane = (int)round((fin-debut)/2);    /* Calcul de l'index median */
  printf("ok prof : %d debut : %d fin : %d\n", prof, debut, fin);
  if(mediane == 0){                           /* Si l'intervalle est de 1 : */
    return creer_noeud(&tab->tab[debut]);     /* On retourne la feuille */
  }

  /* On trie l'intervalle selon l'axe */
  tri_tab(tab->tab, debut, fin, prof%axe);

  /* On renvoie l'arbre créé en rappellant la fonction sur ses fils : */
  /* Légende : D : Debut, M : Mediane, F : Fin */
  return creer_arbre(&tab->tab[debut+mediane],
                     creer_arbre_kd_aux(tab,  /* Intervalle : D -> D+M-1 */
                                        debut,
                                        debut+mediane-1,
                                        prof+1,
                                        axe),
                     creer_arbre_kd_aux(tab,  /* Intervalle : D+M+1 -> F */
                                        debut+mediane+1,
                                        fin,
                                        prof+1,
                                        axe)
                    );
}

/* Permet de construire un arbre_kd à partir d'un tableau de points */
arbre_kd creer_arbre_kd(TabPts *tab){
  /* On retourne l'arbre créé recursivement */
  return creer_arbre_kd_aux(tab, 0, tab->taille, 0, tab->dimension);
}
