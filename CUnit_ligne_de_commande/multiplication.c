#include <stdio.h>
#include <stdlib.h>

#include "erreur.h"
#include "nombre.h"

int main(int argc, char** argv) {
	long double n1, n2;

	traiter_commande(argc != 3, argv[0], "<nombre 1> <nombre 2>\nmauvais nombre d'arguments");
	traiter_commande(! est_un_nombre(argv[1]), argv[0], "<nombre 1> <nombre 2>\n<nombre 1> doit être un nombre");
	traiter_commande(! est_un_nombre(argv[2]), argv[0], "<nombre 1> <nombre 2>\n<nombre 2> doit être un nombre");
	
	n1 = convertir_nombre(argv[1]);
	n2 = convertir_nombre(argv[2]);

	printf("%Lf * %Lf = %Lf\n", n1, n2, n1 * n2);

	exit(0);
}
