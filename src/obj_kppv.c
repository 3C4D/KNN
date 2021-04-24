#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "obj_kppv.h"
#include "erreur.h"
#include "kppv.h"
#include "recherche.h"
#include "sauvegarde.h"
#include "couleur.h"
#include "math_op.h"

Id_Obj gkppv_ajouter_pt_classe(MLV_Clickable click, Info_Souris souris);
Id_Obj gkppv_maj_pt(MLV_Clickable click, Info_Souris souris);

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
  graph_kppv->option_aff = 0x07;
  graph_kppv->pt_kppv = malloc(sizeof(point));
  *graph_kppv->pt_kppv = creer_point(2, -1);
  graph_kppv->tab_kppv = NULL;
  graph_kppv->pts_classes = creer_tab_pts(2, 0);
  graph_kppv->arbre = NULL;
  graph_kppv->pts_ajoutes = 0;
  graph_kppv->classe_util = 0;
  graph_kppv->k = 1;
  graph_kppv->curseur = init_clickable(pos, ACTIF, INTERNE);
  click_maj_proprio((void *)graph_kppv, graph_kppv->curseur);
  click_init_fct(gkppv_maj_pt, graph_kppv->curseur);

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
  if (tab_pts != NULL){
    graph_kppv->pts_ajoutes = 0;
    detruire_tab_pts(graph_kppv->pts_classes);
    graph_kppv->pts_classes = tab_pts;
  }
}

void graph_kppv_import_tab_pts(char *fichier, MLV_GraphKNN graph_kppv){
  TabPts *tab = NULL;

  if (strcmp(fichier, "ressources/data/") == 0) {
    tab = creer_tab_pts(2, 0);
    detruire_arbre(graph_kppv->arbre);
    graph_kppv->tab_kppv = NULL;
    graph_kppv->arbre = NULL;
    graph_kppv_ajouter_tab_pts(tab, graph_kppv);
  } else if (fichier != NULL && graph_kppv != NULL){
    tab = chargement_fichier(fichier);
    graph_kppv_ajouter_tab_pts(tab, graph_kppv);
    graph_kppv_maj_arbre(graph_kppv);
    graph_kppv_maj_tab_kppv(graph_kppv);
  }
}

void graph_kppv_export_tab_pts(char *fichier, MLV_GraphKNN graph_kppv){
  if (fichier != NULL && graph_kppv != NULL){
    sauvegarde_fichier(graph_kppv->pts_classes, fichier);
  } 
}

void graph_kppv_ajouter_opt_aff(char opt, MLV_GraphKNN graph_kppv){
  graph_kppv->option_aff |= opt;
}

void graph_kppv_suppr_opt_aff(char opt, MLV_GraphKNN graph_kppv){
  graph_kppv->option_aff &= ~(opt);
}

void graph_kppv_maj_classe_utilise(int classe, MLV_GraphKNN graph_kppv){
  if (classe >= 0){
    graph_kppv->classe_util = classe;
  }
}

void graph_kppv_maj_k(int k, MLV_GraphKNN graph_kppv){
  if (k >= 1){
    graph_kppv->k = k;
  }
}

void graph_kppv_classer_pt(MLV_GraphKNN graph_kppv){
  int classe_maj = classe_majoritaire(*graph_kppv->tab_kppv);
  graph_kppv->pt_kppv->classe = classe_maj;
}

void graph_kppv_declasser_pt(MLV_GraphKNN graph_kppv){
  graph_kppv->pt_kppv->classe = 0;
}

void graph_kppv_cacher_pt(MLV_GraphKNN graph_kppv){
  graph_kppv->pt_kppv->classe = -1;
}

