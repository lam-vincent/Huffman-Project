# PROJET HUFFMAN

<!-- INTRODUCTION -->

## Introduction

Dans le cadre de notre projet informatique de PréING 2, notre groupe a programmé en C l’algorithme de Huffman, un algorithme dont l’objectif est de compresser des fichiers texte. 
Précisément, nous devions créer une archive contenant les fichiers sources du code commenté, les fichiers textes et un fichier README contenant la ligne de compilation et la commande d'exécution à écrire dans un terminal sur Linux. 

## Prérequis

Pour exécuter le programme, nous sommes obligés d’utiliser Linux. 

<!-- LIGNE DE COMPILATION -->

## Ligne de compilation

Grâce à la réalisation du makefile pour compiler le programme, il suffit d’écrire “make” dans le terminal.

- Pour compiler le programme
  ```sh
  make
  ```
## Executer le programme

- Pour compresser le fichier, la structure est la suivant :
  ```sh
  ./bin/main -c [FILE] [DIRECTORY]
  ```

- Vous pouvez écrire : 
  ```sh
  ./bin/main -c data/lorem.txt data/loremComp.txt
  ```

- Pour décompresser le fichier, la structure est la suivant :
  ```sh
  ./bin/main -c [FILE] [DIRECTORY]
  ```

- Vous pouvez écrire :
  ```sh
  ./bin/main -d data/loremComp.txt data/loremDecomp.txt
  ```


<p align="right">(<a href="#top">retourner en haut de la page</a>)</p>



