/*
 * File:   dkp.c
 * Author: chandu
 *
 * Created on September 2, 2026, 1:02 PM
 */



#include <xc.h>
#include "dkp.h"

void init_digital_keypad(void)
{
    TRISC = TRISC | 0x0F;
}

unsigned char read_digital_keypad(unsigned char triggering)
{
    if(triggering == LEVEL)
    {
        return PORTC & 0x0F;
    }

    else if(triggering == EDGE)
    {
        static unsigned char flag = 1;

        if(((PORTC & 0x0F) != 0x0F) && flag)
        {
            flag = 0;
            return PORTC & 0x0F;
        }

        else if((PORTC & 0x0F) == 0x0F)
        {
            flag = 1;
        }

        return 0x0F;
    }

    return 0x0F;
}

