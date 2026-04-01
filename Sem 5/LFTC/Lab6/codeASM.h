#define CODEASM_H


#define ADD_ASM_FORMAT "\
mov eax, %s \n\
add eax, %s \n\
mov %s, eax \n\
" 

#define MINUS_ASM_FORMAT "\
mov eax, %s \n\
sub eax, %s \n\
mov %s, eax \n\
"

#define MULTIPLY_ASM_FORMAT "\
mov eax, 0\n\
mov ax, %s \n\
mul word %s \n\
mov eax, %s \n\
"

#define CITIRE_ASM_FORMAT "\
push %s\n\
push format\n\
call [scanf]\n\
add esp, 8\n\
"

#define AFISARE_ASM_FORMAT "\
push dword %s\n\
push format\n\
call [printf]\n\
add esp, 8\n\
"

#define INIT_ASM "\
bits 32\n\
\n\
global start\n\
\n\
extern exit, printf, scanf\n\
import exit msvcrt.dll\n\
import printf msvcrt.dll\n\
import scanf msvcrt.dll\n\
segment data use32 class=data\n\
    format db \"%%d\", 0\n\
    temp1 dd 0\n\
    temp2 dd 0\n\
    temp3 dd 0\n\
    temp4 dd 0\n\
    temp5 dd 0\n\
    temp6 dd 0\n\
    temp7 dd 0\n\
    temp8 dd 0\n\
    temp9 dd 0\n\
    temp10 dd 0\n\
    a db 0\n\
    b db 0\n\
    c db 0\n\
    d db 0\n\
    e db 0\n\
    f db 0\n\
segment code use32 class=code\n\
start:\n\
"

#define END_ASM "\
push    dword 0\n\
call    [exit]\n\
"
