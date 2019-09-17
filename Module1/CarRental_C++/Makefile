CXX=g++
CXXFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 -std=c++11 -Iproduct
SOURCES=$(wildcard src/*.cpp)
HEADERS=$(wildcard src/*.h)
OBJECTS=$(wildcard src/*.cpp):.cpp = .o
TARGET=CarRental

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) 
	@$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)

clean:
	@rm -f src/*.o *~ 
