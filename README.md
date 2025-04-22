# C++ TCP Client–Server Demo

A minimal pair of console programs demonstrating a basic TCP client and server in C++11 using POSIX sockets.

---

## Table of Contents

- [Overview](#overview)  
- [Prerequisites](#prerequisites)  
- [Building](#building)  
- [Running the Server](#running-the-server)  
- [Running the Client](#running-the-client)  
- [Code Files](#code-files)  
- [How It Works](#how-it-works)  

---

## Overview

This project contains two standalone programs:

- **server.cpp**: Listens on TCP port 8080, accepts one client connection, receives a message, prints it, and quits. :contentReference[oaicite:0]{index=0}&#8203;:contentReference[oaicite:1]{index=1}  
- **client.cpp**: Connects to `localhost:8080`, sends a short “Hello server!” message, and exits. :contentReference[oaicite:2]{index=2}&#8203;:contentReference[oaicite:3]{index=3}

Use this as a learning exercise in socket programming, connection handling, and basic network I/O in C++.

---

## Prerequisites

- A Unix‑like OS (Linux, macOS) with POSIX sockets  
- A C++11‑capable compiler (`g++`, `clang++`)  
- Standard build tools (`make` or plain shell)  

---

## Building

Compile each source file into its own executable:

```bash
# From project root
g++ -std=c++11 server.cpp -o server
g++ -std=c++11 client.cpp -o client
```

---

## Running the Server

1. Start the server (listening on port 8080):

```bash
./server
```
2. You should see:
```bash
Server is listening on port 8080...
```
3. The server will block in `accept()` until a client connects.

---

## Running the Client

1. In a separate terminal (while the server is running):

```bash
./client
```
2. Expected output in the client terminal:

```pgsql
Connected to server on port 8080.
Sent message: Hello server!
```

3. Meanwhile, the server terminal will print:

```arduino
Client connected!
Message from client: Hello server!
```

---

## Code Files

- server.cpp:

  - Creates a listening socket on `INADDR_ANY:8080`

  - Binds, listens (backlog 5), accepts one client

  - Receives up to 1023 bytes and prints the message

  - Closes client and server sockets ​

- client.cpp:

  - Creates a socket and connects to `127.0.0.1:8080`

  - Sends the null‑terminated string `"Hello server!"`

  - Closes the socket
 
---
 
## How It Works

1. Socket Creation: Both programs call socket(AF_INET, SOCK_STREAM, 0).

2. Address Setup: Fill a sockaddr_in struct with IPv4, port 8080, and INADDR_ANY.

3. Server Bind & Listen:

  - bind() associates the socket with the local port.

  - listen() marks it passive for incoming connections.

4. Client Connect: connect() establishes a TCP session with the server.

5. Data Transfer:

  - Client uses send().

  - Server uses recv().

6. Cleanup: Both programs call close() on socket descriptors.

