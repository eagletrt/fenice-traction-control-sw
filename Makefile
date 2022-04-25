CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm
SRC_DIR := ./src
BUILD_DIR := ./build
.PHONY: all clean


# --------------------------------- Variables ----------------------------------

# Target executables (main program and model servers)
ALL_TARGETS := fenice-traction-control server-sc server-tv server-all server-no

# Matlab models base directory
MATLAB_ROOT := ./matlab-model-code

# Slip-Control model source
MODEL_SC_DIR   := $(MATLAB_ROOT)/Slip_ert_rtw
MODEL_SC_SRCS  := $(addprefix $(MODEL_SC_DIR)/,Slip.c Slip_data.c)

# Torque-Vectoring model source
MODEL_TV_DIR   := $(MATLAB_ROOT)/Torque_ert_rtw
MODEL_TV_SRCS  := $(addprefix $(MODEL_TV_DIR)/,Torque.c Torque_data.c)

# Complete-Control model source
MODEL_ALL_DIR  := $(MATLAB_ROOT)/All0_ert_rtw
MODEL_ALL_SRCS := $(addprefix $(MODEL_ALL_DIR)/,All0.c All0_data.c)

# No-Control model source
MODEL_NO_DIR   := $(MATLAB_ROOT)/No_ert_rtw
MODEL_NO_SRCS  := $(addprefix $(MODEL_NO_DIR)/,No.c No_data.c)


# ------------------------------- Build targets --------------------------------

# Build target for the slip-control server
$(BUILD_DIR)/server-sc: $(SRC_DIR)/server-sc-main.c $(MODEL_SC_SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(MATLAB_ROOT) -I$(MODEL_SC_DIR) $^ -o $@ $(LDFLAGS)

all: $(addprefix $(BUILD_DIR)/,$(ALL_TARGETS))
	;

clean:
	rm -r $(BUILD_DIR)