all: BSTree.o BSTree_main.o
	c++ -g -std=c++17 BSTree.o BSTree_main.o -o run-trees

BSTree.o: BSTree.cpp BSTree.h
	c++ -std=c++17 -g -c BSTree.cpp

BSTree_main.o: BSTree_main.cpp BSTree.h
	c++ -std=c++17 -g -c BSTree_main.cpp

clean:
	rm *.o run-trees

run:
	./run-trees


