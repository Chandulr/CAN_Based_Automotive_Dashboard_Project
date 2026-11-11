/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

#ifndef CAN_H
#define CAN_H

#include <stdint.h>

/* Defines ECAN */
#define   F_ECAN_MODE2_FP		CANCON & 0x0F
#define   F_ECANFIFO_0			RXB0CONbits.RXFUL
#define   F_ECANFIFO_1			RXB1CONbits.RXFUL
#define   F_ECANFIFO_2			B0CONbits.RXFUL
#define   F_ECANFIFO_3			B1CONbits.RXFUL
#define   F_ECANFIFO_4			B2CONbits.RXFUL
#define   F_ECANFIFO_5			B3CONbits.RXFUL
#define   F_ECANFIFO_6			B4CONbits.RXFUL
#define   F_ECANFIFO_7			B5CONbits.RXFUL

#define CAN_SET_OPERATION_MODE_NO_WAIT(mode)		\
{													\
	CANCON &= 0x1F;									\
	CANCON |= mode;									\
}

#define EIDH					0
#define EIDL					1
#define SIDH					2
#define SIDL					3
#define DLC						4
#define D0						5
#define D1						6
#define D2						7
#define D3						8
#define D4						9
#define D5						10
#define D6						11
#define D7						12

/* Function Prototypes  */
void init_can(void);
//void can_transmit(uint16_t msg_id, const uint8_t *data, uint8_t len);
void can_receive(uint16_t *msg_id, uint8_t *data, uint8_t *len);

#endif