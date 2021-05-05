/*
Ce module introduit le gestionnaire d'éléments de l'interface.
Cet objet permet de centralisé ces éléments, dans notre cas:
  - Les boites
  - Les clickables
  - Les textes
  - Les canvas
  - Les keyloggers
*/

#ifndef GESTION_H_
#define GESTION_H_

#include "boite.h"
#include "interactif.h"
#include "canvas.h"
#include "texte.h"

struct Box_List_s {
  MLV_Box *liste; /* Liste des boites */
  int nb_boites; /* Nombre de boites */
};
typedef struct Box_List_s *Box_List;

struct Click_List_s {
  MLV_Clickable *liste; /* Liste des clickables */
  int nb_clicks; /* Nombre de clickables */
};
typedef struct Click_List_s *Click_List;

struct Text_List_s {
  MLV_Text *liste; /* Liste des textes */
  int nb_textes; /* Nombre de textes */
};
typedef struct Text_List_s *Text_List;

struct Canvas_List_s{
  MLV_Canvas *liste; /* Liste des canvas */
  int nb_canvas; /* Nombre de canvas */
};
typedef struct Canvas_List_s *Canvas_List;

struct Keylog_List_s{
  MLV_Keylogger *liste; /* Liste des keyloggers */
  int nb_keylog; /* Nombre de keyloggers */
};
typedef struct Keylog_List_s *Keylog_List;


struct Manager_s{
  Box_List liste_boite;
  Click_List liste_click;
  Text_List liste_texte;
  Canvas_List liste_canvas;
  Keylog_List liste_keylog;
};
typedef struct Manager_s *Manager;

/*-----==========Gestion des Listes de Boites==========-----*/
/* Crée une liste de Boites */
Box_List init_liste_boite();
/* Libère l'espace occupé par la liste de Boites */
void liberer_liste_boite(Box_List *liste);
/* Ajoute une boite à la liste de Boites */
void ajouter_boite(MLV_Box boite, Box_List liste);
/* Affiche la liste des Boites */
void afficher_liste_boite(Box_List liste);

/*-----==========Gestion des Listes de Canvas==========-----*/
/* Crée une liste de Canvas */
Canvas_List init_liste_canvas();
/* Libère l'espace occupé par la liste de Canvas */
void liberer_liste_canvas(Canvas_List *liste);
/* Ajooute un Canvas à la liste */
void ajouter_canvas(MLV_Canvas canvas, Canvas_List liste);
/* Affiche la liste de Canvas */
void afficher_liste_canvas(Canvas_List liste);

/*-----==========Gestion des Listes de Textes==========-----*/
/* Crée une liste de Textes */
Text_List init_liste_texte();
/* Libère l'espace occupé par la liste de Textes */
void liberer_liste_texte(Text_List *liste);
/* Ajoute un Texte à la liste */
void ajouter_texte(MLV_Text texte, Text_List liste);
/* Affiche la liste de Texte */
void afficher_liste_texte(Text_List liste);

/*-----==========Gestion des Listes de Clickables==========-----*/
/* Crée une liste de Clickables */
Click_List init_liste_click();
/* Libère l'espace occupé par la liste de Clickables */
void liberer_liste_click(Click_List *liste);
/* Ajoute un Clickable à la liste */
void ajouter_click(MLV_Clickable click, Click_List liste);

/*-----==========Gestion des Listes de Keyloggers==========-----*/
/* Crée une liste de Keyloggers */
Keylog_List init_liste_keylog();
/* Libère l'espace occupé par la liste de Keyloggers */
void liberer_liste_keylog(Keylog_List *liste);
/* Ajoute un Keylogger à la liste */
void ajouter_keylog(MLV_Keylogger keylog, Keylog_List liste);

/*-----==========Gestion du Gestionnaire==========-----*/
/* Crée un gestionnaire */
Manager init_gestionnaire();
/* Libère l'espace mémoire occupé par un gestionnaire */
void liberer_gestionnaire(Manager *gest);
/* Affiche les éléments de la fenếtre */
void affichage_fenetre(Manager gest);
/* Affiche les éléments de la fenêtre et les délimitaitons des boites */
void affichage_debug(Manager gest);

#endif
