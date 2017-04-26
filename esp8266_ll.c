/** 
   ----------------------------------------------------------------------
    Copyright (c) 2016 Tilen Majerle

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge,
    publish, distribute, sublicense, and/or sell copies of the Software, 
    and to permit persons to whom the Software is furnished to do so, 
    subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
    AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
   ----------------------------------------------------------------------
 */
#include "esp8266_ll.h"
#include "mcc_generated_files/uart1.h"

/* Include platform dependant libraries */

uint8_t ESP_LL_Init(ESP_LL_t* LL) {
        
    /* We were successful */
    return 0;
}

uint8_t ESP_LL_SendData(ESP_LL_t* LL, const uint8_t* data, uint16_t count) {
    /* Send data */
    UART1_WriteBuffer((uint8_t *)data, count);
    
    /* We were successful */
    return 0;
}

uint8_t ESP_LL_SetReset(ESP_LL_t* LL, uint8_t state) {
    /* Set pin according to status */
    if (state == ESP_RESET_SET) {
        //TM_GPIO_SetPinLow(LL_RESET_PORT, LL_RESET_PIN);
    } else {
        //TM_GPIO_SetPinHigh(LL_RESET_PORT, LL_RESET_PIN);
    }
    
    /* We are OK */
    return 0;
}

uint8_t ESP_LL_SetRTS(ESP_LL_t* LL, uint8_t state) {
    /* We are OK */
    return 0;
}

/* USART receive interrupt handler */
void U1_RX_Callback(uint8_t ch) {
    /* Send received character to ESP stack */
    ESP_DataReceived(&ch, 1);
}
