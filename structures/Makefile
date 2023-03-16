test.out:test.o
	g++ -o $@ $^

test.o:test.cc
	g++ -c $^ -std=c++11

.PHONY:clean
clean:
	rm -f test.out test.o