CC_FLAGS=-std=c++11 -g
LD_FLAGS=-lboost_system
CXX=-I/usr/include/cxxtest

TST_SRC=$(wildcard tests/*.h)
TST_FILES=$(patsubst tests/%.h,bin/tests/%.cpp,$(TST_SRC))

CPP_FILES=$(wildcard src/$(1)/*.cpp)
OBJ_FILES=$(patsubst src/%.cpp,bin/%.o,$(call CPP_FILES,$(1)))

all: test.exe server.exe client.exe

server.exe: $(call OBJ_FILES,protocol) $(call OBJ_FILES,server)
	g++ $(LD_FLAGS) -o $@ $^

client.exe: $(call OBJ_FILES,protocol) $(call OBJ_FILES,client) 
	g++ $(LD_FLAGS) -o $@ $^

run_tests.exe: $(TST_FILES) bin/server/IntervalSleeper.o
	cxxtestgen --root --error-printer -o bin/tests/runner.cpp
	g++ $(CC_FLAGS) $(LD_FLAGS) -o $@ bin/tests/runner.cpp $^

bin/%.o: src/%.cpp
	mkdir -p $(dir $@)
	g++ $(CC_FLAGS) -c -o $@ $<


bin/tests/%.o: bin/tests/%.cpp
	g++ $(CC_FLAGS) $(CXX) -c -o $@ $<

bin/tests/%.cpp: tests/%.h
	mkdir -p bin/tests
	cxxtestgen --part --error-printer -o $@  $<

.PHONY: clean
clean:
	rm -rf bin
	rm -f *.exe

#rebuild-lib:
#	lib/boost_1_55_0/b2 -a	#tar låååång tid
