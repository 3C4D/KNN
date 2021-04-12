/* Fichier header contenant les prototypes des fonctions concernant les kppv */
/* à savoir trouver les kppv et trouver la classe d'un point par rapport */
/* à ses kppv */

#ifndef KPPV_H_
#define KPPV_H_

/* Renvoie le tableau des k plus proches voisins*/
TabPts trouver_kppv_tab(TabPts tab_pts, point pt, int k);

/* Permet de trouver la classe d'un point par rapport à ses kppv */
int trouver_classe_kppv_tab(TabPts tab, point pt, int k);

#endif
