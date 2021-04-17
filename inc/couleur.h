#ifndef COULEUR_H_
#define COULEUR_H_

#include <MLV/MLV_all.h>
#include <stdint.h>

MLV_Color couleur_hex(char *hex);
MLV_Color couleur_hsla(int hue, int sat, int lum, int alpha);
MLV_Color couleur_changer_alpha(int alpha, MLV_Color col);
uint32_t joaat_hash(const char* graine);
MLV_Color gen_couleur(int graine);

#endif