/*
Ce module introduit des fonctions permettant la gestion des couleurs
*/

#ifndef COULEUR_H_
#define COULEUR_H_

#include <MLV/MLV_all.h>
#include <stdint.h>

/* Crée une couleur à partir d'une chaine de caractère hexadecimal */
MLV_Color couleur_hex(char *hex);
/* Crée un couleur à partir des valeurs 
h: hue (teinte)
s: saturation
l: luminosité */
MLV_Color couleur_hsla(int hue, int sat, int lum, int alpha);
/* Change la composante alpha d'une couleur */
MLV_Color couleur_changer_alpha(int alpha, MLV_Color col);
/* Génère une couleur à partir d'une graine */
MLV_Color gen_couleur(int graine);

#endif