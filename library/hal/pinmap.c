#include "pinmap.h"
#include "bcm2836.h"

#define WAIT150CYCLE for(int i=0;i<15;i++){ __asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop"); __asm__("nop");}

void pin_pull(PinName pin, PinMode mode) {
    // vuint32_t *res = GPPUDCLK(pin / 33);
    vuint32_t * res = GPPUDCLK((pin & 0xffffffdf) ? 1:0);

    switch(mode){
        case PullUp:
            *GPPUD = 0x02;
            break;
        case PullDown:
            *GPPUD = 0x01;
            break;
        default:
            // PullNone
            *GPPUD = 0x00;
    }
    // 150 cycle wait
    WAIT150CYCLE;
    // *res = (0x01 << (pin % 32));
    *res = (0x01 << (pin & 0x1F));
    // 150 cycle wait
    WAIT150CYCLE;
    // remove the control signal
    *GPPUD = 0x00;
    // remove the clock
    *res = 0x00;
}

void pin_mode(PinName pin, PinMode mode) {
    if (pin == (PinName)NC) { return; }
    // set pullup, pulldown,...

    // select resister number
    int group = pin / 10;
    vuint32_t *res = GPFSEL(group);
    vuint32_t shift = (pin % 10) * 3;

    switch(mode){
        case Output:
        case Alt0:
        case Alt1:
        case Alt2:
        case Alt3:
        case Alt4:
        case Alt5:
            *res = (mode << shift) | (*res & ~(0x07 << shift));
            break;
        case PullUp:
        case PullDown:
        case PullNone:
            pin_pull(pin, mode);
            break;
        case Input:
            // register clear(3bit)
            *res &= ~(0x07 << shift);
        default:
            return;
    }
}
