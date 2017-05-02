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
#include "esp8266.h"
#include <float.h>

// CONFIG PARAMETERS

#define DEV_BOARD   0
#define VEHICLE_NUM 0
#define WIFINAME        "NETGEAR85"
#define WIFIPASS        "vastwater606"

// CONSTANTS

#define FORWARD 0
#define REVERSE 1

#define LED_ON 1
#define LED_OFF 0

#define BUTTON_PRESSED      0
#define BUTTON_NOT_PRESSED  1

#define INPUT  1
#define OUTPUT 0

#define FAULT_CONDITION 1

// DEFINE PIN NAMES

#if DEV_BOARD

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

#endif

#define LED_D5_LAT      LATAbits.LATA2
#define LED_D5_TRIS     TRISAbits.TRISA2

#define LED_BACK_LAT    LATFbits.LATF5
#define LED_BACK_TRIS   TRISFbits.TRISF5

#define LED_RIGHT_LAT      LATFbits.LATF4
#define LED_RIGHT_TRIS     TRISFbits.TRISF4

#define LED_LEFT_LAT      LATAbits.LATA9
#define LED_LEFT_TRIS     TRISAbits.TRISA9

#define LED_FRONT_LAT      LATAbits.LATA10
#define LED_FRONT_TRIS     TRISAbits.TRISA10

#define AIN1_TRIS       TRISAbits.TRISA0
#define AIN1_LAT        LATAbits.LATA0

#define BIN1_TRIS       TRISAbits.TRISA1
#define BIN1_LAT        LATAbits.LATA1

#define WIFI_LED_TRIS   TRISAbits.TRISA3
#define WIFI_LED_LAT    LATAbits.LATA3

#define HB_LED_TRIS     TRISEbits.TRISE8
#define HB_LED_LAT      LATEbits.LATE8     

#define RA5_TRIS        TRISAbits.TRISA5
#define RA5_PORT        PORTAbits.RA5

#define MTR_DRIVER_EN_TRIS  TRISEbits.TRISE2
#define MTR_DRIVER_EN_LAT   LATEbits.LATE2

#define MTR_DRIVER_NF_TRIS      TRISEbits.TRISE4
#define MTR_DRIVER_NF_PORT      PORTEbits.RE4

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

// MOTOR PARAMS

#define MOTOR_PERIOD    0x280

#define HIGH_CAL    0x0F
#define LOW_CAL     0x0F

/////////////////
// DATA TYPES
/////////////////

// Infrared States
typedef enum {
    IR_IDLE,
    IR_HEADER_HI,
    IR_HEADER_LO,
    IR_HEADER_DONE,
    IR_DATA_HI,
    IR_DATA_LO,
} ir_state_t;

// Motor Parameters
typedef struct {
    char dir;
    char speed[3];
} MotorParams_t;

// Running time counter
unsigned int time_ref = 0;
unsigned int count = 0;

// Button Debounce
#if DEV_BOARD
unsigned int button_cnt = 0;
unsigned int button_state = 0;
unsigned int button_pressed = 0;

unsigned int mbutton_state = 0;
unsigned int mbutton_pressed = 0;

unsigned int motor_state = 1;
#endif

// Receive IR
ir_state_t ir_state;

unsigned int hit_received = 0;
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
ir_state_t ir_state_o;

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
unsigned int ic4_count_old = 0;
unsigned int ic4_flag = 0;

unsigned int led_flash_count = 0;
unsigned int led_flash_flag = 0;

// ESP working structure and result enumeration
ESP_t ESP;
ESP_Result_t espRes;

// Client connection pointer
ESP_CONN_t* conn;

uint32_t bw;
MotorParams_t * motor_params;

// FUNCTION DECLARATIONS

void IO_Initialize(void);
void IR_Initialize(void);
void WiFi_Initialize(void);

int ESP_Callback(ESP_Event_t evt, ESP_EventParams_t* params);
unsigned int toPercent(unsigned int);

void Check_Hits(void);
int power2(int);
void parse(unsigned int[32]);
void irl(void);
void ir_shot(void);

// FUNCTION DEFINITIONS

