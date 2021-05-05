#include <stdlib.h>
#include "interactif.h"
#include "erreur.h"

/*-----==========Gestion des Clickables==========-----*/
/* Crée un clickable */
MLV_Clickable init_clickable(MLV_Position pos, Etat etat, Espace esp){
  MLV_Clickable click = malloc(sizeof(struct MLV_Clickable_s));
  verif_alloc((void *)click);
  click->pos = pos;
  click->etat = etat;
  click->espace = esp;
  click->fct = NULL;
  click->proprio = click;

  return click;
}

/* Libère l'espace occupé par un Clickable */
void liberer_clickable(MLV_Clickable *click){
  if (*click != NULL) {
    liberer_position(&(*click)->pos);
    free(*click);
  }

  *click = NULL;
}

/* (Ré)initialise la fonction d'action du Clickable */
void click_init_fct(FctClick fct, MLV_Clickable click){
  click->fct = fct;
}

/* Change le propriétaire du Clickable */
void click_maj_proprio(void *proprio, MLV_Clickable click){
  click->proprio = proprio;
}

/* Renvoie le propriétaire d'un Clickable */
void *click_proprio(MLV_Clickable click){
  return (click->proprio);
}

/* Lance la fonction d'action d'un Clickable si les conditions sont correctes */
Id_Obj click_lancer_fct(MLV_Clickable click, Info_Souris souris){
  if (
    (click_est_dedant(souris, click) && click->espace == INTERNE) ||
    (click_est_dehors(souris, click) && click->espace == EXTERNE)
  ){
    if (click->fct != NULL) {
      return ((click->fct)(click, souris));
    }
  }

  return NON_DEFINI;
}

/* Détermine si un click est actif et à l'intérieur de la zone */
bool click_est_dedant(Info_Souris souris, MLV_Clickable click){
  if (click->etat == INACTIF) {
    return false;
  } else {
    return (
      est_dans_zone(coord_souris(souris), click->pos) &&
      souris->etat_bouton == MLV_PRESSED
    );
  }
}

/* Détermine si un click est actif et à l'extérieur de la zone */
bool click_est_dehors(Info_Souris souris, MLV_Clickable click){
  if (click->etat == INACTIF) {
    return false;
  } else {
    return (
      !est_dans_zone(coord_souris(souris), click->pos) &&
      souris->etat_bouton == MLV_PRESSED
    );
  }
}

/* Change l'état d'un Clickable */
void click_changer_etat(MLV_Clickable click){
  if (click->etat == ACTIF) {
    desactiver_click(click);
  } else {
    activer_click(click);
  }
}

/* Désactive un Clickable */
void desactiver_click(MLV_Clickable click){
  click->etat = INACTIF;
}

/* Active un Clickable */
void activer_click(MLV_Clickable click){
  click->etat = ACTIF;
}

/* Détermine si une coordonée est dans la zone */
bool est_dans_zone(Coord c, MLV_Position pos){
  return (
    pos->decalage.x <= c.x && (pos->decalage.x + pos->dimension.x) > c.x &&
    pos->decalage.y <= c.y && (pos->decalage.y + pos->dimension.y) > c.y
  );
}

/*-----==========Gestion des Hoverables==========-----*/
/* Crée un Hoverable */
MLV_Hoverable init_hoverable(MLV_Position pos, Etat etat, Espace esp){
  MLV_Hoverable hover = malloc(sizeof(struct MLV_Hoverable_s));
  verif_alloc((void *)hover);
  hover->pos = pos;
  hover->etat = etat;
  hover->espace = esp;
  hover->fct = NULL;
  hover->proprio = hover;

  return hover;
}

/* Libère l'espace occupé par un Hoverable */
void liberer_hoverable(MLV_Hoverable *hover){
  if (*hover != NULL) {
    liberer_position(&(*hover)->pos);
    free(*hover);
  }

  *hover = NULL;
}

/* (Ré)initialise la fonction d'action du Hoverable */
void hover_init_fct_dedans(FctHover fct, MLV_Hoverable hover){
  hover->fct = fct;
}

/* Change le propriétaire du Hoverable */
void hover_maj_proprio(void *proprio, MLV_Hoverable hover){
  hover->proprio = proprio;
}

