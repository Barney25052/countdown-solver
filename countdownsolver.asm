SECTION         .text                       ;Create the text section
global          _start                      ;Declared for linker
_start:                                     ;Start of program
    mov edx, len                            ;Store message length in edx
    mov ecx, msg                            ;Move message to ecx
    mov ebx, 1                              ;Set descriptor
    mov eax, 4                              ;Tell system to print
    int 0x80                                ;Start system call
    mov eax, 1                              ;System call for exit
    int 0x80                                ;Confirm system call

SECTION         .data                       ;Create the data section
    msg         db "Hello World!", 0xa      ;Store message
    len         equ $ -msg

;0xa for \n