void IO_Initialize(void)
{   
    WIFI_LED_TRIS = OUTPUT;
    HB_LED_TRIS = OUTPUT;
    
    AIN1_TRIS = OUTPUT;
    BIN1_TRIS = OUTPUT;
    
    MTR_DRIVER_EN_TRIS = OUTPUT;
    MTR_DRIVER_NF_TRIS = INPUT;
    
    LED_D5_TRIS = OUTPUT;
    
    LED_LEFT_TRIS = OUTPUT;     
    LED_FRONT_TRIS = OUTPUT;
    LED_RIGHT_TRIS = OUTPUT;
    LED_BACK_TRIS = OUTPUT;
    
    #if DEV_BOARD

    S3_TRIS = INPUT;        // PWM Duty Cycle - Button S3
    S6_TRIS = INPUT;        // Motor On/OFF - Button S6
    
    LED_D6_TRIS = OUTPUT;   // LED D6
    LED_D7_TRIS = OUTPUT;   // IC1 Callback indicator
    LED_D8_TRIS = OUTPUT;   // IC1 Callback indicator
    LED_D9_TRIS = OUTPUT;   // IC1 Callback indicator
    LED_D10_TRIS = OUTPUT;   // IC1 Callback indicator
    
    #endif
    
    // Set Input Captures to INPUT
    
    IC1_TRIS = INPUT;
    IC2_TRIS = INPUT;
    IC3_TRIS = INPUT;
    IC4_TRIS = INPUT;
    IC5_TRIS = INPUT;
}

