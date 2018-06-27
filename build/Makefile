CC = g++
SRC =  $(wildcard ../ConsoleApplication1/*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
DOBJ = $(patsubst %.cpp, %.og, $(SRC))
CXXFLAGS = -std=c++14 -Wall -pedantic
SFMLLIBS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDES = 
prog: $(OBJ)
	$(CC) -o $@ $(OBJ) $(OLVL) $(SFMLLIBS)

debug: $(DOBJ)
	$(CC) -g  -o $@ $(DOBJ) $(SFMLLIBS)

clean: 
	rm ../ConsoleApplication1/*.o ../ConsoleApplication1/*.og prog debug

%.og: %.cpp
	$(CC) $(CXXFLAGS)  -g -o $@  -c $<

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(OLVL) -c -o $@ $<
