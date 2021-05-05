/*
Ce module implémente les objets avec lesquels les interactions utilisateur sont
faites. Ici les différentes interactions prises en compte sont:
  - Le click avec un MLV_Clickable
  - Le survol avec un MLV_Hoverable
  - Le frappe d'une touche clavier avec un MLV_Keylogger
NB: Hoverable n'est jamais utilisé mais pourrait l'être à l'avenir.
*/

#ifndef INTERACTIF_H_
#define INTERACTIF_H_

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include "id_objet.h"
#include "geometrie.h"
#include "position.h"
#include "peripheriques.h"

typedef enum {ACTIF, INACTIF} Etat; /* Défini l'état d'un interactif */
/* Défini le champs d'action des interactifs liés à la souris */
typedef enum {INTERNE, EXTERNE} Espace; 

typedef struct MLV_Clickable_s *MLV_Clickable;
typedef Id_Obj (*FctClick) (MLV_Clickable,Info_Souris);
struct MLV_Clickable_s {
  MLV_Position pos; /* Position du champs d'action */
  Etat etat; /* Etat du Clickable */
  Espace espace; /* Action réalisée lorsque le curseur est en dehors ou non */
  FctClick fct; /* Action à realiser */
  void *proprio; /* Propriétaire du Clickable */
};

typedef struct MLV_Hoverable_s *MLV_Hoverable;
typedef Id_Obj (*FctHover) (MLV_Hoverable,Info_Souris);
struct MLV_Hoverable_s {
  MLV_Position pos; /* Position du champs d'action */
  Etat etat; /* Etat du Hoverable */
  Espace espace; /* Action réalisée lorsque le curseur est en dehors ou non */
  FctHover fct; /* Action à realiser */
  void *proprio; /* Propriétaire du Hoverable */
};

typedef struct MLV_Keylogger_s *MLV_Keylogger;
typedef Id_Obj (*FctKeylog) (MLV_Keylogger,Info_Clavier);
struct MLV_Keylogger_s {
  Etat etat; /* Etat du Keylogger */
  FctKeylog fct; /* Action à realiser */
  void *proprio; /* Propriétaire du Keylogger */
};

/*-----==========Gestion des Clickables==========-----*/
/* Crée un clickable */
MLV_Clickable init_clickable(MLV_Position pos, Etat etat, Espace esp);
/* Libère l'espace occupé par un Clickable */
void liberer_clickable(MLV_Clickable *click);
/* (Ré)initialise la fonction d'action du Clickable */
void click_init_fct(FctClick fct, MLV_Clickable click);
/* Change le propriétaire du Clickable */
void click_maj_proprio(void *proprio, MLV_Clickable click);
/* Renvoie le propriétaire d'un Clickable */
void *click_proprio(MLV_Clickable click);
/* Change l'état d'un Clickable */
void click_changer_etat(MLV_Clickable click);
/* Désactive un Clickable */
void desactiver_click(MLV_Clickable click);
/* Active un Clickable */
void activer_click(MLV_Clickable click);
/* Lance la fonction d'action d'un Clickable si les conditions sont correctes */
Id_Obj click_lancer_fct(MLV_Clickable click, Info_Souris souris);
/* Détermine si un click est actif et à l'intérieur de la zone */
bool click_est_dedant(Info_Souris souris, MLV_Clickable click);
/* Détermine si un click est actif et à l'extérieur de la zone */
bool click_est_dehors(Info_Souris souris, MLV_Clickable click);
/* Détermine si une coordonée est dans la zone */
bool est_dans_zone(Coord c, MLV_Position pos);

/*-----==========Gestion des Hoverables==========-----*/
/* Crée un Hoverable */
MLV_Hoverable init_hoverable(MLV_Position pos, Etat etat, Espace esp);
/* Libère l'espace occupé par un Hoverable */
void liberer_hoverable(MLV_Hoverable *hover);
/* (Ré)initialise la fonction d'action du Hoverable */
void hover_init_fct(FctHover fct, MLV_Hoverable hover);
/* Change le propriétaire du Hoverable */
void hover_maj_proprio(void *proprio, MLV_Hoverable hover);
/* Renvoie le propriétaire d'un Hoverable */
void *hover_proprio(MLV_Hoverable hover);
/* Lance la fonction d'action d'un Hoverable si les conditions sont correctes */
Id_Obj hover_lancer_fct(MLV_Hoverable hover, Info_Souris souris);
/* Détermine si un Hoverable est actif */
bool hover_est_active(Info_Souris souris, MLV_Hoverable hover);
/* Détermine si un survol est actif et à l'intérieur de la zone */
bool hover_est_dedant(Info_Souris souris, MLV_Hoverable hover);
/* Détermine si un survol est actif et à l'extérieur de la zone */
bool hover_est_dehors(Info_Souris souris, MLV_Hoverable hover);
/* Change l'état d'un Hoverable */
void hover_changer_etat(MLV_Hoverable hover);

/*-----==========Gestion des Keyloggers==========-----*/
/* Crée un Keylogger */
MLV_Keylogger init_keylogger(Etat etat);
/* Libère l'espace occupé par un Keylogger */
void liberer_keylogger(MLV_Keylogger *keylog);
/* (Ré)initialise la fonction d'action du Keylogger */
void keylog_init_fct(FctKeylog fct, MLV_Keylogger keylog);
/* Change le propriétaire du Keylogger */
void keylog_maj_proprio(void *proprio, MLV_Keylogger keylog);
/* Renvoie le propriétaire d'un Keylogger */
void *keylog_proprio(MLV_Keylogger keylog);
/* Lance la fonction d'action d'un Keylogger si les conditions sont correctes */
Id_Obj keylog_lancer_fct(MLV_Keylogger keylog, Info_Clavier clavier);
/* Détermine si un Keylogger est actif */
bool keylog_est_active(Info_Clavier clavier, MLV_Keylogger keylog);
/* Change l'état d'un Keylogger */
void keylog_changer_etat(MLV_Keylogger keylog);
/* Désactive un Keylogger */
void desactiver_keylog(MLV_Keylogger keylog);
/* Active un Keylogger */
void activer_keylog(MLV_Keylogger keylog);

#endif
