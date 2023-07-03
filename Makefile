BUILD_DIR   := ./build
INCLUDE_DIR := ./include
SRC_DIR     := ./src

objects = main.o odos.o srtf.o sint.o interface.o memory.o semaphore.o disk.o

all: output

output: $(objects)
	gcc $(BUILD_DIR)/main.o $(BUILD_DIR)/sint.o $(BUILD_DIR)/odos.o $(BUILD_DIR)/srtf.o $(BUILD_DIR)/memory.o $(BUILD_DIR)/interface.o $(BUILD_DIR)/semaphore.o -o $(BUILD_DIR)/output -pthread -lncurses


$(objects): %.o: $(SRC_DIR)/%.c
	gcc -c $^ -o $(BUILD_DIR)/$*.o -I $(INCLUDE_DIR)

run:
	$(BUILD_DIR)/output

clean:
	rm -r $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)
	
.PHONY: all run clean
