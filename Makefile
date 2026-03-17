CXXFLAGS += -Wall -Wextra -std=c++14 -Weffc++ -MMD

-include main.o

top-vect: main.cpp
	g++ -o $@ $^

clean:
	rm -rf *.d *.o top-vect
