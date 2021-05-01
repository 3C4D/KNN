/* Fichier principal correspondant à l'executable kppv */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "interface.h"
#include "points.h"
#include "erreur.h"
#include "kppv.h"
#include "sauvegarde.h"
#include "arbre.h"
#include "generation.h"
#include "recherche.h"
#include "string_obj.h"

int main(int argc, char **argv){
  srand(time(NULL));
  lancer_interface();
  exit(0);
}
