# Makefile for the socket programming example
#

server_objects = ServerSocket.o Socket.o server_main.o

all : server

server: $(server_objects)
	g++ -std=c++11 -o server $(server_objects)

Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
server_main: server_main.cpp

clean:
	rm -f *.o simple_server
