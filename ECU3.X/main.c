/*
 * File:   main.c
 * Author: chandu
 *
 * Created on October 1, 2026, 12:04 PM
 */


#include <xc.h>
#include <stdint.h>

#include "clcd.h"
#include "ssd.h"
#include "CAN.h"
#include "msg_id.h"


#define left_led0      RB0
#define left_led1      RB1

#define right_led0     RB7
#define right_led1     RB6


#define IND_OFF        0
#define IND_LEFT       1
#define IND_RIGHT      2


unsigned int rpm = 0;
unsigned int speed = 0;

unsigned char indicator = IND_OFF;

unsigned char gear[3] = "ON";

void init_config(void)
{
    init_clcd();
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

void speed_to_string(unsigned int speed, unsigned char *str)
{
    str[0] = (speed / 10) + '0';
    str[1] = (speed % 10) + '0';
    str[2] = '\0';
}


void rpm_to_string(unsigned int rpm, unsigned char *str)
{

    str[0] = (rpm / 1000) + '0';
    str[1] = ((rpm / 100) % 10) + '0';
    str[2] = ((rpm / 10) % 10) + '0';
    str[3] = (rpm % 10) + '0';
    str[4] = '\0';

}

void main(void)
{
    uint16_t rx_id;
    uint8_t rx_data[8];
    uint8_t rx_len = 0;
    
    unsigned char rpm_str[5];
    unsigned char speed_str[5];
    
    unsigned int led_blink = 0;
    unsigned char blink_state = 0;

    unsigned char ssd[MAX_SSD_CNT];

    init_config();

    /* Initial CLCD display */

    clcd_print("RPM ", LINE1(0));
    clcd_print("SPD ", LINE1(4));
    clcd_print("GER ", LINE1(8));
    clcd_print("IND ", LINE1(11));

    while (1)
    {

        can_receive(&rx_id, rx_data, &rx_len);

        if (rx_len > 0)
        {
            switch (rx_id)
            {
                case RPM_MSG_ID:
                    if (rx_len == 2)
                    {
                        rpm = ((unsigned int)rx_data[0] << 8) | rx_data[1];
                    }

                    break;

                case INDICATOR_MSG_ID:
                    if (rx_len == 1)
                    {
                        indicator = rx_data[0];
                    }
                    break;

                case SPEED_MSG_ID:
                    if (rx_len == 2)
                    {
                        speed = ((unsigned int)rx_data[0] << 8) | rx_data[1];
                    }
                    break;

                case GEAR_MSG_ID:
                    if (rx_len == 2)
                    {
                        gear[0] = rx_data[0];
                        gear[1] = rx_data[1];
                        gear[2] = '\0';
                    }
                    break;
            }
        }

        rpm_to_string(rpm, rpm_str);
        clcd_print(rpm_str, LINE2(0));
        
        speed_to_string(speed, speed_str);
       clcd_print(speed_str, LINE2(5));


        clcd_print(gear, LINE2(8));


        if (indicator == IND_LEFT)
        {
             led_blink++;

           if(led_blink >= 5000)
            {
                led_blink = 0;
                blink_state = !blink_state;
            }

            left_led0 = blink_state;
            left_led1 = blink_state;

            right_led0 = 0;
            right_led1 = 0;
            clcd_print("<_", LINE2(11));

        }
        else if (indicator == IND_RIGHT)
        {
           led_blink++;

           if(led_blink >= 5000)
            {
                led_blink = 0;
                blink_state = !blink_state;
            }

            right_led0 = blink_state;
            right_led1 = blink_state;

            left_led0 = 0;
            left_led1 = 0;
            clcd_print("_>", LINE2(11));
        }
        else
        {
                        /* Indicators OFF */

            left_led0 = 0;
            left_led1 = 0;

            right_led0 = 0;
            right_led1 = 0;
            clcd_print("  ", LINE2(11));//off
        }
    }
}
