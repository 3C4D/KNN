#include "math_op.h"
#include <math.h>

/* Renvoie 1 si n est une puissance de 2, sinon 0 */
int est_puissance_2(int n){
  return (n && !(n & (n-1)));
}

/* Renvoie le logarithme binaire de n */
double log_bin(int n){
  return (log2((double)n));
}

/* Renvoie l'arrondi à l'entier supérieur */
int entier_sup(double x){
  return (int)(ceil(x));
}

/* Renvoie l'arrondi */
int arrondi(double x){
  return (int)(round(x));
}