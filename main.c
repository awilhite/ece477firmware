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

enum {
    IR_IDLE_O,
    IR_HEADER_HI_O,
    IR_HEADER_LO_O,
    IR_HEADER_DONE_O,
    IR_DATA_HI_O,
    IR_DATA_LO_O,
} ir_state_o;

// Button Debounce

unsigned int count = 0;
unsigned int button_cnt = 0;
unsigned int button_state = 0;
unsigned int button_pressed = 0;

unsigned int mbutton_state = 0;
unsigned int mbutton_pressed = 0;

unsigned int motor_state = 1;

// Receive IR

unsigned int time_ref = 0;

unsigned int hit_received = 0;  //SET THIS FLAG FOR HIT (then clear once sent)
unsigned int ir_received = 0;
unsigned int ir_success = 0;
unsigned int ir_error = 0;
unsigned int ir_done = 0;

unsigned int x = 0;
unsigned int y = 0;

unsigned int comm_cnt = 0;

unsigned int ir_data[32];
unsigned int ir_addr = 0;
unsigned int ir_addrc = 0;
unsigned int ir_comm = 0;
unsigned int ir_commc = 0;
unsigned int ir_wait = 0;
unsigned int error_watch = 0;
unsigned int ir_progress_flag = 0;

unsigned int exp_count = 0; 
unsigned int timarr[67] = {0};
unsigned int timarr2[67] = {0};
unsigned int timind = 0;

// Send IR

unsigned int shot_data [32] =   {0,0,1,0,0,0,0,0,
                                1,1,0,1,1,1,1,1,
                                0,0,0,1,0,0,0,0,
                                1,1,1,0,1,1,1,1};
unsigned int ir_send;
unsigned int ir_shot_flag;
unsigned int timindo = 0;
unsigned int comm_cnto = 0;


// IR interrupt signals
unsigned int ic1_callback = 0;
unsigned int ic1_count = 0;
unsigned int ic1_flag = 0;
unsigned int ic2_count = 0;
unsigned int ic2_flag = 0;
unsigned int ic3_count = 0;
unsigned int ic3_flag = 0;
unsigned int ic4_count = 0;
unsigned int ic4_flag = 0;




// Function Declarations

void println(char *);
void esp_println(char *);
void IO_Initialize(void);

void IR_Initialize(void);

int power2(int);
void parse(unsigned int[32]);
void irl(void);

void ir_shot(void);

//FUNCTIONS BEGIN

