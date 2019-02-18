CXX := /usr/bin/g++
CXXFLAGS := -O2 -lm -std=c++14 -Wall -Wshadow -W
INCLUDE := ./src/include

all: bin/Solver

bin/digit.o: src/digit.cpp src/include/digit.h src/include/config.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o bin/digit.o src/digit.cpp

bin/face.o: src/face.cpp src/include/face.h src/include/config.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o bin/face.o src/face.cpp
	
bin/cube.o: src/cube.cpp src/include/cube.h src/include/config.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o bin/cube.o src/cube.cpp

bin/solve.o: src/solve.cpp src/include/solve.h src/include/config.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o bin/solve.o src/solve.cpp

bin/gen.o: src/gen.cpp src/include/gen.h src/include/config.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o bin/gen.o src/gen.cpp

bin/main.o: src/main.cpp src/include/config.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o bin/main.o src/main.cpp

bin/Solver: bin/digit.o bin/face.o bin/cube.o bin/main.o bin/gen.o bin/solve.o
	$(CXX) $(CXXFLAGS) -o bin/Solver bin/main.o bin/cube.o bin/digit.o bin/face.o bin/solve.o bin/gen.o


clean:
	@rm bin/*.o bin/Solver

.PHONY: all clean
