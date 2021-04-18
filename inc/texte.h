#ifndef TEXTE_H_
#define TEXTE_H_

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include "string_obj.h"
#include "position.h"

struct MLV_Text_Format_s{
  MLV_Text_justification justif;
  MLV_Horizontal_position h_pos;
  MLV_Vertical_position v_pos;
};
typedef struct MLV_Text_Format_s *MLV_Text_Format;

struct MLV_Text_s {
  String msg;
  MLV_Position placement;
  MLV_Text_Format format;
  MLV_Color couleur;
  int remplissage;
  bool visible;
  bool bordure;
};
typedef struct MLV_Text_s *MLV_Text;

#include "texte.h"
#include "erreur.h"

MLV_Text_Format init_format(
  MLV_Text_justification justif,
  MLV_Horizontal_position h_pos,
  MLV_Vertical_position v_pos
);
MLV_Text_Format init_format_defaut();
MLV_Text_Format init_format_centre();
void liberer_format(MLV_Text_Format *format);

MLV_Text init_texte(int remplissage, MLV_Position pos, MLV_Text_Format format);
void liberer_texte(MLV_Text *texte);
String contenu_texte(MLV_Text texte);
void texte_changer_couleur(MLV_Color col, MLV_Text texte);
void modif_texte(char *chaine, MLV_Text texte);
void modif_texte_int(int val, MLV_Text texte);
void texte_ajouter_str(char *str, MLV_Text texte);
void texte_ajouter_int(char *n, MLV_Text texte);
void texte_suppr_char(MLV_Text texte);
void texte_changer_visibilite(MLV_Text texte);
void texte_visible(MLV_Text texte);
void texte_invisible(MLV_Text texte);
bool texte_est_visible(MLV_Text texte);
int dist_texte_droite(MLV_Text texte);
int dist_texte_bas(MLV_Text texte);
void afficher_texte(MLV_Text texte);

#endif