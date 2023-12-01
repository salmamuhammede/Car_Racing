
welcome proc far
;clear screen
mov ax,0600h
mov bh,9eh  ;fore yellow/back blue 
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
mov dl,0
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
mov dl,0; second player turn
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
mov bh,9eh  ;fore yellow/back blue 
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
mov bl,9eh
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
mov ah,0    
     mov al,13h  ;GRAPHICS
     INT 10H  
     
      mov aX, 0600h ;bacground
      mov bh, 02h
      mov cx, 0000h
      mov dx, 184Fh       
      int 10h 
ret

welcome endp 




