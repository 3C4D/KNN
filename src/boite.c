#include <stdlib.h>
#include "boite.h"
#include "erreur.h"

/*-----==========Fonctions privées==========-----*/
/* Calcule les dimentions d'un conteneur dans une boite */
Coord cont_calc_taille(int remplissage, MLV_Box boite);
/* Calcule le décalage par rapport à l'origine d'un conteneur dans une boite */
Coord cont_calc_decalage(MLV_Box boite);
/* Calcule la taille occupée dans une boite */
int boite_long_remplie(MLV_Box boite);
/* Change les dimensions d'un conteneur */
void def_dimension_cont(MLV_Container cont, Coord dimension);
/* Change le décalage par rapport à l'origine d'un conteneur */
void def_decalage_cont(MLV_Container cont, Coord decalage);

/*-----==========Gestion des boîtes==========-----*/
/* Crée une boite placée en [pos] et de sens [dir] */
MLV_Box init_boite(BoxDirection dir, MLV_Position pos){
  MLV_Box boite_out = malloc(sizeof(struct MLV_Box_s));
  verif_alloc(boite_out);
  boite_out->dir = dir;
  boite_out->pos = pos;
  boite_out->remplissage = 0;
  boite_out->elements = malloc(0);
  verif_alloc(boite_out->elements);
  boite_out->nb_elems = 0;

  return boite_out;
}

/* Libère l'espace occupé par [boite] */
void liberer_boite(MLV_Box *boite) {
  int i;
  if (*boite != NULL) {
    liberer_position(&(*boite)->pos);
    for (i = 0; i < (*boite)->nb_elems; i++) {
      liberer_conteneur(&((*boite)->elements[i]));
    }
    free(*boite);
  }

  *boite = NULL;
}

/* Ajoute le conteneur [cont] dans [boite] 
qui prend un espace de [remplissage] */
void ajouter_conteneur(MLV_Container cont, int remplissage, MLV_Box boite){
  Coord tmp_taille = cont_calc_taille(remplissage, boite);
  Coord tmp_decalage = cont_calc_decalage(boite);
  if (cont == NULL || boite == NULL) {
    return;
  }

  def_dimension_cont(cont, tmp_taille);
  def_decalage_cont(cont, tmp_decalage);
  boite->elements = realloc(
    boite->elements,
    (boite->nb_elems + 1) * sizeof(MLV_Container)
  );
  verif_alloc(boite->elements);
  boite->elements[boite->nb_elems] = cont;
  boite->nb_elems++;
}

/* Ajoute du remplissge pour espacer les conteneurs */
void ajouter_remplissage(int remplissage, MLV_Box boite){
  if (boite == NULL) {
    return;
  }

  boite->remplissage += remplissage;
}

Coord cont_calc_taille(int remplissage, MLV_Box boite){
  Coord tmp_coord;

  /* Un conteneur placé dans une boite prend toute la dimension orthogonale
  au sens de la boite, d'où le code suivant */
  if (boite->dir == VERTICAL) {
    tmp_coord = init_coord(boite->pos->dimension.x, remplissage);
  } else {
    tmp_coord = init_coord(remplissage, boite->pos->dimension.y);
  }

  return tmp_coord;
}

Coord cont_calc_decalage(MLV_Box boite){
  Coord tmp_coord;

  /* Bien que non-recommandé il est possible de remplir une boite au dela de
  sa dimension sur l'axe parallèle au sens */
  if (boite->dir == VERTICAL) {
    tmp_coord = init_coord(
      boite->pos->decalage.x,
      boite->pos->decalage.y + boite_long_remplie(boite)
    );
  } else {
    tmp_coord = init_coord(
      boite->pos->decalage.x + boite_long_remplie(boite),
      boite->pos->decalage.y
    );
  }

  return tmp_coord;
}

int boite_long_remplie(MLV_Box boite){
  int i, long_remplie = boite->remplissage;
  for (i = 0; i < boite->nb_elems; i++) {
    if (boite->dir == VERTICAL) {
      long_remplie += boite->elements[i]->pos_externe->dimension.y;
    } else {
      long_remplie += boite->elements[i]->pos_externe->dimension.x;
    }
  }

  return long_remplie;
}

