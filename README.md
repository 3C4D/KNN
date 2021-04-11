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
  - Son nombre de point
  - Le nombre de coordonnée(s) des points
  - Le nombre de classes maximum
  - Le nom du fichier (qui doit être nouveau)

Exemple, la commande :
```
bin/generation_test 1000 50 6 nouveau_fichier
```

Cette commande va créer un fichier nommé nouveau_fichier contenant 1000 points,
ils auront 50 coordonnées et 6 classes maximum.
L'exécutable retournera une erreur si le fichier existe ou bien si on ne peut
pas y écrire.

## Application
