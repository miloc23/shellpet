# Shell Pet
A pet for your shell.

Mainly written as an exercise to learn about Unix Domain Sockets

## Design
The pet is just a struct that has information about the pet.
We send commands from the client to the server and then we get a response back.
What commands do we want?
We also want the server to be a daemon process that isn't connected to the terminal.

## Commands

init
: Creates a new pet with some information

get
: Retrives the current pet and prints it out

save
: Saves a pet to disk

load
: Loads a pet from disk

exit
: exits the server process
