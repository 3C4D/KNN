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
