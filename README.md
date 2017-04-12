# 42sh

[![Build Status](https://travis-ci.org/42shpimanmls/42sh.svg?branch=master)](https://travis-ci.org/42shpimanmls/42sh)

FEATURES
---

- [ ] Édition de ligne
	- [ ] Éditer la ligne à l’endroit où se trouve le curseur.
	- [ ] Déplacer le curseur vers la gauche et vers la droite.
	- [ ] Les flèches du haut et du bas pour naviguer dans l’historique.
	- [ ] Couper, copier et/ou coller tout ou partie d’une ligne.
	- [ ] Se déplacer par "mot" vers la gauche et vers la droite.
	- [ ] Aller directement au début et à la fin d’une ligne.
	- [ ] Écrire ET éditer une commande sur plusieurs lignes.
	- [ ] Saut d’une ligne à l’autre.
	- [ ] Retour à la ligne partie parenthésée de la commande non refermée.
	- [ ] ctrl+D et ctrl+C dans l’édition de la ligne.
	- [ ] Gérer complètement les quotes et doubles quotes, (hors expansions).

- [ ] Builtins
	- [ ] cd [-L|-P] [directory]
	- [ ] echo [string...]
	- [ ] exit [n]
	- [ ] env [-i] [name=value]... [utility [argument...]]
	- [ ] Setenv
	- [ ] Unsetenv
	- [ ] unset [-fv] name...
	- [ ] export [-p] name[=word]...
	- [ ] history

- [ ] Exécution
	- [ ] Exécution de commandes avec leurs paramètres et gestion du PATH.
	- [ ] Gestion des erreurs et de la valeur de retour des commandes.
	- [ ] Les redirection suivantes : ">", ">>", "<".
	- [ ] Les pipes “|”.
	- [ ] Les opérateurs logiques "&&" et "||".
	- [ ] Les back quotes "‘".
	- [ ] Le séparateur ";".

- [ ] Shell
	- [ ] Les variables locales.
	- [ ] Les inhibiteurs """ (double quote), "’" (simple quote) et "\" (backslash).

- [ ] Signaux 
	- [ ] ctrl+D 
	- [ ] ctrl+C

- [ ] Bonus
	- [ ] Le heredoc "<<".
	- [ ] Complétion dynamique.
	- [ ] Le Job control, job, fg et bg, et l’operateur "&".
	- [ ] Les aggrégations de descripteurs de fichiers 2>&- etc.
	- [ ] Rechercher dans l’historique avec ctrl+R.

- [ ] Structure
	- [ ] init
	- [ ] edit input
	- [ ] break input
	- [ ] parse input
	- [ ] word expansion
	- [ ] redirection
	- [ ] execution
	- [ ] wait
