# Elevator Simulator

A client-server elevator simulation system using TCP socket programming in C++.

## Features

- TCP socket communication
- Elevator scheduling simulation
- Client-server architecture
- Input validation
- Multiple executable programs

## Build

Compile all programs:

```bash
make
```

Remove executables:

```bash
make clean
```

## Usage

Start the server:

```bash
./server 8080
```

Run the client:

```bash
./client 8080
```

Run the elevator simulator:

```bash
./elevator_simulator
```

Run tests:

```bash
./test
```

## Project Structure

```text
.
├── src
│   ├── client.cpp
│   ├── server.cpp
│   ├── elevator.cpp
│   ├── elevator.h
│   ├── scheduler.cpp
│   ├── scheduler.h
│   ├── main.cpp
│   └── test.cpp
├── Makefile
├── README.md
└── .gitignore
```

## Environment

- Language: C++
- Compiler: g++
- OS: Linux / macOS

## Notes

- The server must be started before the client.
- Executable files are ignored using `.gitignore`.
