#ifndef PERIPH_H_
#define PERIPH_H_

#include <MLV/MLV_all.h>
#include "geometrie.h"

typedef struct Info_Periphs_s *Info_Periphs;
typedef struct Info_Souris_s *Info_Souris;
typedef struct Info_Clavier_s *Info_Clavier;
typedef struct Info_TextIO_s *Info_TextIO;

struct Info_Souris_s {
  int x;
  int y;
  MLV_Mouse_button bouton;
  MLV_Button_state etat_bouton;
  Info_Periphs parent;
};

struct Info_Clavier_s {
  MLV_Keyboard_button touche;
  MLV_Keyboard_modifier mode;
  int lettre_unicode;
  MLV_Button_state etat_touche;
  Info_Periphs parent;
};

struct Info_TextIO_s {
  char *texte_saisi;
  MLV_Input_box *boite_saisie;
  Info_Periphs parent;
};

struct Info_Periphs_s {
  Info_Souris souris;
  Info_Clavier clavier;
  Info_TextIO texte; 
};


Info_Souris init_info_souris(Info_Periphs periphs);
Info_Clavier init_info_clavier(Info_Periphs periphs);
Info_TextIO init_info_texte(Info_Periphs periphs);
Info_Periphs init_info_periph();
MLV_Event maj_evenement(Info_Periphs periphs);
Coord coord_souris(Info_Souris souris);
void nettoyer_texte_periphs(Info_Periphs periphs);

#endif
