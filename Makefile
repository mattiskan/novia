CXX=g++
CPPFLAGS=-std=c++11 -g -Wall -Wfatal-errors
LDFLAGS=

ALL_SRC=$(wildcard src/*.cpp)
SRC=$(filter-out src/main_%, $(ALL_SRC))
MAINS=$(filter     src/main_%, $(ALL_SRC))
OBJ=$(patsubst src/%.cpp,bin/%.o,$(SRC))


TST=$(wildcard tests/*.h)
TSTSRC=$(patsubst tests/%.h,bin/%.cpp,$(TST))
TSTOBJ=$(patsubst %.cpp,%.o,$(TSTSRC))

test: bin/test.exe
	$<
bin/test.exe: bin/test_runner.o $(TSTOBJ) $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

# ex: "make main_hello_world"
main_%: bin/main_%.exe
	$<
bin/main_%.exe: src/main_%.cpp $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

depend: bin/depend
bin/depend: $(ALL_SRC) $(TST)
	mkdir -p bin
	$(CXX) $(CPPFLAGS) src/*.cpp tests/*.h -MM | sed 's%^.*:%bin/&%'>bin/depend

bin/test_runner.cpp:
	cxxtestgen --root --error-printer -o bin/test_runner.cpp
bin/test_%.cpp: tests/test_%.h
	cxxtestgen --part --error-printer -o $@ $^
bin/test_%.o: bin/test_%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<


bin/%.o: src/%.cpp $(wildcard src/%.h)
	$(CXX) $(CPPFLAGS) -c -o $@ $<
clean:
	rm -rf bin/
	rm -f *.exe


.PHONY: test # test directory is not 'make test'
.SECONDARY: $(wildcard bin/%.exe) # keep .exe files until outdated


include bin/depend
