#include <stdlib.h>
#include "position.h"
#include "erreur.h"

/* Gestion du TAD Position */
MLV_Position init_positon(Coord decalage, Coord dimension) {
  MLV_Position pos_out = malloc(sizeof(struct MLV_Position_s));
  verif_alloc((void *)pos_out);
  pos_out->decalage = decalage;
  pos_out->dimension = dimension;

  return pos_out;
}

void liberer_position(MLV_Position *pos) {
  if (*pos != NULL) {
    free(*pos);
  }

  *pos = NULL;
}

MLV_Position cp_pos(MLV_Position pos){
  return(init_positon(pos->decalage, pos->dimension ));
}

void afficher_position(MLV_Position pos, MLV_Color col){
  if (pos != NULL) {
    MLV_draw_rectangle(
      pos->decalage.x,
      pos->decalage.y,
      pos->dimension.x,
      pos->dimension.y,
      col
    );
  }
}
