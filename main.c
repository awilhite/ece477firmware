/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : v1.25
        Device            :  PIC24FJ128GA010
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB             :  MPLAB X 3.45
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

#define LED_D3_LAT      LATAbits.LATA0
#define LED_D4_LAT      LATAbits.LATA1
#define LED_D5_LAT      LATAbits.LATA2
#define LED_D6_LAT      LATAbits.LATA3
#define LED_D7_LAT      LATAbits.LATA4
#define LED_D8_LAT      LATAbits.LATA5
#define LED_D9_LAT      LATAbits.LATA6
#define LED_D10_LAT     LATAbits.LATA7      //Overlaps with S5

#define LED_D3_TRIS     TRISAbits.TRISA0
#define LED_D4_TRIS     TRISAbits.TRISA1
#define LED_D5_TRIS     TRISAbits.TRISA2
#define LED_D6_TRIS     TRISAbits.TRISA3
#define LED_D7_TRIS     TRISAbits.TRISA4
#define LED_D8_TRIS     TRISAbits.TRISA5
#define LED_D9_TRIS     TRISAbits.TRISA6
#define LED_D10_TRIS    TRISAbits.TRISA7    //Overlaps with S5

#define LED_ON 1
#define LED_OFF 0

#define INPUT  1
#define OUTPUT 0

#define IC1 PORTDbits.RD8
#define IC2 PORTDbits.RD9
#define IC3 PORTDbits.RD10
#define IC4 PORTDbits.RD11
#define IC5 PORTDbits.RD12

#define INFRARED_IDLE       0
#define INFRARED_HEADER     1
#define INFRARED_MARK       2
#define INFRARED_SPACE      3
#define INFRARED_DONE       4

#define HEADER_MARK     9000
#define HEADER_SPACE    4500
#define ONE_MARK        560
#define ONE_SPACE       1700
#define ZERO_MARK       560
#define ZERO_SPACE      560


#include "mcc_generated_files/mcc.h"

unsigned int count = 0;
unsigned int time_ref = 0;
unsigned int infrared_state = INFRARED_IDLE;
unsigned int mark = 0;
unsigned int space = 0;
unsigned int infrared_received = 0;
unsigned int x = 0;
unsigned int y = 0;
unsigned int send_at = 0;
unsigned int send_response = 0;
uint8_t buffer_read;

void TMR2_CallBack(void)
{
    time_ref++;
    count++;
    
    if (count == 10000)
    {
        LED_D3_LAT = LED_ON;
    }
    else if (count == 20000)
    {
        LED_D3_LAT = LED_OFF;
        count = 0;
        send_at = 1;
    }
}

void IC1_CallBack(void)
{
    switch(infrared_state)
    {
        case INFRARED_IDLE:
            if (IC1) { // rising edge
                x = time_ref;
                infrared_state = INFRARED_HEADER;
            }
            break;
        case INFRARED_HEADER:
            if (!IC1) {
                y = time_ref;
            }
            else { // expecting falling edge
                infrared_state = INFRARED_IDLE;
            }
            break;
        case INFRARED_MARK:
            break;
        case INFRARED_SPACE:
            break;
        case INFRARED_DONE:
            infrared_received = 1;
            break;
    }
}

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    LED_D3_TRIS = OUTPUT;

    while (1)
    {
        if (!UART2_TransmitBufferIsFull())
        {
            if (send_at)
            {
                send_at = 0;
                UART2_Write("AT/r/n");
            }
        }
        
        if (!UART2_ReceiveBufferIsEmpty())
        {   // Incoming command from phone
            
            // Read buffer because it has something
            buffer_read = UART2_Read();
            // do_command(buffer_read))
            // send response
        }
        
        if (infrared_received)
        {   // Incoming hit from vehicle
            
            // data = infrared_verify(&buffer)
            // 
            // send_hit(data)
            
            infrared_received = 0;
        }
        
    }

    return -1;
}
/**
 End of File
*/