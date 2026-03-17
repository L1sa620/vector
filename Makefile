CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++14
top-vect: main.cpp
	        g++ -o $@ $^

clean:
		rm -rf *.o top-vect
