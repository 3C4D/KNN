/*
Module d'opérations mathématiques
*/

#ifndef MATH_OP_H_
#define MATH_OP_H

/* Renvoie 1 si n est une puissance de 2, sinon 0 */
int est_puissance_2(int n);
/* Renvoie le logarithme binaire de n */
double log_bin(int n);
/* Renvoie l'arrondi à l'entier supérieur */
int entier_sup(double x);
/* Renvoie l'arrondi */
int arrondi(double x);

#endif