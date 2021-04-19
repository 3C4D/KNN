#include "lien_elems.h"

MLV_Button boutons[2];
MLV_Toggle bascules[1];
MLV_CheckBox coches[6];
MLV_SpinBox compteurs[2];
MLV_FileManager gests_fichier[2];
MLV_GraphKNN graphes[1];
MLV_Text labels[4];

void maj_elem_coches();
void maj_elem_bascules();
void maj_elem_compteurs();
void maj_elem_gkppv();

Id_Obj tog(MLV_Clickable click, Info_Souris souris) {
  bascule_changer_pose(bascules[0]);

  return TOGGLE;
}

Id_Obj tester(MLV_Clickable click, Info_Souris souris) {
  bascule_changer_etat(bascules[0]);
  desactiver_compteur(compteurs[0]);
  desactiver_coche(coches[0]);

  return BUTTON;
}

void importer_fichier(char *fichier){
  graph_kppv_import_tab_pts(fichier, graphes[0]);
  graph_kppv_aff(graphes[0]);
}

void exporter_fichier(char *fichier){
  graph_kppv_export_tab_pts(fichier, graphes[0]);
  graph_kppv_aff(graphes[0]);
}


void init_elements(){
  maj_elem_coches();
  maj_elem_bascules();
  maj_elem_compteurs();
}

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
  if (coches[0]->valide) {
    graph_kppv_ajouter_opt_aff(AXE, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(AXE, graphes[0]);
  }
  
  if (coches[1]->valide) {
    graph_kppv_ajouter_opt_aff(GRILLE, graphes[0]);
    activer_coche(coches[2]);
  } else {
    graph_kppv_suppr_opt_aff(GRILLE, graphes[0]);
    decocher_case_coche(coches[2]);
    desactiver_coche(coches[2]);
  }
  
  if (coches[2]->valide) {
    graph_kppv_ajouter_opt_aff(SOUS_GRILLE, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(SOUS_GRILLE, graphes[0]);
  }

  if (coches[3]->valide) {
    graph_kppv_maj_tab_kppv(graphes[0]);
    graph_kppv_ajouter_opt_aff(CERCLE_KPPV, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(CERCLE_KPPV, graphes[0]);
  }

  if (coches[4]->valide) {
    graph_kppv_maj_tab_kppv(graphes[0]);
    graph_kppv_ajouter_opt_aff(KPPV_DECISION, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(KPPV_DECISION, graphes[0]);
  }

  graph_kppv_aff(graphes[0]);
}

void maj_elem_bascules(){
  if (bascules[0]->etat == ETAT_A){
    activer_compteur(compteurs[1]);
    graph_kppv_maj_classe_utilise(compteurs[1]->val, graphes[0]);
    click_init_fct(gkppv_ajouter_pt_classe, graphes[0]->curseur);
  } else {
    desactiver_compteur(compteurs[1]);
    graph_kppv_maj_classe_utilise(0, graphes[0]);
    click_init_fct(gkppv_maj_pt, graphes[0]->curseur);
  }
}

void maj_elem_compteurs(){
  graph_kppv_maj_classe_utilise(compteurs[1]->val, graphes[0]);
  graph_kppv_maj_k(compteurs[0]->val, graphes[0]);
  graph_kppv_maj_tab_kppv(graphes[0]);
  graph_kppv_aff(graphes[0]);
}

void maj_elem_gkppv(){
  graph_kppv_maj_tab_kppv(graphes[0]);
  graph_kppv_aff(graphes[0]);
}