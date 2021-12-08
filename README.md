# PROJET HUFFMAN 👨‍💻 ‍💻 📚

### La création de l'arbre binaire qui rend le codage de Huffman possible
![HuffmanDemo](https://upload.wikimedia.org/wikipedia/commons/a/ac/Huffman_huff_demo.gif)

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
  ./bin/main -c [SOURCE] [DIRECTORY]
  ```

- Vous pouvez écrire : 
  ```sh
  ./bin/main -c data/lorem.txt data/loremComp.txt
  ```

- Pour décompresser le fichier, la structure est la suivant :
  ```sh
  ./bin/main -d [SOURCE] [DIRECTORY]
  ```

- Vous pouvez écrire :
  ```sh
  ./bin/main -d data/loremComp.txt data/loremDecomp.txt
  ```

Pour [DIRECTORY], vous pouvez choisir le nom de votre fichier en sortie.

<p align="right">(<a href="#top">retourner en haut de la page</a>)</p>



