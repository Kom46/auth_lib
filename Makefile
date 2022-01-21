#  Makefile template for Static library. 
# 1. Compile every *.cpp in the folder 
# 2. All obj files under obj folder
# 3. static library .a at lib folder
# 4. run 'make dirmake' before calling 'make'

TARGET = libauth
TOOLCHAIN_PATH = /opt/toolchains/gcc-arm-none-eabi-10.3-2021.10/bin
PREFIX = arm-none-eabi-
CC = $(TOOLCHAIN_PATH)/$(PREFIX)gcc
AR = $(TOOLCHAIN_PATH)/$(PREFIX)ar
OUTPUT = $(TARGET).a

CFLAGS= -fPIC -O0 -g -Wall -c -fpermissive
INC_DIR = inc
SRC_DIR = src
TEST_DIR = test
INC = -I$(INC_DIR)

OBJ_DIR = ./obj
OUT_DIR = ./lib
DEPS_DIR= ./deps

SRC = $(wildcard $(SRC_DIR)/*.c)
TEST = $(wildcard $(TEST_DIR)/*.c)
DEPS = $(SRC:.c,.o)
DEPS += $(TEST:.c,.o)

OBJS := $(patsubst %.c,%.o, $(SRC))
TEST_OBJS := $(patsubst %.c,%.o, $(TESTS))


all: | $(OUTPUT) tests

$(OUTPUT): $(OBJS)
	@echo $(SRC)
	@echo $(OBJS)
	$(AR) -r -o $(OUT_DIR)/$@ $^



%.o: %.c dirmake
	$(CC) -c $(INC) $(CFLAGS) -o $@  $<

%.c:
dirmake:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)
	
clean:
	rm -f $(OBJ_DIR)/* $(OUT_DIR)/$(OUTPUT) Makefile.bak

rebuild: clean all

tests: | $(OUTPUT) $(TEST_OBJS)