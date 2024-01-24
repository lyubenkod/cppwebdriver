all: build 
	clear
	./main

run: main
	clear
	./main

build: main.cpp
	bear -- g++ main.cpp -o main -lcurl -ljsoncpp -Wall -pedantic
