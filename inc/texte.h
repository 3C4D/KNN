/*
Ce module implémente la gestion du texte sur l'interface. Surtout crée dans un 
soucis de compatibilité avec les autres module. MLV proposant déjà des options
identiques, ce module est principalement de l'emballage
*/

#ifndef TEXTE_H_
#define TEXTE_H_

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include "string_obj.h"
#include "position.h"

struct MLV_Text_Format_s{
  MLV_Text_justification justif; /* Justification du texte */
  MLV_Horizontal_position h_pos; /* Position horizontale */
  MLV_Vertical_position v_pos; /* Position verticale */
};
typedef struct MLV_Text_Format_s *MLV_Text_Format;

struct MLV_Text_s {
  String msg; /* Contenu textuel */
  MLV_Position placement; /* Position absolue */
  MLV_Text_Format format; /* Formattage du texte */
  MLV_Color couleur; /* Couleur du texte */
  int remplissage; /* rembourrage ou padding */
  bool visible; /* Visibilité du texte */
  bool bordure; /* Visibilité de la bordure */
};
typedef struct MLV_Text_s *MLV_Text;

#include "texte.h"
#include "erreur.h"

/*-----==========Gestion du formattage==========-----*/
/* Crée un formattage de texte */
MLV_Text_Format init_format(
  MLV_Text_justification justif,
  MLV_Horizontal_position h_pos,
  MLV_Vertical_position v_pos
);
/* Crée un formattage par défaut => Centré verticalement et collé à gauche */
MLV_Text_Format init_format_defaut();
/* Crée un fomattage centré => Centré verticalement et horizontalement */
MLV_Text_Format init_format_centre();
/* Libère l'espace occupé par le formattage */
void liberer_format(MLV_Text_Format *format);

/*-----==========Gestion du texte==========-----*/
/* Crée un texte */
MLV_Text init_texte(int remplissage, MLV_Position pos, MLV_Text_Format format);
/* Libère l'espace occupé par le texte */
void liberer_texte(MLV_Text *texte);
/* Retourne le contenu du texte */
String contenu_texte(MLV_Text texte);
/* Change la couleur du texte */
void texte_changer_couleur(MLV_Color col, MLV_Text texte);
/* Change le contenu du texte */
void modif_texte(char *chaine, MLV_Text texte);
/* Change le contenu du texte à partir de la représentation d'un entier */
void modif_texte_int(int val, MLV_Text texte);
/* Concatène str au contenu du texte */
void texte_ajouter_str(char *str, MLV_Text texte);
/* Concatène n au contenu du texte si celui-ci est un chiffre */
void texte_ajouter_int(char *n, MLV_Text texte);
/* Supprime un charactère du contenu du texte */
void texte_suppr_char(MLV_Text texte);
/* Change la visibilité du texte */
void texte_changer_visibilite(MLV_Text texte);
/* Rend le texte visible */
void texte_visible(MLV_Text texte);
/* Rend le texte invisible */
void texte_invisible(MLV_Text texte);
/* Retourne 1 si le texte est visible, sinon 0 */
bool texte_est_visible(MLV_Text texte);
/* Distance du texte du côté gauche en allant vers la droite */
int dist_texte_droite(MLV_Text texte);
/* Distance du texte du haut en allant vers le bas */
int dist_texte_bas(MLV_Text texte);
/* Affiche le texte sur l'interface */
void afficher_texte(MLV_Text texte);

#endif