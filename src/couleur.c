
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "couleur.h"

/* Crée une couleur à partir d'une chaine de caractère hexadecimal */
MLV_Color couleur_hex(char *hex){
  char buff_comp[3] = {0};
  uint8_t comp[4]; /* Composantes red, green, blue, alpha */  
  int nb_comp = strlen(hex)/2, i;

  if (nb_comp < 3){
    return MLV_COLOR_BLACK;
  } else if (nb_comp < 4) {
    comp[3] = 0xff; /* Par défaut si non précisé l'opacité est maximale */
  }
  
  for (i = 0; i < nb_comp; i++){
    strncpy(buff_comp, hex, 2);
    comp[i] = strtol(buff_comp, NULL, 16); /* Converti une chaine hex en long */
    hex += 2;
  }
  
  return MLV_rgba(comp[0], comp[1], comp[2], comp[3]);
}

/* Crée un couleur à partir des valeurs 
h: hue (teinte)
s: saturation
l: luminosité */
MLV_Color couleur_hsla(int hue, int sat, int lum, int alpha){
  /* Formule de conversion selon:
  https://www.rapidtables.com/convert/color/hsl-to-rgb.html */
  int r, g, b;
  int tmp_rgb[3];
  r = g = b = 0;
  /* Hue est en ° càd comprit entre 0 et 359 */
  double lum_d = lum / 100.0; /* Pourcentage de luminosité */
  double sat_d = sat / 100.0; /* Pourcentage de saturation */
  double c = (1 - fabs(2 * lum_d - 1)) * sat_d;
  double x = c * (1 - fabs(fmod(hue / 60.0, 2.0) - 1));
  double m = lum_d - c / 2;

  tmp_rgb[0] = (int)((c + m) * 255);
  tmp_rgb[1] = (int)((x + m) * 255);
  tmp_rgb[2] = (int)(m * 255);

  if (hue >= 0 && hue < 60){
    r = tmp_rgb[0];
    g = tmp_rgb[1];
    b = tmp_rgb[2];
  } else if (hue >= 60 && hue < 120){
    r = tmp_rgb[1];
    g = tmp_rgb[0];
    b = tmp_rgb[2];
  } else if (hue >= 120 && hue < 180) {
    r = tmp_rgb[2];
    g = tmp_rgb[0];
    b = tmp_rgb[1];
  } else if (hue >= 180 && hue < 240) {
    r = tmp_rgb[2];
    g = tmp_rgb[1];
    b = tmp_rgb[0];
  } else if (hue >= 240 && hue < 300) {
    r = tmp_rgb[1];
    g = tmp_rgb[2];
    b = tmp_rgb[0];
  } else {
    r = tmp_rgb[0];
    g = tmp_rgb[2];
    b = tmp_rgb[1];
  }
  
  return (MLV_rgba(r, g, b, alpha));
}

/* Change la composante alpha d'une couleur */
MLV_Color couleur_changer_alpha(int alpha, MLV_Color col){
  uint8_t r, g, b, a;
  MLV_convert_color_to_rgba(col, &r, &g, &b, &a);
  return (MLV_rgba(r, g, b, alpha));
}

/* Génère une valeur 8-bits selon une graine */
u_int8_t gen_val(int graine){
  /* Chaque v est en réalité sur 2 bits */
  u_int8_t v1 = 0; /* Pour la teinte */
  u_int8_t v2 = 0; /* Pour la teinte */
  u_int8_t v3 = 0; /* Pour la saturation */
  u_int8_t v4 = 0; /* Pour la luminosité */
  u_int8_t val;
  int i;
  
  /* Fonctionne comme un compteur */
  for (i = 1; i <= graine; i++){
    v1 = i % 3;

    if (v1 == 0){
      v2++;

      if ((v2 % 4) == 0) {
        v2 = 0;
        v3++;

        if ((v3 % 4) == 0) {
          v3 = 0;
          v4++;
        }
      }
    }
  } 

  val = v1 | v2 << 2 | v3 << 4 | v4 << 6;
  return val;
}

/* Somme des inverses d'une valeur 8 bits*/
double inverse_char(u_int8_t val){
  double out = 0.0;
  int i;
  /* Soit un octets dont les bits dont numérotés de droite à gauche en partant
  de 0. Avec cet algorithme bit x = 1/2^x */

  for (i = 0; i < 8; i++){
    if (val & (1 << i)) {
      out += 1/(double)(2 << i);
    }
  }

  return out;
}

/* Génère une couleur à partir d'une graine */
MLV_Color gen_couleur(int graine){
  int h, s, l;
  u_int8_t val;

  if(graine == 0){ /* Valeur forcée pour la graine 0: Noir */
    return MLV_COLOR_BLACK;
  }
  
  val = gen_val(graine - 1);
  /* Pour la teinte:
  On pars de 0°, on ajoute 120° jusqu'à faire un tour,
  On pars de 60°, on fait un tour,
  On pars de 30°, on fait un tour, 
  On pars de (30 + 60)°, on fait un tour
  On reviens au départ */
  h = (120 * (val & 0x03) + (int)(inverse_char((val & 0x0c) >> 2) * 120)) % 360;
  s = (((val & 0x30) >> 4) + 1) * 10 + 55; /* Valeur comprise entre  65 et 95*/
  l = 66 - (((val & 0xc0) >> 6) + 1) * 8; /* Valeur comprise entre  58 et 34*/
  
  return (couleur_hsla(h, s, l, 0xff));
}
