#include "elevator.h"
#include "scheduler.h"

#include <cassert>
#include <iostream>

void testElevatorMoveUp() {
    Elevator elevator("test1", 1);
    elevator.move(1, 5);

    assert(elevator.getCurrentFloor() == 5);
    assert(elevator.getDirection() == Direction::IDLE);
    std::cout << "Test elevator move up passed!\n\n";
}

void testElevatorMoveDown() {
    Elevator elevator("test2", 8);
    elevator.move(8, 3);

    assert(elevator.getCurrentFloor() == 3);
    assert(elevator.getDirection() == Direction::IDLE);
    std::cout << "Test elevator move down passed!\n\n";
}

void testElevatorSameFloor() {
    Elevator elevator("test3", 5);
    elevator.move(5, 5);

    assert(elevator.getCurrentFloor() == 5);
    assert(elevator.getDirection() == Direction::IDLE);
    std::cout << "Test elevator stay at the same floor passed!\n\n";
}

void testSchedulerChooseCloserElevator() {
    Elevator elevator1("elevator1", 1);
    Elevator elevator2("elevator2", 10);

    Elevator& selectedElevator = Scheduler::chooseElevator(elevator1, elevator2, 8);

    assert(selectedElevator.getName() == "elevator2");
    std::cout << "Test scheduler choose the closer elevator passed!\n\n";
}

int main() {
    testElevatorMoveUp();
    testElevatorMoveDown();
    testElevatorSameFloor();
    testSchedulerChooseCloserElevator();

    std::cout << "All tests passed!\n";

    return 0;
}