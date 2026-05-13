#include "elevator.h"

#include <chrono>
#include <iostream>
#include <thread>

// Initialize
Elevator::Elevator(const std::string& name, int current_floor) :
    name(name), current_floor(current_floor), direction(Direction::IDLE) {}

// Get the name of the elevator
std::string Elevator::getName() const {
    return name;
}

// Get the current floor of the elevator
int Elevator::getCurrentFloor() const {
    return current_floor;
}

// Get the status of the elevator
Direction Elevator::getDirection() const {
    return direction;
}

// Display the current floor of the elevator
void Elevator::displayFloor() const {
    std::cout << name << " is now on floor " << current_floor << ".\n";
}

// Display the current status of the elevator
void Elevator::displayStatus() const {
    std::cout << name << " {\tFloor : " << current_floor << "\tDirection: ";

    if (direction == Direction::UP) {
        std::cout << "Up\t}\n";
    }         
    else if (direction == Direction::DOWN) {
        std::cout << "Down\t}\n";
    }
    else {
        std::cout << "Idle\t}\n";
    }
}

// Move the elevator from current to the floor
void Elevator::move(int current, int floor) {
    current_floor = current;

    // Don't need to move
    if (current_floor == floor) {
        direction = Direction::IDLE;
        std::cout << name << " is already on floor " << floor << ".\n";
        return;
    }

    // Need to move the elevator
    // Going up
    if (current_floor < floor) { 
        direction = Direction::UP;
        std::cout << name << " is going up.\n";
    }
    // Going down
    else {
        direction = Direction::DOWN;
        std::cout << name << " is going down.\n";
    }

    while (current_floor != floor) {
        if (direction == Direction::UP) {
            current_floor++;
        } 
        else {
            current_floor--;
        }   

        displayFloor();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    direction = Direction::IDLE;
    std::cout << name << " has arrived at floor " << floor << ".\n";
}