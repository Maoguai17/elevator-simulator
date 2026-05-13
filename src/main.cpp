#include "elevator.h"
#include "scheduler.h"

#include <iostream>
#include <limits>
#include <string>

int getFloor(const std::string& prompt) {
    int floor;

    while (true) {
        std::cout << prompt;
        std::cin >> floor;

        // Invalid type
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number!\n";
            continue;
        }

        // Invalid number
        if (floor < 1 || floor > 10) {
            std::cout << "Please enter a number between 1 and 10!\n";
            continue;
        }

        return floor;
    }
}

int main() {
    // Initalize two elevators
    Elevator elevator1("elevator1", 1);
    Elevator elevator2("elevator2", 10);

    while (true) {
        std::cout << "\n----------------------------------------\n";
        std::cout << "Current elevator status: \n";
        elevator1.displayStatus();
        elevator2.displayStatus();
        std::cout << "----------------------------------------\n";

        int userCurrentFloor = getFloor("Please enter your current floor: ");
        int userDesiredFloor = getFloor("Please enter your desired floor: ");

        Elevator& selectedElevator = Scheduler::chooseElevator(elevator1, elevator2, userCurrentFloor);

        std::cout << "\n" << selectedElevator.getName() << " is selected.\n";

        selectedElevator.move(selectedElevator.getCurrentFloor(), userCurrentFloor);
        std::cout << "\nPlease enter the " << selectedElevator.getName() << ".\n\n";
        
        selectedElevator.move(userCurrentFloor, userDesiredFloor);
        std::cout << "\nYou have arrived at floor " << userDesiredFloor << ".\n";

        std::cout << "\n----------------------------------------\n";
        std::cout << "Final elevator status: \n";
        elevator1.displayStatus();
        elevator2.displayStatus();
        std::cout << "----------------------------------------\n";


        char c;
        std::cout << "\nDo you want to continue? (y/n): ";
        std::cin >> c;
        
        while (true) {
            if (c == 'y' || c == 'Y' || c == 'n' || c == 'N') {
                break;
            } 
            else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nPlease enter \"y\" or \"n\"!!!\n"; 
                std::cin >> c;
            }
        }
        
        if (c == 'n' || c == 'N') {
            break;
        }
    }

    return 0;
}