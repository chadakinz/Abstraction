CXX       := g++
CXXFLAGS  := -std=c++20 -O3 -Wall -Wextra -pedantic

# Include path so you can do: #include <phevaluator/card.h>
INCLUDES  := -Iinclude

# Library path + libraries
LIBDIR    := -Llib
LIBS      := -lpheval -lpheval5 -lpheval6 -lpheval7

TARGET    := abstraction
SRCS      := river_abstraction.cpp hand_groups.cpp
OBJS      := $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LIBDIR) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)