# Because i like it nice and tidy

CC_FLAGS=-std=c++11 -g -I $(wildcard lib/*)
LD_FLAGS=-lboost_system

CPP_FILES=$(wildcard src/$(1)/*.cpp)
OBJ_FILES=$(patsubst src/%.cpp,bin/%.o,$(call CPP_FILES,$(1)))

all: client.exe server.exe

server.exe: $(call OBJ_FILES,protocol) $(call OBJ_FILES,server)
	g++ $(LD_FLAGS) -o $@ $^

client.exe: $(call OBJ_FILES,protocol) $(call OBJ_FILES,client) 
	g++ $(LD_FLAGS) -o $@ $^

bin/%.o: src/%.cpp
	mkdir -p $(dir $@)
	g++ $(CC_FLAGS) -c -o $@ $<

#VectorTest.cpp: VectorTest.h
#	cxxtestgen --error-printer -o $@ $<



.PHONY: clean
clean:
	rm -rf bin
	rm -f *.exe

rebuild-lib:
	lib/boost_1_55_0/b2 -a	#tar låååång tid
