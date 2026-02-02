analog: bin/main.o bin/Configuration.o bin/Requete.o bin/Structures.o bin/Graphe.o
	g++ -o bin/analog bin/main.o bin/Configuration.o bin/Requete.o bin/Structures.o bin/Graphe.o

bin/main.o: src/main.cpp
	g++ -o bin/main.o -c src/main.cpp

bin/Requete.o: src/Requete.cpp src/Requete.h
	g++ -o bin/Requete.o -c src/Requete.cpp

bin/Configuration.o: src/Configuration.cpp src/Configuration.h
	g++ -o bin/Configuration.o -c src/Configuration.cpp

bin/Structures.o: src/Structures.cpp src/Structures.h
	g++ -o bin/Structures.o -c src/Structures.cpp

bin/Graphe.o: src/Graphe.cpp src/Graphe.h
	g++ -o bin/Graphe.o -c src/Graphe.cpp

clean:
	rm -f bin/*.dot bin/*.o bin/*.ou