# Network Monitor

Ce projet contient un script serveur en C qui écoute les connexions réseau sur un port spécifique pour surveiller les activités suspectes. Il comprend également un script client en Python dans ce README.md qui peut envoyer des données au serveur pour tester la fonctionnalité de surveillance.

## Fonctionnalités

- **Écoute du réseau** : Le serveur en C écoute continuellement le port spécifié pour toute connexion entrante.
- **Détection d'activités suspectes** : Le serveur analyse les données reçues à la recherche de commandes ou de chaînes spécifiques indiquant une activité potentiellement suspecte.
- **Test du serveur** : Le script en Python peut être utilisé pour envoyer des données au serveur pour tester sa réactivité et sa capacité à enregistrer les activités.

## Prérequis

Pour utiliser ce projet, vous aurez besoin des éléments suivants installés sur votre système :
- GCC pour compiler le serveur en C
- Python 3 pour exécuter le script client

### Installation de GCC

Sur Debian ou Ubuntu, vous pouvez installer GCC en utilisant APT :

```bash
sudo apt update
sudo apt install build-essential
```

## Installation de Python 3

Sur Debian ou Ubuntu, installez Python 3 avec APT si ce n'est pas déjà fait :

```bash
sudo apt update
sudo apt install python3
```

## Compilation et Exécution du Serveur

Pour compiler et exécuter le serveur, utilisez les commandes suivantes :

```bash
gcc server.c -o server
sudo ./server
```

Le serveur écoute par défaut sur le port 8080. Assurez-vous que ce port est libre ou modifiez le port dans le code source si nécessaire.

### Utilisation du Script Client Python (test)

Pour envoyer des données au serveur afin de tester sa fonctionnalité, exécutez le script client suivant en Python :

```bash
import socket

# Paramètres de connexion
host = 'localhost'
port = 8080

# Création d'un socket
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((host, port))
    s.sendall(b'Hello, server!')
    data = s.recv(1024)

print('Received', repr(data))
```

## Exécution 

```bash
python3 send.py
```

Vous pouvez modifier le script send.py pour personnaliser les données envoyées au serveur.

## Contributions

Les contributions à ce projet sont les bienvenues. Pour proposer des améliorations ou des corrections, veuillez ouvrir une issue ou soumettre une pull request.

## Licence
Ce projet est distribué sous licence MIT. Vous êtes libre de l'utiliser, le modifier et le distribuer tant que vous respectez les termes de cette licence.
