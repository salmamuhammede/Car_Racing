             .MODEL SMALL
        .STACK 64 
        .DATA
          startChatMsg db 'power ups ','$'
        .CODE
MAIN    PROC    FAR  
        mov ax , @data
        mov ds ,ax 
        
        mov ax  , 0013h 
        int 10h 
        mov aX, 0600h ;bacground
      mov bh, 02h
      mov cx, 0000h
      mov dx, 184Fh       
      int 10h 
        MOV AH,0CH
        MOV AL,14 
        mov cx , 0
        mov dx ,180 
        
         
     here: int 10h 
     inc cx 
     cmp cx,320
     jnz here   
     
     
     ;mov dx, 100d 
     ;mov cx, 0d
     
    
               
    ;change position of cursor
    MOV AH,02  
    MOV BH,00  ;page    
    MOV DL,0  ;column  
    MOV DH,23  ;row 
    INT 10H 

    mov ah,9

        mov dx,offset startChatMsg
    int 21h

MAIN ENDP
    END MAIN