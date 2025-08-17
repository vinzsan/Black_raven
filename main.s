section .rodata
    L1 db "Hello world",0x0A,0

section .text
    global _start

_start:
    
    xor rbp,rbp