void println(char * str)
{
    unsigned int length = 0;
    
    while (str[length] != '\0')
    {
        length++;
    }
    
    //UART2_WriteBuffer((uint8_t *) str, length);
    //UART2_WriteBuffer((uint8_t *) "\r\n", (uint8_t) 2);
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

void IR_Initialize(void)
{
    time_ref = 0;

    ir_received = 0;
    ir_success = 0;
    ir_error = 0;
    ir_done = 0;

    x = 0;
    y = 0;

    comm_cnt = 0;
    //ir_data[32]
    ir_addr = 0;
    ir_addrc = 0;
    ir_comm = 0;
    ir_commc = 0;
    ir_wait = 0;

    exp_count = 0; 
    unsigned int i;
    for(i=0;i<67;i++){
        timarr[i] = 0;
    }
    
    for(i=0;i<32;i++){
        ir_data[i] = 0;
    }
    timind = 0;

    // Send IR

    //shot_data [32] = {0};
    ir_send = 0;

    ic1_callback = 0;
    ic1_count = 0;
    ic1_flag = 0;
    ic2_count = 0;
    ic2_flag = 0;
    ic3_count = 0;
    ic3_flag = 0;
    ic4_count = 0;
    ic4_flag = 0;
}

void ir_shot(void){
    //OC2_Start();
    switch(ir_state_o)
    {
        case IR_IDLE_O:        

            OC2_Start();
            ir_state_o = IR_HEADER_HI_O;
            timindo = 0;
            OC2RS = 0x00D3;
            
            break;
        case IR_HEADER_HI_O:
            timindo++;
            
            if (timindo >= (HEADER_MARK/14)) {
                ir_state_o = IR_HEADER_LO_O;
                timindo = 0;
                OC2RS = 0x0000;
            } 
            else {    
                ir_state_o = IR_HEADER_HI_O;
            }
            break;
            
        case IR_HEADER_LO_O: 
            timindo++;
            if (timindo >= (HEADER_SPACE/14)) {
                ir_state_o = IR_HEADER_DONE_O;
                timindo = 0;
                OC2RS = 0x00D3;
            }
            else {  
                ir_state_o = IR_HEADER_LO_O;
            }
                
            break;
        case IR_HEADER_DONE_O: 
            timindo++;
            if (timindo >= (DATA_MARK/14)){
                ir_state_o = IR_DATA_LO_O;
                timindo = 0;
                OC2RS = 0x0000;
            }
            else {  
                ir_state_o = IR_HEADER_DONE_O;
            }            
            
            break;
        case IR_DATA_LO_O: 
            timindo++;
            ir_state_o = IR_DATA_LO_O;
            if (shot_data[comm_cnto] == 0){
                if(timindo >= (ZERO_SPACE/14)) {
                    comm_cnto++;
                    ir_state_o = IR_DATA_HI_O;
                    timindo = 0;
                    OC2RS = 0x00D3;
                }
            } else if (shot_data[comm_cnto] == 1){
                if(timindo >= (ONE_SPACE/14)) {
                    comm_cnto++;
                    ir_state_o = IR_DATA_HI_O;
                    timindo = 0;
                    OC2RS = 0x00D3;
                }
            }
                      
            break;
        case IR_DATA_HI_O: 
            timindo++;
            
            if (timindo >= (DATA_MARK/14)) {
                if(comm_cnto == 32){
                    ir_state_o = IR_IDLE_O;
                    ir_shot_flag = 0; //ir_shot_flag
                    comm_cnto = 0;
                    OC2RS = 0x0000;
                    OC2_Stop();
                } else {
                    ir_state_o = IR_DATA_LO_O;
                    timindo = 0;
                    OC2RS = 0x0000;
                }
            }
            else {  
                ir_state_o = IR_DATA_HI_O;
            }

            break;
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

void IC4_CallBack(void)
{
    if(!ir_wait && !ic1_flag && !ic2_flag && !ic3_flag){
        if(ic4_count == 0){
            time_ref = 0;
            error_watch = 0;
            ir_progress_flag = 1;
            ic4_flag = 1;
        }
        timarr[ic4_count] = time_ref;
        ic4_count++;
    }
    if(ic4_count>66){
        ir_received = 1; //set the flag for main
        ir_wait = 1;     //prevent new samples from being written
        ic4_count = 0;
        ir_progress_flag = 0;
        ic4_flag = 0;
    }
}

void IC3_CallBack(void)
{
    if(!ir_wait && !ic1_flag && !ic2_flag !ic4_flag){
        if(ic3_count == 0){
            time_ref = 0;
            error_watch = 0;
            ir_progress_flag = 1;
            ic3_flag = 1;
        }
        timarr[ic3_count] = time_ref;
        ic3_count++;
    }
    if(ic3_count>66){
        ir_received = 1; //set the flag for main
        ir_wait = 1;     //prevent new samples from being written
        ic3_count = 0;
        ir_progress_flag = 0;
        ic3_flag = 0;
    }
}

void IC2_CallBack(void)
{
    if(!ir_wait && !ic1_flag && !ic3_flag && !ic4_flag){
        if(ic2_count == 0){
            time_ref = 0;
            error_watch = 0;
            ir_progress_flag = 1;
            ic2_flag = 1;
        }
        timarr[ic2_count] = time_ref;
        ic2_count++;
    }
    if(ic2_count>66){
        ir_received = 1; //set the flag for main
        ir_wait = 1;     //prevent new samples from being written
        ic2_count = 0;
        ir_progress_flag = 0;
        ic2_flag = 0;
    }
}

void IC1_CallBack(void)
{
    ic1_callback = !ic1_callback;
    
    if(!ir_wait && !ic2_flag && !ic3_flag && !ic4_flag){
        if(ic1_count == 0){
            time_ref = 0;
            error_watch = 0;
            ir_progress_flag = 1;
            ic1_flag = 1;
        }
        timarr[ic1_count] = time_ref;
        ic1_count++;
    }
    if(ic1_count>66){
        ir_received = 1; //set the flag for main
        ir_wait = 1;     //prevent new samples from being written
        ic1_count = 0;
        ir_progress_flag = 0;
        ic1_flag = 0;
    }
}

void TMR2_CallBack(void)
{
    // 40us period
    
    time_ref++;
    count++;
    ir_send++;
    
    if(ir_progress_flag){
        error_watch++;
        if(error_watch > 2185){
            unsigned int i;
            for(i=0;i<67;i++){
                timarr[i] = 0;
            }
            ir_progress_flag = 0;
            ic1_count = 0;
        }
    }
        
    
    // 1ms period
    if (((ir_send % 14) == 0) && ir_shot_flag)
    {
        ir_shot();
    }
    
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
    }
}

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    IO_Initialize();
    IR_Initialize();
    
    ir_state = IR_IDLE;
    
    println("Started");
    
    //shot_data [32] =    
    
    
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
                if(ir_addr == 0x0020){
                    if(ir_comm == 0x0010){  //A8 for 5, 10 for "power"
                        hit_received = 1;
                    }
                }
            }              
            
            //ir_received = 0;
            //ir_success = 0;
            //ir_error = 0;
            //ir_wait = 0;     
            //ic1_count = 0;
            IR_Initialize();
        }
                //LED_D8_LAT = 1;//done;
        
        // Button 3
        if (button_pressed)
        {
            button_pressed = 0;
            //button_cnt++;
            ir_shot_flag = 1;
            ir_send = 0;
            ir_state_o = IR_IDLE_O;
            //ir_shot(shot_data);
            // Motor PWM
            //OC1RS = ((button_cnt % 10) + 1)*64;
            //LED_D6_LAT = ~LED_D6_LAT;
        }
        
        // Button 6
        if (mbutton_pressed)
        {
            mbutton_pressed = 0;
            //ir_shot(shot_data);
            //sprintf(ic1_str, "%d", ic1_count);
            
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
            
            //println(ic1_str);
            
        }
        
        if (!UART1_TransmitBufferIsFull())
        {
            //esp_println("AT");
        }        
    }

    return -1;
}
/**
 End of File
*/