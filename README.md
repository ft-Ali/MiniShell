 # MiniShell
# Fonctionnalités et Utilités

## Catégories et Utilités des Fonctions

| Catégorie                     | Fonction           | Utilité                                                                 | Bibliothèque à inclure        |
|-------------------------------|--------------------|------------------------------------------------------------------------|-------------------------------|
| **Manipulation de chaînes**   |                    |                                                                        |                               |
|                               | `strerror`         | Retourne une chaîne décrivant une erreur                               | `<string.h>`                  |
|                               | `strtok`           | Divise une chaîne en tokens basés sur des délimiteurs                  | `<string.h>`                  |
| **Entrées/sorties standards** |                    |                                                                        |                               |
|                               | `printf`           | Affiche une chaîne formatée sur la sortie standard                     | `<stdio.h>`                   |
|                               | `write`            | Écrit des données dans un descripteur de fichier                       | `<unistd.h>`                  |
|                               | `read`             | Lit des données depuis un descripteur de fichier                       | `<unistd.h>`                  |
|                               | `close`            | Ferme un descripteur de fichier                                        | `<unistd.h>`                  |
|                               | `perror`           | Affiche un message d'erreur sur la sortie d'erreur standard            | `<stdio.h>`                   |
| **Gestion de la mémoire**     |                    |                                                                        |                               |
|                               | `malloc`           | Alloue de la mémoire dynamique                                         | `<stdlib.h>`                  |
|                               | `free`             | Libère de la mémoire allouée                                           | `<stdlib.h>`                  |
| **Gestion des fichiers**      |                    |                                                                        |                               |
|                               | `open`             | Ouvre un fichier et retourne un descripteur de fichier                 | `<fcntl.h>`                   |
|                               | `access`           | Vérifie l'accessibilité d'un fichier                                   | `<unistd.h>`                  |
|                               | `stat`             | Obtient les informations sur un fichier                                | `<sys/stat.h>`                |
|                               | `lstat`            | Comme `stat` mais pour les liens symboliques                           | `<sys/stat.h>`                |
|                               | `fstat`            | Obtient les informations sur un fichier à partir de son descripteur    | `<sys/stat.h>`                |
|                               | `unlink`           | Supprime un fichier                                                    | `<unistd.h>`                  |
| **Gestion des processus**     |                    |                                                                        |                               |
|                               | `fork`             | Crée un nouveau processus en dupliquant le processus actuel            | `<unistd.h>`                  |
|                               | `execve`           | Remplace le processus courant par un nouveau programme                 | `<unistd.h>`                  |
|                               | `wait`             | Attend la fin d'un processus enfant                                    | `<sys/wait.h>`                |
|                               | `waitpid`          | Attend la fin d'un processus enfant spécifique                         | `<sys/wait.h>`                |
|                               | `wait3`            | Attend la fin d'un processus enfant et retourne des statistiques       | `<sys/wait.h>`                |
|                               | `wait4`            | Comme `wait3` mais permet de spécifier un processus spécifique         | `<sys/wait.h>`                |
|                               | `exit`             | Termine le processus courant                                           | `<stdlib.h>`                  |
|                               | `kill`             | Envoie un signal à un processus                                        | `<signal.h>`                  |
|                               | `signal`           | Définit une fonction de gestion des signaux                            | `<signal.h>`                  |
|                               | `sigaction`        | Change l'action à effectuer lors de la réception d'un signal           | `<signal.h>`                  |
|                               | `sigemptyset`      | Initialise un ensemble de signaux vide                                 | `<signal.h>`                  |
|                               | `sigaddset`        | Ajoute un signal à un ensemble de signaux                              | `<signal.h>`                  |
| **Gestion des répertoires**   |                    |                                                                        |                               |
|                               | `getcwd`           | Obtient le répertoire courant                                          | `<unistd.h>`                  |
|                               | `chdir`            | Change le répertoire courant                                           | `<unistd.h>`                  |
|                               | `opendir`          | Ouvre un répertoire                                                    | `<dirent.h>`                  |
|                               | `readdir`          | Lit une entrée de répertoire                                           | `<dirent.h>`                  |
|                               | `closedir`         | Ferme un répertoire                                                    | `<dirent.h>`                  |
| **Gestion des terminaux**     |                    |                                                                        |                               |
|                               | `isatty`           | Vérifie si un descripteur de fichier est associé à un terminal         | `<unistd.h>`                  |
|                               | `ttyname`          | Retourne le nom du fichier de terminal associé à un descripteur        | `<unistd.h>`                  |
|                               | `ttyslot`          | Retourne le numéro de slot du terminal                                 | `<unistd.h>`                  |
|                               | `ioctl`            | Manipule les caractéristiques des périphériques                        | `<sys/ioctl.h>`               |
| **Variables d'environnement** |                    |                                                                        |                               |
|                               | `getenv`           | Obtient la valeur d'une variable d'environnement                       | `<stdlib.h>`                  |
| **Contrôle du terminal**      |                    |                                                                        |                               |
|                               | `tcsetattr`        | Définit les attributs du terminal                                      | `<termios.h>`                 |
|                               | `tcgetattr`        | Obtient les attributs du terminal                                      | `<termios.h>`                 |
|                               | `tgetent`          | Lit la base de données des terminaux                                   | `<termcap.h>`                 |
|                               | `tgetflag`         | Obtient le drapeau booléen d'une capacité de terminal                  | `<termcap.h>`                 |
|                               | `tgetnum`          | Obtient le nombre associé à une capacité de terminal                   | `<termcap.h>`                 |
|                               | `tgetstr`          | Obtient la chaîne associée à une capacité de terminal                  | `<termcap.h>`                 |
|                               | `tgoto`            | Construit une chaîne de positionnement                                 | `<termcap.h>`                 |
|                               | `tputs`            | Écrit une chaîne de contrôle du terminal                               | `<termcap.h>`                 |
| **Gestion des descripteurs**  |                    |                                                                        |                               |
|                               | `dup`              | Duplique un descripteur de fichier                                     | `<unistd.h>`                  |
|                               | `dup2`             | Duplique un descripteur de fichier vers un descripteur spécifié        | `<unistd.h>`                  |
|                               | `pipe`             | Crée un tube pour la communication inter-processus                     | `<unistd.h>`                  |

## Notes
