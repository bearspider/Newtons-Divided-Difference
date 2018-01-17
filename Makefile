main.o: tree.o ndd.o
	g++ -Wall ndd.o tree.o -o ndd
ndd.o:	ndd.cpp
	g++ -Wall -c ndd.cpp
tree.o: tree.cpp tree.h
	g++ -Wall -c tree.cpp
clean:
	rm -f *.o ndd
