#include <stdint.h>
#include "pinmap.h"
#include "gpio_object.h"
#include "bcm2836.h"


void gpio_init(gpio_t *obj, PinName pin){
    int group;
    if(pin == NC || 53 < pin) return;
    group = pin / 32;
    //    group = (pin & 0xffffffe0) ? 1:0;
    if (group > 2) return;

    obj->pin = pin;
    //    int mask_point = pin - (32 * group);
    //    obj->mask = 0x01 << mask_point;

    obj->reg_set = GPSET(group);
    obj->reg_clr = GPCLR(group);
    obj->reg_lev = GPLEV(group);
    obj->mask = 0x01 << (pin % 32);
}

void gpio_mode (gpio_t *obj, PinMode mode){
    pin_mode(obj->pin, mode);
}

void gpio_write(gpio_t *obj, int value) {
    if (value)
      *obj->reg_set = obj->mask;
    else
      *obj->reg_clr = obj->mask;
}

int gpio_read(gpio_t *obj) {
    if(obj->mode == Output){
        return ((*obj->reg_lev & obj->mask) ? 1 : 0);
    }
    else{
        return ((*obj->reg_lev & obj->mask) ? 1 : 0);
    }
}


// the following set of functions are generic and are implemented in the common gpio.c file
void gpio_init_in(gpio_t* gpio, PinName pin){
    gpio_init(gpio, pin);
    gpio_mode(gpio, Input);
}

void gpio_init_in_ex(gpio_t* gpio, PinName pin, PinMode mode){
    gpio_init(gpio, pin);
    gpio_mode(gpio, mode);
}

void gpio_init_out(gpio_t* gpio, PinName pin){
    gpio_init(gpio, pin);
    gpio_mode(gpio, Output);
}

void gpio_init_out_ex(gpio_t* gpio, PinName pin, int value){
    gpio_init(gpio, pin);
    gpio_write(gpio, value);
    gpio_mode(gpio, Output);
    gpio_write(gpio, value);
}
