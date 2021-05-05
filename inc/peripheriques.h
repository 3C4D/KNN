/*
Ce module permet la gestion des périphériques utilisateurs. Plus précisément 
le clavier, la souris et même si jamais utilisé le boite d'entrée MLV.
Ainsi cela centralise leur utilisation.
*/

#ifndef PERIPH_H_
#define PERIPH_H_

#include <MLV/MLV_all.h>
#include "geometrie.h"

typedef struct Info_Periphs_s *Info_Periphs;
typedef struct Info_Souris_s *Info_Souris;
typedef struct Info_Clavier_s *Info_Clavier;
typedef struct Info_TextIO_s *Info_TextIO;

struct Info_Souris_s {
  int x; /* Position sur l'axe x de la souris */
  int y; /* Position sur l'axe y de la souris */
  MLV_Mouse_button bouton; /* Bouton de la souris utilisé */
  MLV_Button_state etat_bouton; /* État du bouton */
  Info_Periphs parent; /* Parent de l'info souris */
};

struct Info_Clavier_s {
  MLV_Keyboard_button touche; /* Touche appuyée */
  MLV_Keyboard_modifier mode; /* Mode de la touche */
  int lettre_unicode; /* Lettre unicode produite */
  MLV_Button_state etat_touche; /* État de la touche */
  Info_Periphs parent; /* Parent de l'info clavier */
};

struct Info_TextIO_s {
  char *texte_saisi; /* Texte saisi */
  MLV_Input_box *boite_saisie; /* Boite utilisée */
  Info_Periphs parent; /* Parent de l'info texte entré */
};

struct Info_Periphs_s {
  Info_Souris souris; /* Souris */
  Info_Clavier clavier; /* Clavier */
  Info_TextIO texte; /* Boite entrée textuelle */
};

/*-----==========Gestion des périphériques==========-----*/
/* Crée un inforamteur périph souris */
Info_Souris init_info_souris(Info_Periphs periphs);
/* Libère l'espace occupé par l'inforamteur périph souris */
void liberer_info_souris(Info_Souris *souris);
/* Crée un inforamteur périph clavier */
Info_Clavier init_info_clavier(Info_Periphs periphs);
/* Libère l'espace occupé par l'inforamteur périph clavier */
void liberer_info_clavier(Info_Clavier *clavier);
/* Crée un inforamteur boite de saisie */
Info_TextIO init_info_texte(Info_Periphs periphs);
/* Libère l'espace occupé par l'inforamteur périph boite de saisie */
void liberer_info_texte(Info_TextIO *texte);
/* Crée un informateur périph */
Info_Periphs init_info_periph();
/* Libère l'espace occupé par l'inforamteur périph */
void liberer_info_periph(Info_Periphs *periphs);
/* Récupère les information de l'évènement suivant dans la queue */
MLV_Event maj_evenement(Info_Periphs periphs);
/* Donne les coordonnées de la souris */
Coord coord_souris(Info_Souris souris);
/* Vide le texte contenu dans les boites d'entrée */
void nettoyer_texte_periphs(Info_Periphs periphs);

#endif
