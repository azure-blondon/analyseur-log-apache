main: main.o Configuration.o Requete.o Structures.o
	g++ -o main main.o Configuration.o Requete.o Structures.o

main.o: main.cpp
	g++ -c main.cpp

Requete.o: Requete.cpp Requete.h
	g++ -c Requete.cpp

Configuration.o: Configuration.cpp Configuration.h
	g++ -c Configuration.cpp

Structure.o: Structures.cpp Structures.h
	g++ -c Structures.cpp

clean:
	rm -f *.dot *.o *.ou