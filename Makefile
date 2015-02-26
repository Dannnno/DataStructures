# This is because travis sets this as an environment variable, but my
# machine doesn't afaik
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
    REMOVE := rm -f
else
    REMOVE := del
endif

CXXFLAGS := -g -Wall -Werror -Wextra -pedantic -std=gnu++11

TESTS = tests/test_%.cpp
TEST_OBJ = $(TESTS:.cpp=.o)

TEST_DEPENDENCIES = $(patsubst %, $(TEST_OBJ), linkedlist deque) 


deque: main.o exceptions.o
	$(CXX) -o deque main.o excceptions.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

exceptions.o: exceptions.cpp
	$(CXX) $(CXXFLAGS) -c exceptions.cpp


all_tests: $(TEST_DEPENDENCIES) runtests.o exceptions.o
	$(CXX) -o all_tests $(TEST_DEPENDENCIES) exceptions.o runtests.o \
		$(LINKERS)

runtests.o: runtests.cpp
	$(CXX) $(CXXFLAGS) -c runtests.cpp

test_linkedlist.o: test_linkedlist.cpp
	$(CXX) $(CXXFLAGS) -c test_linkedlist.cpp

test_deque.o: test_deque.cpp
	$(CXX) $(CXXFLAGS) -c test_deque.cpp


clean:
	FILES := $(wildcard *.o *.exe *.out) $(wildcard tests/*.o)
	$(foreach file,$(FILES),$(REMOVE) file)

commit:
	git commit -a -m "$m"
	git push origin master
