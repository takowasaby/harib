[INSTRSET "i486p"]
[BITS 32]
        MOV     ECX,msg
        MOV     EDX,1
putloop:
        MOV     AL,[CS:ECX]
        CMP     AL,0
        JE      fin
        INT     0x40
        ADD     ECX,1
        JMP     putloop
fin:
        MOV     EDX,4
        INT     0x40
msg:
        DB  "Hello! Can I speak about King Warthur? He is a legendary British leader who, according to medieval histories and romances, led the defence of Britain against Saxon invaders in the late 5th and early 6th centuries.",0
