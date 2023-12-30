extern secondss:word
public displayInitialTime
.model small
.Stack 64
.Code
timed PROC
 ret   
timed ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; timer for game
displayInitialTime proc  
mov ah,2
mov bh,0
mov dl,18
mov dh,19
int 10h
mov bl,100
mov ax,secondss
div bl
mov dl,al
push ax
add dl,30h
mov ah,02h; 0 : up , 1: down, 2: right, 3: left 
int 21h
pop ax
mov bl,10
mov al,ah
mov ah,0
div bl
mov dl,al
push ax
add dl,30h
mov ah,02h; 0 : up , 1: down, 2: right, 3: left
int 21h
pop ax
mov dl,ah
add dl,30h 
mov ah,02h
int 21h;
dec secondss
ret
displayInitialTime endp
end timed