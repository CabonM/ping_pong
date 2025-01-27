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

    traiter_commande(argc == 4, argv[0], "<adresse IP> <port> <message>\nmauvais nombre d'arguments");
    
    const char* adresse_ip = argv[1];
    int port = atoi(argv[2]);
    const char* message = argv[3];
    

    traiter_commande(inet_addr(adresse_ip) != INADDR_NONE, argv[0], "<adresse IP> <port> <message>\n<adresse IP> est une adresse IP au format décimal pointé");
    
 
    traiter_commande(port > 1023 && port < 65536, argv[0], "<adresse IP> <port> <message>\n<port> est un port non réservé");

    if (envoyer_message_udp(adresse_ip, port, message) < 0) {
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

int envoyer_message_udp(const char* adresse_ip, int port, const char* message) {
    int sockfd;
    struct sockaddr_in dest_addr;
    

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }
    
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(adresse_ip);
    
 
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0) {
        close(sockfd);
        return -1;
    }
    
    close(sockfd);
    return 0;
}
