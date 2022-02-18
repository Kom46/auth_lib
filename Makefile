#  Makefile template for Static library. 
# 1. Compile every *.c in the folder 
# 2. All obj files under obj folder
# 3. static library .a at lib folder
# 4. run 'make dirmake' before calling 'make'

TARGET = libauth
TOOLCHAIN_PATH =
PREFIX =
ifeq ($(PLATFORM), arm-none)
TOOLCHAIN_PATH = /opt/toolchains/gcc-arm-none-eabi-10.3-2021.10/bin
PREFIX = $(TOOLCHAIN_PATH)/arm-none-eabi-
endif
CC = $(PREFIX)gcc
AR = $(PREFIX)ar
OUTPUT = $(TARGET).a

CFLAGS= -fPIC -O0 -g -Wall -c -fpermissive
DEFINES = 

INC_DIR = inc
SRC_DIRS = src
TEST_DIR = test

OBJ_DIR = ./obj
OUT_DIR = ./lib

ifeq ($(OS), FREERTOS)
DEFINES += FREERTOS
endif

INC = $(addprefix -I, $(INC_DIR))
SRC = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
TEST = $(wildcard $(TEST_DIR)/*.c)
DEPS = $(patsubst %.c,%.d, $(SRC))
DEPS += $(patsubst %.c,%.d, $(TEST))
DEFS = $(addprefix -D,  $(DEFINES))
-include $(DEPS)

OBJS := $(patsubst %.c,%.o, $(SRC))

all: $(OUTPUT) test

$(OUTPUT): $(OBJS)
	$(AR) -r -o $(OUT_DIR)/$@ $^



%.o: %.c dirmake
	$(CC) $(DEFS) $(INC) $(CFLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	$(CC) -c $(DEFS) $(INC) $(CFLAGS) -o $@  $<

dirmake:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)
	
clean:
	rm -f $(OBJS) $(DEPS) $(OUT_DIR)/$(OUTPUT) Makefile.bak

rebuild: clean all