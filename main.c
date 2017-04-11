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

#include "mcc_generated_files/mcc.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include <math.h>

// Development Board Button Register Bits

#define S3_PORT  PORTDbits.RD6
#define S6_PORT  PORTDbits.RD7
#define S5_PORT  PORTAbits.RA7       //Overlaps with D10
#define S4_PORT  PORTDbits.RD13

#define S3_TRIS  TRISDbits.TRISD6
#define S6_TRIS  TRISDbits.TRISD7
#define S5_TRIS  TRISAbits.TRISA7
#define S4_TRIS  TRISDbits.TRISD13

// Development Board LED Register Bits

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

#define BUTTON_PRESSED      0
#define BUTTON_NOT_PRESSED  1

#define INPUT  1
#define OUTPUT 0

// Input Capture Register Bit Definitions

#define IC1_TRIS        TRISDbits.TRISD8
#define IC2_TRIS        TRISDbits.TRISD9
#define IC3_TRIS        TRISDbits.TRISD10
#define IC4_TRIS        TRISDbits.TRISD11
#define IC5_TRIS        TRISDbits.TRISD12

#define IC1_LAT         LATDbits.LATD8
#define IC2_LAT         LATDbits.LATD9
#define IC3_LAT         LATDbits.LATD10
#define IC4_LAT         LATDbits.LATD11
#define IC5_LAT         LATDbits.LATD12

// IR Timing Parameters (all numbers x40 microseconds)

#define HEADER_MARK     224 
#define HEADER_SPACE    112 
#define ONE_MARK        14  
#define DATA_MARK       14  
#define ONE_SPACE       42  
#define ZERO_MARK       14  
#define ZERO_SPACE      14  
#define CUSHION         4

#define READ_BUF_LEN    0x80

// Infrared States

enum {
    IR_IDLE,
    IR_HEADER_HI,
    IR_HEADER_LO,
    IR_HEADER_DONE,
    IR_DATA_HI,
    IR_DATA_LO,
} ir_state;

unsigned int count = 0;

unsigned int button_cnt = 0;
unsigned int button_state = 0;
unsigned int button_pressed = 0;

unsigned int mbutton_state = 0;
unsigned int mbutton_pressed = 0;

unsigned int motor_state = 1;

unsigned int time_ref = 0;
unsigned int mark = 0;
unsigned int space = 0;

unsigned int ir_received = 0;
unsigned int ir_success = 0;
unsigned int ir_error = 0;
unsigned int ir_done = 0;

unsigned int x = 0;
unsigned int y = 0;
unsigned int send_at = 0;
unsigned int send_response = 0;
unsigned int buffer_size;

uint8_t buffer_read[READ_BUF_LEN];

unsigned int comm_cnt = 0;
unsigned int ir_data[32];
unsigned int ir_addr = 0;
unsigned int ir_addrc = 0;
unsigned int ir_comm = 0;
unsigned int ir_commc = 0;
unsigned int ir_wait = 0;

unsigned int exp_count = 0; 
unsigned int timarr[67] = {0};
unsigned int timind = 0;

unsigned int shot_data [32];
//unsigned int fif_ind = 0;
//unsigned long exp_ans = 0;

unsigned int done = 0;// flag for when the ir data received is complete 

unsigned int ic1_callback = 0;
unsigned int ic1_count = 0;
unsigned int ic1_flag = 0;
char ic1_str[6];

//unsigned int store_buffer[72];


// Function Declarations

void println(char *);
void esp_println(char *);
void IO_Initialize(void);
int power2(int);
void parse(unsigned int[32]);
void irl(void);

void send_mark(void);
void send_space(void);
void ir_shot(unsigned int[32]);
//void event_fifo(unsigned int);


// Function Definitions
//void event_fifo(int new_stamp, int dir){
//    if(dir){
//        timarr[fif_ind] = new_stamp;
//        fif_ind++;
//        if(fif_ind > 7){
//            LED_D6_LAT = LED_ON;
//        }
//    }
//}
void ir_shot(unsigned int data[32]){
    
}

