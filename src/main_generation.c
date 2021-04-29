/* Fichier principal correspondant à l'executable de generation de fichiers */
/* de test */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "generation.h"
#include "erreur.h"

int main(int argc, char **argv){
  int test;

  srand(time(NULL));  /* Initialisation de l'horloge servant au hasard */

  if(argc != 5){  /* Vérification du nombre d'argument */
    fprintf(stderr,
            "\nUsage : %s <nbpoint> <dimension> <nbclasse> <nom_fic>\n",
            argv[0]
          );
    exit(0);
  }

  /* Vérification des arguments dans l'ordre */
  if(!sscanf(argv[1], "%d", &test)){  /* Le nombre de point est incorrect */
    erreur("\nErreur, le nombre de point donné n'est pas un nombre entier\n");
  }
  if(!sscanf(argv[2], "%d", &test)){  /* La dimension est incorrecte */
    erreur("\nErreur, la dimension donnée n'est pas un nombre entier\n");
  }
  if(!sscanf(argv[3], "%d", &test)){  /* Le nombre de classe est incorrect */
    erreur("\nErreur, le nombre de classe donné n'est pas un nombre entier\n");
  }

  /* Si tout convient on essayer de créer le fichier */
  generation_fichier(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4]);
  exit(0);
}
