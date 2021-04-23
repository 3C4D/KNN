#include <stdlib.h>
#include "repertoire_pts.h"
#include "erreur.h"

RepertoirePts init_repertoire(){
  RepertoirePts rep = malloc(sizeof(struct RepertoirePts_s));
  verif_alloc(rep);
  rep->taille = 0;
  rep->taille_limite = 16;
  rep->addr_pts = malloc(sizeof(point *) * rep->taille_limite);

  return rep;
}

void liberer_repertoire(RepertoirePts *rep){
  if (*rep != NULL){
    free((*rep)->addr_pts);
    free(*rep);
  }
  
  *rep = NULL;
}

void rep_inc_espace(RepertoirePts rep){
  if (rep->taille == rep->taille_limite){
    rep->taille_limite *= 2;
    rep->addr_pts = realloc(rep->addr_pts, rep->taille_limite);
    verif_alloc(rep->addr_pts);
  }
}

void rep_dec_espace(RepertoirePts rep){
  if (rep->taille == rep->taille_limite / 2){
    rep->taille_limite /= 2;
    rep->addr_pts = realloc(rep->addr_pts, rep->taille_limite);
    verif_alloc(rep->addr_pts);
  }
}

void rep_ajouter_pt(point *pt, RepertoirePts rep){
  rep_inc_espace(rep);
  rep->addr_pts[rep->taille] = pt;
  rep->taille++;
}

void rep_suppr_pt(int index, RepertoirePts rep){
  int i;
  if (index < 0 || index >= rep->taille){
    return;
  }
  
  rep->addr_pts[index] = NULL;
  for (i = index + 1; i < rep->taille; i++) {
    rep->addr_pts[i - 1] = rep->addr_pts[i];
  }

  rep->taille--;
  rep_dec_espace(rep);
}

void rep_suppr_dernier_pt(RepertoirePts rep){
  if (rep->taille <= 0){
    return;
  }
  
  rep->taille--;
  rep->addr_pts[rep->taille] = NULL;
  rep_dec_espace(rep);
}

point *rep_trouver_pt(int index, RepertoirePts rep) {
  if (index < 0 || index >= rep->taille){
    return NULL;
  }

  return (rep->addr_pts[index]);
}