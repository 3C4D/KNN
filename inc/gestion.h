#ifndef GESTION_H_
#define GESTION_H_

#include "boite.h"
#include "interactif.h"
#include "canvas.h"
#include "texte.h"

struct Box_List_s {
  MLV_Box *liste;
  int nb_boites;
};
typedef struct Box_List_s *Box_List;

struct Click_List_s {
  MLV_Clickable *liste;
  int nb_clicks;
};
typedef struct Click_List_s *Click_List;

struct Text_List_s {
  MLV_Text *liste;
  int nb_textes;
};
typedef struct Text_List_s *Text_List;

struct Canvas_List_s{
  MLV_Canvas *liste;
  int nb_canvas;
};
typedef struct Canvas_List_s *Canvas_List;

struct Keylog_List_s{
  MLV_Keylogger *liste;
  int nb_keylog;
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

/* Fonctions sur l'agencement */
Box_List init_liste_boite();
void liberer_liste_boite(Box_List *liste);
void ajouter_boite(MLV_Box boite, Box_List liste);
void afficher_liste_boite(Box_List liste);

Canvas_List init_liste_canvas();
void ajouter_canvas(MLV_Canvas canvas, Canvas_List liste);
void afficher_liste_canvas(Canvas_List liste);

Text_List init_liste_texte();
void ajouter_texte(MLV_Text texte, Text_List liste);
void afficher_liste_texte(Text_List liste);

/* gestion des zone interactive */
Click_List init_liste_click();
void ajouter_click(MLV_Clickable click, Click_List liste);

/*Keylog*/
Keylog_List init_liste_keylog();
void ajouter_keylog(MLV_Keylogger keylog, Keylog_List liste);

/* Gestionnaire */
Manager init_gestionnaire();
void affichage_fenetre(Manager gest);
void affichage_debug(Manager gest);

#endif
