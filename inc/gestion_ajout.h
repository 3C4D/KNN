/*
Ce module implémente les fonctions d'ajout à un gestionnaire (Manager).
Cette action consiste en l'inclusion des différents composant d'un objet 
de l'interface.
*/

#ifndef GESTION_AJOUT_H_
#define GESTION_AJOUT_H_

#include "obj_simple.h"
#include "obj_complexe.h"
#include "obj_kppv.h"
#include "gestion.h"

/*-----==========Fonctions d'ajout des Objets==========-----*/
/* Charge un objet bouton dans le gestionnaire */
void charger_bouton(MLV_Button bouton, Manager gest);
/* Charge un objet bouton dans le gestionnaire */
void charger_bascule(MLV_Toggle bascule, Manager gest);
/* Charge un bascule bouton dans le gestionnaire */
void charger_saisie(MLV_Input saisie, Manager gest);
/* Charge un coche bouton dans le gestionnaire */
void charger_coche(MLV_CheckBox coche, Manager gest);
/* Charge un compteur bouton dans le gestionnaire */
void charger_compteur(MLV_SpinBox compteur, Manager gest);
/* Charge un graphique bouton dans le gestionnaire */
void charger_graphe2d(MLV_Graph2D graph2d, Manager gest);
/* Charge un graphique kppv bouton dans le gestionnaire */
void charger_graph_kppv(MLV_GraphKNN graph_kppv, Manager gest);
/* Charge un gestionnaire de fichier dans le gestionnaire */
void charger_gest_fichier(MLV_FileManager gest_fichier, Manager gest);

#endif
