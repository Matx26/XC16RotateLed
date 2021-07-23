/*
 * File:   RotateLedV010.c
 * Author: Electronica
 *V0.1.0: El programa hara rotar el led encendido a lo largo del puerto B
 * Created on 31 de mayo de 2018, 08:48
 */


#include <xc.h>
#include "ConfigBits.h"
#define FCY 16000000UL      //definimos la felocidad FCY=16MIPS,  UL=40bits (unsigned long)
#include <libpic30.h>

/*****************************************************************************/
//ConfigOscillator: config of oscilator a 32 Mhz, FRC a 8Mhz x 4 del PLL  
/*****************************************************************************/
void ConfigOscillator(void)
{
    OSCCONbits.COSC = 0b001;    // FCR fast RC oscillator with PLL
    OSCCONbits.NOSC = 0b001;    // New osc in case clock switch is FRC with PLL
    OSCCONbits.CLKLOCK = 1;   // Clock and PLL are lock
    OSCCONbits.IOLOCK = 1;    //IO PPS lock enable
    OSCCONbits.SOSCEN = 0;      //secondary oscillator is disable
    
    CLKDIVbits.DOZE = 0b000;         // peripheral clock ratio is 1:1
    CLKDIVbits.RCDIV = 0b000;       //FRC postscaler divideby 1
}

/*****************************************************************************/
//ConfigPortsMCU: config ports    
/*****************************************************************************/
void ConfigPortsMCU(void)
{
    AD1PCFG = 0xFFFF;     //all ports ANX as digital I/O
    TRISB = 0x0000;       //all portB as output
    LATB = 0x0000;        // ponemos a cero para empezar
}

int main(void) 
{
    ConfigOscillator();     //call the function that set the oscillator
    ConfigPortsMCU();       //call the function the set the ports

    LATB = 0x0101;        // Led0 ON
    while(1)
    {
        __delay_ms(200);
        if(PORTB == 0x8080)       //pregunto si se prendio el ultimo led (led15)
        {
            LATB = 0x0101;    //si es asi, reiniciamos la rotacion       
        }
        else
        {
            LATB = LATB << 1;  //desplazamos un bit ahacia l aizquierda.
        }
    
    }
        

    return 0;
}
