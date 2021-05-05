/*
Ce module implémente les objets dis complexes, ils sont formés d'objets simples
et reproduisent des classiques des interfaces modernes.
*/

#ifndef OBJ_COMPLEXE_H_
#define OBJ_COMPLEXE_H_

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include "string_obj.h"
#include "texte.h"
#include "position.h"
#include "obj_simple.h"
#include "interactif.h"
#include "id_objet.h"
#include "peripheriques.h"

/* Forme des points */
typedef enum {LOSANGE, ROND, CARRE, TRIANGLE, CROIX} Forme;

typedef struct MLV_CheckBox_s *MLV_CheckBox;
struct MLV_CheckBox_s {
  MLV_Position placement; /* Position absolue du coche */
  MLV_Toggle case_coche; /* Bascule du coche */
  MLV_Text label; /* Label du coche */
  bool valide; /* Validité du coche */
};

typedef struct MLV_SpinBox_s *MLV_SpinBox;
struct MLV_SpinBox_s {
  MLV_Position placement; /* Position absolue du compteur */
  MLV_Button aug; /* Bouton d'incrément */
  MLV_Button dim; /* Bouton de décrément */
  MLV_Input info; /* Entrée nombre */
  int min; /* Valeur minimale */
  int max; /* Valeur maximale */
  int val; /* Valeur actuelle */
};

typedef struct MLV_Graph2D_s *MLV_Graph2D;
struct MLV_Graph2D_s {
  MLV_Position placement; /* Position absolu du graphique */
  MLV_Canvas surface; /* Surface d'affichage */
  Plan_R plan; /* Plan réel */
  Plan_Z mat_pix; /* Plan affiché en pixel */
};

typedef struct MLV_FileManager_s *MLV_FileManager;
struct MLV_FileManager_s {
  MLV_Position placement; /* Placement absolu du gestionnaire de fichier */
  MLV_Input fichier; /* Fichier utilisé */
  MLV_Button operation; /* Bouton d'action avec le fichier */
  String repertoire; /* Répertoire par défaut */
  void (*fct_fichier)(char *); /* Action avec le fichier */
};

/*-----==========Gestion des coches==========-----*/
/* Crée un coche */
MLV_CheckBox init_coche(MLV_Position pos, char *label, bool valide);
/* Libère l'espace occupé par le coche */
void liberer_coche(MLV_CheckBox *coche);
/* Change la validation du coche */
Id_Obj changer_validation(MLV_Clickable click, Info_Souris souris) ;
/* Coche/valide le coche */
void cocher_case_coche(MLV_CheckBox coche);
/* Décoche le coche */
void decocher_case_coche(MLV_CheckBox coche);
/* Désactive le coche */
void desactiver_coche(MLV_CheckBox coche);
/* Active le coche */
void activer_coche(MLV_CheckBox coche);

/*-----==========Gestion des compteurs==========-----*/
/* Crée un compteur */
MLV_SpinBox init_compteur(MLV_Position pos, int min, int max, int val);
/* Libère l'espace occupé par le compteur */
void liberer_compteur(MLV_SpinBox *compteur);
/* Désactive le compteur */
void desactiver_compteur(MLV_SpinBox compteur);
/* Active le compteur */
void activer_compteur(MLV_SpinBox compteur);

/*-----==========Gestion des graphiques==========-----*/
/* Crée un graphique */
MLV_Graph2D init_graph2D(MLV_Position pos, Plan_R plan);
/* Libère l'espace occupé par le graphique */
void liberer_graph2D(MLV_Graph2D *graph2D);
/* Efface tout le contenu du graphique */
void vider_graph(MLV_Graph2D graph2D);
/* Affiche l'axe des abscisses */
void aff_axe_x(MLV_Graph2D graph2D);
/* Affiche l'axe des ordonnées */
void aff_axe_y(MLV_Graph2D graph2D);
/* Affiche la grille sur les x */
void aff_grille_x(MLV_Graph2D graph2D);
/* Affiche la grille sur les y */
void aff_grille_y(MLV_Graph2D graph2D);
/* Affiche la sous-grille sur les x */
void aff_sous_grille_x(int nb_sections, MLV_Graph2D graph2D);
/* Affiche la sous-grille sur les y */
void aff_sous_grille_y(int nb_sections, MLV_Graph2D graph2D);
/* Place un segmenet sur le graphique */
void graph_placer_segment(
  Coord_R debut, Coord_R fin, MLV_Color col, MLV_Graph2D graph2D
);
/* Place un cercle plein sur le graphique */
void graph_placer_cercle_plein(
  Coord_R centre, double rayon, MLV_Color col, MLV_Graph2D graph
);
/* Place un cercle sur le graphique */
void graph_placer_cercle(
  Coord_R centre, double rayon, MLV_Color col, MLV_Graph2D graph
);
/* Place un point sur le graphique */
void graph_placer_point(
  Coord_R centre, int taille, Forme type, MLV_Color col, MLV_Graph2D graph
);

/*-----==========Gestion des gestionnaires de fichiers==========-----*/
/* Crée un gestionnaire de fichier */
MLV_FileManager init_gest_fichier(
  MLV_Position pos, char const *rep, void (*fct)(char *)
);
/* Libère l'espace occupé par le gestionnaire de fichier */
void liberer_gest_fichier(MLV_FileManager *gest_fichier);
/* Change l'icon du bouton du gestionnaire de fichier */
void ajouter_icon_gest_fichier(char *chemin, MLV_FileManager gest_fichier);

#endif
