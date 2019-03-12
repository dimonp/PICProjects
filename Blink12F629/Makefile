# GNU/Linux specific Make directives.

# Environment 
CP=cp
CC=sdcc
LD=gplink
PRG=pk2cmd

MCU = 12f629
ARCH = pic14

LIB=-I/usr/share/sdcc/lib/$(ARCH) -I/usr/share/sdcc/non-free/lib/$(ARCH)
SCRIPT=/usr/share/gputils/lkr/$(MCU)_g.lkr

BINARY=blink
CFLAGS  = -m$(ARCH) -p$(MCU) --use-non-free --opt-code-size
LDFLAGS = -m -w -r -s $(SCRIPT) $(LIB) libsdcc.lib pic$(MCU).lib libm.lib
PRGFLAGS = -PPIC$(MCU) -R -T -X -M

SRC_DIR = src
BUILD_DIR = build

SRC = $(wildcard  $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
EXECUTABLE = $(OBJ:.o=.hex)

.PHONY: clean build rebuild program

all: build

rebuild: clean build

build: $(SRC) $(OBJ) $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	@echo $(OBJ)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(BUILD_DIR)/$(BINARY).hex

%.o: %.c
	@echo $(SRC)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/ -c $<

dir:
	mkdir -p $(BUILD_DIR)

program:
	$(PRG) $(PRGFLAGS) -F$(BUILD_DIR)/$(BINARY).hex

clean:
	@echo Clean $(BUILD_DIR)
	rm -rf $(BUILD_DIR)/*
