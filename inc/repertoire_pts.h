#ifndef TAB_ADDR_PT_H_
#define TAB_ADDR_PT_H_

#include "points.h"

typedef struct RepertoirePts_s *RepertoirePts;
struct RepertoirePts_s {
  int taille;
  int taille_limite;
  point **addr_pts;
};

RepertoirePts init_repertoire();
void liberer_repertoire(RepertoirePts *rep);
void rep_inc_espace(RepertoirePts rep);
void rep_dec_espace(RepertoirePts rep);
void rep_ajouter_pt(point *pt, RepertoirePts rep);
void rep_suppr_pt(int index, RepertoirePts rep);
void rep_suppr_dernier_pt(RepertoirePts rep);
point *rep_trouver_pt(int index, RepertoirePts rep);

#endif