void graph_kppv_aff(MLV_GraphKNN graph_kppv){
  int i;

  vider_graph(graph_kppv->graph2D);
  if(graph_kppv->option_aff & SOUS_GRILLE){
    aff_sous_grille_x(5, graph_kppv->graph2D);
    aff_sous_grille_y(5, graph_kppv->graph2D);
  }
  if(graph_kppv->option_aff & GRILLE){
    aff_grille_x(graph_kppv->graph2D);
    aff_grille_y(graph_kppv->graph2D);
  }
  if(graph_kppv->option_aff & AXE){
    aff_axe_x(graph_kppv->graph2D);
    aff_axe_y(graph_kppv->graph2D);
  }

  if (graph_kppv->arbre != NULL && graph_kppv->pts_classes->taille != 0) {
    if (graph_kppv->option_aff & ARBRE_KD){
      graph_kppv_aff_arbre_kd(
        init_coordr(-1.0, -1.0), init_coordr(1.0, 1.0),
        0, graph_kppv->arbre, graph_kppv
      );
    }
  }

  if(graph_kppv->pts_classes != NULL){
    for (i = 0; i < graph_kppv->pts_classes->taille; i++) {
      graph_kppv_aff_pt(graph_kppv->pts_classes->tab[i], graph_kppv);
    }
  }

  if(graph_kppv->pt_kppv != NULL && graph_kppv->pt_kppv->classe != -1){
    if(graph_kppv->option_aff & CERCLE_KPPV){
      graph_kppv_aff_zone_kppv(graph_kppv);
    }
    if (graph_kppv->option_aff & KPPV_DECISION){
      graph_kppv_classer_pt(graph_kppv);
    } else {
      graph_kppv_declasser_pt(graph_kppv);
    }
    graph_kppv_aff_pt(*graph_kppv->pt_kppv, graph_kppv);
  }
}

void graph_kppv_aff_pt(point pt, MLV_GraphKNN graph_kppv){
  graph_placer_point(
    coord2d_point(pt),
    gen_couleur(pt.classe),
    graph_kppv->graph2D
  );
}

void graph_kppv_aff_zone_kppv(MLV_GraphKNN graph_kppv){
  point *loin;

  if(graph_kppv->tab_kppv == NULL){
    return;
  }

  loin = plus_lointain(*graph_kppv->pt_kppv, *graph_kppv->tab_kppv);
  graph_placer_cercle(
    coord2d_point(*graph_kppv->pt_kppv),
    calc_distance(*graph_kppv->pt_kppv, *loin, 2),
    MLV_COLOR_BLACK,
    graph_kppv->graph2D
  );
}

void graph_kppv_aff_arbre_kd(
  Coord_R min, Coord_R max, int prof, arbre_kd arbre, MLV_GraphKNN graphe
){
  point noeud;
  Coord_R tmp;
  if (arbre != NULL) {
    noeud = *arbre->racine;
    if (prof % 2 == 0) {
      graph_placer_segment(
        init_coordr(noeud.coord[0], min.y),
        init_coordr(noeud.coord[0], max.y),
        MLV_COLOR_BLUE, graphe->graph2D
      );

      tmp = init_coordr(noeud.coord[0], max.y);
      graph_kppv_aff_arbre_kd(
        min, tmp, prof + 1,
        arbre->fils_g, graphe
      );

      tmp = init_coordr(noeud.coord[0], min.y);
      graph_kppv_aff_arbre_kd(
        tmp, max, prof + 1,
        arbre->fils_d, graphe
      );
    } else {
      graph_placer_segment(
        init_coordr(min.x, noeud.coord[1]),
        init_coordr(max.x, noeud.coord[1]),
        MLV_COLOR_RED, graphe->graph2D
      );
      tmp = init_coordr(max.x, noeud.coord[1]);
      graph_kppv_aff_arbre_kd(
        min, tmp, prof + 1,
        arbre->fils_g, graphe
      );

      tmp = init_coordr(min.x, noeud.coord[1]);
      graph_kppv_aff_arbre_kd(
        tmp, max, prof + 1,
        arbre->fils_d, graphe
      );
    }
  }
}

void graph_kppv_maj_tab_kppv(MLV_GraphKNN graph_kppv){
  if (
    graph_kppv->k < 1 ||
    graph_kppv->pt_kppv->classe == -1 ||
    graph_kppv->pts_classes->taille == 0
  ){
    return;
  }
  
  graph_kppv->tab_kppv = recherche(
    graph_kppv->arbre, graph_kppv->pt_kppv,
    graph_kppv->k, graph_kppv->pts_classes->nbclasse
  );
}

