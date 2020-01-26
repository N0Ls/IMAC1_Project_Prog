imacwars: main.o game.o menu.o grid.o infantry.o player.o bonus.o
	gcc main.o game.o menu.o grid.o infantry.o player.o bonus.o -o imacwars -Wall -lstdc++

main.o: main.cpp
	gcc -c -Wall main.cpp -lstdc++

game.o : game.cpp
	gcc -c -Wall game.cpp -lstdc++

menu.o: menu.cpp
	gcc -c -Wall menu.cpp -lstdc++

grid.o: grid.cpp
	gcc -c -Wall grid.cpp -lstdc++

infantry.o: infantry.cpp
	gcc -c -Wall infantry.cpp -lstdc++

player.o: player.cpp
	gcc -c -Wall player.cpp -lstdc++

bonus.o: bonus.cpp
	gcc -c -Wall bonus.cpp -lstdc++
