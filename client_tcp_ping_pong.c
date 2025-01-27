#include "tcp.h"
#include "erreur.h"
#include "nombre.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

void traiter_commande(int condition, const char* nom_programme, const char* message) {
    if (condition) {
        fprintf(stderr, "%s: %s\n", nom_programme, message);
        exit(1);
    }
}

int main(int argc, char** argv) {
 
    traiter_commande(argc != 4, argv[0], "<adresse IP> <port> <message>\nmauvais nombre d'arguments");


    struct in_addr addr;
    traiter_commande(inet_pton(AF_INET, argv[1], &addr) != 1, argv[0], "<adresse IP> <port> <message>\n<adresse IP> est une adresse IP au format décimal pointé");

 
    int port = atoi(argv[2]);
    traiter_commande(port <= 1024 || port > 65535, argv[0], "<adresse IP> <port> <message>\n<port> est un port non réservé");


    int socket_fd = tcp_connect(argv[1], port);
    traiter_commande(socket_fd < 0, argv[0], "Échec de la connexion au serveur");

    // Envoyer le message
    ssize_t sent_bytes = send(socket_fd, argv[3], strlen(argv[3]), 0);
    traiter_commande(sent_bytes < 0, argv[0], "Échec de l'envoi du message");


    char buffer[1024];
    ssize_t received_bytes = recv(socket_fd, buffer, sizeof(buffer) - 1, 0);
    traiter_commande(received_bytes < 0, argv[0], "Échec de la réception de la réponse");

    buffer[received_bytes] = '\0';
    printf("Réponse du serveur: %s\n", buffer);

    // Fermer la connexion    close(socket_fd);

    exit(0);
}
