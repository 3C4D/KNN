#include <stdlib.h>
#include "gestion.h"
#include "erreur.h"

/* Fonctions sur l'agencement */
Box_List init_liste_boite(){
  Box_List liste_boite = malloc(sizeof(struct Box_List_s));
  verif_alloc((void *)liste_boite);
  liste_boite->liste = malloc(0);
  verif_alloc((void *)liste_boite->liste);
  liste_boite->nb_boites = 0;

  return liste_boite;
}

void liberer_liste_boite(Box_List *liste){
  int i;
  if (*liste != NULL) {
    for (i = 0; i < (*liste)->nb_boites; i++) {
      liberer_boite(&(*liste)->liste[i]);
    }

    free(*liste);
  }

  *liste = NULL;
}

void ajouter_boite(MLV_Box boite, Box_List liste){
  if (liste == NULL || boite == NULL) {
    return;
  }

  liste->liste = realloc(
    liste->liste,
    (liste->nb_boites + 1) * sizeof(MLV_Box)
  );
  verif_alloc((void *)liste->liste);
  liste->liste[liste->nb_boites] = boite;
  liste->nb_boites++;
}

void afficher_liste_boite(Box_List liste){
  int i;
  if (liste != NULL) {
    for (i = 0; i < liste->nb_boites; i++) {
      afficher_boite(liste->liste[i]);
    }
  }
}

/* gestion des canvas */
Canvas_List init_liste_canvas(){
  Canvas_List liste_canvas = malloc(sizeof(struct Canvas_List_s));
  verif_alloc((void *)liste_canvas);
  liste_canvas->liste = malloc(0);
  verif_alloc((void *)liste_canvas->liste);
  liste_canvas->nb_canvas = 0;

  return liste_canvas;
}

void ajouter_canvas(MLV_Canvas canvas, Canvas_List liste) {
  if (canvas == NULL || liste == NULL) {
    return;
  }

  liste->liste = realloc(
    liste->liste,
    (liste->nb_canvas + 1) * (sizeof(MLV_Canvas))
  );
  verif_alloc((void *)liste->liste);
  liste->liste[liste->nb_canvas] = canvas;
  liste->nb_canvas++;
}

void afficher_liste_canvas(Canvas_List liste){
  int i;
  for (i = 0; i < liste->nb_canvas; i++) {
    if (est_visible(liste->liste[i])) {
      afficher_canvas(liste->liste[i]);
    }
  }
}

/* zone texte */
Text_List init_liste_texte(){
  Text_List liste_texte = malloc(sizeof(struct Text_List_s));
  verif_alloc((void *)liste_texte);
  liste_texte->liste = malloc(0);
  verif_alloc((void *)liste_texte->liste);
  liste_texte->nb_textes = 0;

  return liste_texte;
}

void ajouter_texte(MLV_Text texte, Text_List liste){
  if (texte == NULL || liste == NULL) {
    return;
  }

  liste->liste = realloc(
    liste->liste,
    (liste->nb_textes + 1) * (sizeof(MLV_Text))
  );
  verif_alloc((void *)liste->liste);
  liste->liste[liste->nb_textes] = texte;
  liste->nb_textes++;
}

void afficher_liste_texte(Text_List liste){
  int i;
  for (i = 0; i < liste->nb_textes; i++) {
    if (texte_est_visible(liste->liste[i])) {
      afficher_texte(liste->liste[i]);
    }
  }
}

/* gestion des zone interactive */
Click_List init_liste_click(){
  Click_List liste_click = malloc(sizeof(struct Click_List_s));
  verif_alloc((void *)liste_click);
  liste_click->liste = malloc(0);
  verif_alloc(liste_click->liste);
  liste_click->nb_clicks = 0;

  return liste_click;
}

void ajouter_click(MLV_Clickable click, Click_List liste){
  if (click == NULL || liste == NULL) {
    return;
  }

  liste->liste = realloc(
    liste->liste,
    (liste->nb_clicks + 1) * (sizeof(MLV_Clickable))
  );
  verif_alloc((void *)liste->liste);
  liste->liste[liste->nb_clicks] = click;
  liste->nb_clicks++;
}

/* Keylog */
Keylog_List init_liste_keylog(){
  Keylog_List liste_keylog = malloc(sizeof(struct Keylog_List_s));
  verif_alloc((void *)liste_keylog);
  liste_keylog->liste = malloc(0);
  verif_alloc(liste_keylog->liste);
  liste_keylog->nb_keylog = 0;

  return liste_keylog;
}

void ajouter_keylog(MLV_Keylogger keylog, Keylog_List liste){
  if (keylog == NULL || liste == NULL) {
    return;
  }

  liste->liste = realloc(
    liste->liste,
    (liste->nb_keylog + 1) * (sizeof(MLV_Keylogger))
  );
  verif_alloc((void *)liste->liste);
  liste->liste[liste->nb_keylog] = keylog;
  liste->nb_keylog++;
}

/* Gestionnaire */
Manager init_gestionnaire(){
  Manager gestionnaire = malloc(sizeof(struct Manager_s));
  verif_alloc((void *)gestionnaire);
  gestionnaire->liste_boite = init_liste_boite();
  gestionnaire->liste_click = init_liste_click();
  gestionnaire->liste_texte = init_liste_texte();
  gestionnaire->liste_canvas = init_liste_canvas();
  gestionnaire->liste_keylog = init_liste_keylog();

  return gestionnaire;
}

void affichage_fenetre(Manager gest){
  afficher_liste_canvas(gest->liste_canvas);
  afficher_liste_texte(gest->liste_texte);
}

void affichage_debug(Manager gest){
  affichage_fenetre(gest);
  afficher_liste_boite(gest->liste_boite);
}
