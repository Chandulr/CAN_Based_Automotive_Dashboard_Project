/*
 * File:   main.c
 * Author: Chandu
 *
 * Created on September 28, 2026, 12:40 PM
 */

#include <xc.h>
#include <stdint.h>
#include "adc.h"
#include "clcd.h"
#include "ssd.h"
#include "dkp.h"
#include "mkp.h"
#include "CAN.h"
#include "msg_id.h"


#define left_led0      RB0
#define left_led1      RB1

#define right_led0     RB7
#define right_led1     RB6


#define IND_OFF        0
#define IND_LEFT       1
#define IND_RIGHT      2


void init_config(void)
{
    init_adc();
    init_clcd();
    init_digital_keypad();
    init_ssd_control();
    init_can();

    /* LED pins as output */
    TRISB0 = 0;
    TRISB1 = 0;
    TRISB6 = 0;
    TRISB7 = 0;

    /* LEDs OFF initially */
    left_led0 = 0;
    left_led1 = 0;
    right_led0 = 0;
    right_led1 = 0;
}


/* Convert a single digit into corresponding SSD pattern */

unsigned char get_ssd_digit(unsigned char digit)
{
    switch (digit)
    {
        case 0: return ZERO;
        case 1: return ONE;
        case 2: return TWO;
        case 3: return THREE;
        case 4: return FOUR;
        case 5: return FIVE;
        case 6: return SIX;
        case 7: return SEVEN;
        case 8: return EIGHT;
        case 9: return NINE;

        default: return BLANK;
    }
}


/* Convert RPM into four SSD digits */

void rpm_to_ssd(unsigned int rpm, unsigned char *ssd)
{
    unsigned char digit0;
    unsigned char digit1;
    unsigned char digit2;
    unsigned char digit3;

    digit0 = rpm / 1000;
    digit1 = (rpm / 100) % 10;
    digit2 = (rpm / 10) % 10;
    digit3 = rpm % 10;

    ssd[0] = get_ssd_digit(digit0);
    ssd[1] = get_ssd_digit(digit1);
    ssd[2] = get_ssd_digit(digit2);
    ssd[3] = get_ssd_digit(digit3);
}


void main(void)
{
    unsigned char key;

    unsigned int adc_value;
    unsigned int rpm;

    unsigned int led_blink = 0;
    unsigned char blink_state = 0;

    unsigned char indicator = IND_OFF;

    unsigned char ssd[MAX_SSD_CNT];
    
    /* CAN TX data */
    unsigned char rpm_data[2];
    unsigned char indicator_data;
    
//    /* CAN RX data */
//    uint8_t rx_data[5];
//    uint8_t rx_len;
//    uint16_t rx_id;

    /* Received values */
    unsigned int rx_rpm;

    init_config();

    while (1)
    {
        key = read_digital_keypad(EDGE);


        if (key == sw1)
        {
            /* Select LEFT indicator */
            indicator = IND_LEFT;

            led_blink = 0;
            blink_state = 0;
        }
        else if (key == sw2)
        {
            /* Select RIGHT indicator */
            indicator = IND_RIGHT;

            led_blink = 0;
            blink_state = 0;
        }
        else if (key == sw3)
        {
            /* Turn indicators OFF */
            indicator = IND_OFF;

            led_blink = 0;
            blink_state = 0;
        }


        
        // RPM CONTROL
        adc_value = read_adc(CHANNEL4);

        /*
         * ADC = 0     -> 0 RPM
         *  ADC = 1023  -> 6000 RPM
         */

        rpm = (adc_value * 6000UL) / 1023;

         // TRANSMITING RPM
        rpm_data[0] = (rpm >> 8) & 0xFF;
        rpm_data[1] = rpm & 0xFF;

        can_transmit(RPM_MSG_ID,rpm_data,2);

        // TRANSMITING INDICATOR
        indicator_data = indicator;
        can_transmit(INDICATOR_MSG_ID,&indicator_data,1);
       
//        // RECEIVEING CAN DATA
//        can_receive(&rx_id,rx_data,&rx_len);
//
//        if (rx_len > 0)
//        {
//             // RECEIVED RPM
//
//            if (rx_id == RPM_MSG_ID && rx_len == 2)
//            {
//                rx_rpm = ((unsigned int)rx_data[0] << 8)| rx_data[1];
//
//                rpm_to_ssd(rx_rpm, ssd);
//                display(ssd);
//
//            }
//            
//            // RECEIVED INDICATOR
//
//            else if (rx_id == INDICATOR_MSG_ID && rx_len == 1)
//            {
//                indicator = rx_data[0];
//            }
//        }
            
            
            
//            
//            
//         // INDICATOR BLINKING
//
//        if (indicator == IND_LEFT)
//        {
//            led_blink++;
//
//            if (led_blink >= 5)
//            {
//                led_blink = 0;
//                blink_state = !blink_state;
//            }
//
//            left_led0 = blink_state;
//            left_led1 = blink_state;
//
//            right_led0 = 0;
//            right_led1 = 0;
//        }
//        else if (indicator == IND_RIGHT)
//        {
//            led_blink++;
//
//            if (led_blink >= 5)
//            {
//                led_blink = 0;
//                blink_state = !blink_state;
//            }
//
//            right_led0 = blink_state;
//            right_led1 = blink_state;
//
//            left_led0 = 0;
//            left_led1 = 0;
//        }
//        else
//        {
//            /* Indicators OFF */
//
//            left_led0 = 0;
//            left_led1 = 0;
//
//            right_led0 = 0;
//            right_led1 = 0;
//        }


            
            

        


        
        
        
        
        
        
//        /* Convert RPM to SSD pattern */
//        rpm_to_ssd(rpm, ssd);
//
//        /* Display RPM */
//        display(ssd);
    }
}