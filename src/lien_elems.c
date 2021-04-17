#include "lien_elems.h"

MLV_Button boutons[2];
MLV_Toggle bascules[1];
MLV_CheckBox coches[5];
MLV_SpinBox compteurs[2];
MLV_FileManager gests_fichier[2];
MLV_GraphKNN graphes[1];
MLV_Text labels[1];

Id_Obj tog(MLV_Clickable click, Info_Souris souris) {
  printf("clocked!\n");
  bascule_changer_pose(bascules[0]);

  bouton_changer_etat(boutons[0]);
  

  return NON_DEFINI;
}

Id_Obj tester(MLV_Clickable click, Info_Souris souris) {
  bascule_changer_etat(bascules[0]);

  return NON_DEFINI;
}