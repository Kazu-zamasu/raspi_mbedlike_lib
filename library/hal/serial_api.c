#include "serial_api.h"
#include "pinmap.h"
#include "PinNames.h"
#include "bcm2836.h"

void uart0_init(void){
    // stop UART0
    *UART0_CR   = 0;

    // setup GPIO function to UART0
    pin_pull(UART_TXD0, PullDown);
    pin_pull(UART_RXD0, PullDown);
    pin_mode(UART_TXD0, Alt0);
    pin_mode(UART_RXD0, Alt0);

    // set default baudrate(115200bps)
    // see BCM2835-ARM-Peripherals.pdf(pp.183)
    *UART0_IBRD = 1;
    *UART0_FBRD = 40;

    // set Line Control Register
    // stick parity dis, 8bit, FIFO en, two stop bit no, odd parity, parity dis, break no
    UART0_LCRH_BF lcrh;
    lcrh.raw = 0x00000070; 
    *UART0_LCRH = lcrh.raw;

    // set Control Register
    // CTS dis, RTS dis, OUT1-2=0, RTS dis, DTR dis, RXE en, TXE en, loop back dis, SIRLP=0, SIREN=0, UARTEN en
    UART0_CR_BF cr;
    cr.raw = 0x00000301;
    *UART0_CR   = cr.raw;
}

void uart0_baud(int baudrate){
    unsigned int baudrate_table[11]={300, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200 };
    unsigned int ib_table[] = {625, 156,78,39,19,13,9,6,4,3,1};
    unsigned int fb_table[] = {0,16,8,4,34,1,49,33,57,16,40};

    // search baudrate table
    int table_index;
    for(table_index = 10; table_index >= 0; table_index--){
        if(baudrate_table[table_index] == baudrate){
            break;
        }
    }
    *UART0_IBRD = ib_table[table_index];
    *UART0_FBRD = fb_table[table_index];

}

void uart0_format(int data_bits, SerialParity parity, int stop_bits){
    // get now configure
    UART0_LCRH_BF lcrh;
    lcrh.raw = *UART0_LCRH; 

    // deta bits
    data_bits -= 5;
    if(data_bits <= 3){
        lcrh.bits.WLEN = data_bits;
    }

    // parity
    if(parity != ParityNone){
        lcrh.bits.PEN = 1;
        lcrh.bits.EPS = ((parity == ParityEven) ? 1:0);
    }
    else{
        lcrh.bits.PEN = 0;
    }

    // stop_bits
    if(stop_bits > 1){
        lcrh.bits.STP2 = 1;
    }
    else{
        lcrh.bits.STP2 = 0;
    }

    // set new configure
    *UART0_LCRH = lcrh.raw;
}

int uart0_getc(void){
    int c = *UART0_DR;
    return c & 0xff;
}

int uart0_putc(int c){
    *UART0_DR = c;
    return c;
}

int uart0_readable(void){
    UART0_FR_BF fr;
    fr.raw = *UART0_FR;
    if(fr.bits.RXFE == 0){
        // FIFO is not empty
        return 1;
    }
    // FIFO is empty
    return 0;
}

int uart0_writable(void){
    UART0_FR_BF fr;
    fr.raw = *UART0_FR;
    if(fr.bits.TXFF == 0){
        // FIFO is not full
        return 1;
    }
    // FIFO is not full
    return 0;
}

void serial_init(serial_t *obj, PinName tx, PinName rx){
    // select uart
    if(tx == UART_TXD0 && rx == UART_RXD0){
        // not supported other uart
        uart0_init();
        obj->uart       = UART0;
        obj->baudrate   = 115200;
        obj->databits   = 8;
        obj->stopbits   = 1;
        obj->parity     = ParityNone;
    }
    return;
}

void serial_free(serial_t *obj){
    return;
}
void serial_baud(serial_t *obj, int baudrate){
    // select uart
    if(obj->uart == UART0){
        // not supported other uart
        uart0_baud(baudrate);
    }
    return;
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits){
    // select uart
    if(obj->uart == UART0){
        // not supported other uart
        uart0_format(data_bits, parity, stop_bits);
    }
    return;
}

// void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id){
// }
// void serial_irq_set    (serial_t *obj, SerialIrq irq, uint32_t enable){
// }

int  serial_getc(serial_t *obj){
    while(serial_readable(obj));

    int c = -1;
    if(obj->uart == UART0){
        // not supported other uart
        c = uart0_getc();
    }

    return c;
}

void serial_putc(serial_t *obj, int c){
    while(serial_writable(obj));

    if(obj->uart == UART0){
        // not supported other uart
        uart0_putc(c);
    }

    return;
}

int  serial_readable(serial_t *obj){
    // select uart
    if(obj->uart == UART0){
        // not supported other uart
        return uart0_readable();
    }
    return -1;
}

int  serial_writable(serial_t *obj){
    // select uart
    if(obj->uart == UART0){
        // not supported other uart
        return uart0_writable();
    }
    return -1;
}

void serial_clear(serial_t *obj){

}

// void serial_break_set  (serial_t *obj){
// }
// void serial_break_clear(serial_t *obj){
// }

void serial_pinout_tx(PinName tx){

}
