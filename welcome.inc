
welcome proc far
;clear screen
mov ax,0600h
mov bh,9eh  ;fore yellow/back blue 
mov cx,0 ;start
mov dx,184FH ;end
int 10h

mov ah,2
mov bh,0
mov dl,0
mov dh,0
int 10h

;printMsg Player1msg
mov ah,9
mov dx,offset Player1msg
int 21h


welcome endp 
