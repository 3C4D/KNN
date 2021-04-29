/* Fichier header contenant les prototypes des fonctions de test permettant */
/* de juger de l'efficacité des différentes algorithmes de calcul des KPPV */

#ifndef BENCHMARK_H_
#define BENCHMARK_H_

/* Fonction usage de l'exécutable benchmark */
void usage(char *str);

/* Fonction faisant un comparatif entre les deux algorithmes */
void benchmark(int nbpoints, int dimension, int nbclasse, int debug);

#endif
