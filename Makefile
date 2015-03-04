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
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
    	# Must be linked for gtest on linux machines, possibly OSX
        TEST_LINK = -lpthread
    endif
    REMOVE := rm -f
else
    REMOVE := del
endif

# Flags to ensure proper compilation
CXXFLAGS := -g -Wall -Werror -Wextra -pedantic -std=gnu++11
# Flags necessary to run gcov
COVERAGE := -fprofile-arcs -ftest-coverage
# Libraries to link for gtest
TEST_LINK += -lgtest -fprofile-arcs

# Allows me to minimize code repetition when compiling source files
TO_TEST := deque linkedlist #mergesort
TESTS = $(foreach file, $(TO_TEST), tests/test_$(file).cpp)
TEST_OBJ = $(patsubst %.cpp, obj/%.o, $(patsubst tests/%.cpp, %.cpp, $(TESTS)))

# Other things that need to be compiled
_OTHERS := exceptions runtests #mergesort
OTHERS := $(foreach file, $(_OTHERS), $(file).cpp)
OTHER_OBJ := $(patsubst %.cpp, obj/%.o, $(OTHERS))

tests: $(TEST_OBJ) $(OTHER_OBJ)
	$(CXX) -o all_tests $(TEST_OBJ) $(OTHER_OBJ) $(TEST_LINK)

obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(COVERAGE) -c -o $@ $< 

# runtests.o: runtests.cpp
# 	$(CXX) $(CXXFLAGS) $(COVERAGE) -c runtests.cpp -o obj/runtests.o

# exceptions.o: exceptions.cpp
# 	$(CXX) $(CXXFLAGS) $(COVERAGE) -c exceptions.cpp -o obj/exceptions.o

clean:
	rm -f $(wildcard *.out *.exe obj/*) all_tests
