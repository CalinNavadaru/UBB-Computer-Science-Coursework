bits 32

global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
segment data use32 class=data
    format db "%d", 0
    temp1 dd 0
    temp2 dd 0
    temp3 dd 0
    temp4 dd 0
    temp5 dd 0
    temp6 dd 0
    temp7 dd 0
    temp8 dd 0
    temp9 dd 0
    temp10 dd 0
    a db 0
    b db 0
    c db 0
    d db 0
    e db 0
    f db 0
segment code use32 class=code
start:


mov eax, 0
mov ax, 5 
mul word 3 
mov eax, [temp1] 


mov ax, [temp1] 
add ax, 5 
mov [temp2], ax 

mov ax, [temp2]
mov [b],ax
push    dword 0
call    [exit]
bits 32

global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
segment data use32 class=data
    format db "%d", 0
    temp1 dd 0
    temp2 dd 0
    temp3 dd 0
    temp4 dd 0
    temp5 dd 0
    temp6 dd 0
    temp7 dd 0
    temp8 dd 0
    temp9 dd 0
    temp10 dd 0
    a db 0
    b db 0
    c db 0
    d db 0
    e db 0
    f db 0
segment code use32 class=code
start:



mov eax, 0
mov ax, 5 
mul word 3 
mov eax, [temp1] 

mov ax, 5 
add ax, [temp1] 
mov [temp2], ax 

mov ax, [temp2]
mov [b],ax
push    dword 0
call    [exit]
