
main.o: main.cpp
	g++ -c -Wall main.cpp

infantry.o: infantry.cpp
	g++ -c -Wall infantry.cpp

testProjet: main.o infantry.o
	g++ main.o infantry.o -o testProjet -lstdc++
