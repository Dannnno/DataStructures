# Directories to search for files
VPATH = . ./algorithms ./tests ./structures ./obj ./obj/tests

# This is because travis sets this as an environment variable, but my
# machine doesn't afaik
ifndef CXX
    # Checking if either of these commands exists
    CLANG := $(shell clang++ --version)
    MINGW := $(shell mingw32-g++ --version)

    # Picking a compiler depending on what is available
    ifdef CLANG:
        CXX = clang++
    else
        ifdef MINGW
            CXX = mingw32-g++
        else
            CXX = g++
        endif
    endif
endif

# Adapted from http://stackoverflow.com/a/12099167/3076272
# Handles specific command differences between operating systems
ifneq ($(OS), Windows_NT)
    # The uname command doesn't exist on most Windows machines
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        # Must be linked for gtest on linux machines, possibly OSX
        TEST_LINK = -lpthread
    endif
endif

# Flags to ensure proper compilation
CXXFLAGS := -g -Wall -Wextra -Werror -pedantic -std=gnu++11 -O2
# Libraries to link for gtest and coverage
TEST_LINK += -lgtest

# Allows me to minimize code repetition when compiling source files
TO_TEST := linkedlist deque nonhashmap # mergesort
TESTS = $(foreach file, $(TO_TEST), tests/test_$(file).cpp)
TEST_OBJ = $(patsubst %.cpp, obj/%.o, $(patsubst tests/%.cpp, %.cpp, $(TESTS)))

# Other things that need to be compiled
_OTHERS := runtests
OTHERS := $(foreach file, $(_OTHERS), $(file).cpp)
OTHER_OBJ := $(patsubst %.cpp, obj/%.o, $(OTHERS))

tests: exceptions $(TEST_OBJ) $(OTHER_OBJ)
	$(CXX) -o a_tests $(TEST_OBJ) $(OTHER_OBJ) $(TEST_LINK)

coverage: cover tests

cover:
    # Flags necessary to run gcov
	COVERAGE += -fprofile-arcs -ftest-coverage
	TEST_LINK += -fprofile-arcs

obj/test_%.o: test_%.cpp %.hpp _%.hpp _%_iterator.hpp
    # The $@ variable binds to the target obj/%.o
    # The $< variable binds to the dependencies %.cpp
	$(CXX) $(CXXFLAGS) $(COVERAGE) -c -o $@ $< 

exceptions: exceptions.hpp _exceptions.hpp

obj/runtests.o: runtests.cpp
	$(CXX) $(CXXFLAGS) $(COVERAGE) -c -o obj/runtests.o runtests.cpp

clean:
	rm -rf *.out *.exe *.gcno *.o *.gcda all_tests
