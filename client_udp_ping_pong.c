#include "udp.h"
#include "erreur.h"
#include "nombre.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void traiter_commande(int condition, const char* exe_name, const char* message) {
    if (!condition) {
        fprintf(stderr, "Usage: %s %s\n", exe_name, message);
        exit(EXIT_FAILURE);
    }
}

void erreur(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
    traiter_commande(argc == 4, argv[0], "<adresse IP> <port> <message>\nmauvais nombre d'arguments");
    traiter_commande(inet_addr(argv[1]) != INADDR_NONE, argv[0], "<adresse IP> <port> <message>\n<adresse IP> est une adresse IP au format décimal pointé");
    traiter_commande(atoi(argv[2]) > 1024 && atoi(argv[2]) < 65536, argv[0], "<adresse IP> <port> <message>\n<port> est un port non réservé");

    const char* ip = argv[1];
    int port = atoi(argv[2]);
    const char* message = argv[3];

    int sockfd;
    struct sockaddr_in server_addr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        erreur("Erreur de création de la socket");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        erreur("Adresse IP invalide");
    }

    if (sendto(sockfd, message, strlen(message), 0, (const struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        erreur("Erreur d'envoi de message");
    }

    char buffer[1024];
    socklen_t len = sizeof(server_addr);

    int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*) &server_addr, &len);
    if (n < 0) {
        erreur("Erreur de réception de message");
    }

    buffer[n] = '\0';
    printf("Réponse du serveur: %s\n", buffer);


    if ((strcmp(message, "ping") == 0 && strcmp(buffer, "pong") == 0) || (strcmp(message, "pong") == 0 && strcmp(buffer, "ping") == 0)) {
        printf("Vous avez gagné !\n");
    } else {
        printf("Vous avez perdu !\n");
    }

    close(sockfd);
    exit(0);
}
