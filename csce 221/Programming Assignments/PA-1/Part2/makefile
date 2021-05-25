  
col: Collection.o Stress_ball.o 
	g++ Collection.o Stress_ball.o -o testCol
	./testCol

stress: Stress_ball.o
	g++ Stress_ball.o -o stress
	./stress
run:
	./test

all: main.o Collection.o Stress_ball.o
	g++ main.o Collection.o Stress_ball.o -o test

main.o: main.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -c main.cpp

Collection.o: Collection.cpp Stress_ball.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -c Collection.cpp Stress_ball.cpp 

Stress_ball.o: Stress_ball.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -c Stress_ball.cpp

clean: 
	rm *.o -rf

