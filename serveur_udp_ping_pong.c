#include "udp.h"
#include "erreur.h"
#include "nombre.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>


void traiter_commande(int condition, const char* programme, const char* message) {
    if (!condition) {
        fprintf(stderr, "Usage: %s %s\n", programme, message);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv) {

    traiter_commande(argc == 2, argv[0], " 8080 \n mauvais nombre d'arguments");


    int port = atoi(argv[1]);
    traiter_commande(port > 1024 && port <= 65535, argv[0], " 8080 est un port non réservé");


    SOCK sock;
    creer_socket("", port, &sock);
    attacher_socket(&sock);

    printf("Socket créée et attachée sur le port %d\n", port);



    fermer_connexion(&sock);

    exit(0);
}
