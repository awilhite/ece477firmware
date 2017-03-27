
/**
  IC1 Generated Driver API Source File

  @Company
    Microchip Technology Inc.

  @File Name
    ic1.c

  @Summary
    This is the generated source file for the IC1 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for driver for IC1.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : v1.25
        Device            :  PIC24FJ128GA010
        Driver Version    :  0.5
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB 	          :  MPLAB X 3.45
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/
/**
  Section: Included Files
*/
#include <xc.h>
#include "ic1.h"

/**
  IC Mode.

  @Summary
    Defines the IC Mode.

  @Description
    This data type defines the IC Mode of operation.

*/

static uint16_t         gIC1Mode;

/**
  Section: Driver Interface
*/

void IC1_Initialize (void)
{
    IC1CON = 0x81;
    
    /*IC1CONbits.ICM = 0b00; // Disable Input Capture 1 module

    IC1CONbits.ICTMR = 1; // Select Timer2 as the IC1 Time base

    IC1CONbits.ICI = 0b11; // Interrupt on every capture event

    IC1CONbits.ICM = 0b001; // Generate capture event on every Rising and Falling edge*/

    // Enable Capture Interrupt And Timer2

    IPC0bits.IC1IP = 7; // Setup IC1 interrupt priority level - Highest
    IFS0bits.IC1IF = 0; // Clear IC1 Interrupt Status Flag
    IEC0bits.IC1IE = 1; // Enable IC1 interrupt
    
    gIC1Mode = IC1CONbits.ICM;
    
}

void __attribute__ ((weak)) IC1_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _IC1Interrupt( void )
{
    if(IFS0bits.IC1IF)
    {
        IFS0bits.IC1IF = 0;
    }
    IC1_CallBack();
}

void IC1_Start( void )
{
    IC1CONbits.ICM = gIC1Mode;
}

void IC1_Stop( void )
{
    IC1CONbits.ICM = 0;
}

uint16_t IC1_CaptureDataRead( void )
{
    return(IC1BUF);
}

bool IC1_HasCaptureBufferOverflowed( void )
{
    return( IC1CONbits.ICOV );
}


bool IC1_IsCaptureBufferEmpty( void )
{
    return( ! IC1CONbits.ICBNE );
}

/**
 End of File
*/
