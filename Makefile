PROJECT_NAME=example
BUILD_DIR=build

DEBUG=1

include mk/config.mk
include mk/toolchain.mk

# Project files
SRC_C = \
    src/uart.c \
    src/timers.c \
    src/lcd_font.c \
    src/app.c \
    src/pseudo_rand.c \
    src/lcd_watchface_font.c \
    src/lcd.c \
    src/btn.c \
    src/main.c \
    src/icons8px.c \
    src/mainloop.c \
    src/strings.c \
    src/system_stm32f10x.c \
    src/syscalls.c \
    src/apps/animation.c \
    src/apps/tetris.c \
    src/apps/mainmenu.c \
    src/apps/serial.c \
    src/apps/watchface.c \
    src/apps/dummy.c \
    src/apps/freqcheck.c \
	CMSIS/core/core_cm3.c


SRC_ASM = \
    startup/startup_stm32.s

INCLUDES = \
	-Iinc \
	-ICMSIS/device/ \
	-ICMSIS/core/ \
	-IStdPeriph_Driver/inc/

C_DEFS =  \
	-DUSE_STDPERIPH_DRIVER\
	-DSTM32F1 \
	-DSTM32F103C8Tx \
	-DSTM32 \
	-DSTM32F10X_MD \
    -DHSE_VALUE=12000000 \
    -DSYSCLK_FREQ_HSE \
    -DHW_IDENT="MOKKI-M3"

MCU = -mcpu=cortex-m3 -mthumb

LDSCRIPT = LinkerScript.ld
LIBS = -lc -lm -lnosys
OPT = -Og

# The only flags passed
CFLAGS = $(MCU) $(C_DEFS) $(INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections


ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif
# CFLAGS += -Wall -Wpointer-arith -Werror -Wformat

# ----------------------------------------------------------
# ST HAL Driver sources
SRC_C += \
    StdPeriph_Driver/src/stm32f10x_dma.c  \
    StdPeriph_Driver/src/stm32f10x_adc.c  \
    StdPeriph_Driver/src/stm32f10x_bkp.c  \
    StdPeriph_Driver/src/stm32f10x_wwdg.c  \
    StdPeriph_Driver/src/stm32f10x_fsmc.c  \
    StdPeriph_Driver/src/stm32f10x_rcc.c  \
    StdPeriph_Driver/src/stm32f10x_pwr.c  \
    StdPeriph_Driver/src/stm32f10x_flash.c  \
    StdPeriph_Driver/src/stm32f10x_can.c  \
    StdPeriph_Driver/src/stm32f10x_i2c.c  \
    StdPeriph_Driver/src/stm32f10x_spi.c  \
    StdPeriph_Driver/src/stm32f10x_cec.c  \
    StdPeriph_Driver/src/stm32f10x_exti.c  \
    StdPeriph_Driver/src/stm32f10x_crc.c  \
    StdPeriph_Driver/src/stm32f10x_usart.c  \
    StdPeriph_Driver/src/misc.c  \
    StdPeriph_Driver/src/stm32f10x_rtc.c  \
    StdPeriph_Driver/src/stm32f10x_sdio.c  \
    StdPeriph_Driver/src/stm32f10x_tim.c  \
    StdPeriph_Driver/src/stm32f10x_dbgmcu.c  \
    StdPeriph_Driver/src/stm32f10x_dac.c  \
    StdPeriph_Driver/src/stm32f10x_iwdg.c  \
    StdPeriph_Driver/src/stm32f10x_gpio.c  \

# ----------------------------------------------------------

OBJ = $(addprefix $(BUILD_DIR)/, $(SRC_C:.c=.o)) $(addprefix $(BUILD_DIR)/, $(SRC_ASM:.s=.o))

all: $(BUILD_DIR)/$(PROJECT_NAME).elf

include mk/gdb.mk

# For each object file
$(BUILD_DIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/%.o: %.s
	$(CC) -c -o $@ $< $(CFLAGS)

# Whole project link
$(BUILD_DIR)/$(PROJECT_NAME).elf: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	$(SZ) $@

clean:
	rm -rf $(BUILD_DIR)

# ----- Utils -----

# Creates directory tree
OBJ_DIRS = $(sort $(dir $(OBJ)))
$(OBJ): | $(OBJ_DIRS)
$(OBJ_DIRS):
	mkdir -p $@
