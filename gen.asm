extern pos_box1:word
extern pos_box2:word
extern startChatMsg:byte
extern changesLeft:word
extern displayInitialTime:far
extern drawleftcarinstatus:far
extern drawrightcarinstatus:far
extern drawtrack:far


public EnterGame
.model small

.Code

EnterGame proc far

continuee:
mov ax, 0600h ; Set background color
mov bh, 196
mov cx, 0000h
mov dx, 184Fh
int 10h       ; Clear the screen in video page 1
 
; Clear the screen in video page 0
      ;call game
      ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
      mov aX, 0600h ;bacground
      mov bh, 09h
      mov cx, 1200h
      mov dx, 154fh       
      int 10h 
;;;;;;;;;;;;;;;;
call displayInitialTime
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
    MOV BH,0  ;page    
    MOV DL,0  ;column  
    MOV DH,23  ;row 
    INT 10H 
    mov ah,9
    mov dx,offset startChatMsg
    int 21h
    mov DI,46720
    call drawleftcarinstatus
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov Di ,46675
    call drawrightcarinstatus
    call drawtrack
    
    
        mov ax, changesLeft
        cmp ax, 3
        jb continuee

      mov pos_box1, 321
      mov pos_box2, 333
    ret



EnterGame endp
end EnterGame