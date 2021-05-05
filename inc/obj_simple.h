/*
Ce module implémente les objets simples, ce sont les briques élémentaires de la
construction d'un interface. Il peuvent ếtre utilisés telquels ou bien faire
partie d'un autre objet (cf. obj_complexe.h)
*/

#ifndef OBJ_SIMPLE_H_
#define OBJ_SIMPLE_H_

#include "id_objet.h"
#include "interactif.h"
#include "position.h"
#include "canvas.h"
#include "string_obj.h"
#include "texte.h"

typedef enum {ETAT_A, ETAT_B} Pose; /* Etats des bascules */

typedef struct MLV_Button_s *MLV_Button;
struct MLV_Button_s {
  MLV_Clickable zone; /* Zone de click */

  MLV_Canvas actif; /* Image bouton actif */
  MLV_Canvas inactif; /* Image bouton inactif */
};

typedef struct MLV_Toggle_s *MLV_Toggle;
struct MLV_Toggle_s {
  MLV_Clickable zone; /* Zone de click */
  Pose etat; /* Etat de la bascule */

  MLV_Canvas etat_on_a; /* Image bascule etat_a actif */
  MLV_Canvas etat_on_b; /* Image bascule etat_b actif */
  MLV_Canvas etat_off_a; /* Image bascule etat_a inactif */
  MLV_Canvas etat_off_b; /* Image bascule etat_b inactif */
};

typedef struct MLV_Input_s *MLV_Input;
struct MLV_Input_s {
  MLV_Clickable zone; /* Zone de click d'entrée */
  MLV_Clickable sortie; /* Zone de click de sortie */
  MLV_Keylogger keylog; /* Keylogger */

  MLV_Canvas fond; /* Fond de la saisie */
  MLV_Text texte; /* Texte de la saisie */
};

/*-----==========Gestion des boutons==========-----*/
/* Crée un bouton */
MLV_Button init_bouton(MLV_Position pos, FctClick fonction);
/* Libère l'espace occupé par un bouton */
void liberer_bouton(MLV_Button *bouton);
/* Change l'état d'un bouton */
void bouton_changer_etat(MLV_Button bouton);
/* Désactive le bouton */
void desactiver_bouton(MLV_Button bouton);
/* Active le bouton */
void activer_bouton(MLV_Button bouton);
/* Défini le label d'un bouton */
void bouton_label(char *label, MLV_Button bouton);
/* Défini l'image d'un bouton */
void bouton_image(char *chemin, MLV_Button bouton);

/*-----==========Gestion des bascules==========-----*/
/* Crée une bascule */
MLV_Toggle init_bascule(MLV_Position pos, FctClick fonction, Pose pose);
/* Libère l'espace occupé par une bascule */
void liberer_bascule(MLV_Toggle *bascule);
/* Change l'état de la bascule */
void bascule_changer_etat(MLV_Toggle bascule);
/* Désactive la bascule */
void desactiver_bascule(MLV_Toggle bascule);
/* Active la bascule */
void activer_bascule(MLV_Toggle bascule);
/* Défini la pose d'une bascule */
void bascule_pose(Pose pose, MLV_Toggle bascule);
/* Change la pose d'une bascule */
void bascule_changer_pose(MLV_Toggle bascule);
/* Défini les labels d'une bascule */
void bascule_label(char *label_a, char *label_b, MLV_Toggle bascule);
/* Défini les images d'une bascule */
void bascule_image(char *chemin_a, char *chemin_b, MLV_Toggle bascule);

/*-----==========Gestion des saisies==========-----*/
/* Crée une saisie */
MLV_Input init_saisie(MLV_Position pos, FctKeylog en_cours, FctClick fini);
/* Libère l'espace occupé par la saisie */
void liberer_saisie(MLV_Input *saisie);
/* Désactive la saisie */
void desactiver_saisie(MLV_Input saisie);
/* Active la saisie */
void activer_saisie(MLV_Input saisie);

#endif
