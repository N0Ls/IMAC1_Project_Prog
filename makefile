testProjet: main.o infantry.o player.o
	g++ main.o infantry.o player.o -o testProjet -Wall -lstdc++

main.o: main.cpp
	g++ -c -Wall main.cpp

infantry.o: infantry.cpp
	g++ -c -Wall infantry.cpp

player.o: player.cpp
	g++ -c -Wall player.cpp
