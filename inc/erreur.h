#ifndef ERREUR_H_
#define ERREUR_H_

/* Renvoie un message d'erreur sur stderr */
void err_log(char *error);

/* Renvoie un message d'erreur sur stderr et interrompt le programme */
void erreur(char *error);

/* Vérifie une allocation (jamais utilisée) */
void verif_alloc(void *ptr);

#endif
