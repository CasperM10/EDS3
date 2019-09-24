CXX=g++
CXXFLAGS=-Wall -Werror -Wextra -pedantic
SOURCES=mainClient.cpp Client.cpp
OBJECTS=mainClient.o Client.o
TARGET=Client

.PHONY: all clean

$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	@rm -f *.o *~ 
