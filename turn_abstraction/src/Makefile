CXX = g++
CXXFLAGS  := -std=c++20 -Wall -g

INCLUDES  := -I../include -I../../include

LIBDIR= -L../../lib

LIBS = -lpheval -lpheval5 -lpheval6 -lpheval7

TEST_FILES = get_equity_distribution.o

TEST_EQUITY_DIST := get_equity_dist

TURN_ABSTRACTION := turn_abstraction

ALL_FILES =canonical.o get_equity_distribution.o main.o

CANON := cannonical

CANON_FILES := canonical.o get_equity_distribution.o


all: $(TURN_ABSTRACTION)

test_canon: $(CANON)

cannonical: $(CANON_FILES)
	$(CXX) $(CXXFLAGS) $(CANON_FILES) -o $@ $(LIBDIR) $(LIBS)

turn_abstraction: $(ALL_FILES)
	$(CXX) $(CXXFLAGS) $(ALL_FILES) -o $@ $(LIBDIR) $(LIBS)

test_equity: $(TEST_EQUITY_DIST)

$(TEST_EQUITY_DIST): $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(TEST_FILES) -o $@ $(LIBDIR) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean_equity:
	rm -f $(TEST_FILES) $(TEST_EQUITY_DIST)

clean_canon:
	rm -f $(CANON_FILES) $(CANON)

clean:
	 rm -f $(ALL_FILES) $(TURN_ABSTRACTION)