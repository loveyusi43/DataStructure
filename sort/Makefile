sort.out:test.o
	g++ -o $@ $^

test.o:test.cc sort.hpp
	g++ -c $^ -std=c++11

.PHONY:clean
clean:
	rm -f sort.out test.o