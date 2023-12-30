extern Player1msg:far
extern Player2msg:far
extern wrongname1flag:byte
extern wrongname2flag:byte
extern firstPlayerName:byte
extern secondPlayerName:byte
extern wrong:far
extern wrong2:far
extern drawbeginpage:far
extern intermediate:far
public welcome

.model small
.Stack 64
.Code

welcome proc far
    mov ah,0    
    mov al,13h  ;GRAPHICS
    INT 10H       
    mov aX, 0600h ;bacground
    mov bh, 105
    mov cx, 0000h
    mov dx, 184Fh       
    int 10h 
    MOV DI,6420 ;STARTING PIXEL
      ;;;;;;;;;;;;;;;;;
    MOV AX,0A000h
    MOV ES,AX
    call drawbeginpage
    lm:
    mov ah,0
    int 16h  
    mov bl,28
    cmp ah, bl
    jz label2
    jnz lm
    label2:
 

mov ax, 0600h ; Background color
mov bh, 00h
mov cx, 0504h
mov dx, 0813h
int 10h
mov ah,2
mov bh,0
mov dl,4 ;take name
mov dh,5
int 10h

;printMsg EnterPlayer1msg
mov ah, 9
mov dx, offset Player1msg
mov bl, 3eh  ; Set the desired color attribute
int 21h
tryagainname1:
cmp wrongname1flag,0
jz continuenaming
mov wrongname1flag,0
mov cx,17  
mov di,offset firstPlayerName[2] 

lopplk: 
mov [di],'$'
inc di
loop lopplk
mov ax, 0600h ; Background color
mov bh, 00h
mov cx, 0604h
mov dx, 0713h
int 10h
mov ah,2
mov bh,0
mov dl,4 ;take name
mov dh,7
int 10h
mov ah, 9
mov dx, offset wrong
mov bl, 3eh  ; Set the desired color attribute
int 21h
continuenaming:

;;;;;begin pos
;;;;;;;;;;;;
mov ah,2
mov bh,0
mov dl,4;take name
mov dh,6
int 10h

; get the name
mov ah,0AH 
mov dx,offset firstPlayerName
int 21h

    mov dl, byte ptr [firstPlayerName+1] ; Load the length of the input string
    cmp dl, 15
    jbe checkalpha
    mov wrongname1flag, 1
    jmp tryagainname1
checkalpha:
mov dl,firstPlayerName[2]
;check below Z
checkATOZ:
    mov cl,'Z'
    cmp dl,cl ;check if between A,Z
    jbe above
    jmp checkaTOzsmall

above:
   mov cl,'A'
   cmp dl,cl
    jae taketheother
    mov wrongname1flag,1
    jmp tryagainname1

checkaTOzsmall:
   mov al,'z'
    cmp dl,al     ;check if between a,z   
    jbe taketheother
    mov wrongname1flag,1
    jmp tryagainname1
taketheother:
mov ax, 0600h ; Background color
mov bh, 00h
mov cx, 0704h
mov dx, 0813h
int 10h

mov ax, 0600h ; Background color
mov bh, 00h
mov cx, 0a04h
mov dx, 0d13h
int 10h

mov ah,2
mov bh,0
mov dl,4 ;take name
mov dh,10
int 10h

;printMsg EnterPlayer1msg
mov ah, 9
mov dx, offset Player2msg
mov bl, 3eh  ; Set the desired color attribute
int 21h

tryagainname2:
cmp wrongname2flag,0
jz continuenaming2
mov wrongname2flag,0
mov cx,17  
mov di,offset secondPlayerName[2] 
lopplk2: 
mov [di],'$'
inc di
loop lopplk2
mov ax, 0600h ; Background color
mov bh, 00h
mov cx, 0b04h
mov dx, 0d13h
int 10h

mov ah,2
mov bh,0
mov dl,4 ;take name
mov dh,12
int 10h

mov ah, 9
mov dx, offset wrong2
mov bl, 3eh  ; Set the desired color attribute
int 21h

continuenaming2:

;;;;;begin pos
;;;;;;;;;;;;
mov ah,2
mov bh,0
mov dl,4;take name
mov dh,11
int 10h
; get the name
mov ah,0AH 
mov dx,offset secondPlayerName
int 21h
 mov dl, byte ptr [secondPlayerName+1] ; Load the length of the input string
    cmp dl, 15
    jbe checkalpha2
    mov wrongname2flag, 1
    jmp tryagainname2
checkalpha2:
mov dl,secondPlayerName[2]
;check below Z
checkATOZ2:
    mov cl,'Z'
    cmp dl,cl ;check if between A,Z
    jbe above2
    jmp checkaTOzsmall2

above2:
   mov cl,'A'
   cmp dl,cl
    jae LOOPL
    mov wrongname2flag,1
    jmp tryagainname2

checkaTOzsmall2:
   mov al,'z'
    cmp dl,al     ;check if between a,z   
    jbe LOOPL 
    mov wrongname2flag,1
    jmp tryagainname2


LOOPL:
mov ah,0
int 16h  
mov bl,28
cmp ah, bl 
jNz LOOPL ; Clear the screen 
call intermediate
ret

welcome endp 
end welcome



