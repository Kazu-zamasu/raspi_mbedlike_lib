include ../config.make

INCLUDE = -I./ -I./hal -I./api/ -I./cmsis/

HAL_PREFIX = ./hal
HAL_OBJS = $(HAL_PREFIX)/gpio_api.o
HAL_OBJS += $(HAL_PREFIX)/pinmap.o
HAL_OBJS += $(HAL_PREFIX)/serial_api.o

# COMMON_OBJS = common/Serial.o
# COMMON_OBJS += common/SerialBase.o
# COMMON_OBJS += common/Stream.o

all: libbcm2836.a

libbcm2836.a: $(HAL_OBJS)
	$(AR) cr $@ $^

.c.o:	
	$(CC) $(CFLAGS) -std=c99 $(INCLUDE) -c $< -o $@
.cpp.o:
	$(CPP) $(CFLAGS) -std=c++98 $(INCLUDE) -c $< -o $@
.S.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean::
	$(RM) -f *.o *.bin *.elf */*.o */*/*.o *.a
	$(RM) -f tags *~ *.disas *.readelf *.size
