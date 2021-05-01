#include "math_op.h"
#include <math.h>

int est_puissance_2(int n){
  return (n && !(n & (n-1)));
}

double log_bin(int n){
  return (log2((double)n));
}

int entier_sup(double x){
  return (int)(ceil(x));
}