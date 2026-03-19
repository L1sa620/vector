CXXFLAGS += -Wall -Wextra -std=c++14 -Weffc++ -MMD

top-vect: main.o
	g++ -o $@ $^

-include main.d

clean:
	rm -rf *.o *.d top-vect
