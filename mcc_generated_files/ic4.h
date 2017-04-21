/**
  IC4 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    ic4.h

  @Summary
    This is the generated header file for the IC4 driver using MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for driver for IC4.
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

#ifndef _IC4_H
#define _IC4_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Interface Routines
*/


/**
  @Summary
    This function initializes IC instance : 4

  @Description
    This routine initializes the IC driver instance for : 4
    index, making it ready for clients to open and use it.
    This routine must be called before any other IC4 routine is called.
	
  @Preconditions
    None.

  @Param
    None
 
  @Returns
    None.

  @Example
    <code>
    bool bufferStatus;
    uint16_t data;
 
    IC4_Initialize();
    
    IC4_Start();
 
    while(1)
    {
        bufferStatus = IC4_IsCaptureBufferEmpty( void );
        if(!bufferStatus)
        {
            data = IC4_CaptureDataRead();
        }
    }
    IC4_Stop();
 
    </code>

*/

void IC4_Initialize (void);


/**
  @Summary
    Enables the IC module with the corresponding operation mode.

  @Description
    This routine enables the IC module with the corresponding operation mode.

  @Preconditions
    IC4_Initialize function should have been called 

  @Param
    None
 
  @Returns
    None.

  @Example 
    Refer to IC4_Initialize() for an example	
 
*/

void IC4_Start( void );
  /** 
  @Summary
    Disables the IC module.

  @Description
    This routine disables the IC module.

  @Preconditions
    IC4_Initialize function should have been called 

  @Param
    None
 
  @Returns
    None.

  @Example 
    Refer to IC4_Initialize() for an example	
  	
*/

void IC4_Stop( void );
/**
  @Summary
    Reads the captured data from buffer.

  @Description
    This routine reads the captured data from buffer.

  @Preconditions
    IC4_Initialize function should have been called 

  @Param
    None
 
  @Returns
    Read data from buffer.

  @Example 
    Refer to IC4_Initialize() for an example	
  	
*/

uint16_t IC4_CaptureDataRead( void );

/**
  @Summary
    Gets the buffer overflow status.

  @Description
    This routine gets the buffer overflow status.
	
  @Preconditions
    IC4_Initialize function should have been called 
	
  @Param
    None
 
  @Returns
    Boolean value describing the buffer overflow status.
    true  : When the capture buffer has overflowed
    false : When the capture buffer has not overflowed

   @Example 
    <\code>	
    bool status;

    status = IC4_HasCaptureBufferOverflowed();
    <\code>	
*/

bool IC4_HasCaptureBufferOverflowed( void );
/**  
@Summary
    Gets the buffer empty status.

  @Description
    This routine gets the buffer empty status.
	
  @Preconditions
    IC4_Initialize function should have been called 
	
  @Param
    None

  @Returns
    Boolean value describing the buffer empty status.
    True- If buffer empty
    False-If buffer not empty

   @Example 
    Refer to IC4_Initialize() for an example	
 */

bool IC4_IsCaptureBufferEmpty( void );

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_IC4_H
    
/**
 End of File
*/
