 
all: prog4pages

prog4pages: prog4pages.o
	g++ -std=c++11 prog4pages.o -o prog4pages

prog4pages.o: prog4pages.cpp
	g++ -std=c++11 -c prog4pages.cpp

clean:
	rm -f *.o prog4pages
