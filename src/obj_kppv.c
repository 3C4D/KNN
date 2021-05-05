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

/*-----Fonctions privées-----*/
/* Affiche un point sur le GraphKPPV */
void graph_kppv_aff_pt(point pt, int taille, MLV_GraphKNN graph_kppv);
/* Affiche le cercle des KPPV */
void graph_kppv_aff_zone_kppv(MLV_GraphKNN graph_kppv);
/* Affiche l'arbre de recherche (fonction récursive) */
void graph_kppv_aff_arbre_kd( 
  Coord_R min, Coord_R max, int prof, arbre_kd arbre, MLV_GraphKNN graphe
);
/* Classe le point de recherche KPPV selon le tableau des KPPV */
void graph_kppv_classer_pt(MLV_GraphKNN graph_kppv);
/* Déclasse le point de recherche KPPV (Lui donne la classe 0) */
void graph_kppv_declasser_pt(MLV_GraphKNN graph_kppv);
/* Convertie un point en coordonées réelles 2D */
Coord_R coord2d_point(point pt);
/* Vérifie si une coordonnée est comprise entre -1.0 et 1.0 pour x et y */
bool coord_valide_kppv(Coord_R c);

/*-----==========Gestion du GraphKPPV==========-----*/
/* Crée un GraphKPPV */
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
  graph_kppv->curseur = init_clickable(cp_pos(pos), ACTIF, INTERNE);
  click_maj_proprio((void *)graph_kppv, graph_kppv->curseur);
  click_init_fct(gkppv_maj_pt, graph_kppv->curseur);

  return graph_kppv;
}

/* Libère l'espace occupé par le GraphKPPV */
void liberer_graph_kppv(MLV_GraphKNN *graph_kppv){
  if (*graph_kppv != NULL){
    liberer_position(&(*graph_kppv)->placement);
    liberer_graph2D(&(*graph_kppv)->graph2D);
    liberer_clickable(&(*graph_kppv)->curseur);
    free(*graph_kppv);
  }

  *graph_kppv = NULL;
}

/*-----Gestion du tableau de point-----*/
/* Ajoute un tableau de points au GraphKPPV */
void graph_kppv_ajouter_tab_pts(TabPts *tab_pts, MLV_GraphKNN graph_kppv){
  if (tab_pts != NULL){
    graph_kppv->pts_ajoutes = 0;
    detruire_tab_pts(graph_kppv->pts_classes);
    graph_kppv->pts_classes = tab_pts;
  }
}

