/*
 * AssemblerApplication2.asm
 *
 *  Created: 2/24/2015 11:59:36 PM
 *   Author: daniel schussler
 */ 



.MACRO INITSTACK
	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16
.ENDMACRO

ldi r20, 25				; set counter to 25
L1:				
	ldi r19, 0x20
	push r19			; push r19 into stack
	inc r19				; incline address
	dec r20				; decline counter
	brne L1				; if z = 0 

ldi r17, 0				; r17 will be ram middle. 
add r17, r19			; adding RAMBEGIN to the sum

ldi r20, 25
L2:
	pop r19
	dec r20
	brne L1

add r17, r19			; adding RAMEND to the sum
mul r17, .5				; that will get RAM MIDDLE


ldi r20, 25				; setting counter to 25
ldi YL, low(r20)		; low r20 into y
ldi YH, high(r20)		; high r20 into y
L3:
	push y				; pushing all 25 numbers onto the stack 
	inc yl
	dec r20
	Brne L3

ldi r21, 0				; sum of numbers divisble by 7
ldi	r24, 0				; sum of numbers divisible by 3 
ldi r19, 25				; setting counter
L4:
	pop y
	ldi r16, y
	div r16, 7			; divide y by 7 
	brvs no_seven		; if overflow then theres a remainder meaning not divisible by 7 
	add r21, y			; add y to 7 sum
no_seven:				; jump to not divis by 7
	ldi r16, y
	div r16, 3			; divide y by 3
	brvs no_three		; if overflow then theres a remainder meaning not divisible by 3
	add r24, y			; add y to 3 sum
no_three:				; jump to not divis by 3
	dec r19
	brne L4				; if counter not 0 then reset

