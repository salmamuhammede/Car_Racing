.model small
.stack 64
.data 
redx dw  0
reedy dw 0 
square equ 5
arr db 100 dup(2)
arr1 db 100 dup(4)
arr2 db 100 dup(196)
posx dw ?
posy dw ?
screen_width equ 320
screenheight equ 640
.code

main proc far
 mov ax,@data
 mov ds,ax   
 ;;;;;;;;;;;;;;;;;;;;;;;
 MOV AX, 0A000h
MOV ES, AX

; Set video mode 13h (graphics mode)
mov ax, 0013h
mov bh,0
int 10h

mov ax, 0600h ; Set background color
mov bh, 196
mov cx, 0000h
mov dx, 184Fh
int 10h    
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

 lea si, arr
 mov di,30710            
      MOV DX,10

    REPEAT4:
    MOV CX,10
    REP MOVSB
    ADD DI,screen_width-10
    DEC DX
    JNZ REPEAT4                 
    MOV DX,10
            
    mov di,30400
    mov posx,di 
    lea si,arr1        
    REPEAT5:
    MOV CX,10
    REP MOVSB
    ADD DI,320-10
    DEC DX
    
    JNZ REPEAT5     

mov cx,99
loopmain:
mov di,posx
call clear 
cmp di , 60800d
jg skip 
call moved 
dec cx 
skip:
jnz loopmain





MOV AH, 0
INT 16h
MOV AH,4CH
INT 21H
ret   
 main endp
moved proc far

push cx
mov di,posx 
add di,330 

mov dx,10
    mov posx,di 
    lea si,arr1        
    REPEAT6:
    
    MOV CX,10
    REP MOVSB
    ADD DI,320-10
    DEC DX
    
    JNZ REPEAT6
   

    
 pop cx
    ret
moved endp
moveu proc far

mov di,posx 
add di,330 
mov dx,10   
    mov posx,di 
    lea si,arr1        
    REPEAT8:
    MOV CX,10
    REP MOVSB
    sub DI,320-10
    DEC DX
    
    JNZ REPEAT8
    ret
moveu endp
clear proc far

    mov dx,10
    lea si,arr2  
     push cx     
    REPEAT7:
    
    MOV CX,10
    REP MOVSB
    ADD DI,320-10
    DEC DX
   
    JNZ REPEAT7
     pop cx
    ret 
clear endp
end main