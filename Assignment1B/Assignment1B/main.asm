;
; Assignment1B.asm
;
; Created: 2/22/2019 4:27:26 PM
; Author : Mat Tomljenovic
;

	
	.org 0                      ;program starts at memory 0
	ldi xl, low(0x0200)         ;load low byte into x register
	ldi xh, high(0x0200)        ;load high byte into x register
	ldi yl, low(0x0400)         ;load low byte into y register
	ldi yh, high(0x0400)        ;load high byte into y register
	ldi zl, low(0x0600)         ;load low byte into z register
	ldi zh, high(0x0600)        ;load high byte into z register
	
	ldi r21, 154                ;load 154 into register 21
	ldi r23 ,0                  ;load 0 into register 23

	;loop to incriment r21 and count
	start:
		inc r21	                ;increment value in register 21
		st x+, r21              ;store value in r21 into x and increment
		mov  r22, r21           ;copy value in r21 into r22
		cpi r21, 254            ;compare 254 which is 155+99 to vlue in r21
		breq hold               ;branch if not equal to hold label

		;loop for to check if number is divisble by 3
		loop1:
			subi r22, 3         ;subtract value in r22 by 3
			cp   r22, r23       ;compare value in r23 to r22
			brmi loop3          ;branch if result is negative to label loop3
			breq loop2          ;branch if result is equal to 0 to label loop2
			rjmp loop1          ;if result is a positive value repat loop1

		;loop to store result in y and increment 
		loop2:
			st y+, r21          ;store value in r21 into y and increment
			add r16, r21        ;add r21 to r16 and store result in r16
			adc r17, r23        ;add carry of previous reult into r17
			rjmp start          ;jump to label start

		;loop to store result of r21 into z and increment
		loop3:
			st z+, r21          ;store value in r21 into z and increment
			add r18, r21        ;add r21 and r18 and store result in r18
			adc r19, r23        ;add carry of previous result and store into r19
			rjmp start          ;jump to label start

		hold: break             ;label used to break and end program
			

		
			
			






	
	






