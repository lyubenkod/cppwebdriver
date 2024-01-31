SRC = main.cpp driver.cpp
OBJ = $(SRC:.cpp = .o)
CFLAGS = -Wall -pedantic

all: build 
	./main

run: main
	./main

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

driver.o: driver.cpp
	g++ $(CFLAGS) -c driver.cpp

build: main.o driver.o
	bear -- g++ $(CFLAGS) -ljsoncpp -lcurl -o main $(OBJ) 

clean: *.o
	rm *.o
