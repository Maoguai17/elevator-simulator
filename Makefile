CXX = g++
CXXFLAGS = -Wall -std=c++11

all: client server elevator_simulator test

client: client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o client

server: server.cpp elevator.cpp scheduler.cpp
	$(CXX) $(CXXFLAGS) server.cpp elevator.cpp scheduler.cpp -o server

elevator_simulator: main.cpp elevator.cpp scheduler.cpp
	$(CXX) $(CXXFLAGS) main.cpp elevator.cpp scheduler.cpp -o elevator_simulator

test: test.cpp elevator.cpp scheduler.cpp
	$(CXX) $(CXXFLAGS) test.cpp elevator.cpp scheduler.cpp -o test

clean:
	rm -f client server elevator_simulator test
