#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

/* Permet de charger des informations contenues dans un fichier dans un
   tableau de points et de retourner ce dernier */
TabPts chargement_fichier(char *nom_fic);

/* Permet de sauvegarder un tableau de points dans un fichier */
void sauvegarde_fichier(TabPts tab, char *nom_fic);

#endif
