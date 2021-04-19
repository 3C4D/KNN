#include "math_op.h"

int est_puissance_2(int n){
  return (n && !(n & (n-1)));
}