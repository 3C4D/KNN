#ifndef INTERACTIF_H_
#define INTERACTIF_H_

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include "id_objet.h"
#include "geometrie.h"
#include "position.h"
#include "peripheriques.h"

typedef enum {ACTIF, INACTIF} Etat;
typedef enum {INTERNE, EXTERNE} Espace;

typedef struct MLV_Clickable_s *MLV_Clickable;
typedef Id_Obj (*FctClick) (MLV_Clickable,Info_Souris);
struct MLV_Clickable_s {
  MLV_Position pos;
  Etat etat;
  Espace espace;
  FctClick fct;
  void *proprio;
};

typedef struct MLV_Hoverable_s *MLV_Hoverable;
typedef Id_Obj (*FctHover) (MLV_Hoverable,Info_Souris);
struct MLV_Hoverable_s {
  MLV_Position pos;
  Etat etat;
  Espace espace;
  FctHover fct;
  void *proprio;
};

typedef struct MLV_Keylogger_s *MLV_Keylogger;
typedef Id_Obj (*FctKeylog) (MLV_Keylogger,Info_Clavier);
struct MLV_Keylogger_s {
  Etat etat;
  FctKeylog fct;
  void *proprio;
};

MLV_Clickable init_clickable(MLV_Position pos, Etat etat, Espace esp);
void liberer_clickable(MLV_Clickable *click);
void click_init_fct(FctClick fct, MLV_Clickable click);
void click_maj_proprio(void *proprio, MLV_Clickable click);
void *click_proprio(MLV_Clickable click);
void click_changer_etat(MLV_Clickable click);
Id_Obj click_lancer_fct(MLV_Clickable click, Info_Souris souris);
int click_est_dedant(Info_Souris souris, MLV_Clickable click);
int click_est_dehors(Info_Souris souris, MLV_Clickable click);
int est_dans_zone(Coord c, MLV_Position pos);

MLV_Hoverable init_hoverable(MLV_Position pos, Etat etat, Espace esp);
void liberer_hoverable(MLV_Hoverable *hover);
void hover_init_fct(FctHover fct, MLV_Hoverable hover);
void hover_maj_proprio(void *proprio, MLV_Hoverable hover);
void *hover_proprio(MLV_Hoverable hover);
Id_Obj hover_lancer_fct(MLV_Hoverable hover, Info_Souris souris);
int hover_est_active(Info_Souris souris, MLV_Hoverable hover);
int hover_est_dedant(Info_Souris souris, MLV_Hoverable hover);
int hover_est_dehors(Info_Souris souris, MLV_Hoverable hover);
void hover_changer_etat(MLV_Hoverable hover);

MLV_Keylogger init_keylogger(Etat etat);
void liberer_keylogger(MLV_Keylogger *keylog);
void keylog_init_fct(FctKeylog fct, MLV_Keylogger keylog);
void keylog_maj_proprio(void *proprio, MLV_Keylogger keylog);
void *keylog_proprio(MLV_Keylogger keylog);
Id_Obj keylog_lancer_fct(MLV_Keylogger keylog, Info_Clavier clavier);
bool keylog_est_active(Info_Clavier clavier, MLV_Keylogger keylog);
void keylog_changer_etat(MLV_Keylogger keylog);

#endif
