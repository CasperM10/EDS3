CXX=g++
CXXFLAGS=-Wall -Werror -Wextra -pedantic
all: client server

client: client.cpp
	$(CXX) -o client client.cpp

server: server.cpp
	$(CXX) -o server server.cpp

clean:
	@rm -f src/*.o *~ 