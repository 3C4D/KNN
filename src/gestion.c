#include <stdlib.h>
#include "gestion.h"
#include "erreur.h"

/*-----==========Gestion des Listes de Boites==========-----*/
/* Crée une liste de Boites */
Box_List init_liste_boite(){
  Box_List liste_boite = malloc(sizeof(struct Box_List_s));
  verif_alloc((void *)liste_boite);
  liste_boite->liste = malloc(0);
  verif_alloc((void *)liste_boite->liste);
  liste_boite->nb_boites = 0;

  return liste_boite;
}

/* Libère l'espace occupé par la liste de Boites */
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

/* Ajoute une boite à la liste de Boites */
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

/* Affiche la liste des Boites */
void afficher_liste_boite(Box_List liste){
  int i;
  if (liste != NULL) {
    for (i = 0; i < liste->nb_boites; i++) {
      afficher_boite(liste->liste[i]);
    }
  }
}

/*-----==========Gestion des Listes de Canvas==========-----*/
/* Crée une liste de Canvas */
Canvas_List init_liste_canvas(){
  Canvas_List liste_canvas = malloc(sizeof(struct Canvas_List_s));
  verif_alloc((void *)liste_canvas);
  liste_canvas->liste = malloc(0);
  verif_alloc((void *)liste_canvas->liste);
  liste_canvas->nb_canvas = 0;

  return liste_canvas;
}

/* Libère l'espace occupé par la liste de Canvas */
void liberer_liste_canvas(Canvas_List *liste){
  int i;
  if (*liste != NULL) {
    for (i = 0; i < (*liste)->nb_canvas; i++) {
      liberer_canvas(&(*liste)->liste[i]);
    }

    free(*liste);
  }

  *liste = NULL;
}

/* Ajooute un Canvas à la liste */
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

/* Affiche la liste de Canvas */
void afficher_liste_canvas(Canvas_List liste){
  int i;
  for (i = 0; i < liste->nb_canvas; i++) {
    if (est_visible(liste->liste[i])) {
      afficher_canvas(liste->liste[i]);
    }
  }
}

/*-----==========Gestion des Listes de Textes==========-----*/
/* Crée une liste de Textes */
Text_List init_liste_texte(){
  Text_List liste_texte = malloc(sizeof(struct Text_List_s));
  verif_alloc((void *)liste_texte);
  liste_texte->liste = malloc(0);
  verif_alloc((void *)liste_texte->liste);
  liste_texte->nb_textes = 0;

  return liste_texte;
}

/* Libère l'espace occupé par la liste de Textes */
void liberer_liste_texte(Text_List *liste){
  int i;
  if (*liste != NULL) {
    for (i = 0; i < (*liste)->nb_textes; i++) {
      liberer_texte(&(*liste)->liste[i]);
    }

    free(*liste);
  }

  *liste = NULL;
}

/* Ajoute un Texte à la liste */
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

/* Affiche la liste de Texte */
void afficher_liste_texte(Text_List liste){
  int i;
  for (i = 0; i < liste->nb_textes; i++) {
    if (texte_est_visible(liste->liste[i])) {
      afficher_texte(liste->liste[i]);
    }
  }
}

/*-----==========Gestion des Listes de Clickables==========-----*/
/* Crée une liste de Clickables */
Click_List init_liste_click(){
  Click_List liste_click = malloc(sizeof(struct Click_List_s));
  verif_alloc((void *)liste_click);
  liste_click->liste = malloc(0);
  verif_alloc(liste_click->liste);
  liste_click->nb_clicks = 0;

  return liste_click;
}

/* Libère l'espace occupé par la liste de Clickables */
void liberer_liste_click(Click_List *liste){
  int i;
  if (*liste != NULL) {
    for (i = 0; i < (*liste)->nb_clicks; i++) {
      liberer_clickable(&(*liste)->liste[i]);
    }

    free(*liste);
  }

  *liste = NULL;
}

/* Ajoute un Clickable à la liste */
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

/*-----==========Gestion des Listes de Keyloggers==========-----*/
/* Crée une liste de Keyloggers */
Keylog_List init_liste_keylog(){
  Keylog_List liste_keylog = malloc(sizeof(struct Keylog_List_s));
  verif_alloc((void *)liste_keylog);
  liste_keylog->liste = malloc(0);
  verif_alloc(liste_keylog->liste);
  liste_keylog->nb_keylog = 0;

  return liste_keylog;
}

/* Libère l'espace occupé par la liste de Keyloggers */
void liberer_liste_keylog(Keylog_List *liste){
  int i;
  if (*liste != NULL) {
    for (i = 0; i < (*liste)->nb_keylog; i++) {
      liberer_keylogger(&(*liste)->liste[i]);
    }

    free(*liste);
  }

  *liste = NULL;
}

/* Ajoute un Keylogger à la liste */
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

/*-----==========Gestion du Gestionnaire==========-----*/
/* Crée un gestionnaire */
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

/* Libère l'espace mémoire occupé par un gestionnaire */
void liberer_gestionnaire(Manager *gest){
  if (*gest != NULL){
    liberer_liste_boite(&(*gest)->liste_boite);
    liberer_liste_canvas(&(*gest)->liste_canvas);
    liberer_liste_texte(&(*gest)->liste_texte);
    liberer_liste_click(&(*gest)->liste_click);
    liberer_liste_keylog(&(*gest)->liste_keylog);
    free(*gest);
  }
  
  *gest = NULL;
}

/* Affiche les éléments de la fenếtre */
void affichage_fenetre(Manager gest){
  afficher_liste_canvas(gest->liste_canvas);
  afficher_liste_texte(gest->liste_texte);
}

/* Affiche les éléments de la fenêtre et les délimitaitons des boites */
void affichage_debug(Manager gest){
  affichage_fenetre(gest);
  afficher_liste_boite(gest->liste_boite);
}
