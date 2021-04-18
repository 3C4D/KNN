#ifndef OBJ_SIMPLE_H_
#define OBJ_SIMPLE_H_

#include "id_objet.h"
#include "interactif.h"
#include "position.h"
#include "canvas.h"
#include "string_obj.h"
#include "texte.h"

typedef enum {ETAT_A, ETAT_B} Pose;

typedef struct MLV_Button_s *MLV_Button;
struct MLV_Button_s {
  MLV_Clickable zone;

  MLV_Canvas actif;
  MLV_Canvas inactif;
};

typedef struct MLV_Toggle_s *MLV_Toggle;
struct MLV_Toggle_s {
  MLV_Clickable zone;
  Pose etat;

  MLV_Canvas etat_on_a;
  MLV_Canvas etat_on_b;
  MLV_Canvas etat_off_a;
  MLV_Canvas etat_off_b;
};

typedef struct MLV_Input_s *MLV_Input;
struct MLV_Input_s {
  MLV_Clickable zone;
  MLV_Clickable sortie;
  MLV_Keylogger keylog;

  MLV_Canvas fond;
  MLV_Text texte;
};

MLV_Button init_bouton(MLV_Position pos, FctClick fonction);
void liberer_bouton(MLV_Button *bouton);
void bouton_changer_etat(MLV_Button bouton);
void desactiver_bouton(MLV_Button bouton);
void activer_bouton(MLV_Button bouton);
void bouton_label(char *label, MLV_Button bouton);
void bouton_image(char *chemin, MLV_Button bouton);

MLV_Toggle init_bascule(MLV_Position pos, FctClick fonction, Pose pose);
void liberer_bascule(MLV_Toggle *bascule);
void bascule_changer_etat(MLV_Toggle bascule);
void desactiver_bascule(MLV_Toggle bascule);
void activer_bascule(MLV_Toggle bascule);
void bascule_pose(Pose pose, MLV_Toggle bascule);
void bascule_changer_pose(MLV_Toggle bascule);
void bascule_label(char *label_a, char *label_b, MLV_Toggle bascule);
void bascule_image(char *chemin_a, char *chemin_b, MLV_Toggle bascule);

MLV_Input init_saisie(MLV_Position pos, FctKeylog en_cours, FctClick fini);
void liberer_saisie(MLV_Input *saisie);
void desactiver_saisie(MLV_Input saisie);
void activer_saisie(MLV_Input saisie);

#endif
