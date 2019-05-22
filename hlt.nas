[BITS 32]
        MOV     AL,'A'
        CALL    2*8:0xbd4
fin:
        HLT
        JMP     fin
