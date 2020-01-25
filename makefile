ProgAlgoS1_Scavinner_Landrodie: main.o game.o menu.o grid.o infantry.o player.o bonus.o
	g++ main.o game.o menu.o grid.o infantry.o player.o bonus.o -o ProgAlgoS1_Scavinner_Landrodie -Wall -lstdc++

main.o: main.cpp
	g++ -c -Wall main.cpp

game.o : game.cpp
	g++ -c -Wall game.cpp

menu.o: menu.cpp
	g++ -c -Wall menu.cpp

grid.o: grid.cpp
	g++ -c -Wall grid.cpp

infantry.o: infantry.cpp
	g++ -c -Wall infantry.cpp

player.o: player.cpp
	g++ -c -Wall player.cpp

bonus.o: bonus.cpp
	g++ -c -Wall bonus.cpp