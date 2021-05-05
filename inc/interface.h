/*
Ce module est le module lançant l'interface et s'occupant de l'initialisation
de celle-ci.
*/

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "obj_simple.h"
#include "obj_complexe.h"
#include "obj_kppv.h"

/* Lance l'interface */
int lancer_interface();

/* Élements externes au module (cf. lien_elems.c) */
extern MLV_Button boutons[2];
extern MLV_Toggle bascules[1];
extern MLV_CheckBox coches[6];
extern MLV_SpinBox compteurs[2];
extern MLV_FileManager gests_fichier[2];
extern MLV_GraphKNN graphes[1];
extern MLV_Text labels[4];

#endif
