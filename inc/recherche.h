/* Fichier header contenant les prototypes des fonctions concernant */
/* la recherche de kppv dans un arbre kd */

#ifndef RECHERCHE_H_
#define RECHERCHE_H_

typedef struct zone{  /* Une zone est délimitée par deux points (ses coins) */
  double x1;
  double x2;
  double y1;
  double y2;
}zone;

/* Met à jour une liste de point en fonction d'un nouveau point */
int maj_liste(point *p_tmp, point *cible, point *liste, int *taille_k, int k);

/* Renvoie le point le plus proche du point p dans la zone z_tmp */
point* point_proche_dans_zone(point *p, zone z_tmp);

/* Recherche les kppv d'un point dans un arbre kd */
TabPts *recherche(arbre_kd a, point *p, int k, int nbclasse);

#endif
