#include <stdlib.h>
#include "peripheriques.h"
#include "erreur.h"

Info_Souris init_info_souris(Info_Periphs periphs){
  Info_Souris souris = malloc(sizeof(struct Info_Souris_s));
  verif_alloc((void *)souris);
  souris->parent = periphs;

  return souris;
}

Info_Clavier init_info_clavier(Info_Periphs periphs){
  Info_Clavier clavier = malloc(sizeof(struct Info_Clavier_s));
  verif_alloc((void *)clavier);
  clavier->parent = periphs;

  return clavier;
}

Info_TextIO init_info_texte(Info_Periphs periphs){
  Info_TextIO texte = malloc(sizeof(struct Info_TextIO_s));
  verif_alloc((void *)texte);
  texte->parent = periphs;

  return texte;
}

Info_Periphs init_info_periph(){
  Info_Periphs periphs = malloc(sizeof(struct Info_Periphs_s));
  verif_alloc((void *)periphs);

  periphs->souris = init_info_souris(periphs);
  periphs->clavier = init_info_clavier(periphs);
  periphs->texte = init_info_texte(periphs);

  return periphs;
}

MLV_Event maj_evenement(Info_Periphs periphs){
  MLV_Event evenement = MLV_get_event(
    &periphs->clavier->touche, &periphs->clavier->mode,
    &periphs->clavier->lettre_unicode,
    &periphs->texte->texte_saisi, &periphs->texte->boite_saisie,
    &periphs->souris->x, &periphs->souris->y,
    &periphs->souris->bouton, &periphs->souris->etat_bouton
  );
  periphs->clavier->etat_touche = periphs->souris->etat_bouton;

  return evenement;
}

Coord coord_souris(Info_Souris souris){
  return (init_coord(souris->x, souris->y));
}

void nettoyer_texte_periphs(Info_Periphs periphs){
  if (periphs->texte->texte_saisi)
  {
    free(periphs->texte->texte_saisi);
  }
}