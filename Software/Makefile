

#program
SRC = src/main.c src/delay.c src/primitives.c src/effects.c src/worm.c
INCLUDE_DIR = include
TARGET = test
MCU = atmega168
F_CPU = 16000000UL

#avrdude parameters
AVRDUDE_PROGRAMMER = usbtiny
AVRDUDE_WRITE_FLASH = -U flash:w:$(BIN_DIR)/$(TARGET).hex:i
AVRDUDE_FLAGS = -v -p $(MCU) -c $(AVRDUDE_PROGRAMMER) -B 1


BIN_DIR = bin
BUILD_DIR = build

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AR  = avr-ar
SIZE = avr-size
NM = avr-nm

FORMAT = ihex

CFLAGS = -I$(INCLUDE_DIR) -O2 -std=gnu99 -Wall -Wstrict-prototypes -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums  -mmcu=$(MCU) -DF_CPU=$(F_CPU)

LDFLAGS =

OBJS = $(SRC:.c=.o)
TARGET_OBJ =  $(patsubst src/%, $(BUILD_DIR)/%, $(OBJS))

all: build sizeafter

build: elf hex

elf: $(BIN_DIR)/$(TARGET).elf

hex: $(BIN_DIR)/$(TARGET).hex

upload: $(BIN_DIR)/$(TARGET).hex
	avrdude $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)

# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(BIN_DIR)/$(TARGET).hex
ELFSIZE = $(SIZE)  $(BIN_DIR)/$(TARGET).elf

sizebefore:
	@if [ -f $(BIN_DIR)/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); echo; fi

sizeafter:
	@if [ -f $(BIN_DIR)/$(TARGET).hex ]; then echo; echo $(MSG_SIZE_AFTER); $(HEXSIZE); echo; fi

%.hex: %.elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@


#link
$(BIN_DIR)/$(TARGET).elf: $(BUILD_DIR)/$(TARGET).a
	$(CC) $(CFLAGS) -o $@ $(BUILD_DIR)/$(TARGET).a $(LDFLAGS)

$(BUILD_DIR)/$(TARGET).a: $(TARGET_OBJ)
	@for i in $(TARGET_OBJ); do echo $(AR) rcs $(BUILD_DIR)/$(TARGET).a $$i; $(AR) rcs $(BUILD_DIR)/$(TARGET).a $$i; done

clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

$(BUILD_DIR)/%.o: src/%.c
	$(CC) -c $(CFLAGS) $< -o $@