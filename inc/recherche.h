/* Fichier header contenant les prototypes des fonctions concernant */
/* la recherche de kppv dans un arbre kd */

#ifndef RECHERCHE_H_
#define RECHERCHE_H_

/* Met à jour une liste de point en fonction d'un nouveau point */
point *maj_liste(point *p_tmp, point *liste);

/* Renvoie le point le plus proche du point p dans la zone z_tmp */
point *point_proche_dans_zone(point *p, zone z_tmp);

/* Recherche les kppv d'un point dans un arbre kd */
point *recherche(arbre_kd a, point *p);

#endif
