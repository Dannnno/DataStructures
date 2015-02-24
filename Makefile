CC = g++
CXXFLAGS = -g -Wall -Werror -Wextra -pedantic -std=gnu++11

TESTS = tests/test_%.cpp
TEST_OBJ = $(TESTS:.cpp=.o)

TEST_DEPENDENCIES = $(patsubst %, $(TEST_OBJ), listnode) 

linkedlist: main.o
	$(CC) -o linkedlist main.o

tests: $(TEST_DEPENDENCIES) runtests.o
	$(CC) -o tests $(TEST_DEPENDENCIES) runtests.o -lgtest
	./tests

runtests.o: runtests.cpp
	$(CC) $(CXXFLAGS) -c runtests.cpp

test_listnode.o: test_listnode.cpp
	$(CC) $(CXXFLAGS) -c test_listnode.cpp

main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp

tests.o: tests.cpp
	$(CC) $(CXXFLAGS) -c tests.cpp

clean:
	rm -f *.o *.exe *.out linkedlist tests


