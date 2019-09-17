CXX=g++
CXXFLAGS= -Wall -Werror -Wextra -pedantic -fPIC
TARGET=HelloWorld
OBJECTS = main.o HelloLib.o

$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^

	@ar -cq staticlib.a HelloLib.o
	@g++ -o StaticExecutable main.cpp staticlib.a
	
	@g++ -shared -o libshared.so HelloLib.o
	@g++ -Wall -o SharedExecutable main.cpp libshared.so

#Onderstaande command nodig om de ./SharedExecutable te laten werken.
	@export LD_LIBRARY_PATH=/home/student/Documents/Module1/Part3:$LD_LIBRARY_PATH

clean:
		@$(RM) *.o *.so *.a *.out