void parse (unsigned int packet[32]){
    int p_cnt = 0;
    ir_addr = 0;
    ir_comm = 0;
    ir_addrc = 0;
    ir_commc = 0;
    while(p_cnt < 32){
        if(p_cnt < 8)
        {
            ir_addr = ir_addr + (packet[p_cnt] * power2(7-(p_cnt - 0)));
        }
        else if(p_cnt < 16)
        {
            ir_addrc = ir_addrc + (packet[p_cnt] * power2(7-(p_cnt - 8)));
        }
        else if(p_cnt < 24)
        {
            ir_comm = ir_comm + (packet[p_cnt] * power2(7-(p_cnt - 16)));
        }
        else
        {
            ir_commc = ir_commc + (packet[p_cnt] * power2(7-(p_cnt - 24)));
        }
        p_cnt++;
    }
    return; 
}


int power2(int exp)
{
    int exp_ans = 1;
    while(exp)
    {
        exp_ans = exp_ans * 2;
        exp--;
    }
    return exp_ans;
}

void println(char * str)
{
    unsigned int length = 0;
    
    while (str[length] != '\0')
    {
        length++;
    }
    
    UART2_WriteBuffer((uint8_t *) str, length);
    UART2_WriteBuffer((uint8_t *) "\r\n", (uint8_t) 2);
}

void esp_println(char * str)
{
    unsigned int length = 0;
    
    while (str[length] != '\0')
    {
        length++;
    }
    
    UART1_WriteBuffer((uint8_t *) str, length);
    UART1_WriteBuffer((uint8_t *) "\r\n", (uint8_t) 2);
}

void IO_Initialize(void)
{
    S3_TRIS = INPUT;        // PWM Duty Cycle - Button S3
    S6_TRIS = INPUT;        // Motor On/OFF - Button S6
    
    LED_D3_TRIS = OUTPUT;   // AOUT1 and LED D3
    LED_D4_TRIS = OUTPUT;   // BOUT1 and LED D4
    
    LED_D5_TRIS = OUTPUT;   // LED D5
    LED_D6_TRIS = OUTPUT;   // LED D6
    
    
    
    LED_D7_TRIS = OUTPUT;   // IC1 Callback indicator
    LED_D8_TRIS = OUTPUT;   // IC1 Callback indicator
    LED_D9_TRIS = OUTPUT;   // IC1 Callback indicator
    LED_D10_TRIS = OUTPUT;   // IC1 Callback indicator
    
    
    LED_D4_LAT = LED_OFF;    // Turn on LED 4 and BOUT1
    
    // Set Input Captures to INPUT
    
    IC1_TRIS = INPUT;
    IC2_TRIS = INPUT;
    IC3_TRIS = INPUT;
    IC4_TRIS = INPUT;
    IC5_TRIS = INPUT;
}

void TMR2_CallBack(void)
{
    // 40us period
    
    time_ref++;
    count++;
    
    // 1ms period
    
    if (count % 25 == 0)
    {
        // Button 3
        if (S3_PORT == BUTTON_PRESSED && !button_state)
        { // button pressed now but wasn't before
            button_state = 1;
        }
        else if (S3_PORT == BUTTON_NOT_PRESSED && button_state)
        { // button was pressed, but it's not anymore
            button_state = 0;
            button_pressed = 1;
        }
        
        // Button 6
        if (S6_PORT == BUTTON_PRESSED && !mbutton_state)
        { // button pressed now but wasn't before
            mbutton_state = 1;
        }
        else if (S6_PORT == BUTTON_NOT_PRESSED && mbutton_state)
        { // button was pressed, but it's not anymore
            mbutton_state = 0;
            mbutton_pressed = 1;
        }
    }
    
    // 0.4s period
    
    if (count == 10000)
    {
        LED_D5_LAT = LED_ON;
    }
    
    // 0.8s period
    
    else if (count == 20000)
    {
        LED_D5_LAT = LED_OFF;
        count = 0;
        //send_at = 1;
    }
}



void IC2_CallBack(void)
{
    ic1_callback = !ic1_callback;
}

void IC1_CallBack(void)
{
    ic1_callback = !ic1_callback;
    if(!ir_wait){
        if(ic1_count == 0){
            time_ref = 0;
        }
        timarr[ic1_count] = time_ref;
        ic1_count++;
    }
    if(ic1_count>66){
        ir_received = 1; //set the flag for main
        ir_wait = 1;     //prevent new samples from being written
        ic1_count = 0;
        garbage = time_ref;
    }
}

