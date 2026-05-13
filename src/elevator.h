#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <string>

enum class Direction {
    UP,
    DOWN,
    IDLE
};

class Elevator {
private:
    std::string name;
    int current_floor;
    Direction direction;

public:
    Elevator(const std::string& name, int current_floor);

    std::string getName() const;
    int getCurrentFloor() const;
    Direction getDirection() const;

    void displayFloor() const;
    void displayStatus() const;
    void move(int current, int floor); 
};

#endif