/* Affiche la boite (rectangle bleu) sur l'interface */
void afficher_boite(MLV_Box boite) {
  int i;
  if (boite != NULL) {
    afficher_position(boite->pos, MLV_COLOR_BLUE);
    for (i = 0; i < boite->nb_elems; i++) {
      afficher_conteneur(boite->elements[i]);
    }
  }
}


/*-----==========Gestion des conteneurs==========-----*/
/* Créer un conteneur */
MLV_Container init_conteneur(
  MLV_Horizontal_position hpos_interne,
  MLV_Vertical_position vpos_interne
){
  MLV_Container conteneur_out = malloc(sizeof(struct MLV_Container_s));
  Coord tmp_coord = init_coord(0, 0);
  verif_alloc((void *)conteneur_out);
  conteneur_out->hpos_interne = hpos_interne;
  conteneur_out->vpos_interne = vpos_interne;
  conteneur_out->pos_externe = init_positon(tmp_coord, tmp_coord);

  return conteneur_out;
}

/* Créer un conteneur avec les propriétés de placement centrées */
MLV_Container init_conteneur_centre(){
  return (init_conteneur(MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER));
}

/* Libère l'espace occupé par [cont] */
void liberer_conteneur(MLV_Container *cont){
  if (*cont != NULL) {
    liberer_position(&(*cont)->pos_externe);
    free(*cont);
  }

  *cont = NULL;
}

void def_dimension_cont(MLV_Container cont, Coord dimension){
  if (cont != NULL) {
    cont->pos_externe->dimension = dimension;
  }
}

void def_decalage_cont(MLV_Container cont, Coord decalage){
  if (cont != NULL) {
    cont->pos_externe->decalage = decalage;
  }
}

/* Trouve le placement d'un objet dans un conteneur */
Coord placement_contenu(Coord dimension, MLV_Container cont){
  Coord coord;
  int x, y;

  /* Soit le placement vertical est en haut, en bas ou au milieu */
  if (cont->vpos_interne == MLV_VERTICAL_TOP) {
    y = cont->pos_externe->decalage.y;
  } else if (cont->vpos_interne == MLV_VERTICAL_BOTTOM) {
    y = (
      cont->pos_externe->decalage.y +
      (cont->pos_externe->dimension.y - dimension.y)
    );
  } else {
    y = (
      cont->pos_externe->decalage.y +
      (cont->pos_externe->dimension.y - dimension.y) / 2
    );
  }

  /* Soit le placement horizontal est à gauche, à dorite ou au centre */
  if (cont->hpos_interne == MLV_HORIZONTAL_LEFT) {
    x = cont->pos_externe->decalage.x;
  } else if (cont->hpos_interne == MLV_HORIZONTAL_RIGHT){
    x = (
      cont->pos_externe->decalage.x +
      (cont->pos_externe->dimension.x - dimension.x)
    );
  } else {
    x = (
      cont->pos_externe->decalage.x +
      (cont->pos_externe->dimension.x - dimension.x) / 2
    );
  }

  coord = init_coord(x, y);

  return coord;
}

/* Trouve la position d'un objet par rapport à un conteneur */
MLV_Position position_contenu(Coord dimension, MLV_Container cont){
  MLV_Position pos;
  /* ATTENTION: Contrairement à la permissivité des boite, un conteneur 
  n'accepte pas un contenu plus grand que lui */
  if (
    dimension.x > cont->pos_externe->dimension.x ||
    dimension.y > cont->pos_externe->dimension.y
  ) {
    return NULL;
  }

  pos = init_positon(placement_contenu(dimension, cont), dimension);

  return pos;
}

/* Place une boite dans un conteneur */
MLV_Box placer_boite(Coord dimension, BoxDirection dir, MLV_Container cont){
  MLV_Box boite;
  MLV_Position pos;
  if (
    dimension.x > cont->pos_externe->dimension.x ||
    dimension.y > cont->pos_externe->dimension.y
  ) {
    return NULL;
  }

  pos = position_contenu(dimension, cont);
  boite = init_boite(dir, pos);

  return boite;
}

/* Affiche le conteneur (rectangle rouge) sur l'interface */
void afficher_conteneur(MLV_Container cont){
  if (cont != NULL) {
    afficher_position(cont->pos_externe, MLV_COLOR_RED);
  }
}
