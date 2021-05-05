/*
Ce module défini les interactions enter les différents éléments de l'interface.
*/

#ifndef LIEN_ELEMS_H_
#define LIEN_ELEMS_H_

#include "id_objet.h"
#include "obj_simple.h"
#include "obj_complexe.h"
#include "obj_kppv.h"

/* Initialise les interactions entre les éléments */
void init_elements();
/* Met à jour les éléments en fonction du type d'objet utilisé */
void maj_elements(Id_Obj id);

/*-----Fonctions pour l'initialisation-----*/
/* Fonciton utilisée pour l'initialisation du bouton de réinitialisation */
Id_Obj gkppv_reinit(MLV_Clickable click, Info_Souris souris);
/* Fonctions d'import et d'export utilisées dans l'initialisation des
gestionnaires de fichier */
void importer_fichier(char *fichier);
void exporter_fichier(char *fichier);

#endif