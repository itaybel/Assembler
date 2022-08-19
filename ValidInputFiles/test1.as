.entry LIST
.extern W

MAIN: 	add r3, LIST
LOOP: 	prn #48
	lea STR, K
	inc r6
	mov r3, W
	sub r1, r4
	bne END
	cmp val1, #-6
	bne END
	dec K
mov #10000000, r1
.data 1, 2,3, 3
.entry MAIN
	sub LOOP, r4
END:    rts
STR:   .string "abcd"
.data 6, -9
       .data -100
LIST: .data 5
.entry K
K: .data 31
.extern val1