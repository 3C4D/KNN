/* Fichier header contenant les prototypes des fonctions de sauvegarde */
/* et de chargement de tableaux de points */

#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "points.h"

/* Vérifie l'extension d'un nom de fichier et sa cohérence */
int verif_nom_fic(char *nom_fic);

/* Permet de charger des informations contenues dans un fichier dans un
   tableau de points et de retourner ce dernier */
TabPts *chargement_fichier(char *nom_fic);

/* Permet de sauvegarder un tableau de points dans un fichier */
void sauvegarde_fichier(TabPts *tab, char *nom_fic);

#endif