/* Renvoie le propriétaire d'un Hoverable */
void *hover_proprio(MLV_Hoverable hover){
  return (hover->proprio);
}

/* Lance la fonction d'action d'un Hoverable si les conditions sont correctes */
Id_Obj hover_lancer_fct(MLV_Hoverable hover, Info_Souris souris){
  if (
    (hover_est_dedant(souris, hover) && hover->espace == INTERNE) ||
    (hover_est_dehors(souris, hover) && hover->espace == EXTERNE)
  ){
    if (hover->fct != NULL) {
      return ((hover->fct)(hover, souris));
    }
  }

  return NON_DEFINI;
}

/* Détermine si un Hoverable est actif */
bool hover_est_active(Info_Souris souris, MLV_Hoverable hover){
  if (hover->etat == INACTIF) {
    return false;
  } else {
    return (
      est_dans_zone(coord_souris(souris), hover->pos) &&
      souris->etat_bouton == MLV_PRESSED
    );
  }
}

/* Détermine si un survol est actif et à l'intérieur de la zone */
bool hover_est_dedant(Info_Souris souris, MLV_Hoverable hover){
  if (hover->etat == INACTIF) {
    return false;
  } else {
    return (est_dans_zone(coord_souris(souris), hover->pos));
  }
}

/* Détermine si un survol est actif et à l'extérieur de la zone */
bool hover_est_dehors(Info_Souris souris, MLV_Hoverable hover){
  if (hover->etat == INACTIF) {
    return false;
  } else {
    return (!est_dans_zone(coord_souris(souris), hover->pos));
  }
}

/* Change l'état d'un Hoverable */
void hover_changer_etat(MLV_Hoverable hover){
  if (hover->etat == ACTIF) {
    hover->etat = INACTIF;
  } else {
    hover->etat = ACTIF;
  }
}

/*-----==========Gestion des Keyloggers==========-----*/
/* Crée un Keylogger */
MLV_Keylogger init_keylogger(Etat etat){
  MLV_Keylogger keylog = malloc(sizeof(struct MLV_Keylogger_s));
  verif_alloc(keylog);
  keylog->fct = NULL;
  keylog->etat = etat;
  keylog->proprio = keylog;

  return keylog;
}

/* Libère l'espace occupé par un Keylogger */
void liberer_keylogger(MLV_Keylogger *keylog){
  if (*keylog != NULL){
    free(*keylog);
  }
  
  *keylog = NULL;
}

/* (Ré)initialise la fonction d'action du Keylogger */
void keylog_init_fct(FctKeylog fct, MLV_Keylogger keylog){
  keylog->fct = fct;
}

/* Change le propriétaire du Keylogger */
void keylog_maj_proprio(void *proprio, MLV_Keylogger keylog){
  keylog->proprio = proprio;
}

/* Renvoie le propriétaire d'un Keylogger */
void *keylog_proprio(MLV_Keylogger keylog){
  return (keylog->proprio);
}

/* Lance la fonction d'action d'un Keylogger si les conditions sont correctes */
Id_Obj keylog_lancer_fct(MLV_Keylogger keylog, Info_Clavier clavier){
  if (keylog_est_active(clavier, keylog)){
    if (keylog->fct != NULL){
      return ((keylog->fct)(keylog, clavier));
    } else {
      return NON_DEFINI;
    }
  } else {
    return NON_DEFINI;
  }
}

/* Détermine si un Keylogger est actif */
bool keylog_est_active(Info_Clavier clavier, MLV_Keylogger keylog){
  if (keylog->etat == INACTIF) {
    return false;
  } else {
    return (clavier->etat_touche == MLV_PRESSED);
  }
}

/* Change l'état d'un Keylogger */
void keylog_changer_etat(MLV_Keylogger keylog){
  if (keylog->etat == ACTIF) {
    desactiver_keylog(keylog); 
  } else {
    activer_keylog(keylog); 
  }
}

/* Désactive un Keylogger */
void desactiver_keylog(MLV_Keylogger keylog){
  keylog->etat = INACTIF;
}

/* Active un Keylogger */
void activer_keylog(MLV_Keylogger keylog){
  keylog->etat = ACTIF;
}

