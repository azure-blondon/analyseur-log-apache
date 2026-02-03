# Manuel d'utilisation

## Nom des membres du groupe (et numéros de binôme)

Groupe B3407

- BLONDON Azure (B3405)
- CABIAS Simon (B3412)
- DEBUREAUX Mégane (B3409)
- DUPREZ Juliette (B3405)

## Présentation

Nous avons réalisé un outil en ligne de commande permettant d’analyser un fichier de log Apache. Cet outil peut générer des documents synthétiques au format GraphViz, mais aussi des statistiques.

Lors de notre analyse, nous ne considérons que les requêtes ayant effectivement abouti et les redirections, excluant donc les erreurs.

## Mode d'emploi

### Commande :

`$./analog [cheminFichier] [options]`

Par défaut, c’est-à-dire quand il n’y a aucune option, il affichera sur la console sous forme textuelle la liste des 10 documents les plus consultés par ordre décroissant de popularité. Aucun fichier “.dot” n’est généré dans ce cas. Les options en ligne de commande sont détaillées ci-après.

Si une option n'est pas présente dans la ligne de commande, le programme se réfèrera à la configuration par défaut (fichier config). Si toutefois vous ne voulez pas qu'une option soit considérée, il suffit d'ajouter un # devant la ligne de configuration pour la commenter.

### Options :

- `[-g cheminFichier]`

Cette option permet de produire un fichier au format GraphViz du graphe analysé. Chaque document apparaîtra sous la forme d’un nœud et chaque arc indiquera le nombre de parcours associés.

Le nom du fichier .dot généré est configuré directement après l'option.

- `[-e]`

Cette option permet d’exclure tous les documents qui ont une extension de type image, css ou javascript. Par défaut, cette option est désactivée.

- `[-t heure]`

Cette option permet de ne prendre en compte que les hits qui sont dans le créneau horaire correspondant à l’intervalle ```[heure, heure+1[```.

Le créneau horaire à prendre en compte est configuré directement après l'option.

- `[-c cheminConfig]`

Cette option permet de spécifier le fichier de configuration à utiliser. Par défaut, ce sera le fichier `config` dans le répertoire courant. (Si vous ne souhaitez pas utilier de fichier de configuration malgré la présence d'un fichier nommé `config`, vous pouvez spécifier un fichier qui n'existe pas Ex: `./analog -c ignore`)

Le fichier de configuration remplace les valeurs par défaut de la commande.

Exemple:
Avec le fichier de configuration suivant: (fichier nommé `config` dans le répertoire courant)

```config
fichier_source: logs/coucou.log
creneau_horaire: 13
```

la commande 
```bash
./analog
```

est équivalente à la commande suivante (sans le fichier de configuration)
```bash
./analog logs/coucou.log -t 13
```

et la commande 
```bash
./analog -e -t 7
```

est équivalente à la commande suivante (sans le fichier de configuration)
```bash
./analog logs/coucou.log -e -t 7
```

### Fichier config :

Ce fichier permet de configurer rapidement les options de l'outil.

Quatre champs sont disponibles :

- fichier_source : `[cheminFichier.log]`

Ce champ permet de spécifier le fichier d'entrée, qui contient les logs à analyser.

- fichier_graphe : `[cheminFichier.dot]`

Ce champ permet de spécifier le fichier de sortie, qui permettra de générer le graphe.

- exclure_extensions : `[true|false]`

Ce champ permet de spécifier si l'on veut ou non exclure les fichier avec des extensions de type image, css ou javascript.

- creneau_horaire : `[heure]`

Ce champ permet de spécifier le créneau horaires des requêtes que l'on veut traiter. On traitera les requêtes comprises dans l'intervalle `[heure, heure+1[`.

Toute ligne commençant par `#` sera ignorée.


Exemple:
```config
fichier_source: logs/test.log
fichier_graphe: hello.dot
#creneau_horaire: 15
#exclure_extensions: true
```