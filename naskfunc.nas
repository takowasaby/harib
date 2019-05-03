; naskfunc
; TAB=4

[FORMAT "WCOFF"]
[BITS 32]

; オブジェクトファイルのための情報

[FILE "naskfunc.nas"]

        GLOBAL  _io_hlt

; 以下は実際の関数

[SECTION .text]

_io_hlt:    ; void io_hlt(void);
        HLT
        RET