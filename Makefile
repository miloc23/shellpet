.PHONY all: server client

server: server.c helpers.c helpers.h
	gcc server.c helpers.c -o server

client: client.c helpers.c helpers.h
	gcc client.c helpers.c -o client

