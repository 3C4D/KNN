#include "lien_elems.h"

MLV_Button boutons[2];
MLV_Toggle bascules[1];
MLV_CheckBox coches[5];
MLV_SpinBox compteurs[2];
MLV_FileManager gests_fichier[2];
MLV_GraphKNN graphes[1];
MLV_Text labels[1];

void maj_elem_bascules();

Id_Obj tog(MLV_Clickable click, Info_Souris souris) {
  printf("clocked!\n");
  bascule_changer_pose(bascules[0]);

  bouton_changer_etat(boutons[0]);
  

  return BUTTON;
}

Id_Obj tester(MLV_Clickable click, Info_Souris souris) {
  bascule_changer_etat(bascules[0]);

  return TOGGLE;
}

void maj_elements(Id_Obj id){
  switch (id){
  case CHECKBOX:
    maj_elem_bascules();
    break;
  default:
    break;
  }
}

void maj_elem_bascules(){
  if (coches[0]->valide) {
    graph_kppv_ajouter_opt_aff(AXE, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(AXE, graphes[0]);
  }
  
  if (coches[1]->valide) {
    graph_kppv_ajouter_opt_aff(GRILLE, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(GRILLE, graphes[0]);
  }
  
  if (coches[2]->valide) {
    graph_kppv_ajouter_opt_aff(SOUS_GRILLE, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(SOUS_GRILLE, graphes[0]);
  }

  if (coches[3]->valide) {
    graph_kppv_ajouter_opt_aff(CERCLE_KPPV, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(CERCLE_KPPV, graphes[0]);
  }

  if (coches[4]->valide) {
    graph_kppv_ajouter_opt_aff(KPPV_DECISION, graphes[0]);
  } else {
    graph_kppv_suppr_opt_aff(KPPV_DECISION, graphes[0]);
  }

  graph_kppv_aff(graphes[0]);
}