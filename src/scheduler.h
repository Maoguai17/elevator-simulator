#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "elevator.h"

class Scheduler {
public:
    static Elevator& chooseElevator(
        Elevator& elevator1,
        Elevator& elevator2,
        int requestFloor
    );
};

#endif