CXX = g++

CXXFLAGS  := -std=c++20 -Wall -g

INCLUDES  := -I../turn_abstraction/include -I../include -I../third_party

LIBDIR := -L../lib

LIBS := -lpheval -lCatch2Main -lCatch2

DEPENDED_FILES := ../turn_abstraction/src/canonical.o ../turn_abstraction/src/get_equity_distribution.o

TESTS := test_canonical.o test_get_equity_distribution.o

RUN_TESTS := run_test

all: $(RUN_TESTS)

$(RUN_TESTS): $(DEPENDED_FILES) $(TESTS)
	$(CXX) $(CXXFLAGS) $(TESTS) $(DEPENDED_FILES) $(LIBS) $(LIBDIR) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

../turn_abstraction/src/%.o: ../turn_abstraction/src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(DEPENDED_FILES) $(TESTS) $(RUN_TESTS)