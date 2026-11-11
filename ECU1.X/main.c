/*
 * File:   ECU1_main.c
 * Author: chandu
 *
 * Created on September 28, 2026, 12:40 PM
 */

#include <xc.h>
#include <stdint.h>            // added: needed for uint8_t / uint16_t
#include "adc.h"
#include "clcd.h"
#include "msg_id.h"
#include "mkp.h"
#include "CAN1.h"


#define MAX_GEAR        7
#define MIN_GEAR        0


/* Gear index */
unsigned char gear_index = 0;


/* Gear states */
const unsigned char gear[8][3] =
{
    "ON",
    "GN",
    "G1",
    "G2",
    "G3",
    "G4",
    "G5",
    "GR"
};

void init_config(void)
{
    init_adc();
    init_matrix_keypad();
    init_clcd();
    init_can();
}

//
//void speed_to_string(unsigned int speed, unsigned char *str)
//{
//    str[0] = (speed / 10) + '0';
//    str[1] = (speed % 10) + '0';
//    str[2] = '\0';
//}


void main(void)
{
    unsigned char key;

    unsigned int adc_value;

    unsigned int speed;
    unsigned char speed_str[3];
//
//    uint8_t  rx_data[5];          // CAN frame can hold up to 8 bytes + '\0' but rpm can hold 4bytes + 1bytes to hold NULL character
//    uint8_t  rx_len = 0;          // initialised
//    uint16_t rx_id  = 0;          // matches can_receive() prototype

    unsigned char gear_label[]  = "GEAR:";
    unsigned char speed_label[] = "SPEED:";


    /* Initialize peripherals */
    init_config();

    /* labels never change, so print them once */
//    clcd_print(gear_label,  LINE1(0));
//    clcd_print(speed_label, LINE2(0));


    while (1)
    {
        key = read_switches(STATE_CHANGE);

        // GEAR CONTROL

        if (key == MK_SW1)
        {
            if (gear_index < MAX_GEAR)
            {
                gear_index++;
            }
        }

        else if (key == MK_SW2)
        {
            if (gear_index > MIN_GEAR)
            {
                gear_index--;
            }
        }


        // SPEED CONTROL

        adc_value = read_adc(CHANNEL4);

        // ADC = 0    -> Speed = 0
        // ADC = 1023 -> Speed = 99
        speed = (adc_value * 99UL) / 1023;

//        speed_to_string(speed, speed_str);

//
//        // CAN TRANSMIT
//        can_transmit(GEAR_MSG_ID,  gear[gear_index], 2);
//        can_transmit(SPEED_MSG_ID, speed_str, 2);

        /* SEND SPEED */

        speed_str[0] = (speed >> 8) & 0xFF;
        speed_str[1] = speed & 0xFF;

        can_transmit(SPEED_MSG_ID, speed_str, 2);
        can_transmit(GEAR_MSG_ID, gear[gear_index], 2);
        
        
//
//        // CAN RECEIVE
//        can_receive(&rx_id, rx_data, &rx_len);
//    
//        if (rx_len == 2)
//        {
//            rx_data[2] = '\0';
//            if (rx_id == GEAR_MSG_ID)
//            {
//               clcd_print(rx_data, LINE1(6));
//            }
//        
//            else if (rx_id == SPEED_MSG_ID)
//            {
//               clcd_print(rx_data, LINE2(6));
//            }
//    }
    
    }
}