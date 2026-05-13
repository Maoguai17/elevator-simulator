#include "elevator.h"
#include "scheduler.h"

#include <arpa/inet.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#define MAXLINE 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Server usage: " << argv[0] << " [port number].\n";
        exit(-1);
    }

    Elevator elevator1("elevator1", 1);
    Elevator elevator2("elevator2", 10);

    int                 server_fd, client_fd;
    char                buff[MAXLINE], input[MAXLINE];
    socklen_t           len;
    struct sockaddr_in  serverAddr, clientAddr;

    /* --- Socket --- */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (server_fd < 0) {
        perror("Socket Error.");
        exit(-1);
    }

    /* --- Set Server --- */
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(atoi(argv[1]));

    /* --- Bind --- */
    if (bind(server_fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind Error.");
        exit(-1);
    }

    /* --- Listen --- */
    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("Listen Error.");
        exit(-1);
    }

    std::cout << "Elevator server started on port " << argv[1] << "\n";
    
    while (true) {
        std::memset(input, 0, sizeof(input));

        /* --- Accept --- */
        len = sizeof(clientAddr);
        client_fd = accept(server_fd, (struct sockaddr*) &clientAddr, &len);

        /* --- Read I */
        ssize_t checkSize = read(client_fd, input, MAXLINE - 1);
        if (checkSize <= 0) {
            std::cout << "Read Error.\n";
            close(client_fd);
            continue;
        }
        input[checkSize] = '\0';

        int userCurrentFloor, userDesiredFloor;
        std::stringstream ss(input);
        ss >> userCurrentFloor >> userDesiredFloor;

        std::cout << "\nReceived request: From the " << userCurrentFloor 
                  << " to the " << userDesiredFloor << " floor.\n"; 
        
        Elevator& selectedElevator = Scheduler::chooseElevator(elevator1, elevator2, userCurrentFloor);

        snprintf(buff, sizeof(buff), "%s is selected.\n", selectedElevator.getName().c_str());
        write(client_fd, buff, strlen(buff));

        selectedElevator.move(selectedElevator.getCurrentFloor(), userCurrentFloor);
        snprintf(buff, sizeof(buff), "Please enter the %s.\n", selectedElevator.getName().c_str());        
        write(client_fd, buff, strlen(buff));

        selectedElevator.move(userCurrentFloor, userDesiredFloor);
        snprintf(buff, sizeof(buff), "You have arrived at floor %d.\n", userDesiredFloor);        
        write(client_fd, buff, strlen(buff));

        close(client_fd);

    }

    close(server_fd);

    return 0;
}