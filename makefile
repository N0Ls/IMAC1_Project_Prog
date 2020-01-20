testProjet: main.o infantry.o player.o display.o bonus.o
	g++ main.o infantry.o player.o display.o bonus.o -o testProjet -Wall -lstdc++

main.o: main.cpp
	g++ -c -Wall main.cpp

infantry.o: infantry.cpp
	g++ -c -Wall infantry.cpp

player.o: player.cpp
	g++ -c -Wall player.cpp

display.o: display.cpp
	g++ -c -Wall display.cpp

bonus.o: bonus.cpp
	g++ -c -Wall bonus.cpp
