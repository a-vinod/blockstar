OBJS	= blockchain_push.o block.o transaction.o
SOURCE	= blockchain_push.cpp block.cpp transaction.cpp
HEADER	= block.h transaction.h
OUT	= blockchain_pusher
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

blockchain_push.o: blockchain_push.cpp
	$(CC) $(FLAGS) blockchain_push.cpp 

block.o: block.cpp
	$(CC) $(FLAGS) block.cpp 

transaction.o: transaction.cpp
	$(CC) $(FLAGS) transaction.cpp 


clean:
	rm -f $(OBJS) $(OUT)

