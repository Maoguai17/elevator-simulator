CXX = g++
CXXFLAGS = -Wall -std=c++11

SRC = src

all: client server elevator_simulator test

client: $(SRC)/client.cpp
	$(CXX) $(CXXFLAGS) $(SRC)/client.cpp -o client

server: $(SRC)/server.cpp $(SRC)/elevator.cpp $(SRC)/scheduler.cpp
	$(CXX) $(CXXFLAGS) $(SRC)/server.cpp $(SRC)/elevator.cpp $(SRC)/scheduler.cpp -o server

elevator_simulator: $(SRC)/main.cpp $(SRC)/elevator.cpp $(SRC)/scheduler.cpp
	$(CXX) $(CXXFLAGS) $(SRC)/main.cpp $(SRC)/elevator.cpp $(SRC)/scheduler.cpp -o elevator_simulator

test: $(SRC)/test.cpp $(SRC)/elevator.cpp $(SRC)/scheduler.cpp
	$(CXX) $(CXXFLAGS) $(SRC)/test.cpp $(SRC)/elevator.cpp $(SRC)/scheduler.cpp -o test

clean:
	rm -f client server elevator_simulator test
