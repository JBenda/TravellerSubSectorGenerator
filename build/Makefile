CC = g++
SRC =  $(wildcard ../ConsoleApplication1/*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
DOBJ = $(patsubst %.cpp, %.og, $(SRC))
CXXFLAGS = -std=c++14 -Wall -pedantic
INCLUDES = 
prog: $(OBJ)
	$(CC) -o $@ $(OBJ)

debug: $(DOBJ)
	$(CC) -g  -o $@ $(DOBJ)

clean: 
	rm *.o *.og prog debug

%.og: %.cpp
	$(CC) $(CXXFLAGS) -g -o $@  -c $<

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $<
