# This is because travis sets this as an environment variable, but my
# machine doesn't
ifndef CXX
    CXX := g++
endif

LINKERS = -lgtest

# Adapted from http://stackoverflow.com/a/12099167/3076272
ifneq ($(OS),Windows_NT)
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LINKERS += -lpthread
    endif
endif

CXXFLAGS := -g -Wall -Werror -Wextra -pedantic -std=gnu++11

TESTS = tests/test_%.cpp
TEST_OBJ = $(TESTS:.cpp=.o)

TEST_DEPENDENCIES = $(patsubst %, $(TEST_OBJ), listnode linkedlist) 

linkedlist: main.o
	$(CXX) -o linkedlist main.o

all_tests: $(TEST_DEPENDENCIES) runtests.o
	$(CXX) -o all_tests $(TEST_DEPENDENCIES) runtests.o $(LINKERS)

runtests.o: runtests.cpp
	$(CXX) $(CXXFLAGS) -c runtests.cpp

test_listnode.o: test_listnode.cpp
	$(CXX) $(CXXFLAGS) -c test_listnode.cpp

test_linkedlist.o: test_linkedlist.cpp
	$(CXX) $(CXXFLAGS) -c test_linkedlist.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp

clean:
	rm -f *.o *.exe linkedlist all_tests
	rm -f tests/*.o

commit:
	git commit -a -m "$m"
	git push origin master
