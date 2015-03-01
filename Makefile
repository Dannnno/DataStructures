# This is because travis sets this as an environment variable, but my
# machine doesn't afaik
ifndef CXX
    CXX := g++
endif

LINKERS = -lgtest -fprofile-arcs

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

CXXFLAGS := -g -Wall -Werror -Wextra -pedantic -std=gnu++11 \
	-fprofile-arcs -ftest-coverage

TESTS = tests/test_%.cpp
TEST_OBJ = $(TESTS:.cpp=.o)

TEST_DEPENDENCIES = $(patsubst %, $(TEST_OBJ), linkedlist deque) 


all_tests: $(TEST_DEPENDENCIES) runtests.o exceptions.o
	$(CXX) -o all_tests $(TEST_DEPENDENCIES) exceptions.o runtests.o \
		$(LINKERS)

main : main.o exceptions.o
	$(CXX) -o main main.o exceptions.o $(LINKERS)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

runtests.o: runtests.cpp
	$(CXX) $(CXXFLAGS) -c runtests.cpp

# tests/test_%.o: tests/test_%.cpp
# 	$(CXX) $(CXXFLAGS) -c test_%.cpp
# 	$(info test_%)

test_linkedlist.o: test_linkedlist.cpp linkedlist.hpp
	$(CXX) $(CXXFLAGS) -c test_linkedlist.cpp

test_deque.o: test_deque.cpp deque.hpp
	$(CXX) $(CXXFLAGS) -c test_deque.cpp

exceptions.o: exceptions.cpp exceptions.hpp
	$(CXX) $(CXXFLAGS) -c exceptions.cpp


clean:
	FILES := $(wildcard *.o *.exe *.out *.gcno) \
		$(wildcard tests/*.o tests/*.gcno)
	$(foreach file,$(FILES),$(REMOVE) file)

commit:
	git commit -a -m "$m"
	git push origin master
