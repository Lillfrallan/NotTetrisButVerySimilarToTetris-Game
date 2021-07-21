#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw (void)
{
    int sw = (PORTD >> 8) & 0x000f;

    return sw;
}

int getbtns(void){
    int btn = (PORTD >> 5) & 0x0007;

    return btn;
}

int getbtn1(void){
    int btn1 = (PORTF >> 1) & 0x0001;

    return btn1;
}

int getsw3(void){
    int sw3 = (PORTF >> 1) & 0x0001;

    return sw3;
}