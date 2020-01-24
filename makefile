ProgAlogS1_Scaviner_Landrodie: main.o infantry.o player.o bonus.o display.o
	g++ main.o infantry.o player.o bonus.o display.o -o ProgAlogS1_Scaviner_Landrodie -Wall -lstdc++

main.o: main.cpp
	g++ -c -Wall main.cpp

infantry.o: infantry.cpp
	g++ -c -Wall infantry.cpp

player.o: player.cpp
	g++ -c -Wall player.cpp

bonus.o: bonus.cpp
	g++ -c -Wall bonus.cpp

display.o: display.cpp
	g++ -c -Wall display.cpp
