a.out:
	g++ -std=c++11 myBinarySearchTree_i127p615.hpp
	g++ -std=c++11 test_main.cpp
	./a.out inputs/instance10.txt output.txt

clean:
	rm *.gch output.txt a.out
