#include "msp430fr4133.h"
#include <stdint.h>
//Define a second at 1MHz
#define BLINK_CYCLES 500000L

typedef struct {

    unsigned short bit_0 : 1;
    unsigned short bit_1 : 1;
    unsigned short bit_2 : 1;
    unsigned short bit_3 : 1;
    unsigned short bit_4 : 1;
    unsigned short bit_5 : 1;
    unsigned short bit_6 : 1;
    unsigned short bit_7 : 1;
}reg8_t;

typedef volatile union{
    
    uint8_t all;
    reg8_t bit;

}PORT1_t;

int main(void){


    PORT1_t * const PORT1 = (PORT1_t *) 0x0202;

    //Stop the WDT Module 
    WDTCTL = WDTPW |WDTHOLD;

    //Enable Output from PMM
    PM5CTL0 &= ~LOCKLPM5;

    //Set Pin 1.0 as output
    P1DIR |= 0xFF;

    while(1){
        PORT1->all = 0x00;
        PORT1->bit.bit_2 = 1;

        for(int i = 0; i < 5; i++){
            PORT1->all <<= 1;
            __delay_cycles(BLINK_CYCLES);
        }
    }

    return 0;
}

