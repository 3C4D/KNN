#ifndef OBJ_KPPV_H_
#define OBJ_KPPV_H_

#include "geometrie.h"
#include "obj_complexe.h"
#include "points.h"
#include "arbre.h"
#include "id_objet.h"

typedef enum {
  AXE = 0x01,
  GRILLE = 0x02,
  SOUS_GRILLE = 0x4,
  CERCLE_KPPV = 0x8,
  KPPV_DECISION = 0x10,
  ARBRE_KD = 0x20
} DrapOptAff;

typedef struct MLV_GraphKNN_s *MLV_GraphKNN;
struct MLV_GraphKNN_s {
  MLV_Position placement;
  MLV_Clickable curseur;
  MLV_Graph2D graph2D;
  TabPts *pts_classes;
  TabPts *tab_kppv;
  arbre_kd arbre;
  point *pt_kppv;
  int pts_ajoutes;
  int classe_util;
  int k;
  char option_aff;
};

MLV_GraphKNN init_graph_kppv(MLV_Position pos);
void liberer_graph_kppv(MLV_GraphKNN *graph_kppv);
void graph_kppv_ajouter_tab_pts(TabPts *tab_pts, MLV_GraphKNN graph_kppv);
void graph_kppv_import_tab_pts(char *fichier, MLV_GraphKNN graph_kppv);
void graph_kppv_export_tab_pts(char *fichier, MLV_GraphKNN graph_kppv);
void graph_kppv_ajouter_opt_aff(char opt, MLV_GraphKNN graph_kppv);
void graph_kppv_suppr_opt_aff(char opt, MLV_GraphKNN graph_kppv);
void graph_kppv_maj_classe_utilise(int classe, MLV_GraphKNN graph_kppv);
void graph_kppv_maj_k(int k, MLV_GraphKNN graph_kppv);
void graph_kppv_cacher_pt(MLV_GraphKNN graph_kppv);
void graph_kppv_aff(MLV_GraphKNN graph_kppv);
void graph_kppv_aff_pt(point pt, MLV_GraphKNN graph_kppv);
void graph_kppv_aff_zone_kppv(MLV_GraphKNN graph_kppv);
void graph_kppv_aff_arbre_kd(
  Coord_R min, Coord_R max, int prof, arbre_kd arbre, MLV_GraphKNN graphe
);
void graph_kppv_maj_tab_kppv(MLV_GraphKNN graph_kppv);
void graph_kppv_maj_arbre(MLV_GraphKNN graph_kppv);
void graph_kppv_nettoyage_tab_pt(MLV_GraphKNN graph_kppv);
void graph_kppv_suppr_pt_ajoute(MLV_GraphKNN graph_kppv);
void graph_kppv_reinit_pt(MLV_GraphKNN graph_kppv);
Coord_R coord2d_point(point pt);
Id_Obj gkppv_ajouter_pt_classe(MLV_Clickable click, Info_Souris souris);
Id_Obj gkppv_maj_pt(MLV_Clickable click, Info_Souris souris);

#endif