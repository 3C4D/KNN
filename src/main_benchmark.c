/* Fichier contenant la fonction principale de l'executable benchmark */
/* Permettant de juger de l'efficacité des differents algorithmes de calcul */
/* des KPPV*/

#include <stdlib.h>
#include <stdio.h>
#include "erreur.h"
#include "benchmark.h"

int main(int argc, char **argv){

  int nbpoint, dimension, nbclasse, debug;

  /* Contrôle du nombre d'argument et de leur cohérence*/
  if(argc < 5){
    usage(argv[0]);
  }
  if(sscanf(argv[1], "%d", &nbpoint) != 1 || nbpoint < 1){
    err_log("\n##############################################\n");
    err_log("########## Premier argument invalide #########\n");
    err_log("##############################################\n\n");
    usage(argv[0]);
  }
  if(sscanf(argv[2], "%d", &dimension) != 1 || dimension <= 1){
    err_log("\n###############################################\n");
    err_log("########## deuxieme argument invalide #########\n");
    err_log("###############################################\n\n");
    usage(argv[0]);
  }
  if(sscanf(argv[3], "%d", &nbclasse) != 1 || nbclasse < 1){
    err_log("\n################################################\n");
    err_log("########## troisième argument invalide #########\n");
    err_log("################################################\n\n");
    usage(argv[0]);
  }
  if(sscanf(argv[4], "%d", &debug) != 1 || (debug != 0 && debug != 1)){
    err_log("\n##############################################\n");
    err_log("########## dernier argument invalide #########\n");
    err_log("##############################################\n\n");
    usage(argv[0]);
  }

  benchmark(nbpoint, dimension, nbclasse, debug);
  exit(0);
}
