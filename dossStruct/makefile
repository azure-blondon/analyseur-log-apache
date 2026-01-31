testStructure: main.o Structures.o Requete.o
	g++ -o testStructure main.o Structures.o Requete.o
main.o:main.cpp Structures.h Requete.h
	g++ -o main.o -c main.cpp

Structures.o:Structures.cpp Structures.h Requete.h
	g++ -o Structures.o -c Structures.cpp
Requete.o:Requete.cpp Requete.h
	g++ -o Requete.o -c Requete.cpp
clean:
	rm -f *.o testStructure;
