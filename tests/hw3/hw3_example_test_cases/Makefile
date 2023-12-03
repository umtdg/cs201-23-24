######################################################################
# Makefile for testing CS 201 homework assignments
######################################################################

######################################################################
# Test code base
NUM_TESTS = 5
BASE = $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
SRC = $(addprefix test,$(shell seq 1 $(NUM_TESTS)))
######################################################################

# Settings
CXX = g++
CXX_FLAGS = -Wall $(INC_FLAGS) $(LIB_FLAGS)
INC_FLAGS = -I. -I$(BASE)
LIB_FLAGS =
LIBS = -lgtest -lpthread

# Help
help:
	@echo Type \"make build\", followed by \"make tests\"
	@echo Type \"make clean\" to cleanup the built executables

# Target for building the student code
build: $(SRC)

# Target for testing the student code
tests: build
	@for x in $(SRC); do \
		echo ============================== Start $$x ==============================; \
       		./$$x --gtest_color=yes; \
		echo ==============================  End $$x  ==============================; \
	done

# Target for cleanup
clean:
	$(RM) $(SRC)

# Test cases
test%: $(BASE)/test%.cpp
	$(CXX) $(CXX_FLAGS) -D BASE="\"$(BASE)\"" -o $@ $(BASE)/$@.cpp *.cpp $(LIBS)

