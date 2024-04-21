#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

// Fonction pour initialiser le socket serveur
int initialize_server(int *server_fd, struct sockaddr_in *address)
{
    int opt = 1;

    // Création du descripteur de socket
    if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        return -1;
    }

    // Attachement du socket au port 8080
    if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        return -1;
    }

    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(PORT);

    // Association du socket à l'adresse et au port
    if (bind(*server_fd, (struct sockaddr *)address, sizeof(*address)) < 0)
    {
        perror("bind failed");
        return -1;
    }
    return 0;
}

// Fonction principale
int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Initialiser le serveur
    if (initialize_server(&server_fd, &address) < 0)
    {
        exit(EXIT_FAILURE);
    }

    // Écouter les connexions entrantes
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("En attente de connexions...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        char buffer[300] = {0};
        long valread = read(new_socket, buffer, 300);
        printf("Connexion détectée de %s\n", inet_ntoa(address.sin_addr));
        printf("Données reçues : %s\n", buffer);

        if (strstr(buffer, "suspicious_command"))
        {
            printf("Activité suspecte détectée!\n");
            // Ajouter des actions spécifiques en cas d'activité suspecte
        }

        close(new_socket);
    }

    return 0;
}