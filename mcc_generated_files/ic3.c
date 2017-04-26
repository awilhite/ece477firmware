
/**
  IC3 Generated Driver API Source File

  @Company
    Microchip Technology Inc.

  @File Name
    ic3.c

  @Summary
    This is the generated source file for the IC3 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for driver for IC3.
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
#include "ic3.h"

/**
  IC Mode.

  @Summary
    Defines the IC Mode.

  @Description
    This data type defines the IC Mode of operation.

*/

static uint16_t         gIC3Mode;

/**
  Section: Driver Interface
*/

void IC3_Initialize (void)
{
    // ICSIDL disabled; ICM Edge Detect Capture; ICTMR TMR2; ICI Every; 
    IC3CON = 0x0081;
    
    gIC3Mode = IC3CONbits.ICM;
    
    IFS2bits.IC3IF = false;
    IEC2bits.IC3IE = true;
}

void __attribute__ ((weak)) IC3_CallBack(void)
{
    
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _IC3Interrupt( void )
{
    if(IFS2bits.IC3IF)
    {
        IFS2bits.IC3IF = 0;
    }
    IC3_CallBack();
}
void IC3_Start( void )
{
    IC3CONbits.ICM = gIC3Mode;
}

void IC3_Stop( void )
{
    IC3CONbits.ICM = 0;
}

uint16_t IC3_CaptureDataRead( void )
{
    return(IC3BUF);
}

bool IC3_HasCaptureBufferOverflowed( void )
{
    return( IC3CONbits.ICOV );
}


bool IC3_IsCaptureBufferEmpty( void )
{
    return( ! IC3CONbits.ICBNE );
}

/**
 End of File
*/
