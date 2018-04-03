# Compétition de Systèmes d'Exploitation

## Mise en Contexte

Lors du crash du vaisseau, les pingouins ont malheureusement perdu leur dépôt git 
contenant leur librairie middleware (espace utilisateur communiquant à l'espace noyau) pour lire et écrire dans la boîte noire du vaisseau.

Les pingouins n'étant pas très actuels et réticents aux changement, ils hébergaient
eux-mêmes leur dépôt sur le vaisseau.

La boîte noire en question, nommée «`kiki`», est un périphérique capricieux (très instable) avec un pilote répondant à une interface d'appels peu (pas du tout) standard. 

Il est essentiel pour les pingouins de reproduire une implémentation fonctionnelle de la librairie perdue avec leur gestionnaire de version, s'ils veulent pouvoir un jour récupérer les informations cruciales enregistrées lors du vol.


## Objectif Principal

Reproduire une implémentation fonctionnelle de la librairie middleware `libkiki_api`, permettant de communiquer avec le pilote du périphérique `kiki`.

L'implémentation doit répondre __en tout point__ aux spécifications et exigences définies dans la documentation de la librairie disponible dans le manuel UNIX du système.


## Exigences

- Le __tout__ doit être implémenté en langage C. Le C++ ou tout autre langage n'est pas accepté.
- Toute dépendance, en termes de librairie externe est __illégale__.
- La librairie devrait pouvoir compiler statiquement (sous forme d'archive (`.a`)).
- Il faut répondre au format de remise décrit dans la section «Livrable».

__Ne pas répondre aux exigences__ résultera en la __note de 0%__.


## Directives

Toute la documentation nécessaire à l'exécution de la compétition se trouve sur le système, dans le manuel UNIX:

- Rubrique `kiki` pour la documentation du périphérique et son interface d'appel noyau.
- Rubrique `nom_de_la_fonction_à_implémenter` pour la documentation par fonction à implémenter.

Pour la documentation française, simplement suffixer le nom de la rubrique par `-fr`. Par exemple, `man kiki_device_init-fr`, 
pour la documentation de `kiki_device_init` en français.

Vous trouverez la __définition de l'interface d'appel noyau__ dans l'entête `kiki.h` installée dans `/usr/include`.

Vous trouverez __la liste des fonctions à implémenter__ dans l'entête `kiki_api.h` installée dans `/usr/include`.


## Livrable

__Toutes les fonctions__ dont la déclaration se trouve dans `kiki_api.h` doivent être implémentées dans __un seul__ fichier source nommé `kiki_api.c`.

Ce fichier (`kiki_api.c`) doit par la suite être livré.


## Bonuses

- Un bonus mystère sera accordé à quelque soit l'implémentation compilant sans «warning» en standard C89.
