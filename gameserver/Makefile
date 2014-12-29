CPPFLAGS=-std=c++11 -g -Wall -Wfatal-errors -fexceptions
INCLUDES=-Iincludes/
LDFLAGS+=-lboost_system -pthread

LIB_OBJS+=bin/json.o

ALL_SRC=$(wildcard src/*.cpp)
ALL_SRC+=$(wildcard src/protocol/*.cpp)
SRC=$(filter-out src/_%, $(ALL_SRC))
MAINS=$(filter     src/main_%, $(ALL_SRC))
OBJ=$(patsubst src/%.cpp,bin/%.o,$(SRC))
OBJ+=$(LIB_OBJS)


TST=$(wildcard tests/*.h)
TSTSRC=$(patsubst tests/%.h,bin/%.cpp,$(TST))
TSTOBJ=$(patsubst %.cpp,%.o,$(TSTSRC))

test: bin/test.exe
	$<
start: _main_server

bin/test.exe: bin/test_runner.o $(TSTOBJ) $(OBJ) bin/_link_mocks.o
	g++ -o $@ $^ $(LDFLAGS)
# ex: "make main_hello_world"
start_%: bin/_main_%.exe
	$<
bin/_main_%.exe: bin/_main_%.o $(OBJ) bin/_link_real.o
	g++ -o $@ $^ $(LDFLAGS)

depend: bin/depend
bin/depend: $(ALL_SRC) $(TST)
	mkdir -p bin/protocol
	g++ $(CPPFLAGS) src/*.cpp tests/*.h -MM | sed 's%^.*:%bin/&%'>bin/depend

bin/test_runner.cpp:
	cxxtestgen --root --error-printer -o bin/test_runner.cpp
bin/test_%.cpp: tests/test_%.h
	cxxtestgen --part --error-printer -o $@ $^
bin/test_%.o: bin/test_%.cpp
	g++ $(CPPFLAGS) $(INCLUDES) -c -o $@ $<

bin/%.o: src/%.cpp $(wildcard src/%.h)
	g++ $(CPPFLAGS) $(INCLUDES) -c -o $@ $<


# make jsoncpp:
bin/json.o: includes/jsoncpp/json.cpp
	g++ $(CPPFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -rf bin/
	rm -f *.exe


.PHONY: test # test directory is not 'make test'
.SECONDARY: $(wildcard bin/%.exe) # keep .exe files until outdated


include bin/depend
