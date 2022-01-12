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
INC = -I$(INC_DIR)

OBJ_DIR=./obj

OUT_DIR=./lib

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst %.c,%.o, $(SRC))
# Enumerating of every *.cpp as *.o and using that as dependency.	
# filter list of .c files in a directory.
# FILES =dump_l.c \
#	kter.c \
#
# $(OUT_FILE_NAME): $(patsubst %.c,$(OBJ_DIR)/%.o,$(wildcard $(FILES))) 

all: $(OUTPUT)
# Enumerating of every *.cpp as *.o and using that as dependency
$(OUTPUT): $(OBJS)
	@echo $(SRC)
	@echo $(OBJS)
	$(AR) -r -o $(OUT_DIR)/$@ $^



#Compiling every *.c to *.o
%.o: %.c dirmake
	$(CC) -c $(INC) $(CFLAGS) -o $@  $<

dirmake:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)
	
clean:
	rm -f $(OBJ_DIR)/*.o $(OUT_DIR)/$(OUTPUT) Makefile.bak

rebuild: clean build