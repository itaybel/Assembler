MAIN:    mov    S1.1
         add    r2,STR
strct8: .struct 8, "xyz"
LOOP:    jmp    END
	 macro m1
        prn    #-3
        prn    #-4
        prn    #-5
	 endmacro
         prn    #-5
         sub    r1, r4
         m1
         

macro m3
        prn    #-3
        prn    #-4
        prn    #-5ddqdqwdqwdqw
	 endmacro



         bne    LOOP
END:     hlt
STR:     .string "abcdef"
LENGTH:  .data  6,-9,15
K:       .data  22
S1:      .struct 8, "ab"
m1