#include "obj_kppv.h"
#include "erreur.h"
#include "couleur.h"

MLV_GraphKNN init_graph_kppv(MLV_Position pos){
  MLV_GraphKNN graph_kppv = malloc(sizeof(struct MLV_GraphKNN_s));
  verif_alloc(graph_kppv);
  graph_kppv->placement = pos;
  graph_kppv->graph2D = init_graph2D(
    pos, init_planr(
      init_axer(-1.025, 1.025, 0.2),
      init_axer(-1.025, 1.025, 0.2)
    )
  );
  graph_kppv->option_aff = 0x3f;
  graph_kppv->pt_kppv = NULL;
  graph_kppv->pts_classes = NULL;
  graph_kppv->curseur = init_clickable(pos, ACTIF, INTERNE);
  click_maj_proprio((void *)graph_kppv, graph_kppv->curseur);

  return graph_kppv;
}

void liberer_graph_kppv(MLV_GraphKNN *graph_kppv){
  if (*graph_kppv != NULL){
    liberer_position(&(*graph_kppv)->placement);
    liberer_graph2D(&(*graph_kppv)->graph2D);
    liberer_clickable(&(*graph_kppv)->curseur);
    free(*graph_kppv);
  }

  *graph_kppv = NULL;
}

void graph_kppv_ajouter_tab_pts(TabPts *tab_pts, MLV_GraphKNN graph_kppv){
  graph_kppv->pts_classes = tab_pts;
}

void graph_kppv_ajouter_pt(point *pt, MLV_GraphKNN graph_kppv){
  graph_kppv->pt_kppv = pt;
}

void graph_kppv_ajouter_opt_aff(char opt, MLV_GraphKNN graph_kppv){
  graph_kppv->option_aff |= opt;
}

void graph_kppv_suppr_opt_aff(char opt, MLV_GraphKNN graph_kppv){
  graph_kppv->option_aff &= ~(opt);
}

void graph_kppv_aff(MLV_GraphKNN graph_kppv){
  int i;

  if(graph_kppv->option_aff && SOUS_GRILLE_X){
    aff_sous_grille_x(5, graph_kppv->graph2D);
  }
  if(graph_kppv->option_aff && SOUS_GRILLE_Y){
    aff_sous_grille_y(5, graph_kppv->graph2D);
  }
  if(graph_kppv->option_aff && GRILLE_X){
    aff_grille_x(graph_kppv->graph2D);
  }
  if(graph_kppv->option_aff && GRILLE_Y){
    aff_grille_y(graph_kppv->graph2D);
  }
  if(graph_kppv->option_aff && AXE_X){
    aff_axe_x(graph_kppv->graph2D);
  }
  if(graph_kppv->option_aff && AXE_Y){
    aff_axe_y(graph_kppv->graph2D);
  }

  if(graph_kppv->pts_classes != NULL){
    for (i = 0; i < graph_kppv->pts_classes->taille; i++) {
      graph_kppv_aff_pt(graph_kppv->pts_classes->tab[i], graph_kppv);
    }
  }
}

void graph_kppv_aff_pt(point pt, MLV_GraphKNN graph_kppv){
  graph_placer_point(
    coord2d_point(pt), 
    gen_couleur(pt.classe),
    graph_kppv->graph2D
  );
}

Coord_R coord2d_point(point pt){
  if (pt.dimension == 1){
    return (init_coordr(pt.coord[0], 0.0));
  } else {
    return (init_coordr(pt.coord[0], pt.coord[1]));
  }
}

