# Visualisation des K plus proches voisins en 2D

## Compilation

Afin de compiler l'application, utiliez la commande :
```
make bin/kppv
```

Afin de compiler le générateur de fichier de test, utiliez la commande :
```
make bin/generation_test
```

Afin de compiler le comparateur de fonctions, utiliez la commande :
```
make bin/benchmark
```

Pour compiler les deux, utiliez simplement la commande :
```
make
```
ou bien
```
make all
```

Pour émonder les fichiers objets, utilisez la commande :
```
make clean
```

Pour émonder les fichiers objets et les fichiers exécutables, utiliez la
commande :
```
make clean_all
```

## Génération de fichier de test

Vous pouvez générer aléatoirement des fichiers de test avec l'exécutable
bin/generation_test.

il suffit de lui passer en paramètre, dans l'ordre :
  - Le nombre de point
  - Le nombre de coordonnée(s) des points
  - Le nombre de classes maximum
  - Le nom du fichier (qui doit être nouveau)

Exemple, la commande :
```
bin/generation_test 1000 50 6 nouveau_fichier.dat
```

Cette commande va créer un fichier nommé nouveau_fichier.dat contenant 1000
points, ils auront 50 coordonnées et 6 classes maximum.
L'exécutable retournera une erreur si le fichier ne possède pas la bonne
extension.

Extensions autorisées :
  - .dat
  - .log
  - .txt

## Application kppv

Quand vous démarrez l'exécutable kppv situé dans le dossier bin, libre à vous
de :
  - Charger un fichier existant.
  - Sauvegarder ce que vous avez fait.
  - Créer de nouveaux point en cliquant sur le mode création.
  - Placer le point dont on veut connaitre les plus proches voisins
    en cliquant sur le mode KPPV.
  - Changer le nombre de voisins (K).
  - Dessiner l'arbre kd.
  - Déterminer la classe du point dont on connait les plus proches voisins.
  - Afficher/enlever les axes, la grille ainsi que la sous-grille.

## Chargement de fichier(s)

Pour charger un fichier il suffit d'entrer le nom du fichier dans la première
case de saisie et d'appuyer sur l'icône à sa droite.

Les fichiers sont chargés à partir du dossier ressources/data.

## Sauvegarde de fichier(s)

Pour sauvegarder un fichier il suffit d'entrer le nom du fichier dans la
première case de saisie et d'appuyer sur l'icône à sa droite.

Les fichiers sont sauvegardés dans le dossier ressources/data.

## Benchmark temps de calcul

Un exécutable permettant de juger des temps de calcul des différents algorithmes
de calcul des KPPV (tableau et arbre_kd) est mis à disposition.

Afin d'utiliser cet exécutable qui se trouve dans le chemin : `./bin/benchmark`,
il vous faudra lui donner des arguments, dans l'ordre :
  - Le nombre de point avec lequel on veut tester les fonctions.
  - La dimension de ces points.
  - Le nombre de classe maximum de ces points.
  - Le mode utilisé (0 pour classique, 1 pour debug)

(Précisons que le mode debug affiche le tableau et l'arbre qui sont obtenus
durant la fonction).

Exemple, la commande:
```
bin/generation_test 15 4 6 1
```

Cette commande va comparer les fonctions de recherche sur les KPPV avec
15 points possédants 4 dimensions et disposant au maximum de 6 classes.

La sortie sera le temps d'exécution de chaque fonction.

Le mode debug est activé donc le tableau de point ainsi que l'arbre seront
affichés.

## Crédits

Soam LeDortz - Enzo Cadoni
