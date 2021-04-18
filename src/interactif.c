#include <stdlib.h>
#include "interactif.h"
#include "erreur.h"

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

void liberer_clickable(MLV_Clickable *click){
  if (*click != NULL) {
    liberer_position(&(*click)->pos);
    free(*click);
  }

  *click = NULL;
}

void click_init_fct(FctClick fct, MLV_Clickable click){
  click->fct = fct;
}

void click_maj_proprio(void *proprio, MLV_Clickable click){
  click->proprio = proprio;
}

void *click_proprio(MLV_Clickable click){
  return (click->proprio);
}

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

int click_est_dedant(Info_Souris souris, MLV_Clickable click){
  if (click->etat == INACTIF) {
    return 0;
  } else {
    return (
      est_dans_zone(coord_souris(souris), click->pos) &&
      souris->etat_bouton == MLV_PRESSED
    );
  }
}

int click_est_dehors(Info_Souris souris, MLV_Clickable click){
  if (click->etat == INACTIF) {
    return 0;
  } else {
    return (
      !est_dans_zone(coord_souris(souris), click->pos) &&
      souris->etat_bouton == MLV_PRESSED
    );
  }
}

void click_changer_etat(MLV_Clickable click){
  if (click->etat == ACTIF) {
    desactiver_click(click);
  } else {
    activer_click(click);
  }
}

void desactiver_click(MLV_Clickable click){
  click->etat = INACTIF;
}

void activer_click(MLV_Clickable click){
  click->etat = ACTIF;
}

int est_dans_zone(Coord c, MLV_Position pos){
  return (
    pos->decalage.x <= c.x && (pos->decalage.x + pos->dimension.x) > c.x &&
    pos->decalage.y <= c.y && (pos->decalage.y + pos->dimension.y) > c.y
  );
}


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

void liberer_hoverable(MLV_Hoverable *hover){
  if (*hover != NULL) {
    liberer_position(&(*hover)->pos);
    free(*hover);
  }

  *hover = NULL;
}

void hover_init_fct_dedans(FctHover fct, MLV_Hoverable hover){
  hover->fct = fct;
}

void hover_maj_proprio(void *proprio, MLV_Hoverable hover){
  hover->proprio = proprio;
}

void *hover_proprio(MLV_Hoverable hover){
  return (hover->proprio);
}

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

int hover_est_active(Info_Souris souris, MLV_Hoverable hover){
  if (hover->etat == INACTIF) {
    return 0;
  } else {
    return (
      est_dans_zone(coord_souris(souris), hover->pos) &&
      souris->etat_bouton == MLV_PRESSED
    );
  }
}

int hover_est_dedant(Info_Souris souris, MLV_Hoverable hover){
  if (hover->etat == INACTIF) {
    return 0;
  } else {
    return (est_dans_zone(coord_souris(souris), hover->pos));
  }
}

int hover_est_dehors(Info_Souris souris, MLV_Hoverable hover){
  if (hover->etat == INACTIF) {
    return 0;
  } else {
    return (!est_dans_zone(coord_souris(souris), hover->pos));
  }
}

void hover_changer_etat(MLV_Hoverable hover){
  if (hover->etat == ACTIF) {
    hover->etat = INACTIF;
  } else {
    hover->etat = ACTIF;
  }
}


MLV_Keylogger init_keylogger(Etat etat){
  MLV_Keylogger keylog = malloc(sizeof(struct MLV_Keylogger_s));
  verif_alloc(keylog);
  keylog->fct = NULL;
  keylog->etat = etat;
  keylog->proprio = keylog;

  return keylog;
}

void liberer_keylogger(MLV_Keylogger *keylog){
  if (*keylog != NULL){
    free(*keylog);
  }
  
  *keylog = NULL;
}

void keylog_init_fct(FctKeylog fct, MLV_Keylogger keylog){
  keylog->fct = fct;
}

void keylog_maj_proprio(void *proprio, MLV_Keylogger keylog){
  keylog->proprio = proprio;
}

void *keylog_proprio(MLV_Keylogger keylog){
  return (keylog->proprio);
}

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

bool keylog_est_active(Info_Clavier clavier, MLV_Keylogger keylog){
  if (keylog->etat == INACTIF) {
    return false;
  } else {
    return (clavier->etat_touche == MLV_PRESSED);
  }
}

void keylog_changer_etat(MLV_Keylogger keylog){
  if (keylog->etat == ACTIF) {
    desactiver_keylog(keylog); 
  } else {
    activer_keylog(keylog); 
  }
}

void desactiver_keylog(MLV_Keylogger keylog){
  keylog->etat = INACTIF;
}

void activer_keylog(MLV_Keylogger keylog){
  keylog->etat = ACTIF;
}

