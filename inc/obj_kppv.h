/*
Ce module implémente les graphiques ad-hoc à l'utilisation des KPPV
Il fait ainsi la liaison entre l'interface et la partie logique
*/

#ifndef OBJ_KPPV_H_
#define OBJ_KPPV_H_

#include "geometrie.h"
#include "obj_complexe.h"
#include "points.h"
#include "arbre.h"
#include "id_objet.h"

/* Drapeaux pour les options d'affichage */
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
  MLV_Position placement; /* Placement absolu du graph kppv */
  MLV_Clickable curseur; /* Detecteur de click sur le graphique */
  MLV_Graph2D graph2D; /* Graphique affiché */
  TabPts *pts_classes; /* Tableau des points classés */
  TabPts *tab_kppv; /* Tableau des KPPV du point pt_kppv */
  arbre_kd arbre; /* Arbre de recherche */
  point *pt_kppv; /* Point de recherche */
  int pts_ajoutes; /* Nombre de points ajoutés */
  int classe_util; /* Classe utilisée pour le placement des points */
  int k; /* Constante K */
  char option_aff; /* Options d'affichage */
};

/*-----==========Gestion du GraphKPPV==========-----*/
/* Crée un GraphKPPV */
MLV_GraphKNN init_graph_kppv(MLV_Position pos);
/* Libère l'espace occupé par le GraphKPPV */
void liberer_graph_kppv(MLV_GraphKNN *graph_kppv);

/*-----Gestion du tableau de point-----*/
/* Ajoute un tableau de points au GraphKPPV */
void graph_kppv_ajouter_tab_pts(TabPts *tab_pts, MLV_GraphKNN graph_kppv);
/* Importe, depuis un fichier, un tableau de points au GraphKPPV */
void graph_kppv_import_tab_pts(char *fichier, MLV_GraphKNN graph_kppv);
/* Exporte, dans un ficher, le tableau de points contenu dans le GraphKPPV */
void graph_kppv_export_tab_pts(char *fichier, MLV_GraphKNN graph_kppv);

/*-----Options d'affichage-----*/
/* Ajoute une option d'affichage */
void graph_kppv_ajouter_opt_aff(char opt, MLV_GraphKNN graph_kppv);
/* Supprime une option d'affichage */
void graph_kppv_suppr_opt_aff(char opt, MLV_GraphKNN graph_kppv);

/*-----Valeurs utilisées-----*/
/* Change la classe utilisée pour le mode création */
void graph_kppv_maj_classe_utilise(int classe, MLV_GraphKNN graph_kppv);
/* Change le K utilisé */
void graph_kppv_maj_k(int k, MLV_GraphKNN graph_kppv);

/*-----Affichage-----*/
/* Cache le point de recherche KPPV */
void graph_kppv_cacher_pt(MLV_GraphKNN graph_kppv);
/* Affiche le GraphKPPV */
void graph_kppv_aff(MLV_GraphKNN graph_kppv);

/*-----Mises à jour des composants-----*/
/* Met à jour le tableau des KPPV */
void graph_kppv_maj_tab_kppv(MLV_GraphKNN graph_kppv);
/* Met à jour l'arbre de recherche */
void graph_kppv_maj_arbre(MLV_GraphKNN graph_kppv);

/*-----Gestions des points-----*/
/* Supprime le dernier point ajouté */
void graph_kppv_suppr_pt_ajoute(MLV_GraphKNN graph_kppv);
/* Supprime tous les points ajoutés */
void graph_kppv_reinit_pt(MLV_GraphKNN graph_kppv);
/* Ajoute un point dans le tableau des points classés */
Id_Obj gkppv_ajouter_pt_classe(MLV_Clickable click, Info_Souris souris);
/* Change le point kppv de recherche */
Id_Obj gkppv_maj_pt(MLV_Clickable click, Info_Souris souris);

#endif