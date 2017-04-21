
/**
  IC4 Generated Driver API Source File

  @Company
    Microchip Technology Inc.

  @File Name
    ic4.c

  @Summary
    This is the generated source file for the IC4 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for driver for IC4.
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
#include "ic4.h"

/**
  IC Mode.

  @Summary
    Defines the IC Mode.

  @Description
    This data type defines the IC Mode of operation.

*/

static uint16_t         gIC4Mode;

/**
  Section: Driver Interface
*/

void IC4_Initialize (void)
{
    // ICSIDL disabled; ICM Edge Detect Capture; ICTMR TMR2; ICI Every; 
    IC4CON = 0x0081;
    
    gIC4Mode = IC4CONbits.ICM;
    
    IFS2bits.IC4IF = false;
    IEC2bits.IC4IE = true;
}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _IC4Interrupt( void )
{
    if(IFS2bits.IC4IF)
    {
        IFS2bits.IC4IF = 0;
    }
}
void IC4_Start( void )
{
    IC4CONbits.ICM = gIC4Mode;
}

void IC4_Stop( void )
{
    IC4CONbits.ICM = 0;
}

uint16_t IC4_CaptureDataRead( void )
{
    return(IC4BUF);
}

bool IC4_HasCaptureBufferOverflowed( void )
{
    return( IC4CONbits.ICOV );
}


bool IC4_IsCaptureBufferEmpty( void )
{
    return( ! IC4CONbits.ICBNE );
}

/**
 End of File
*/