void IR_Initialize(void)
{
    unsigned int i;
    
    ir_state = IR_IDLE;
    time_ref = 0;

    ir_received = 0;
    ir_success = 0;
    ir_error = 0;
    ir_done = 0;

    x = 0;
    y = 0;

    comm_cnt = 0;
    ir_addr = 0;
    ir_addrc = 0;
    ir_comm = 0;
    ir_commc = 0;
    ir_wait = 0;
    
    

    exp_count = 0; 

    // Clear time array
    
    for(i=0;i<67;i++){
        timarr[i] = 0;
    }
    ir_progress_flag = 0;
    error_watch = 0;
    
    // Clear data array 
    
    for(i=0;i<32;i++){
        ir_data[i] = 0;
    }
    timind = 0;

    // Send IR

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

void WiFi_Initialize(void)
{    
    unsigned int wifi_status = 0;
    
    /* Init ESP library with 115200 baud */
    if ((espRes = ESP_Init(&ESP, 115200, ESP_Callback)) == espOK) {
        printf("ESP module init successfully!\r\n");
        wifi_status = 1;
    } else {
        wifi_status = 0;
        printf("ESP Init error. Status: %d\r\n", espRes);
    }
    
    if ((espRes = ESP_STA_Connect(&ESP, WIFINAME, WIFIPASS, NULL, 1, 1)) == espOK) {
        printf("Connected to network\r\n");
        wifi_status = wifi_status && 1;
    } else {
        wifi_status = 0;
        printf("Problems trying to connect to network: %d\r\n", espRes);
    }
    
    /* Enable server mode on port 4444 in non-blocking mode */
    
    if ((espRes = ESP_SERVER_Enable(&ESP, 4444, 0)) == espOK) {
        printf("Server mode enabled. Connect to %d.%d.%d.%d:%d\r\n", ESP.STAIP[0], ESP.STAIP[1], ESP.STAIP[2], ESP.STAIP[3], 4444);
        wifi_status = wifi_status && 1;
    }
    else {
        wifi_status = 0;
        printf("Problems trying to enable server mode: %d\r\n", espRes);
    }
    
    if (wifi_status)
    {
        WIFI_LED_LAT = LED_ON;
    }
}

void Check_Hits(void)
{   
    if (ir_received)
        {   // Incoming hit from vehicle
           
            ir_state = IR_IDLE;
            
            while (!ir_success && !ir_error)
            {
                irl();
            }
            
            if(ir_success)
            {
                parse(ir_data); 
                
                if(ir_addr == 0x0020){
                    if(ir_comm == 0x0010){  //A8 for "5", 10 for "power"
                        hit_received = 1;
                        led_flash_flag = 1;
                        led_flash_count = 0;
                    }
                }
            }              
           
            IR_Initialize();
        }
}

void ir_shot(void){

    switch(ir_state_o)
    {
        case IR_IDLE:        

            OC1_Start();
            ir_state_o = IR_HEADER_HI;
            timindo = 0;
            OC1RS = 0x00D3;
            
            break;
        case IR_HEADER_HI:
            timindo++;
            
            if (timindo >= (HEADER_MARK/14)) {
                ir_state_o = IR_HEADER_LO;
                timindo = 0;
                OC1RS = 0x0000;
            } 
            else {    
                ir_state_o = IR_HEADER_HI;
            }
            break;
            
        case IR_HEADER_LO: 
            timindo++;
            if (timindo >= (HEADER_SPACE/14)) {
                ir_state_o = IR_HEADER_DONE;
                timindo = 0;
                OC1RS = 0x00D3;
            }
            else {  
                ir_state_o = IR_HEADER_LO;
            }
                
            break;
        case IR_HEADER_DONE: 
            timindo++;
            if (timindo >= (DATA_MARK/14)){
                ir_state_o = IR_DATA_LO;
                timindo = 0;
                OC1RS = 0x0000;
            }
            else {  
                ir_state_o = IR_HEADER_DONE;
            }            
            
            break;
        case IR_DATA_LO: 
            timindo++;
            ir_state_o = IR_DATA_LO;
            if (shot_data[comm_cnto] == 0){
                if(timindo >= (ZERO_SPACE/14)) {
                    comm_cnto++;
                    ir_state_o = IR_DATA_HI;
                    timindo = 0;
                    OC1RS = 0x00D3;
                }
            } else if (shot_data[comm_cnto] == 1){
                if(timindo >= (ONE_SPACE/14)) {
                    comm_cnto++;
                    ir_state_o = IR_DATA_HI;
                    timindo = 0;
                    OC1RS = 0x00D3;
                }
            }
                      
            break;
        case IR_DATA_HI: 
            timindo++;
            
            if (timindo >= (DATA_MARK/14)) {
                if(comm_cnto == 32){
                    ir_state_o = IR_IDLE;
                    ir_shot_flag = 0; //ir_shot_flag
                    comm_cnto = 0;
                    OC1RS = 0x0000;
                    OC1_Stop();
                } else {
                    ir_state_o = IR_DATA_LO;
                    timindo = 0;
                    OC1RS = 0x0000;
                }
            }
            else {  
                ir_state_o = IR_DATA_HI;
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
    if(!ir_wait){ //&& !ic1_flag && !ic2_flag && !ic3_flag){
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
    if (!ir_wait){ // && !ic1_flag && !ic2_flag && !ic4_flag){
        if(ic3_count == 0){
            time_ref = 0;
            error_watch = 0;
            ir_progress_flag = 1;
            ic3_flag = 1;
        }
        timarr[ic3_count] = time_ref;
        ic3_count++;
    }
    if (ic3_count>66){
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
            //ir_progress_flag = 1;
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
        //ir_progress_flag = 1;
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
    
    if (ir_progress_flag){
        error_watch++;
        
        if(error_watch > 227){//(error_watch > 2200){
            if(ic4_count_old == ic4_count){
                unsigned int i;
                for(i=0;i<67;i++){
                    timarr[i] = 0;
                }
                ir_progress_flag = 0;
                ic1_count = 0;
                error_watch = 0;
                IR_Initialize();
             }
            error_watch = 0;   
        }
    }
         
    
    if (led_flash_flag)
    {
        led_flash_count++;
        if((led_flash_count == 500) || (led_flash_count == 1500) || (led_flash_count == 2500) || (led_flash_count == 3500) || (led_flash_count == 4500))
        {
            LED_LEFT_LAT = LED_ON;
            LED_RIGHT_LAT = LED_ON;
            LED_FRONT_LAT = LED_ON;
            LED_BACK_LAT = LED_ON;
        }
        else if((led_flash_count == 1000) || (led_flash_count == 2000) || (led_flash_count == 3000) || (led_flash_count == 4000) || (led_flash_count == 5000)){
            LED_LEFT_LAT = LED_OFF;
            LED_RIGHT_LAT = LED_OFF;
            LED_FRONT_LAT = LED_OFF;
            LED_BACK_LAT = LED_OFF;
        }
        if(led_flash_count >= 5005){
            led_flash_flag = 0;
            led_flash_count = 0;
        }
    }
    
    
    if (((ir_send % 14) == 0) && ir_shot_flag)
    {
        ir_shot();
    }
    
    if (count % 25 == 0)
    {   // 1ms period
        
        ESP_UpdateTime(&ESP, 1);
        #if DEV_BOARD
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
        #endif
    }
    
    // 0.4s period
    
    if (count == 10000)
    {
        HB_LED_LAT = LED_ON;
        LED_D5_LAT = LED_ON;
    }
    
    // 0.8s period
    
    else if (count == 20000)
    {
        HB_LED_LAT = LED_OFF;
        LED_D5_LAT = LED_OFF;
        count = 0;
    }
}

unsigned int toPercent(unsigned int speed)
{   
    speed = (speed > 0x7F) ? (speed - 0x7F) : speed;
    return (unsigned int) (((float) speed)/((float) 0x7F) * 100);
}

int ESP_Callback(ESP_Event_t evt, ESP_EventParams_t* params) {
    ESP_CONN_t* conn;
    uint8_t* data;
    char resp_str[10];
    unsigned int speed;
    uint16_t period;
    uint16_t calc_period;
    
    switch (evt) {                              /* Check events */
        case espEventIdle:
            printf("Stack is IDLE!\r\n");
            break;
        case espEventConnActive: {
            conn = (ESP_CONN_t *)params->CP1;   /* Get connection for event */
            printf("Connection %d just became active!\r\n", conn->Number);
            break;
        }
        case espEventConnClosed: {
            conn = (ESP_CONN_t *)params->CP1;   /* Get connection for event */
            printf("Connection %d was just closed!\r\n", conn->Number);
            break;
        }
        case espEventDataReceived: {
            conn = (ESP_CONN_t *)params->CP1;   /* Get connection for event */
            data = (uint8_t *)params->CP2;      /* Get data */
        
            /* Notify user about information */
        
            if (ESP_IsReady(&ESP) == espOK) {   /* Send data back when we have received all the data from device */
                if (data[0] == 'r') {
                    // received "r"
                    motor_params = (MotorParams_t *) data;
                    motor_params->speed[2] = '\0';
                    speed = strtol(motor_params->speed, NULL, 16);
                    printf("Motor: %c \r\n", motor_params->dir);
                    printf("Raw Speed: %u \r\n", speed);
                    printf("Speed Percent: %d%% \r\n", toPercent(speed));
                    
                    if (speed > 0xF8)
                    {
                        speed = 0xF8;
                    }
                    
                    if (speed < 0x05)
                    {
                        speed = 0x05;
                    }
                    
                    if (speed > 0x7F)
                    { // forward
                        speed = speed - 0x7F;
                        AIN1_LAT = REVERSE;
                        printf("Direction: forward\r\n");
                    }
                    else
                    { // reverse
                        AIN1_LAT = FORWARD;
                        printf("Direction: reverse\r\n");
                    }
                    
                    period = (uint16_t) ((float)speed * (float) MOTOR_PERIOD / (float) (0x7F));
                    printf("Period Register: %X\r\n", period);
                    espRes = ESP_CONN_Send(&ESP, conn, (const uint8_t *) "r received\r\n", sizeof("r received\r\n"), &bw, 0);
                
                    OC2RS = MOTOR_PERIOD - period;
                }
                else if (data[0] == 'l')
                {
                    // received "l"
                    motor_params = (MotorParams_t *) data;
                    motor_params->speed[2] = '\0';
                    speed = strtol(motor_params->speed, NULL, 16);
                    printf("Motor: %c \r\n", motor_params->dir);
                    printf("Raw Speed: %u \r\n", speed);
                    printf("Speed Percent: %d%% \r\n", toPercent(speed));
                    
                    if (speed > 0xF8)
                    {
                        speed = 0xF8;
                    }
                    
                    if (speed < 0x05)
                    {
                        speed = 0x05;
                    }
                    
                    if (speed > 0x7F)
                    { // forward
                        /*if (speed < 0x7F + LOW_CAL)
                        {
                            speed = 0x7F + LOW_CAL;
                        }
                        if (speed > 0xFF - HIGH_CAL)
                        {
                            speed = 0xFF - HIGH_CAL;
                        }*/
                        
                        speed = speed - 0x7F;
                        BIN1_LAT = REVERSE;
                        printf("Direction: forward\r\n");
                    }
                    else // speed < 0x7F
                    { // reverse
                        
                        /*if (speed < 0x7F - LOW_CAL)
                        {
                            speed = 0x7F - LOW_CAL;
                        }
                        if (speed < 0xFF - HIGH_CAL)
                        {
                            speed = 0xFF - HIGH_CAL;
                        }*/
                        
                        BIN1_LAT = FORWARD;
                        printf("Direction: reverse\r\n");
                    }
                    
                    
                    period = (uint16_t) ((float)speed * (float) MOTOR_PERIOD / (float) (0x7F));
                    printf("Period Register: %X\r\n", period);
                    espRes = ESP_CONN_Send(&ESP, conn, (const uint8_t *) "l received\r\n", sizeof("l received\r\n"), &bw, 0);
                
                    calc_period = MOTOR_PERIOD - period;
                    OC3RS = calc_period;
                }
                else if (data[0] == 'c')
                {
                    // received "connect"
                    printf("Data received: %s (%lu bytes)\r\n", (char *) data, (unsigned long) params->UI);
                    espRes = ESP_CONN_Send(&ESP, conn, (const uint8_t *) "connect received\r\n", sizeof("connect received\r\n"), &bw, 0);
                }
                else if (data[0] == 'h')
                { // received "hits"
                    
                    printf("Data received: %s (%lu bytes)\r\n", (char *) data, (unsigned long) params->UI);
                    
                    if (hit_received)
                    {
                        hit_received = 0;
                        sprintf(resp_str, "h%d\r\n", VEHICLE_NUM);
                        espRes = ESP_CONN_Send(&ESP, conn, (const uint8_t *) resp_str, sizeof(resp_str), &bw, 0);
                    }
                }
                else if (data[0] == 'f')
                {
                    // received "fire"
                    ir_shot_flag = 1;
                    printf("Data received: %s (%lu bytes)\r\n", (char *) data, (unsigned long) params->UI);
                    espRes = ESP_CONN_Send(&ESP, conn, (const uint8_t *) "fire received\r\n", sizeof("fire received\r\n"), &bw, 0);
                }
                else {
                    printf("Data received: %s (%lu bytes)\r\n", (char *) data, (unsigned long) params->UI);
                    espRes = ESP_CONN_Send(&ESP, conn, (const uint8_t *) "hello\r\n", sizeof("hello\r\n"), &bw, 0); /* Send data on other requests */
                }
            }
            break;
        }
        case espEventDataSent:
            conn = (ESP_CONN_t *)params->CP1;   /* Get connection for event */
            printf("Data sent on connection %d\r\n", conn->Number);
            //printf("Close conn resp: %d\r\n", ESP_CONN_Close(&ESP, conn, 0));
            break;
        case espEventDataSentError:
            conn = (ESP_CONN_t *)params->CP1;   /* Get connection for event */
            printf("Data Sent Error\r\n");
            //ESP_CONN_Close(&ESP, conn, 0);
            break;
        default:
            printf("Default State\r\n");
            break;
    }
    
    return 0;
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
    WiFi_Initialize();
    
    MTR_DRIVER_EN_LAT = 1;
    
    //AIN1_LAT = REVERSE;
    //OC2RS = MOTOR_PERIOD/2;
    
    //BIN1_LAT = REVERSE;
    //OC3RS = MOTOR_PERIOD/2;
    
    printf("Started Main Loop\r\n");
     
    while (1)
    {
        #if DEV_BOARD
        LED_D9_LAT = ic1_callback;
        #endif

        ESP_Update(&ESP);
        Check_Hits();
        
        if (MTR_DRIVER_NF_PORT == FAULT_CONDITION)
        {   // motor driver fault
            
        }
        
        #if DEV_BOARD
        // Button 3
        if (button_pressed)
        {
            button_pressed = 0;
            ir_shot_flag = 1;
            ir_send = 0;
            ir_state_o = IR_IDLE_O;
        }
        #endif
    }

    return -1;
}
/**
 End of File
*/