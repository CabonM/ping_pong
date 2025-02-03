COMPILER=gcc
EXE_DIR=/tmp/
FICHIERS=erreur udp nombre
OBJS:=$(FICHIERS:%=%.o)

all: ping_pong testsuite analyse
	-rm $(OBJS)

ping_pong: client_udp_ping_pong.c serveur_udp_ping_pong.c $(EXE_DIR) $(OBJS)
	mkdir -p $(EXE_DIR)/$@/UDP
	$(COMPILER) erreur.o udp.o nombre.o client_udp_$@.c -o $(EXE_DIR)/$@/UDP/client_udp_$@
	$(COMPILER) erreur.o udp.o nombre.o serveur_udp_$@.c -o $(EXE_DIR)/$@/UDP/serveur_udp_$@
	chmod -R u+x $(EXE_DIR)/$@/UDP

testsuite: testsuite.c udp.o erreur.o nombre.o
	$(COMPILER) -o testsuite testsuite.c udp.o erreur.o nombre.o -lcunit

udp.o: udp.c udp.h
	$(COMPILER) -c udp.c -o udp.o

erreur.o: erreur.c erreur.h
	$(COMPILER) -c erreur.c -o erreur.o

nombre.o: nombre.c nombre.h
	$(COMPILER) -c nombre.c -o nombre.o

analyse:
	cppcheck --enable=all --inconclusive --std=c99 --language=c --suppress=missingIncludeSystem .

$(EXE_DIR):
	mkdir -p $(EXE_DIR)

clean:
	rm -f *.o testsuite
	rm -rf $(EXE_DIR)/ping_pong
