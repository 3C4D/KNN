/* Fichier header contenant les prototypes des fonctions relatives à la */
/* génération de fichiers de tests */

#ifndef GENERATION_H_
#define GENERATION_H_
#include "points.h"

/* Permet de générer un point */
point generation_pt_alea(int dimension, int nbclasse);

/* Permet de générer un tableau de point aléatoire */
TabPts *generation_tableau_alea(int nbpoint, int dimension, int nbclasse);

/* Permet de générer un fichier de points aléatoire */
void generation_fichier(int nb_point, int dimension, int nbclasse, char *nom_fic);

#endif
