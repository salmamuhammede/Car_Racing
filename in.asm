extern startgameemsg:byte
extern endmsg:byte
extern EnterGame:far
public intermediate
.model small

.Code

intermediate proc far
lopp:
mov ah,00
mov al,03
int 10h
mov ax,0600h
mov bh,3eh ;fore yellow/back blue 
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
je continue3
mov bl,1
cmp ah, bl
je endgame
jmp lopp
endgame:
MOV AH,4CH
INT 21H
continue3: 
MOV AX, 0A000h
MOV ES, AX
mov ax,0013h
int 10h 
call EnterGame    
ret
intermediate endp
end intermediate