void graph_kppv_maj_arbre(MLV_GraphKNN graph_kppv){
  arbre_kd a = creer_arbre_vide();
  a = creer_arbre_kd(graph_kppv->pts_classes);

  if (graph_kppv->arbre != NULL){
    detruire_arbre(graph_kppv->arbre);
  }

  graph_kppv->arbre = a;
}

void graph_kppv_suppr_pt_ajoute(MLV_GraphKNN graph_kppv){
  int i, index;
  if (graph_kppv->pts_ajoutes == 0){
    return;
  }

  i = 0;
  index = graph_kppv->pts_classes->taille - 1;
  while (index != graph_kppv->pts_classes->tab[i].ordre){
    i++;
  }
  supprimer_point(graph_kppv->pts_classes, i);
  
  graph_kppv_maj_arbre(graph_kppv);
  graph_kppv->pts_ajoutes--;
}

void graph_kppv_reinit_pt(MLV_GraphKNN graph_kppv){
  int i;
  int taille_finale = (
    graph_kppv->pts_classes->taille -
    graph_kppv->pts_ajoutes
  );

  for (i = 0; i < graph_kppv->pts_classes->taille; i++){
    if (graph_kppv->pts_classes->tab[i].ordre >= taille_finale) {
      supprimer_point(graph_kppv->pts_classes, i);
      i--;
    }
  }
  
  graph_kppv_maj_arbre(graph_kppv);
  graph_kppv->pts_ajoutes = 0;
}

Coord_R coord2d_point(point pt){
  if (pt.dimension == 1){
    return (init_coordr(pt.coord[0], 0.0));
  } else {
    return (init_coordr(pt.coord[0], pt.coord[1]));
  }
}

bool coord_valide_kppv(Coord_R c);

Id_Obj gkppv_ajouter_pt_classe(MLV_Clickable click, Info_Souris souris){
  MLV_GraphKNN graph_kppv = (MLV_GraphKNN)click_proprio(click);
  Coord curseur = coord_relative(
    coord_souris(souris), graph_kppv->placement->decalage
  );
  Coord_R coord_pt = coord_ztor(
    curseur, graph_kppv->graph2D->plan, graph_kppv->graph2D->mat_pix
  );
  point pt = creer_point(2, graph_kppv->classe_util);
  double tab_coord[] = {coord_pt.x, coord_pt.y};
  int index_pt;

  if (!coord_valide_kppv(coord_pt)) {
    return GKPPV;
  }

  tab_pts_maj_nb_classe(graph_kppv->classe_util, graph_kppv->pts_classes);
  ajouter_coord(&pt, 2, tab_coord);
  ajouter_point(graph_kppv->pts_classes, pt);
  graph_kppv->pts_ajoutes++;

  if (est_puissance_2(graph_kppv->pts_classes->taille)) {
    graph_kppv_maj_arbre(graph_kppv);
  } else {
    index_pt = graph_kppv->pts_classes->taille-1;
    insere(graph_kppv->arbre, &graph_kppv->pts_classes->tab[index_pt]);
  }

  graph_kppv_maj_tab_kppv(graph_kppv);
  graph_kppv_aff(graph_kppv);

  return GKPPV;
}

Id_Obj gkppv_maj_pt(MLV_Clickable click, Info_Souris souris){
  MLV_GraphKNN graph_kppv = (MLV_GraphKNN)click_proprio(click);
  Coord curseur = coord_relative(
    coord_souris(souris), graph_kppv->placement->decalage
  );
  Coord_R coord_pt = coord_ztor(
    curseur, graph_kppv->graph2D->plan, graph_kppv->graph2D->mat_pix
  );
  double tab_coord[] = {coord_pt.x, coord_pt.y};

  if (!coord_valide_kppv(coord_pt)) {
    return GKPPV;
  }

  graph_kppv->pt_kppv->classe = 0;
  ajouter_coord(graph_kppv->pt_kppv, 2, tab_coord);
  graph_kppv_aff(graph_kppv);

  return GKPPV;
}

void gkppv_desactiver_pt(MLV_GraphKNN graph_kppv){
  graph_kppv->pt_kppv->classe = -1;
}

bool coord_valide_kppv(Coord_R c){
  return (
    c.x >= -1.0 && c.x <= 1.0 &&
    c.y >= -1.0 && c.y <= 1.0
  );
}
