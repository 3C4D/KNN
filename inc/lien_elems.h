#ifndef LIEN_ELEMS_H_
#define LIEN_ELEMS_H_

#include "id_objet.h"
#include "obj_simple.h"
#include "obj_complexe.h"
#include "obj_kppv.h"

void init_elements();
void maj_elements(Id_Obj id);
Id_Obj tog(MLV_Clickable click, Info_Souris souris);
Id_Obj tester(MLV_Clickable click, Info_Souris souris);
void importer_fichier(char *fichier);
void exporter_fichier(char *fichier);

#endif