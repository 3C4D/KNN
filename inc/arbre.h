/* Fichier header contenant les protypes des fonctions relatives aux arbres */

#ifndef ARBRE_H
#define ARBRE_H

#include "points.h"

/* Structure permettant de représenter le Noeud d'un arbre */
typedef struct Noeud{
  point *racine;
  struct Noeud *fils_g;
  struct Noeud *fils_d;
}Noeud;

typedef struct Noeud *arbre_kd;

/* Permet de renvoyer un arbre vide */
arbre_kd creer_arbre_vide();

/* Permet de déterminer si un arbre est vide */
int est_vide(arbre_kd arbre);

/* Permet de creer un noeud à partir de sa racine (ie un point) */
arbre_kd creer_noeud(point *pt);

/* Permet de creer un arbre à partir de sa racine et de ses fils*/
arbre_kd creer_arbre(point *pt, arbre_kd fils_gauche, arbre_kd fils_droit);

/* Permet d'afficher un arbre dans le terminal */
void afficher_arbre(arbre_kd arbre);

/* Permet de renvoyer la racine */
point *racine(arbre_kd arbre);

/* Permet de renvoyer le fils gauche */
arbre_kd renvoyer_fils_gauche(arbre_kd arbre);

/* Permet de renvoyer le fils droite */
arbre_kd renvoyer_fils_droit(arbre_kd arbre);

/* Permet d'insérer le fils gauche d'un arbre */
arbre_kd inserer_fils_gauche(arbre_kd arbre, arbre_kd fils_gauche);

/* Permet d'insérer le fils droit d'un arbre */
arbre_kd inserer_fils_droit(arbre_kd arbre, arbre_kd fils_droit);

/* Permet de déterminer si un noeud est une feuille */
int est_feuille(arbre_kd arbre);

/* Permet de détruire un arbre */
void detruire_arbre(arbre_kd arbre);

#endif