void irl(void)
{
    
    switch(ir_state)
    {
        case IR_IDLE:        
                //time_ref = 0;
                //ic1_count = 0;
                timind = 0;
                x = timarr[0];
                comm_cnt = 0;
                ir_state = IR_HEADER_HI;
            
            break;
        case IR_HEADER_HI:
            timind++;
            y = timarr[timind];
            if (abs(y - x - (HEADER_MARK)) < CUSHION) {
                ir_state = IR_HEADER_LO;
            }
            else {    
                ir_state = IR_IDLE;
                ir_error = 1;
            }
            
            break;
        case IR_HEADER_LO: 
            timind++;
            x = timarr[timind];
            if (abs(x - y - (HEADER_SPACE)) < CUSHION) {
                ir_state = IR_HEADER_DONE;
            }
            else {  
                ir_state = IR_IDLE;
                ir_error = 1;
            }
                
            break;
        case IR_HEADER_DONE: 
            timind++;
            y = timarr[timind];
            if (abs(y - x - (DATA_MARK)) < CUSHION){
                ir_state = IR_DATA_LO;
            }
            else {  
                ir_state = IR_IDLE;
                ir_error = 1;
            }
            
            break;
        case IR_DATA_LO: 
            timind++;
            x = timarr[timind];
            if (abs(x - y - (ZERO_SPACE)) < CUSHION) {
                ir_data[comm_cnt] = 0;
                comm_cnt++;

            } else if (abs(x - y - (ONE_SPACE)) < CUSHION) {
                ir_data[comm_cnt] = 1;
                comm_cnt++;
                //ir_val = ir_val + power2(31-comm_cnt);

            }
            else {  
                comm_cnt = 0;
                ir_state = IR_IDLE;  
                ir_error = 1;
            }
            if(comm_cnt == 32){
                ir_state = IR_IDLE;
                ir_success = 1;
            }
            else 
            {
                ir_state = IR_DATA_HI;
            }
            
            
            break;
        case IR_DATA_HI: 
            timind++;
            y = timarr[timind];
            if (abs(y - x - (DATA_MARK)) < CUSHION) {
                ir_state = IR_DATA_LO;
            }
            else {  
                ir_state = IR_IDLE;
                ir_error = 1;
            }

            break;
    }
    return;
}
/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    IO_Initialize();
    
    ir_state = IR_IDLE;
    
    println("Started");
    
    
    while (1)
    {
        LED_D9_LAT = ic1_callback;

        if (ir_received)
        {   // Incoming hit from vehicle
            
            // data = infrared_verify(&buffer)
            // 
            // send_hit(data)
            ir_state = IR_IDLE;
            
            while (!ir_success && !ir_error){
                irl();
            }
            
            if(ir_success){
                parse(ir_data);
                LED_D7_LAT = LED_OFF;  
                if(ir_addr == 0x0020){
                    if(ir_comm == 0x00A8){
                        LED_D8_LAT = 1;
                    } else {
                        LED_D8_LAT = 0;
                    }
                }
            } else {
                LED_D7_LAT = LED_ON;
            } 
            
            ir_received = 0;
            ir_success = 0;
            ir_error = 0;
            ir_wait = 0;     
            //ic1_count = 0;
        }
                //LED_D8_LAT = 1;//done;
        
        // Button 3
        if (button_pressed)
        {
            button_pressed = 0;
            button_cnt++;
            
            // Motor PWM
            OC1RS = ((button_cnt % 10) + 1)*64;
            LED_D6_LAT = ~LED_D6_LAT;
        }
        
        // Button 6
        if (mbutton_pressed)
        {
            mbutton_pressed = 0;
            
            sprintf(ic1_str, "%d", ic1_count);
            
            // toggle motor on and off
            
            /*motor_state = !motor_state;
            
            if (motor_state == 1)
            {
                OC1_Stop();
                LED_D4_LAT = LED_OFF;
            }
            else {
                OC1_Start();
                LED_D4_LAT = LED_ON;
            }*/
            
            println(ic1_str);
            
        }
        
        if (!UART1_TransmitBufferIsFull())
        {
            //esp_println("AT");
        }
        
        /*if (!UART1_ReceiveBufferIsEmpty())
        {   // response from esp8266
            
            // Read buffer because it has something
            buffer_size = UART2_ReceiveBufferSizeGet();
            
            if (buffer_size > READ_BUF_LEN)
            {
                buffer_size = READ_BUF_LEN;
            }
            
            UART1_ReadBuffer((uint8_t *) &buffer_read, buffer_size);
            
            println((char *) buffer_read);   // output result to serial terminal
            
            // do_command(buffer_read))
            // send response
        }*/
        /*if (ic1_flag){
            irl();
            ic1_flag = 0;
        }*/
        
    }

    return -1;
}
/**
 End of File
*/