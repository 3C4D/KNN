
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "couleur.h"

MLV_Color couleur_hex(char *hex){
  char buff_comp[3] = {0};
  uint8_t comp[4];
  int nb_comp = strlen(hex)/2, i;

  if (nb_comp < 3){
    return MLV_COLOR_BLACK;
  } else if (nb_comp < 4) {
    comp[3] = 0xff;
  }
  
  for (i = 0; i < nb_comp; i++){
    strncpy(buff_comp, hex, 2);
    comp[i] = strtol(buff_comp, NULL, 16);
    hex += 2;
  }
  
  return MLV_rgba(comp[0], comp[1], comp[2], comp[3]);
}

MLV_Color couleur_hsla(int hue, int sat, int lum, int alpha){
  int r, g, b;
  int tmp_rgb[3];
  r = g = b = 0;
  double lum_d = lum / 100.0;
  double sat_d = sat / 100.0;
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

MLV_Color couleur_changer_alpha(int alpha, MLV_Color col){
  uint8_t r, g, b, a;
  MLV_convert_color_to_rgba(col, &r, &g, &b, &a);
  return (MLV_rgba(r, g, b, alpha));
}

uint32_t joaat_hash(const char* graine) {
  uint32_t hash = 0;
  uint8_t c;
  while ((c = (uint8_t)*graine++)) {
    hash += c;
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}

MLV_Color gen_couleur(int graine){
  int i, len_int = 0;
  int h, s, l;
  uint32_t hash;
  char buff[17];
  memset(buff, 0, 17);

  sprintf(buff, "%x", graine);
  len_int = strlen(buff);
  for (i = len_int; i < 16 ; i++){
    buff[i] = 0x21 + (graine * i) % 94;
  }
  
  hash = joaat_hash(buff);
  h = ((graine * 7) % 36) * 10;
  s = ((hash & 0xff00) >> 10) + 32;
  l = ((hash & 0xff) >> 3) + 35;

  return (couleur_hsla(h, s, l, 0xff));
}
