/* Fichier source contenant les fonctions relatives aux arbres */

#include <stdlib.h>
#include <stdio.h>
#include "erreur.h"
#include "arbre.h"

/* Permet de renvoyer un arbre vide */
arbre_kd creer_arbre_vide(){
  return NULL;    /* L'arbre vide correspond à la valeur NULL */
}

/* Permet de déterminer si un arbre est vide */
int est_vide(arbre_kd arbre){
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
  if(est_vide(arbre)){  /* Si le noeud est vide il y a une erreur */
    erreur("Erreur, arbre vide passé en paramètre, fonction est_feuille");
  }
  /* Si les deux fils sont vides le noeud est une feuille */
  if(est_vide(arbre->fils_g) && est_vide(arbre->fils_d)){

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
    if(!est_vide(renvoyer_fils_gauche(arbre))){
      detruire_arbre(renvoyer_fils_gauche(arbre));
    }
    /* On libère le fils droit si il n'est pas vide */
    if(!est_vide(renvoyer_fils_droit(arbre))){
      detruire_arbre(renvoyer_fils_droit(arbre));
    }
    free(arbre);    /* Enfin on libère l'arbre lui-même */
  }
}
