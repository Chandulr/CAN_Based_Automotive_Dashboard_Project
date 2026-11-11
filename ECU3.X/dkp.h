

/* 
 * File:   assignment_5
 * Author: chandu
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef dkp_H
#define	dkp_H

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



#define LEVEL 1
#define EDGE 0

#define all_relesed 0x0F
#define sw1 0x0E
#define sw2 0x0D
#define sw3 0x0B
#define sw4 0x07

void init_digital_keypad(void);
unsigned char read_digital_keypad(unsigned char detection_type);
void check_flag(unsigned int flag);

#endif	
