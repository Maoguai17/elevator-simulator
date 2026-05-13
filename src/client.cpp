#include <arpa/inet.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>

#define MAXLINE 1024

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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Client usage: " << argv[0] << " [port number].\n";
        exit(-1);
    }

    int                 sockfd;
    char                buff[MAXLINE], input[MAXLINE];
    struct sockaddr_in  serverAddr;

    /* --- Socket --- */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        perror("Socket Error.");
        exit(-1);
    }

    /* --- Set Server --- */
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[1]));

    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    /* --- Connect --- */
    if (connect(sockfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connect Error.");
        exit(-1);
    }

    int userCurrentFloor = getFloor("Please enter your current floor: ");
    int userDesiredFloor = getFloor("Please enter your desired floor: ");

    /* --- Send --- */
    std::memset(buff, 0, sizeof(buff));
    snprintf(buff, sizeof(buff), "%d %d", userCurrentFloor, userDesiredFloor);
    write(sockfd, buff, strlen(buff));

    /* --- Receive and Read--- */
    std::cout << "\nResponse from server:\n\n";
    while (true) {
        std::memset(input, 0, sizeof(input));

        ssize_t checkSize = read(sockfd, input, MAXLINE - 1);

        if (checkSize < 0) {
            std::cout << "Read Error.\n";
            close(sockfd);
            return -1;
        }

        // Server closed connection
        if (checkSize == 0) {
            break;
        }

        input[checkSize] = '\0';
        std::cout << input << "\n";
    }

    close(sockfd);
    
    return 0;
}