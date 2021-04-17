/* Fichier header contenant les prototypes des fonctions concernant */
/* la recherche de kppv dans un arbre kd */

#ifndef RECHERCHE_H_
#define RECHERCHE_H_

typedef arbre_kd zone;  /* Une zone est un sous arbre soit un arbre kd */

/* Met à jour une liste de point en fonction d'un nouveau point */
int maj_liste(point *p_tmp, point *cible, point *liste, int *taille_k, int k);

/* Renvoie le point le plus proche du point p dans la zone z_tmp */
point *point_proche_dans_zone(point *p, zone z_tmp);

/* Recherche les kppv d'un point dans un arbre kd */
point *recherche(arbre_kd a, point *p, int k);

#endif
