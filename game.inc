game proc far

 mov ah,0    
     mov al,13h  ;GRAPHICS
     INT 10H  
     
      mov aX, 0600h ;bacground
      mov bh, 02h
      mov cx, 0000h
      mov dx, 184Fh       
      int 10h 

      mov aX, 0600h ;bacground
      mov bh, 0Fh
      mov cx, 0000h
      mov dx, 034fh       
      int 10h 
      mov DI,5
        
   
   MOV AX,0A000h
    MOV ES,AX

    MOV SI,offset leftcaringame
    
    MOV DX,leftcaringame_height

    REPEAT:
    MOV CX,llcar_width
REP MOVSB
ADD DI,SCREEN_WIDTH-llcar_width
DEC DX
JNZ REPEAT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
mov Di ,290
MOV SI,offset rightcar
  MOV DX,leftcaringame_height

    REPEAT2:
    MOV CX,leftcaringame_width
REP MOVSB
ADD DI,SCREEN_WIDTH-leftcaringame_width
DEC DX
JNZ REPEAT2

      ret
game endp
