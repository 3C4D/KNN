#ifndef GESTION_AJOUT_H_
#define GESTION_AJOUT_H_

#include "obj_simple.h"
#include "obj_complexe.h"
#include "obj_kppv.h"
#include "gestion.h"

void charger_bouton(MLV_Button bouton, Manager gest);
void charger_bascule(MLV_Toggle bascule, Manager gest);
void charger_saisie(MLV_Input saisie, Manager gest);
void charger_coche(MLV_CheckBox coche, Manager gest);
void charger_compteur(MLV_SpinBox compteur, Manager gest);
void charger_graphe2d(MLV_Graph2D graph2d, Manager gest);
void charger_graph_kppv(MLV_GraphKNN graph_kppv, Manager gest);
void charger_gest_fichier(MLV_FileManager gest_fichier, Manager gest);

#endif
