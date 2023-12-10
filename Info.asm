extern Player1msg:far
extern firstPlayerName:far
extern initialpmsg:far
extern fppoints:byte
extern interruptmsg:far
extern secondPlayerName:far
extern sppoints:byte
extern choicePhasemsg:far
extern startgameemsg:far
extern endmsg:far
extern llcar_width:byte
extern leftcaringame_height:far
extern rightcar:far
extern leftcaringame_width:far
extern leftcaringame:far
extern startChatMsg:far
public info
.model huge
.code
info proc far
 lm:
   mov ah,0
int 16h  
mov bl,28
cmp ah, bl
jz label2
jnz lm
  
label2:
mov ah,00h 
mov al,03h 
int 10h

mov ax,0600h
mov bh,3eh  ;fore yellow/back blue 
mov cx,0 ;start
mov dx,184FH ;end
int 10h
;;;;;begin pos
mov ah,2
mov bh,0
mov dl,1
mov dh,1
int 10h

;printMsg EnterPlayer1msg
mov ah,9
mov dx,offset Player1msg
int 21h
;;;;;;;;;;;;
mov ah,2
mov bh,0
mov dl,1;take name
mov dh,2
int 10h

mov ah,0AH 
mov dx,offset firstPlayerName
int 21h
lea si, firstPlayerName+2
;cmp [si],
;;;;;;;;;;;
mov ah,2;take initial points for player1
mov bh,0
mov dl,1
mov dh,8
int 10h
mov ah,9
mov dx,offset initialpmsg
int 21h   
 ;;;;;;;;;;;;;;;;;;; store it
mov ah, 1 
INT 21H 
mov fppoints,al 
;;;;;;;;;;;;;;;;;;;;;
mov ah,2
mov bh,0
mov dl,1; second player turn
mov dh,12
int 10h 

mov ah,9
mov dx,offset interruptmsg
int 21h  
mov ah, 02h    
    mov dl, 1
    mov bh,0
    mov dh, 15
    int 10h
;;;;;;;;;;;;;;;;;;;;
mov ah,9
mov dx,offset Player1msg
int 21h 

mov ah,2
mov bh,0
mov dl,1
mov dh,16
int 10h 

mov ah,0AH 
mov dx,offset secondPlayerName
int 21h

mov ah,2
mov bh,0
mov dl,1
mov dh,20
int 10h

mov ah,9
mov dx,offset initialpmsg
int 21h   
  
mov ah, 1 
INT 21H 
mov sppoints,al 
mov ah,2
mov bh,0
mov dl,1
mov dh,22
int 10h
mov ah,9
mov dx,offset choicePhasemsg
int 21h  
;;;;;;;;;;;move to second  page
LOOPL:
mov ah,0
int 16h  
mov bl,28
cmp ah, bl 
jNz LOOPL ; Clear the screen 
lopp:
mov ax,0600h
mov bh,3eh  ;fore yellow/back blue 
mov cx,0 ;start
mov dx,184FH ;end
int 10h
;;;;;;;;;;;;;;chat part
mov ah,2
mov bh,0
mov dl,0
mov dh,19
int 10h
          
mov ah,9                  
mov al,'*'
mov bh,0
mov dx,80
mov cx,dx
mov bl,3eh
int 10h
;;;;;;;;;
mov ah,2
mov bh,0
mov dl,27
mov dh,10
int 10h

mov ah,9
mov dx,offset startgameemsg
int 21h  

mov ah,2
mov bh,0
mov dl,27
mov dh,14
int 10h

mov ah,9
mov dx,offset endmsg
int 21h 
mov ah,0
int 16h  
mov bl,60
cmp ah, bl
je continue
mov bl,1
cmp ah, bl
je endgame
jmp lopp
endgame:
MOV AH,4CH
INT 21H
continue:
;;;;;;;;;;;;;;;;;;;;;
MOV AX,0A000h
   MOV ES,AX
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
      mov cx, 1200h
      mov dx, 154fh       
      int 10h 
      ;call Noobstacleleft
      call NoobstacleRight
       
      ;;;;;;;;;;;;;;;;
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
      mov DI,46720
      ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;z&z 
         

    MOV SI,offset leftcaringame
    
    MOV DX,leftcaringame_height

   REPEAT3:
   mov bx,23
   mov cx,bx
REP MOVSB
ADD DI,320-23
DEC DX
JNZ REPEAT3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
mov Di ,46370
MOV SI,offset rightcar
  MOV DX,leftcaringame_height

    REPEAT2:
    MOV CX,leftcaringame_width
REP MOVSB
ADD DI,320-25
DEC DX
JNZ REPEAT2
ret
info endp
Noobstacleleft proc far
mov aX, 0600h ;bacground
      mov bh, 05h
      mov cx, 1305h
      mov dx, 1407h       
      int 10h 
      
      ret
Noobstacleleft endp
NoobstacleRight proc far
pusha
mov aX, 0600h ;bacground
      mov bh, 05h
      mov cx, 1344h
      mov dx, 1446h       
      int 10h 
      popa
      ret
NoobstacleRight endp
 end info