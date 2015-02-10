/*
 * AssemblerApplication1.asm
 *
 *  Created: 2/9/2015 12:29:24 AM
 *   Author: N
 */ 


 LDI R16, 31		; inputting 31 in register 16
 LDI R17, 52		; inputting 52 in register 17
 LDI R18, 48		; inputtint 48 in register 18
 LDI R19, 39		; inputting 39 in register 19
 LDI R20, 50		; inputting 50 in register 20

 ADD R16, R17
 ADD r16, r18
 ADD R16, R19
 ADD R16, R20

 BRVS PORTB.2, 0x01 ; setting portb pin 2 high
 BRVC portb, 0x01	; setting portb pin2 low 
