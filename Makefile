analog: main.o Configuration.o Requete.o Structures.o Graphe.o
	g++ -o analog main.o Configuration.o Requete.o Structures.o Graphe.o

main.o: main.cpp
	g++ -c main.cpp

Requete.o: Requete.cpp Requete.h
	g++ -c Requete.cpp

Configuration.o: Configuration.cpp Configuration.h
	g++ -c Configuration.cpp

Structures.o: Structures.cpp Structures.h
	g++ -c Structures.cpp

Graphe.o: Graphe.cpp Graphe.h
	g++ -c Graphe.cpp

clean:
	rm -f *.dot *.o *.ou