/* Importe, depuis un fichier, un tableau de points au GraphKPPV */
void graph_kppv_import_tab_pts(char *fichier, MLV_GraphKNN graph_kppv){
  TabPts *tab = NULL;

  /* Si le fichier entré est vide on charge un tableau vide */
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

/* Exporte, dans un ficher, le tableau de points contenu dans le GraphKPPV */
void graph_kppv_export_tab_pts(char *fichier, MLV_GraphKNN graph_kppv){
  if (fichier != NULL && graph_kppv != NULL){
    sauvegarde_fichier(graph_kppv->pts_classes, fichier);
  } 
}

/*-----Options d'affichage-----*/
/* Ajoute une option d'affichage */
void graph_kppv_ajouter_opt_aff(char opt, MLV_GraphKNN graph_kppv){
  graph_kppv->option_aff |= opt;
}
/* Supprime une option d'affichage */
void graph_kppv_suppr_opt_aff(char opt, MLV_GraphKNN graph_kppv){
  graph_kppv->option_aff &= ~(opt);
}

/*-----Valeurs utilisées-----*/
/* Change la classe utilisée pour le mode création */
void graph_kppv_maj_classe_utilise(int classe, MLV_GraphKNN graph_kppv){
  if (classe >= 0){
    graph_kppv->classe_util = classe;
  }
}

/* Change le K utilisé */
void graph_kppv_maj_k(int k, MLV_GraphKNN graph_kppv){
  if (k >= 1){
    graph_kppv->k = k;
  }
}


void graph_kppv_classer_pt(MLV_GraphKNN graph_kppv){
  int classe_maj = -1;
  
  classe_maj = classe_majoritaire(*graph_kppv->tab_kppv);
  graph_kppv->pt_kppv->classe = classe_maj;
}

void graph_kppv_declasser_pt(MLV_GraphKNN graph_kppv){
  graph_kppv->pt_kppv->classe = 0;
}

/*-----Affichage-----*/
/* Cache le point de recherche KPPV */
void graph_kppv_cacher_pt(MLV_GraphKNN graph_kppv){
  graph_kppv->pt_kppv->classe = -1;
}

/* Affiche le GraphKPPV */
void graph_kppv_aff(MLV_GraphKNN graph_kppv){
  int i;

  /* On vide le graphique */
  vider_graph(graph_kppv->graph2D);

  /* Affichage de la sous-grille */
  if(graph_kppv->option_aff & SOUS_GRILLE){
    aff_sous_grille_x(5, graph_kppv->graph2D);
    aff_sous_grille_y(5, graph_kppv->graph2D);
  }

  /* Affichage de la grille */
  if(graph_kppv->option_aff & GRILLE){
    aff_grille_x(graph_kppv->graph2D);
    aff_grille_y(graph_kppv->graph2D);
  }

  /* Affichage des axes */
  if(graph_kppv->option_aff & AXE){
    aff_axe_x(graph_kppv->graph2D);
    aff_axe_y(graph_kppv->graph2D);
  }

  /* Affichage de l'arbre */
  if (graph_kppv->arbre != NULL && graph_kppv->pts_classes->taille != 0) {
    if (graph_kppv->option_aff & ARBRE_KD){
      graph_kppv_aff_arbre_kd(
        init_coordr(-1.0, -1.0), init_coordr(1.0, 1.0),
        0, graph_kppv->arbre, graph_kppv
      );
    }
  }

  /* Affichage des points classés */
  if(graph_kppv->pts_classes != NULL){
    for (i = 0; i < graph_kppv->pts_classes->taille; i++) {
      graph_kppv_aff_pt(graph_kppv->pts_classes->tab[i], 2, graph_kppv);
    }
  }

  /* Affichage des options KPPV */
  if(graph_kppv->pt_kppv != NULL && graph_kppv->pt_kppv->classe != -1){
    graph_kppv_maj_tab_kppv(graph_kppv);
    /* On vérifie s'il est possible de crée le tableau KPPV */
    if (graph_kppv->tab_kppv != NULL) {
      /* Affichage du cercle des KPPV */
      if(graph_kppv->option_aff & CERCLE_KPPV){
        graph_kppv_aff_zone_kppv(graph_kppv);
      }
      /* Classement du point de recherche */
      if (graph_kppv->option_aff & KPPV_DECISION){
        graph_kppv_classer_pt(graph_kppv);
      } else {
        graph_kppv_declasser_pt(graph_kppv);
      }
    } else {
      graph_kppv_declasser_pt(graph_kppv);
    }
    /* Affichage du point de recherche */
    graph_kppv_aff_pt(*graph_kppv->pt_kppv, 4, graph_kppv);
  }
}

void graph_kppv_aff_pt(point pt, int taille, MLV_GraphKNN graph_kppv){
  int type;
  if (pt.classe != 0){
    type = pt.classe % 5;
  } else {
    type = ROND;
  }
  
  graph_placer_point(
    coord2d_point(pt), 
    taille, type,
    gen_couleur(pt.classe),
    graph_kppv->graph2D
  );
}

void graph_kppv_aff_zone_kppv(MLV_GraphKNN graph_kppv){
  point *loin;

  if(graph_kppv->tab_kppv == NULL || graph_kppv->tab_kppv->taille == 0){
    return;
  }

  /* Trouve le point le plus loin pour tracer le cercle */
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
  /* NB:  min représente le coin supérieur gauche de la zone (xmin et ymin)
          max représente le coin inférieur droit de la zone (xmax et ymax) */
  if (arbre != NULL) { /* L'arbre n'est pas vide */
    noeud = *arbre->racine;
    if (prof % 2 == 0) { /* Comparaison sur l'axe x */
      /* On place un segment vertical passant par le point */
      graph_placer_segment(
        init_coordr(noeud.coord[0], min.y),
        init_coordr(noeud.coord[0], max.y),
        MLV_COLOR_BLUE, graphe->graph2D
      );

      /* Partie à droite de la séparation */
      tmp = init_coordr(noeud.coord[0], max.y);
      graph_kppv_aff_arbre_kd(
        min, tmp, prof + 1,
        arbre->fils_g, graphe
      );

      /* Partie à gauche de la séparation */
      tmp = init_coordr(noeud.coord[0], min.y);
      graph_kppv_aff_arbre_kd(
        tmp, max, prof + 1,
        arbre->fils_d, graphe
      );
    } else {  /* Comparaison sur l'axe y */
      /* On place un segment horizontal passant par le point */
      graph_placer_segment(
        init_coordr(min.x, noeud.coord[1]),
        init_coordr(max.x, noeud.coord[1]),
        MLV_COLOR_RED, graphe->graph2D
      );

      /* Partie haute de la séparation */
      tmp = init_coordr(max.x, noeud.coord[1]);
      graph_kppv_aff_arbre_kd(
        min, tmp, prof + 1,
        arbre->fils_g, graphe
      );

      /* Partie basse de la séparation */
      tmp = init_coordr(min.x, noeud.coord[1]);
      graph_kppv_aff_arbre_kd(
        tmp, max, prof + 1,
        arbre->fils_d, graphe
      );
    }
  }
}

/*-----Mises à jour des composants-----*/
/* Met à jour le tableau des KPPV */
void graph_kppv_maj_tab_kppv(MLV_GraphKNN graph_kppv){
  if (
    graph_kppv->k < 1 ||
    graph_kppv->pt_kppv->classe == -1 ||
    graph_kppv->pts_classes->taille == 0
  ){
    graph_kppv->tab_kppv = NULL;
    return;
  }
  
  graph_kppv->tab_kppv = recherche(
    graph_kppv->arbre, graph_kppv->pt_kppv,
    graph_kppv->k, graph_kppv->pts_classes->nbclasse
  );
}

/* Met à jour l'arbre de recherche */
void graph_kppv_maj_arbre(MLV_GraphKNN graph_kppv){
  arbre_kd a = creer_arbre_kd(graph_kppv->pts_classes);

  if (graph_kppv->arbre != NULL){
    detruire_arbre(graph_kppv->arbre);
  }

  graph_kppv->arbre = a;
}

/*-----Gestions des points-----*/
/* Supprime le dernier point ajouté */
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

/* Supprime tous les points ajoutés */
void graph_kppv_reinit_pt(MLV_GraphKNN graph_kppv){
  int i;
  int taille_finale = (
    graph_kppv->pts_classes->taille -
    graph_kppv->pts_ajoutes
  );

  /* Comme les points sont ordonnés ceux qui ont un ordre supérieur à la taille
  finale ont été ajoutés par l'utilisateur et donc peuvent être supprimé */
  for (i = 0; i < graph_kppv->pts_classes->taille; i++){
    if (graph_kppv->pts_classes->tab[i].ordre >= taille_finale) {
      supprimer_point(graph_kppv->pts_classes, i);
      i--;
    }
  }
  
  graph_kppv_maj_arbre(graph_kppv);
  graph_kppv->pts_ajoutes = 0;
}


/* Ajoute un point dans le tableau des points classés */
Id_Obj gkppv_ajouter_pt_classe(MLV_Clickable click, Info_Souris souris){
  MLV_GraphKNN graph_kppv = (MLV_GraphKNN)click_proprio(click);
  /* Conversion de la coordonnée souris en une coordonnée point */
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

  /* Ajout du point au tableau de points classés */
  tab_pts_maj_nb_classe(graph_kppv->classe_util, graph_kppv->pts_classes);
  ajouter_coord(&pt, 2, tab_coord);
  ajouter_point(graph_kppv->pts_classes, pt);

  graph_kppv->pts_ajoutes++;

  /* Si la taille est une puissance de 2 on recrée l'arbre sinon on fait une 
  simple insertion */
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

/* Change le point kppv de recherche */
Id_Obj gkppv_maj_pt(MLV_Clickable click, Info_Souris souris){
  MLV_GraphKNN graph_kppv = (MLV_GraphKNN)click_proprio(click);
  /* Conversion de la coordonnée souris en une coordonnée point */
  Coord curseur = coord_relative(
    coord_souris(souris), graph_kppv->placement->decalage
  );
  Coord_R coord_pt = coord_ztor(
    curseur, graph_kppv->graph2D->plan, graph_kppv->graph2D->mat_pix
  );
  double tab_coord[] = {coord_pt.x, coord_pt.y};

  /* Si la coordonnée n'est pas valide on ne place pas le point */
  if (!coord_valide_kppv(coord_pt)) {
    return GKPPV;
  }

  graph_kppv->pt_kppv->classe = 0;
  ajouter_coord(graph_kppv->pt_kppv, 2, tab_coord);
  graph_kppv_aff(graph_kppv);

  return GKPPV;
}

Coord_R coord2d_point(point pt){
  if (pt.dimension == 1){
    return (init_coordr(pt.coord[0], 0.0));
  } else {
    return (init_coordr(pt.coord[0], pt.coord[1]));
  }
}

bool coord_valide_kppv(Coord_R c){
  return (
    c.x >= -1.0 && c.x <= 1.0 &&
    c.y >= -1.0 && c.y <= 1.0
  );
}
