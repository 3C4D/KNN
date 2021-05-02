/*
Le principe des boites est d'être un ensemble de conteneur imbriqués les 
uns dans les autres. Cela permet de placer des objet sur une interface de
manière relative et non absolu.
NB: Ici, les contenuers ne peuvent contenir qu'un seul objet. Pour placer 
un conteneur dans un autre il faut passer par l'intermediaire d'une boite 
dans un conteneur. 
Le concept de contenir ici est vu au sens large, une boite contient bien une
liste de conteneur mais un conteneur lui n'indique que une position pour se 
placer relativement à lui.
Ce concept est d'ailleurs reprit de ce que des librairies comme Qt5 peuvent 
proposer (e.g. https://doc.qt.io/qt-5/qboxlayout.html)
*/

#ifndef BOITE_H_
#define BOITE_H_

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include "geometrie.h"
#include "position.h"

/* Définie le sens dans lequel les conteneurs seront placés */
typedef enum {VERTICAL, HORIZONTAL} BoxDirection;

struct MLV_Container_s {
  MLV_Position pos_externe; /* Position absolue */
  MLV_Horizontal_position hpos_interne; /* Position horizontale du contenu */
  MLV_Vertical_position vpos_interne; /* Position verticale du contenu */
};
typedef struct MLV_Container_s *MLV_Container;

struct MLV_Box_s {
  BoxDirection dir; /* Sens de placement des conteneurs */
  MLV_Position pos; /* Possition absolue */
  int remplissage; /* Quantité de la boite remplie */
  MLV_Container *elements; /* Liste des conteneurs */
  int nb_elems; /* Nombre de conteneurs */
};
typedef struct MLV_Box_s *MLV_Box;

/*-----==========Gestion des boîtes==========-----*/
/* Crée une boite placée en [pos] et de sens [dir] */
MLV_Box init_boite(BoxDirection dir, MLV_Position pos);
/* Libère l'espace occupé par [boite] */
void liberer_boite(MLV_Box *boite);
/* Ajoute le conteneur [cont] dans [boite] 
qui prend un espace de [remplissage] */
void ajouter_conteneur(MLV_Container cont, int remplissage, MLV_Box boite);
/* Ajoute du remplissge pour espacer les conteneurs */
void ajouter_remplissage(int remplissage, MLV_Box boite);
/* Affiche la boite (rectangle bleu) sur l'interface */
void afficher_boite(MLV_Box boite);

/*-----==========Gestion des conteneurs==========-----*/
/* Créer un conteneur */
MLV_Container init_conteneur(
  MLV_Horizontal_position hpos_interne,
  MLV_Vertical_position vpos_interne
);
/* Créer un conteneur avec les propriétés de placement centrées */
MLV_Container init_conteneur_centre();
/* Libère l'espace occupé par [cont] */
void liberer_conteneur(MLV_Container *cont);
/* Place une boite dans un conteneur */
MLV_Box placer_boite(Coord dimension, BoxDirection dir, MLV_Container cont);
/* Trouve le placement d'un objet dans un conteneur */
Coord placement_contenu(Coord dimension, MLV_Container cont);
/* Trouve la position d'un objet par rapport à un conteneur */
MLV_Position position_contenu(Coord dimension, MLV_Container cont);
/* Affiche le conteneur (rectangle rouge) sur l'interface */
void afficher_conteneur(MLV_Container cont);

#endif
