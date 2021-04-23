#include <stdlib.h>
#include <stdbool.h>
#include "obj_simple.h"
#include "string_obj.h"
#include "geometrie.h"
#include "couleur.h"
#include "erreur.h"

void chemin_img_inactif(String chemin);

MLV_Button init_bouton(MLV_Position pos, FctClick fonction){
  MLV_Button bouton = malloc(sizeof(struct MLV_Button_s));
  verif_alloc((void *)bouton);
  bouton->zone = init_clickable(pos, ACTIF, INTERNE);
  click_init_fct(fonction, bouton->zone);
  click_maj_proprio((void *)bouton, bouton->zone);
  bouton->actif = init_canvas(pos, true);
  bouton->inactif = init_canvas(pos, false);

  return bouton;
}

void liberer_bouton(MLV_Button *bouton){
  if (bouton != NULL) {
    liberer_clickable(&(*bouton)->zone);
    liberer_canvas(&(*bouton)->actif);
    liberer_canvas(&(*bouton)->inactif);
    free(*bouton);
  }

  *bouton = NULL;
}

void bouton_changer_etat(MLV_Button bouton){
  click_changer_etat(bouton->zone);
  changer_visibilite(bouton->actif);
  changer_visibilite(bouton->inactif);
}

void desactiver_bouton(MLV_Button bouton){
  desactiver_click(bouton->zone);
  canvas_invisible(bouton->actif);
  canvas_visible(bouton->inactif);
}

void activer_bouton(MLV_Button bouton){
  activer_click(bouton->zone);
  canvas_visible(bouton->actif);
  canvas_invisible(bouton->inactif);
}

void bouton_label(char *label, MLV_Button bouton){
  couleur_fond_canvas(couleur_hex("39404d"), bouton->actif);
  placer_texte(label, couleur_hex("abb2bf"), bouton->actif);
  couleur_fond_canvas(couleur_hex("5f5f5f"), bouton->inactif);
  placer_texte(label, couleur_hex("9f9f9f"), bouton->inactif);
}

void bouton_image(char *chemin, MLV_Button bouton){
  Coord dec = bouton->actif->placement;
  String rep_img = String_new(chemin);
  
  MLV_Canvas canvas_actif = init_canvas_img(dec, rep_img->str, true);
  redimensionner_canvas(bouton->zone->pos->dimension, canvas_actif);

  chemin_img_inactif(rep_img);
  MLV_Canvas canvas_inactif = init_canvas_img(dec, rep_img->str, false);
  redimensionner_canvas(bouton->zone->pos->dimension, canvas_inactif);

  liberer_canvas(&bouton->actif);
  liberer_canvas(&bouton->inactif);
  bouton->actif = canvas_actif;
  bouton->inactif = canvas_inactif;
  String_free(rep_img);
}

Id_Obj bascule_fct_defaut(MLV_Clickable click, Info_Souris souris);

MLV_Toggle init_bascule(MLV_Position pos, FctClick fonction, Pose pose) {
  MLV_Toggle bascule = malloc(sizeof(struct MLV_Toggle_s));
  verif_alloc((void *)bascule);
  bascule->zone = init_clickable(pos, ACTIF, INTERNE);

  if (fonction != NULL){
    click_init_fct(fonction, bascule->zone);
  } else {
    click_init_fct(bascule_fct_defaut, bascule->zone);
  }
  
  click_maj_proprio((void *)bascule, bascule->zone);
  bascule->etat = pose;
  bascule->etat_on_a = init_canvas(pos, false);
  bascule->etat_on_b = init_canvas(pos, false);
  bascule->etat_off_a = init_canvas(pos, false);
  bascule->etat_off_b = init_canvas(pos, false);

  if (pose == ETAT_A) {
    changer_visibilite(bascule->etat_on_a);
  } else {
    changer_visibilite(bascule->etat_on_b);
  }

  return bascule;
}

void liberer_bascule(MLV_Toggle *bascule){
  if (*bascule != NULL) {
    liberer_clickable(&(*bascule)->zone);
    liberer_canvas(&(*bascule)->etat_on_a);
    liberer_canvas(&(*bascule)->etat_on_b);
    liberer_canvas(&(*bascule)->etat_off_a);
    liberer_canvas(&(*bascule)->etat_off_b);
    free(*bascule);
  }

  *bascule = NULL;
}

Id_Obj bascule_fct_defaut(MLV_Clickable click, Info_Souris souris){
  MLV_Toggle bascule = (MLV_Toggle)click_proprio(click);
  bascule_changer_pose(bascule);

  return TOGGLE;
}

