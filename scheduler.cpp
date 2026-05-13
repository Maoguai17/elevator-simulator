#include "scheduler.h"

#include <cstdlib>

Elevator& Scheduler::chooseElevator(
    Elevator& elevator1, 
    Elevator& elevator2,
    int requestFloor
) {
    int distance1 = std::abs(elevator1.getCurrentFloor() - requestFloor);
    int distance2 = std::abs(elevator2.getCurrentFloor() - requestFloor);

    if (distance1 <= distance2) {
        return elevator1;
    }

    return elevator2;
}