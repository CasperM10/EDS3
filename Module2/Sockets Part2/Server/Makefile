CXX=g++
CXXFLAGS=-Wall -Werror -Wextra -pedantic
SOURCES=mainServer.cpp Server.cpp
OBJECTS=mainServer.o Server.o
TARGET=Server

.PHONY: all clean

$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	@rm -f *.o *~ 
