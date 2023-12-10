extern beginPage:far
public background
.model small
.code
background proc far
mov ah,0    
     mov al,13h  ;GRAPHICS
     INT 10H  
     
      mov aX, 0600h ;bacground
      mov bh, 0fh
      mov cx, 0000h
      mov dx, 184Fh       
      int 10h 
      MOV DI,8380 ;STARTING PIXEL
      ;;;;;;;;;;;;;;;;;

        MOV AX,0A000h
    MOV ES,AX
    MOV SI,offset beginPage
    
    MOV DX,148

    REPEATt:
    MOV CX,200
REP MOVSB
ADD DI,320-200
DEC DX
JNZ REPEATt
ret
 background endp
 end background