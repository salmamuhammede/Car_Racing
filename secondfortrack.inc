second proc far
mov ah,0    
     mov al,13h  ;GRAPHICS
     INT 10H  
     
      mov aX, 0600h ;bacground
      mov bh, 0Ah
      mov cx, 0000h
      mov dx, 184Fh       
      int 10h 
      ;call game
      ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
      mov aX, 0600h ;bacground
      mov bh, 0Fh
      mov cx, 1100h
      mov dx, 154fh       
      int 10h 
        MOV AH,0CH
        MOV AL,14 
        mov cx , 0
        mov dx ,176 
        
         
     here: int 10h 
     inc cx 
     cmp cx,320
     jnz here   
     ;;;;;;;;;;;;;;;;;;;;;;;
     MOV AH,02  
    MOV BH,00  ;page    
    MOV DL,0  ;column  
    MOV DH,23  ;row 
    INT 10H 

    mov ah,9

        mov dx,offset startChatMsg
    int 21h
      mov DI,46080
        
   
   ;MOV AX,0A000h
   ; MOV ES,AX

    MOV SI,offset leftcaringame
    
    MOV DX,leftcaringame_height

    REPEAT3:
    MOV CX,llcar_width
REP MOVSB
ADD DI,SCREEN_WIDTH-llcar_width
DEC DX
JNZ REPEAT3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
mov Di ,46370
MOV SI,offset rightcar
  MOV DX,leftcaringame_height

    REPEAT2:
    MOV CX,leftcaringame_width
REP MOVSB
ADD DI,SCREEN_WIDTH-leftcaringame_width
DEC DX
JNZ REPEAT2


ret


second endp
