CC = gcc
CFLAGS_ALL = -g -Wall -Imicro-libs/logger
CFLAGS_MODELS := -fpic -shared
CFLAGS_MAIN := -ldl -Imicro-libs/ctrl-nwk-utils
LDFLAGS = -lm
BUILD_DIR := ./build
.PHONY: all clean

# --------------------------------- Variables ----------------------------------

# Target executables (main program and model servers)
ALL_TARGETS := fenice-traction-control test-models libctrl-ve.so libctrl-sc.so libctrl-tv.so libctrl-all.so libctrl-no.so

# Matlab models base directory
MATLAB_ROOT := ./fenice-vehicle-model/C_code

# Velocity Estimation model source
MODEL_VE_DIR   := $(MATLAB_ROOT)/Velocity_Estimation_ert_rtw
MODEL_VE_SRCS  := $(addprefix $(MODEL_VE_DIR)/, Velocity_Estimation.c Velocity_Estimation_data.c)

# Slip-Control model source
MODEL_SC_DIR   := $(MATLAB_ROOT)/Slip_ert_rtw
MODEL_SC_SRCS  := $(addprefix $(MODEL_SC_DIR)/, Slip.c Slip_data.c)

# Torque-Vectoring model source
MODEL_TV_DIR   := $(MATLAB_ROOT)/Torque_ert_rtw
MODEL_TV_SRCS  := $(addprefix $(MODEL_TV_DIR)/, Torque.c Torque_data.c)

# Complete-Control model source
MODEL_ALL_DIR  := $(MATLAB_ROOT)/All0_ert_rtw
MODEL_ALL_SRCS := $(addprefix $(MODEL_ALL_DIR)/, All0.c All0_data.c)

# No-Control model source
MODEL_NO_DIR   := $(MATLAB_ROOT)/No_ert_rtw
MODEL_NO_SRCS  := $(addprefix $(MODEL_NO_DIR)/, No.c)

# Main program source files
MAIN_SRC_DIR := ./src
MAIN_SRCS := $(addprefix $(MAIN_SRC_DIR)/, main.c models_interface.c uart_interface.c velocity_estimation.c data_logger.c)
MAIN_SRCS := $(MAIN_SRCS) micro-libs/ctrl-nwk-utils/ctrl-nwk-utils.c micro-libs/logger/logger.c
TEST_SRCS := $(addprefix $(MAIN_SRC_DIR)/, test_models.c models_interface.c velocity_estimation.c)
TEST_SRCS := $(TEST_SRCS) micro-libs/logger/logger.c

# ------------------------------- Build targets --------------------------------

# Build target for the velocity-estimation library
$(BUILD_DIR)/libctrl-ve.so: $(MODEL_VE_SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS_ALL) $(CFLAGS_MODELS) $(CSHAREDFLAGS) -I$(MATLAB_ROOT)/lib -I$(MODEL_VE_DIR) $^ -o $@ $(LDFLAGS)

# Build target for the slip-control library
$(BUILD_DIR)/libctrl-sc.so: $(MODEL_SC_SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS_ALL) $(CFLAGS_MODELS) $(CSHAREDFLAGS) -I$(MATLAB_ROOT)/lib -I$(MODEL_SC_DIR) $^ -o $@ $(LDFLAGS)

# Build target for the torque-vectoring library
$(BUILD_DIR)/libctrl-tv.so: $(MODEL_TV_SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS_ALL) $(CFLAGS_MODELS) $(CSHAREDFLAGS) -I$(MATLAB_ROOT)/lib -I$(MODEL_TV_DIR) $^ -o $@ $(LDFLAGS)

# Build target for the complete-control library
$(BUILD_DIR)/libctrl-all.so: $(MODEL_ALL_SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS_ALL) $(CFLAGS_MODELS) $(CSHAREDFLAGS) -I$(MATLAB_ROOT)/lib -I$(MODEL_ALL_DIR) $^ -o $@ $(LDFLAGS)

# Build target for the no-control library
$(BUILD_DIR)/libctrl-no.so: $(MODEL_NO_SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS_ALL) $(CFLAGS_MODELS) $(CSHAREDFLAGS) -I$(MATLAB_ROOT)/lib -I$(MODEL_NO_DIR) $^ -o $@ $(LDFLAGS)

# Build target for the main program
$(BUILD_DIR)/fenice-traction-control: $(MAIN_SRCS)
	mkdir -p $(BUILD_DIR)
	git submodule update --init --recursive
	$(CC) $(CFLAGS_ALL) $(CFLAGS_MAIN) $^ -o $@ $(LDFLAGS)

# Build target for testing the models
$(BUILD_DIR)/test-models: $(TEST_SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS_ALL) $^ -o $@ $(LDFLAGS)

# Build all
all: $(addprefix $(BUILD_DIR)/,$(ALL_TARGETS))
	
# Clean build directory
clean:
	rm -r $(BUILD_DIR)