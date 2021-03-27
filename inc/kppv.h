#ifndef KNN_H_
#define KNN_H_

/* Renvoie le tableau des k plus proches voisins*/
TabPts trouver_kppv(TabPts tab_pts, point pt, int k);

/* Permet de trouver la classe d'un point par rapport à ses kppv */
int trouver_classe_kppv(TabPts tab, point pt, int k);

#endif
