
#include <stdio.h>
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

u_int8_t gen_val(int graine){
  u_int8_t v1 = 0;
  u_int8_t v2 = 0;
  u_int8_t v3 = 0;
  u_int8_t v4 = 0;
  u_int8_t val;
  int i;
  
  for (i = 0; i < graine; i++){
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

double inverse_char(u_int8_t val){
  double out = 0.0;
  int i;

  for (i = 0; i < 8; i++){
    if (val & (1 << i)) {
      out += 1/(double)(2 << i);
    }
  }

  return out;
}

MLV_Color gen_couleur(int graine){
  int h, s, l;
  u_int8_t val;

  if(graine == 0){
    return MLV_COLOR_BLACK;
  }
  
  val = gen_val(graine - 1);
  h = (120 * (val & 0x03) + (int)(inverse_char((val & 0x0c) >> 2) * 120)) % 360;
  s = (((val & 0x30) >> 4) + 1) * 10 + 55;
  l = 66 - (((val & 0xc0) >> 6) + 1) * 8;
  
  return (couleur_hsla(h, s, l, 0xff));
}
