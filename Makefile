CC_FLAGS=-std=c++11 -Wall -g
LD_FLAGS=null

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,bin/%.o,$(CPP_FILES))

server.exe: $(OBJ_FILES)
	g++ -o $@ $^

bin/%.o: src/%.cpp
	mkdir -p bin
	g++ $(CC_FLAGS) -c -o $@ $<

#VectorTest.o: VectorTest.cpp
#	g++ $(flags) -o $@ $<

#VectorTest.cpp: VectorTest.h
#	cxxtestgen --error-printer -o $@ $<



.PHONY: clean
clean:
	rm -rf bin
	rm -f *.exe
