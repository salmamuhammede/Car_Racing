begin proc far
 mov ah,0    
     mov al,13h  ;GRAPHICS
     INT 10H  
     
      mov aX, 0600h ;bacground
      mov bh, 0Fh
      mov cx, 0000h
      mov dx, 184Fh       
      int 10h 
      MOV DI,16090 ;STARTING PIXEL
    CALL drawImage1
    MOV AH, 01
    INT 10h
    

    ret
 Begin endp
 drawImage1 PROC
    
    MOV AX,0A000h
    MOV ES,AX

    MOV SI,offset beginPage
    
    MOV DX,beginPage_HEIGHT

    REPEAT:
    MOV CX,beginPage_WIDTH
    REP MOVSB
    ADD DI,SCREEN_WIDTH-beginPage_WIDTH
    DEC DX
    JNZ REPEAT

    RET

drawImage1 ENDP