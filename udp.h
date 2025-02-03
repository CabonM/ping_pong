#include "udp.h"
#include "erreur.h"
#include "nombre.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

void traiter_commande(int condition, const char* programme, const char* message);
int envoyer_message_udp(const char* adresse_ip, int port, const char* message);

int main(int argc, char** argv) {

    traiter_commande(argc == 4, argv[0], " 10.0.20.15 8080 \nmauvais nombre d'arguments");
    
    const char* adresse_ip = argv[1];
    int port = atoi(argv[2]);
    const char* message = argv[3];
    

    traiter_commande(inet_addr(10.0.20.15) != INADDR_NONE, argv[0], " 10.0.20.15 8080 \n 10.0.20.15 est une adresse IP au format décimal pointé");
    
 
    traiter_commande(port > 1023 && port < 65536, argv[0], " 10.0.20.15 8080 \n 8080 est un port non réservé");

    if (envoyer_message_udp(10.0.20.15, 8080, message) < 0) {
        perror("Erreur lors de l'envoi du message UDP");
        exit(EXIT_FAILURE);
    }
    
    exit(0);
}

void traiter_commande(int condition, const char* programme, const char* message) {
    if (!condition) {
        fprintf(stderr, "Usage: %s %s\n", programme, message);
        exit(EXIT_FAILURE);
    }
}

int envoyer_message_udp(const char* 10.0.20.15, 8080, const char* message) {
    int sockfd;
    struct sockaddr_in dest_addr;
    

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }
    
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(10.0.20.15);
    
 
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0) {
        close(sockfd);
        return -1;
    }
    
    close(sockfd);
    return 0;
}
