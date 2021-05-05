#include "lien_elems.h"

MLV_Button boutons[2];
/* [0]: Réinitialisation
   [1]: Retour */

MLV_Toggle bascules[1];
/* [0]: Mode */

MLV_CheckBox coches[6];
/* [0]: Axe
   [1]: Grille
   [2]: Sous-Grille
   [3]: KPPV Cercle
   [4]: Decision
   [5]: Arbre */

MLV_SpinBox compteurs[2];
/* [0]: K
   [1]: Classe */

MLV_FileManager gests_fichier[2];
/* [0]: Import
   [1]: Export */

MLV_GraphKNN graphes[1];
/* [0]: Graphique KPPV */

MLV_Text labels[3];
/* [0]: Titre options d'affichage
   [1]: Label Nombre de K
   [2]: Label Classe */

/* Met à jour les éléments de type coche */
void maj_elem_coches();
/* Met à jour les éléments de type bascule */
void maj_elem_bascules();
/* Met à jour les éléments de type compteur */
void maj_elem_compteurs();
/* Met à jour les éléments de type graphique kppv */
void maj_elem_gkppv();

/*-----Fonctions pour l'initialisation-----*/
/* Fonctions d'import et d'export utilisées dans l'initialisation des
gestionnaires de fichier */
void importer_fichier(char *fichier){
  graph_kppv_import_tab_pts(fichier, graphes[0]);
  graph_kppv_aff(graphes[0]);
}

void exporter_fichier(char *fichier){
  graph_kppv_export_tab_pts(fichier, graphes[0]);
  graph_kppv_aff(graphes[0]);
}

/* Fonciton utilisée pour l'initialisation du bouton de réinitialisation */
Id_Obj gkppv_reinit(MLV_Clickable click, Info_Souris souris){
  graph_kppv_reinit_pt(graphes[0]);

  return BUTTON;
}

/* Annule le placement du dernier point en mode Création */
Id_Obj gkppv_annuler_placement_pt(MLV_Clickable click, Info_Souris souris){
  graph_kppv_suppr_pt_ajoute(graphes[0]);

  return BUTTON;
}

/* Supprime le point kppv en mode KPPV */
Id_Obj gkppv_effacer_pt_kppv(MLV_Clickable click, Info_Souris souris){
  graph_kppv_cacher_pt(graphes[0]);

  return BUTTON;
}

/* Initialise les interactions entre les éléments */
void init_elements(){
  maj_elem_coches();
  maj_elem_bascules();
  maj_elem_compteurs();
  maj_elem_gkppv();
}

/* Met à jour les éléments en fonction du type d'objet utilisé */
void maj_elements(Id_Obj id){
  switch (id){
  case CHECKBOX:
    maj_elem_coches();
    break;
  case TOGGLE:
    maj_elem_bascules();
    break;
  case SPINBOX:
    maj_elem_compteurs();
    break;
  case GKPPV:
    maj_elem_gkppv();
    break;
  default:
    break;
  }
}

void maj_elem_coches(){
  /* Affichage des axes */
  if (coches[0]->valide) {
    graph_kppv_ajouter_opt_aff(AXE, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(AXE, graphes[0]);
  }
  
  /* Affichage de la grille */
  if (coches[1]->valide) {
    graph_kppv_ajouter_opt_aff(GRILLE, graphes[0]);
    activer_coche(coches[2]);
  } else {
    graph_kppv_suppr_opt_aff(GRILLE, graphes[0]);
    /* La case [2] est liée à la case [1] ainsi si [1] est désactivée alors on
    désactive [2] */
    decocher_case_coche(coches[2]);
    desactiver_coche(coches[2]);
  }
  
  /* Affichage de la sous-grille */
  if (coches[2]->valide) {
    graph_kppv_ajouter_opt_aff(SOUS_GRILLE, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(SOUS_GRILLE, graphes[0]);
  }

  /* Affichage du cercle des KPPV */
  if (coches[3]->valide) {
    graph_kppv_maj_tab_kppv(graphes[0]);
    graph_kppv_ajouter_opt_aff(CERCLE_KPPV, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(CERCLE_KPPV, graphes[0]);
  }

  /* Affichage de la décision KPPV */
  if (coches[4]->valide) {
    graph_kppv_ajouter_opt_aff(KPPV_DECISION, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(KPPV_DECISION, graphes[0]);
  }

  /* Affichage de l'arbre */
  if (coches[5]->valide) {
    graph_kppv_maj_arbre(graphes[0]);
    graph_kppv_ajouter_opt_aff(ARBRE_KD, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(ARBRE_KD, graphes[0]);
  }

  graph_kppv_aff(graphes[0]);
}

void maj_elem_bascules(){
  if (bascules[0]->etat == ETAT_A){
    /* En mode Création */
    activer_compteur(compteurs[1]);
    graph_kppv_maj_classe_utilise(compteurs[1]->val, graphes[0]);
    /* Changement de fonction adéquat */
    click_init_fct(gkppv_ajouter_pt_classe, graphes[0]->curseur);
    click_init_fct(gkppv_annuler_placement_pt, boutons[1]->zone);
  } else {
    /* En mode KPPV */
    desactiver_compteur(compteurs[1]);
    graph_kppv_maj_classe_utilise(0, graphes[0]);
    /* Changement de fonction adéquat */
    click_init_fct(gkppv_maj_pt, graphes[0]->curseur);
    click_init_fct(gkppv_effacer_pt_kppv, boutons[1]->zone);
  }
}

void maj_elem_compteurs(){
  graph_kppv_maj_classe_utilise(compteurs[1]->val, graphes[0]);
  graph_kppv_maj_k(compteurs[0]->val, graphes[0]);
  graph_kppv_maj_tab_kppv(graphes[0]);
  graph_kppv_aff(graphes[0]);
}

void maj_elem_gkppv(){
  graph_kppv_aff(graphes[0]);
}