void bascule_changer_etat(MLV_Toggle bascule){
  click_changer_etat(bascule->zone);
  if (bascule->etat == ETAT_A) {
    changer_visibilite(bascule->etat_on_a);
    changer_visibilite(bascule->etat_off_a);
  } else {
    changer_visibilite(bascule->etat_on_b);
    changer_visibilite(bascule->etat_off_b);
  }
}

void desactiver_bascule(MLV_Toggle bascule){
  desactiver_click(bascule->zone);
  if (bascule->etat == ETAT_A) {
    canvas_invisible(bascule->etat_on_a);
    canvas_visible(bascule->etat_off_a);
  } else {
    canvas_invisible(bascule->etat_on_b);
    canvas_visible(bascule->etat_off_b);
  }
}

void activer_bascule(MLV_Toggle bascule){
  activer_click(bascule->zone);
  if (bascule->etat == ETAT_A) {
    canvas_visible(bascule->etat_on_a);
    canvas_invisible(bascule->etat_off_a);
  } else {
    canvas_visible(bascule->etat_on_b);
    canvas_invisible(bascule->etat_off_b);
  }
}

void bascule_pose(Pose pose, MLV_Toggle bascule){
  bascule->etat = pose;

  if (pose  == ETAT_A){
    canvas_visible(bascule->etat_on_a);
    canvas_invisible(bascule->etat_on_b);
  } else {
    canvas_invisible(bascule->etat_on_a);
    canvas_visible(bascule->etat_on_b);
  } 
}

void bascule_changer_pose(MLV_Toggle bascule){
  if (bascule->etat == ETAT_A) {
    bascule_pose(ETAT_B, bascule);
  } else {
    bascule_pose(ETAT_A, bascule);
  }
}

void bascule_label(char *label_a, char *label_b, MLV_Toggle bascule){
  couleur_fond_canvas(couleur_hex("39404d"), bascule->etat_on_a);
  placer_texte(label_a, couleur_hex("61afef"), bascule->etat_on_a);
  couleur_fond_canvas(couleur_hex("39404d"), bascule->etat_on_b);
  placer_texte(label_b, couleur_hex("e06c75"), bascule->etat_on_b);

  couleur_fond_canvas(couleur_hex("5f5f5f"), bascule->etat_off_a);
  placer_texte(label_a, couleur_hex("9f9f9f"), bascule->etat_off_a);
  couleur_fond_canvas(couleur_hex("5f5f5f"), bascule->etat_off_b);
  placer_texte(label_b, couleur_hex("9f9f9f"), bascule->etat_off_b);
}

void bascule_image(char *chemin_a, char *chemin_b, MLV_Toggle bascule){
  Coord dec = bascule->etat_on_a->placement;
  String rep_img_a = String_new(chemin_a);
  String rep_img_b = String_new(chemin_b);

  MLV_Canvas canvas_a_on = init_canvas_img(
    dec, rep_img_a->str, est_visible(bascule->etat_on_a)
  );
  redimensionner_canvas(bascule->zone->pos->dimension, canvas_a_on);
  MLV_Canvas canvas_b_on = init_canvas_img(
    dec, rep_img_b->str, est_visible(bascule->etat_on_b)
  );
  redimensionner_canvas(bascule->zone->pos->dimension, canvas_b_on);

  chemin_img_inactif(rep_img_a);
  MLV_Canvas canvas_a_off = init_canvas_img(
    dec, rep_img_a->str, est_visible(bascule->etat_off_a)
  );
  redimensionner_canvas(bascule->zone->pos->dimension, canvas_a_off);

  chemin_img_inactif(rep_img_b);
  MLV_Canvas canvas_b_off = init_canvas_img(
    dec, rep_img_b->str, est_visible(bascule->etat_off_b)
  );
  redimensionner_canvas(bascule->zone->pos->dimension, canvas_b_off);

  liberer_canvas(&bascule->etat_on_a);
  liberer_canvas(&bascule->etat_on_b);
  liberer_canvas(&bascule->etat_off_a);
  liberer_canvas(&bascule->etat_off_b);
  bascule->etat_on_a = canvas_a_on;
  bascule->etat_on_b = canvas_b_on;
  bascule->etat_off_a = canvas_a_off;
  bascule->etat_off_b = canvas_b_off;

  String_free(rep_img_a);
  String_free(rep_img_b);
}

