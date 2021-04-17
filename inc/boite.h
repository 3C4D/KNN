#ifndef BOITE_H_
#define BOITE_H_

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include "geometrie.h"
#include "position.h"

typedef enum {VERTICAL, HORIZONTAL} BoxDirection;

struct MLV_Container_s {
  MLV_Position pos_externe;
  MLV_Horizontal_position hpos_interne;
  MLV_Vertical_position vpos_interne;
};
typedef struct MLV_Container_s *MLV_Container;

struct MLV_Box_s {
  BoxDirection dir;
  MLV_Position pos;
  int remplissage;
  MLV_Container *elements;
  int nb_elems;
};
typedef struct MLV_Box_s *MLV_Box;

/* Gestion des boîtes */
MLV_Box init_boite(BoxDirection dir, MLV_Position pos);
void liberer_boite(MLV_Box *boite);
void ajouter_conteneur(MLV_Container cont, int remplissage, MLV_Box boite);
void ajouter_remplissage(int remplissage, MLV_Box boite);
Coord cont_calc_taille(int remplissage, MLV_Box boite);
Coord cont_calc_decalage(MLV_Box boite);
int boite_long_remplie(MLV_Box boite);
void afficher_boite(MLV_Box boite);

/* Gestion des conteneurs */
MLV_Container init_conteneur(
  MLV_Horizontal_position hpos_interne,
  MLV_Vertical_position vpos_interne
);
MLV_Container init_conteneur_centre();
void liberer_conteneur(MLV_Container *cont);
void def_dimension_cont(MLV_Container cont, Coord dimension);
void def_decalage_cont(MLV_Container cont, Coord decalage);
MLV_Box placer_boite(Coord dimension, BoxDirection dir, MLV_Container cont);
Coord placement_contenu(Coord dimension, MLV_Container cont);
MLV_Position position_contenu(Coord dimension, MLV_Container cont);
void afficher_conteneur(MLV_Container cont);

#endif
