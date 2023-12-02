 .MODEL small
.Stack 64
.Data
seconds db ?
hours  db ?
timer db 0
prevsec db ?
cursec db ?  
gameovermsg db 'Game Over','$'
.code
main PROC far
mov ax, @data
mov ds, ax 
mov ah,0    
     mov al,13h  ;GRAPHICS
     INT 10H  
     
      mov aX, 0600h ;bacground
      mov bh, 0Fh
      mov cx, 0000h
      mov dx, 184Fh       
      int 10h 

    mov ah, 2ch
    int 21h
    mov prevsec, dh

taketime:
mov bl,cursec
mov prevsec,bl
    mov ah, 2ch
    int 21h
    mov cursec, dh
    mov bh,prevsec
    ;sub cursec, bl ; Calculate the difference in seconds
    cmp cursec, bh 
    je taketime
    inc timer      ; Check if 10 seconds have passed
    cmp timer,30

    jge endofgame        ; If 10 seconds have passed, display the message
    jmp taketime
endofgame:
mov aX, 0600h ;bacground
      mov bh, 03h
      mov cx, 0603h
      mov dx, 1224h       
      int 10h 

      MOV AH,02  
    MOV BH,00  ;page    
    MOV DL,16 ;column  
    MOV DH,8  ;row 
    INT 10H 

    mov ah,9

        mov dx,offset gameovermsg
    int 21h
MOV AH, 0
    INT 16h

    MOV AH,4CH
    INT 21H
ret
 main endp



End main
 