void chemin_img_inactif(String chemin){
  int index_pt;
  String extension = String_new_empty(0);
  index_pt = String_find_last(chemin, ".");
  String_split(index_pt, chemin, extension);
  String_concat_str(chemin, "_inactif");
  String_concat(chemin, extension);

  String_free(extension);
}


Id_Obj saisie_en_cours(MLV_Keylogger keylog, Info_Clavier clavier);
Id_Obj debut_saisie(MLV_Clickable click, Info_Souris souris);
Id_Obj saisie_finie(MLV_Clickable click, Info_Souris souris);

MLV_Input init_saisie(MLV_Position pos, FctKeylog en_cours, FctClick fini){
  MLV_Input saisie = malloc(sizeof(struct MLV_Input_s));
  verif_alloc(saisie);

  saisie->fond = init_canvas(pos, true);
  couleur_fond_canvas(couleur_hex("39404d"), saisie->fond);
  saisie->keylog = init_keylogger(INACTIF);
  if (en_cours != NULL){
    keylog_init_fct(en_cours, saisie->keylog);
  } else {
    keylog_init_fct(saisie_en_cours, saisie->keylog);
  }
  keylog_maj_proprio((void *)saisie, saisie->keylog);
  saisie->texte = init_texte(2, pos, init_format_defaut());
  saisie->zone = init_clickable(pos, ACTIF, INTERNE);
  click_maj_proprio((void *)saisie, saisie->zone);
  click_init_fct(debut_saisie, saisie->zone);
  saisie->sortie = init_clickable(pos, ACTIF, EXTERNE);
  if (fini != NULL){
    click_init_fct(fini, saisie->sortie);
  } else {
    click_init_fct(saisie_finie, saisie->sortie);
  }
  click_maj_proprio((void *)saisie, saisie->sortie);

  return saisie;
}

void liberer_saisie(MLV_Input *saisie){
  if (*saisie != NULL){
    liberer_canvas(&(*saisie)->fond);
    liberer_keylogger(&(*saisie)->keylog);
    liberer_texte(&(*saisie)->texte);
    liberer_clickable(&(*saisie)->zone);
    free(*saisie);
  }

  *saisie = NULL;
}

void desactiver_saisie(MLV_Input saisie){
  desactiver_click(saisie->zone);
  desactiver_click(saisie->sortie);
  desactiver_keylog(saisie->keylog);

  couleur_fond_canvas(couleur_hex("5f5f5f"), saisie->fond);
  texte_changer_couleur(couleur_hex("9f9f9f"), saisie->texte);
}

void activer_saisie(MLV_Input saisie){
  activer_click(saisie->zone);
  activer_click(saisie->sortie);
  activer_keylog(saisie->keylog);

  couleur_fond_canvas(couleur_hex("39404d"), saisie->fond);
  texte_changer_couleur(couleur_hex("abb2bf"), saisie->texte);
}

Id_Obj debut_saisie(MLV_Clickable click, Info_Souris souris){
  MLV_Input saisie = (MLV_Input)click_proprio(click);
  if (souris->bouton != MLV_BUTTON_LEFT){
    return INPUT;
  }
  
  saisie->keylog->etat = ACTIF;
  placer_curseur_texte(
    saisie->texte, couleur_hex("abb2bf"), saisie->fond
  );

  return INPUT;
}

Id_Obj saisie_finie(MLV_Clickable click, Info_Souris souris){
  MLV_Input saisie = (MLV_Input)click_proprio(click);
  saisie->keylog->etat = INACTIF;
  couleur_fond_canvas(couleur_hex("39404d"), saisie->fond);
  
  return INPUT;
}

Id_Obj saisie_en_cours(MLV_Keylogger keylog, Info_Clavier clavier){
  MLV_Input saisie = (MLV_Input)keylog_proprio(keylog);
  char *carac = NULL;

  switch (clavier->touche){
  case MLV_KEYBOARD_RETURN:
    return ((saisie->sortie->fct)(saisie->sortie, clavier->parent->souris));

  case MLV_KEYBOARD_BACKSPACE:
    texte_suppr_char(saisie->texte);
    break;
  
  default:
    carac = MLV_convert_unicode_to_string(clavier->lettre_unicode);
    texte_ajouter_str(carac, saisie->texte);
  }

  couleur_fond_canvas(couleur_hex("39404d"), saisie->fond);
  placer_curseur_texte(
    saisie->texte, couleur_hex("abb2bf"), saisie->fond
  );

  if (carac){
    free(carac);
  }
  
  return INPUT;
}