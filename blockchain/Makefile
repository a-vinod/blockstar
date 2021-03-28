SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build

SOURCES = $(SRC_DIR)/blockchain_push.cpp $(SRC_DIR)/block.cpp $(SRC_DIR)/transaction.cpp
OBJS = $(BUILD_DIR)/blockchain_push.o $(BUILD_DIR)/block.o $(BUILD_DIR)/transaction.o

OUT	= blockchain_pusher
CC = g++
CXXFLAGS = -g -c -Wall -Iinclude
LFLAGS = -Lusr/lib -lmysqlcppconn

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(BIN_DIR)/$(OUT) $(LFLAGS)

$(OBJS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(BIN_DIR)/$(OUT)

