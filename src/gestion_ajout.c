#include "gestion_ajout.h"

void charger_bouton(MLV_Button bouton, Manager gest){
  ajouter_canvas(bouton->actif, gest->liste_canvas);
  ajouter_canvas(bouton->inactif, gest->liste_canvas);
  ajouter_click(bouton->zone, gest->liste_click);
}

void charger_bascule(MLV_Toggle bascule, Manager gest){
  ajouter_canvas(bascule->etat_on_a, gest->liste_canvas);
  ajouter_canvas(bascule->etat_on_b, gest->liste_canvas);
  ajouter_canvas(bascule->etat_off_a, gest->liste_canvas);
  ajouter_canvas(bascule->etat_off_b, gest->liste_canvas);
  ajouter_click(bascule->zone, gest->liste_click);
}

void charger_saisie(MLV_Input saisie, Manager gest){
  ajouter_texte(saisie->texte, gest->liste_texte);
  ajouter_canvas(saisie->fond, gest->liste_canvas);
  ajouter_click(saisie->zone, gest->liste_click);
  ajouter_click(saisie->sortie, gest->liste_click);
  ajouter_keylog(saisie->keylog,gest->liste_keylog);
}

void charger_coche(MLV_CheckBox coche, Manager gest){
  charger_bascule(coche->case_coche, gest);
  ajouter_texte(coche->label, gest->liste_texte);
}

void charger_compteur(MLV_SpinBox compteur, Manager gest){
  charger_bouton(compteur->aug, gest);
  charger_bouton(compteur->dim, gest);
  charger_saisie(compteur->info, gest);
}

void charger_graphe2d(MLV_Graph2D graph2d, Manager gest){
  ajouter_canvas(graph2d->surface, gest->liste_canvas);
}

void charger_graph_kppv(MLV_GraphKNN graph_kppv, Manager gest){
  charger_graphe2d(graph_kppv->graph2D, gest);
  ajouter_click(graph_kppv->curseur, gest->liste_click);
}

void charger_gest_fichier(MLV_FileManager gest_fichier, Manager gest){
  charger_saisie(gest_fichier->fichier, gest);
  charger_bouton(gest_fichier->operation, gest);
}