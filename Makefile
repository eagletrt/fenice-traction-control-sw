CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm

TARGET_EXEC := fenice-traction-control
BUILD_DIR := ./build

# Directories from which source files are to be collected
SRC_DIRS := ./matlab-model-code

# Source dirs need to be passed to GCC as -I flags for it to find header files
INC_FLAGS := $(addprefix -I,$(shell find $(SRC_DIRS) -type d -not -path '*/html/*'))
CFLAGS := $(INC_FLAGS)

# Find all .c files in the source directories
SRCS := $(shell find $(SRC_DIRS) -name '*.c' -not -name 'ert_main.c')

# Turn each %.c file into ./build/%.o
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)


# Final build step of the target executable
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build sources: pattern rule to compile every .c into a .o
$(BUILD_DIR)/%.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: all clean
all: $(BUILD_DIR)/$(TARGET_EXEC)
clean:
	rm -r $(BUILD_DIR)
