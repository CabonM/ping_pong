#include "tcp.h"
#include "nombre.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <netinet/in.h>

int main(int argc, char** argv) {

    traiter_commande(argc == 2, argv[0], "<port>\nmauvais nombre d'arguments");
	
    int port = atoi(argv[1]);
    traiter_commande(port > 1024 && port <= 65535, argv[0], "<port>\n<port> est un port non réservé");

	SOCK sock;
    	creer_socket("", port, &sock);
    	attacher_socket(&sock);
	printf("Socket créée et attachée sur le port %d\n", port);
		
	fermer_connexion(&sock);
	exit(0);
}
