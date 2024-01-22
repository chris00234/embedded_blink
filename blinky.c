#include <stdio.h>

#define GPIODATA_F (*((volatile unsigned long *) 0x40025010)) // PF starts at 0x40025000 and our bit masking code is 0x010
//GPIODATA_F = 0x00000100; // go inside of main

#define GPIODIR (*((volatile unsigned long *) 0x40025400)) //pin direction control for port F with offset 0x400
//GPIODIR = 0x00000100;

#define GPIODEN (*((volatile unsigned long *) 0x4002551C)) // digital enable for port F with offset 0x51C
//GPIODEN = 0x00000100;

#define RCGCGPIO (*((volatile unsigned long *) 0x400FE608)) // starting address for clock gate is 0x400FE000 and offset of 0x608
//RCGCGPIO = 0x00000100;

#define blue_led = 0x04 // 0000.0100
#define GPIO_PORTF_CLK_EN 0x20
#define GPIO_PORTF_PIN2_EN  0x04

void delay()
{
    volatile unsigned long i;
    //TM4C123GXL
    for (i = 0; i < 4000000; i++);
}

int main(void){
    // Enable clock for PORTF
    RCGCGPIO |= GPIO_PORTF_CLK_EN; 
    // Enable pin 2 on PORTF
    GPIODEN |= GPIO_PORTF_PIN2_EN; 
    // Set pin 2 as an output
    GPIODIR |= GPIO_PORTF_PIN2_EN; 

    while(1){
        GPIODATA_F = 0x04;
        delay();
        GPIODATA_F = 0x00;
        delay();
    }

}
