game proc far
;;;;;;;;;;;;;;;;;;
 mov ah,0    
     mov al,13h  ;GRAPHICS
     INT 10H  
     
      mov aX, 0600h ;bacground
      mov bh, 0Fh
      mov cx, 0000h
      mov dx, 184Fh       
      int 10h 
      MOV DI,8380 ;STARTING PIXEL
      ;;;;;;;;;;;;;;;;;

        MOV AX,0A000h
    MOV ES,AX

    MOV SI,offset beginPage
    
    MOV DX,beginPage_HEIGHT

    REPEATt:
    MOV CX,beginPage_WIDTH
REP MOVSB
ADD DI,SCREEN_WIDTH-beginPage_WIDTH
DEC DX
JNZ REPEATt
    ;;;;;;;;;;;;;;;;;;;;;
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
    MOV CX,llcar_width
REP MOVSB
ADD DI,SCREEN_WIDTH-llcar_width
DEC DX
JNZ REPEAT3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
mov Di ,46370
MOV SI,offset rightcar
  MOV DX,leftcaringame_height

    REPEAT2:
    MOV CX,leftcaringame_width
REP MOVSB
ADD DI,SCREEN_WIDTH-leftcaringame_width
DEC DX
JNZ REPEAT2

call cs:drawTrack
     mov pos_box1, 1
     mov pos_box2, 12
    
  call initialize_cars
  ;;;;;;;;;;;;;;;;;;;;;;;play
  call gettime
  push di
                push ax
                check_move: 
                        mov di,pos_box1
                        mov ah,1 ; if sth pressed
                        int 16h
                        jz check_move ; nothing prssed
                        call move_b1
                        jmp check_move
                pop ax
                pop di
;call play
      ret
game endp

initialize_cars proc 
                mov di,pos_box1
                mov al,color_box1 
                mov bl,8
                call draw 
                mov di,pos_box2
                mov al,color_box2 
                mov bl,8
                call draw 
                ret
initialize_cars endp
; ------------------------------------------------------------------------------;
draw            proc 
                push di
                pusha  ; for safety
                mov bl,pixel_size ; loop pixel size times
                my_draw:  mov cx,pixel_size ; for stosb 
                        rep stosb  ; draw horizontal line
                        sub di,pixel_size ; return to original position
                        add di,k ; new row
                        dec bl ; loop pixel size times
                        jnz my_draw 
                popa
                pop di
                ret  
draw            endp
; ------------- draw line ----------------- ;
draw_l           proc
        ; ---- store changed vars ------------ ;
                push cx 
                push ax
                push di
                mov cx,pixel_size ; for stosb
                rep stosb
        ; --- return to the original positions -- ;
                pop di
                pop ax
                pop cx
                ret  
draw_l            endp
; ----------------------------------------- ;
; ------------- draw vertical -------------- ;
draw_v          proc 
                push di
                push cx  
                mov cx,pixel_size
                draw_it:
                        stosb
                        dec di
                        add di,k  
                        dec cx
                        jnz draw_it
                pop cx
                pop di  
                ret
draw_v          endp

; - --------------------Move the second box---------------------------- ;
move_b2            proc 
            ; --- push vlues that will be updated -- ;
                push di
                push ax
                push cx
                mov di,pos_box2
                ; ----- Move box 2--------- ;

                move_box2: 
                        push di ; store original value
                        cmp al,119 ; up key
                        jnz down2
                        push si ; save si
                        push di ; save di
                        mov si,offset color_track ; check with color of track
                        sub di,k ; line just above car
                        cmpsb ; compare with track color
                        jnz escape_up2 ; first condition ok
                        pop di ; return values
                        pop si ; return values
                        jmp terminate2 ; end function 
                        escape_up2: ; continue for the next check
                        pop di ; return di
                        pop si ; return si
                        push di
                        push si
                        add di,pixel_size - 1
                        sub di,k
                        mov si,offset color_track ; check the color
                        cmpsb ; compare with the color of the track
                        jnz removelast2 ; ok continue
                        pop si ; return values
                        pop di ; return values
                        jmp terminate2 ; end the call
                        removelast2: 
                                    pop si
                                    pop di 
                                    add di, k*(pixel_size - 1) ; go to last row
                                    mov al,0h ; "MAY BE CHANGED BASED ON BACKGROUND COLOR."
                                    mov cx,pixel_size ; 8 times size of row
                                    rep stosb
                                    
                        pop di
                        sub di,k   ; new  start position
                        push di ; save new start position
                        push ax
                        mov al,color_box2 ; set color before call
                        call draw_l ; draw line at the beginning as if move up
                        pop ax
                        pop di ; set new value of di
                        mov pos_box2,di
                        jmp endmove2
                        down2: 
                        cmp al,115
                        jnz right2
                        
                        push si
                        push di
                        mov si,offset color_track
                        add di,k*(pixel_size)
                        cmpsb 
                        jnz escape_down2
                        pop di
                        pop si
                        jmp terminate2
                        escape_down2:
                        pop di
                        pop si
                        push di
                        push si
                        add di,k*(pixel_size)
                        add di,pixel_size - 1
                        mov si,offset color_track
                        cmpsb
                        jnz removefirst2
                        pop si
                        pop di
                        jmp terminate2
                        
                        removefirst2: 
                                    pop si
                                    pop di 
                                    mov al,0h ; "TO BE REPLACED BY THE BACKGROUND COLOR"
                                    mov cx,pixel_size
                                    rep stosb
                                    
                        pop di 
                        add di,k ; set the new pos
                        push di 
                        add di,k*(pixel_size - 1)
                        push ax
                        mov al,color_box2 ; set color before call
                        call draw_l ; draw horizontal line at the end
                        pop ax
                        pop di
                        mov pos_box2,di ; set the new position 
                        jmp endmove2
                      ; --- right --- ;
                        right2: 
                        cmp al,100 ; d key
                        jnz left2
                        
                        push si
                        push di
                        mov si,offset color_track
                        add di, pixel_size
                        cmpsb 
                        jnz escape_right2
                        pop di
                        pop si
                        jmp terminate2
                        escape_right2:
                        pop di
                        pop si
                        push di
                        push si
                        add di,k*(pixel_size - 1)
                        add di,pixel_size
                        mov si,offset color_track
                        cmpsb
                        jnz removeleft22
                        pop si
                        pop di
                        jmp terminate2

                        removeleft22:
                        pop si
                        pop di
                        mov cx,pixel_size
                        removeleft2:   ; remove the line on the left
                                    mov al,0h
                                    stosb
                                    dec di
                                    add di,k
                                    dec cx
                                    jnz removeleft2
                                    
                        pop di 
                        inc di 
                        push di 
                        add di,pixel_size - 1
                        push ax
                        mov al,color_box2 ; set color before call
                        call draw_v ; draw the line on the right
                        pop ax
                        pop di
                        mov pos_box2,di
                        jmp endmove2
                     ; --- left --- ;
                        left2: 
                        cmp al,97 
                        jnz endmove2
                        
                        push si
                        push di
                        mov si,offset color_track
                        dec di
                        cmpsb 
                        jnz escape_left2
                        pop di
                        pop si
                        jmp terminate2
                        escape_left2:
                        pop di
                        pop si
                        push di
                        push si
                        add di,k*(pixel_size - 1)
                        dec di
                        mov si,offset color_track
                        cmpsb
                        jnz removeright22
                        pop si
                        pop di
                        jmp terminate2

                        removeright22:
                        pop si
                        pop di
                        mov cx,pixel_size 
                        add di,pixel_size - 1
                        removeright2:  
                                    mov al,0h
                                    stosb
                                    dec di
                                    add di,k
                                    dec cx
                                    jnz removeright2
                                    
                        pop di 
                        dec di 
                        push di
                        push ax
                        mov al,color_box2 ; set color before call
                        call draw_v
                        pop ax
                        pop di
                        mov pos_box2,di
                        jmp endmove2
                    terminate2:
                        ;pop bx
                        pop di
                    endmove2:
                        pop cx
                        pop ax
                        pop di
                ret
move_b2             endp 

; --------------------Move the first box--------------------------------- ;
move_b1            proc 
                ; ----- Move box --------- ;
                push di
                push ax
                push cx
                move_box: 
                        push di ; store original value
                        mov ah,0 ; key key pressed from buffer
                        int 16h
                        cmp ah,48h ; up key
                        jnz down

                        push si ; save si
                        push di ; save di
                        mov si,offset color_track ; check with color of track
                        sub di,k ; line just above car
                        cmpsb ; compare with track color
                        jnz escape_up1 ; first condition ok
                        pop di ; return values
                        pop si ; return values
                        jmp terminate1 ; end function 
                        escape_up1: ; continue for the next check
                        mov si,offset color_box2
                        cmpsb
                        pop di ; return di
                        pop si ; return si
                        push di
                        push si
                        add di,pixel_size - 1
                        sub di,k
                        mov si,offset color_track ; check the color
                        cmpsb ; compare with the color of the track
                        jnz removelast ; ok continue
                        pop si ; return values
                        pop di ; return values
                        jmp terminate1 ; end the call

                        removelast:  
                                    pop si
                                    pop di
                                    add di, k*(pixel_size - 1) ; go to last row
                                    mov al,0h ; "MAY BE CHANGED BASED ON BACKGROUND COLOR."
                                    mov cx,pixel_size ; 8 times size of row
                                    rep stosb
                                    
                        pop di
                        sub di,k   ; new  start position
                        push di ; save new start position
                        push ax
                        mov al,color_box1 ; set color before call
                        call draw_l ; draw line at the beginning as if move up
                        pop ax
                        pop di ; set new value of di
                        mov pos_box1,di
                        jmp endmove
                        down: 
                        cmp ah,50h
                        jnz right

                        push si
                        push di
                        mov si,offset color_track
                        add di,k*(pixel_size)
                        cmpsb 
                        jnz escape_down1
                        pop di
                        pop si
                        jmp terminate1
                        escape_down1:
                        pop di
                        pop si
                        push di
                        push si
                        add di,k*(pixel_size)
                        add di,pixel_size - 1
                        mov si,offset color_track
                        cmpsb
                        jnz removefirst
                        pop si
                        pop di
                        jmp terminate1

                        removefirst: 
                                    pop si
                                    pop di 
                                    mov al,0h ; "TO BE REPLACED BY THE BACKGROUND COLOR"
                                    mov cx,pixel_size
                                    rep stosb
                                    
                        pop di 
                        add di,k ; set the new pos
                        push di 
                        add di,k*(pixel_size - 1) 
                        push ax
                        mov al,color_box1 ; set color before call
                        call draw_l ; draw horizontal line at the end
                        pop ax
                        pop di
                        mov pos_box1,di ; set the new position 
                        jmp endmove
                      ; --- right --- ;
                        right: 
                        cmp ah,4Dh
                        jnz left 

                        push si
                        push di
                        mov si,offset color_track
                        add di, pixel_size
                        cmpsb 
                        jnz escape_right1
                        pop di
                        pop si
                        jmp terminate1
                        escape_right1:
                        pop di
                        pop si
                        push di
                        push si
                        add di,k*(pixel_size - 1)
                        add di,pixel_size
                        mov si,offset color_track
                        cmpsb
                        jnz removeleft11
                        pop si
                        pop di
                        jmp terminate1

                        removeleft11:
                        pop si
                        pop di

                        mov cx,pixel_size
                        removeleft:  
                                    mov al,0h
                                    stosb
                                    dec di
                                    add di,k
                                    dec cx
                                    jnz removeleft
                                    
                        pop di 
                        inc di 
                        push di 
                        add di,pixel_size - 1
                        push ax
                        mov al,color_box1 ; set color before call
                        call draw_v
                        pop ax
                        pop di
                        mov pos_box1,di
                        jmp endmove
                     ; --- left --- ;
                        left: 
                        cmp ah,4Bh 
                        jnz box2switch

                        push si
                        push di
                        mov si,offset color_track
                        dec di
                        cmpsb 
                        jnz escape_left1
                        pop di
                        pop si
                        jmp terminate1
                        escape_left1:
                        pop di
                        pop si
                        push di
                        push si
                        add di,k*(pixel_size - 1)
                        dec di
                        mov si,offset color_track
                        cmpsb
                        jnz removeright11
                        pop si
                        pop di
                        jmp terminate1

                        removeright11:
                        pop si
                        pop di
                        mov cx,pixel_size 
                        add di,pixel_size - 1
                        removeright:  
                                    mov al,0h
                                    stosb
                                    dec di
                                    add di,k
                                    dec cx
                                    jnz removeright
                                    
                        pop di 
                        dec di 
                        push di
                        push ax
                        mov al,color_box1 ; set color before call
                        call draw_v
                        pop ax
                        pop di
                        mov pos_box1,di
                        jmp endmove
                    box2switch:
                        call move_b2 ; keys of box 2 not 1
                        pop di
                        jmp endmove
                    terminate1:
                        ;pop bx
                        pop di
                    endmove:
                        
                        pop cx
                        pop ax
                        pop di
                ret
move_b1             endp
; ------------------------------------------------------;


; ------------------------ Draw Track ------------------------------------------ ;
verticalLineD proc far;;;; ersm vertical line ta7t 
    pusha
    mov ax, 320
    mov bx, y
    mul bx
    add ax, x
    mov di, ax
    mov cx, lengthD
    Line:
    
    mov al, 03h
    stosb
    add di, 319 ;;;;; 320 - 1 elly hwa katabo
    loop Line
    mov ax, y
    add ax, lengthD
    mov y, ax     
    
    popa
    ret
verticalLineD endp 
 
verticalLineU proc far  ;;;; ersm vertical line fo2 
    pusha
    mov ax, 320
    mov bx, y
    mul bx
    add ax, x
    mov di, ax
    mov cx, lengthD
    Line1:
    
    mov al, 03h
    stosb
    sub di, 321 ;;;;; 320 + 1 elly hwa katabo
    loop Line1
    mov ax, y
    sub ax, lengthD
    mov y, ax
    
    popa
    ret
verticalLineU endp 


horizLineR proc far;;;; ersm Horizontal line ymen
    pusha
    mov ax, 320
    mov bx, y
    mul bx
    add ax, x
    mov di, ax
    mov cx, lengthD
    mov al, 03h
    rep stosb
    mov ax, x
    add ax, lengthD
    mov x, ax
    
    popa
    ret
horizLineR endp 

horizLineL proc far 
    pusha
    mov ax, 320
    mov bx, y
    mul bx
    add ax, x
    sub ax, lengthD
    mov di, ax
    mov cx, lengthD
    mov al, 03h
    rep stosb
    mov ax, x
    sub ax, lengthD
    mov x, ax
    
    popa
    ret
horizLineL endp   

trackUp proc far
      ;;;; tkmlt track;;;;;

      mov ax, lastDirection
      cmp ax, 0 ;;; same direction fo2
      jz skip1
      cmp ax, 1 ;;; cancel aslan (up then down)
      jnz escape_1
      jmp far ptr cs:exit1
      escape_1:
      cmp ax, 2 ;;; right then up
      jz RU
      cmp ax, 3 ;;; left then up
      jz LU
      LU:
      mov ax, x2
      mov bx, y2
      mov x, ax
      mov y, bx
      mov dx, widthT
      mov lengthD, dx  
      call horizLineL 
      call verticalLineU
      mov ax, x
      mov bx, y
      mov x2, ax
      mov y2, bx 
      jmp skip1
      RU:
      mov ax, x2
      mov bx, y2
      mov x, ax
      mov y, bx
      mov dx, widthT
      mov lengthD, dx 
      call horizLineR
      call verticalLineU
      mov ax, x
      mov bx, y
      mov x2, ax
      mov y2, bx 
      jmp skip1
      skip1: 
      

      mov cx, lengthT
      cmp cx, 0
      jz skipLs1  
      ;;;; tkmlt track;;;;;
      mov ax, x1
      mov bx, y1
      mov x, ax
      mov y, bx
      mov dx, lengthT
      mov lengthD, dx   
      call verticalLineU
      mov ax, x
      mov bx, y
      mov x1, ax
      mov y1, bx 
      mov ax, x2
      mov bx, y2
      mov x, ax
      mov y, bx
      call verticalLineU
      mov ax, x
      mov bx, y
      mov x2, ax
      mov y2, bx
      skipLs1:
      mov ax, 0
      mov lastDirection, ax
      ;;; test for line1, line2 ;;; shmal 3ayzeeeno line1
      mov ax, x2
      mov bx, x1
      cmp ax, bx
      ja exit1
      mov x1, ax ;; xchg
      mov x2, bx
      
      ;;; test for line1, line2
      exit1: 
      ret
trackUp endp

trackDown proc far
      ;;;; tkmlt track;;;;;
      mov ax, lastDirection
      cmp ax, 1 ;;; same direction ta7t
      jz skip
      cmp ax, 0 ;;; cancel aslan (up then down)
      jnz escape_2
      jmp far ptr cs:exit
      escape_2:
      cmp ax, 2 ;;; right then down
      jz RD
      cmp ax, 3 ;;; left then down
      jz LD
      LD:
      mov ax, x1
      mov bx, y1
      mov x, ax
      mov y, bx
      mov dx, widthT
      mov lengthD, dx  
      call horizLineL 
      call verticalLineD
      mov ax, x
      mov bx, y
      mov x1, ax
      mov y1, bx
      jmp skip
      RD:
      mov ax, x1
      mov bx, y1
      mov x, ax
      mov y, bx
      mov dx, widthT
      mov lengthD, dx  
      call horizLineR
      call verticalLineD
      mov ax, x
      mov bx, y
      mov x1, ax
      mov y1, bx
      jmp skip   
      
      ;;;; tkmlt track;;;;;
      skip:

      mov cx, lengthT
      cmp cx, 0
      jz skipLs 

      jz exit
      mov ax, x1
      mov bx, y1
      mov x, ax
      mov y, bx
      mov dx, lengthT
      mov lengthD, dx     
      call verticalLineD
      mov ax, x
      mov bx, y
      mov x1, ax
      mov y1, bx
      mov ax, x2
      mov bx, y2
      mov x, ax
      mov y, bx
      call verticalLineD
      mov ax, x
      mov bx, y
      mov x2, ax
      mov y2, bx
      skipLs:
      mov ax, 1
      mov lastDirection, ax 
      
      ;;; test for line1, line2 ;;; shmal 3ayzeeeno line1
      mov ax, x2
      mov bx, x1
      cmp ax, bx
      ja exit
      mov x1, ax ;; xchg
      mov x2, bx
      
      ;;; test for line1, line2
      exit: 
      ret
trackDown endp 
 

trackRight proc far
      ;;;; tkmlt track;;;;;

      mov ax, lastDirection
      cmp ax, 0 ;;; UP then right
      jz UR
      cmp ax, 1 ;;; down then right
      jz DR
      cmp ax, 2 ;;; right then right (skip)
      jz skip2
      cmp ax, 3 ;;; left then right  (cancel)
      jnz escape_3
      jmp far ptr exit2
      escape_3:
      UR: 
      mov ax, x1
      mov bx, y1
      mov x, ax
      mov y, bx
      mov dx, widthT
      mov lengthD, dx
      call verticalLineU
      call horizLineR
      mov ax, x
      mov bx, y
      mov x1, ax
      mov y1, bx
      jmp skip2
      DR:
      mov ax, x1
      mov bx, y1
      mov x, ax
      mov y, bx
      mov dx, widthT
      mov lengthD, dx
      call verticalLineD
      call horizLineR
       mov ax, x
      mov bx, y
      mov x1, ax
      mov y1, bx
      jmp skip2
      skip2:
      ;;;; tkmlt track;;;;;
      mov cx, lengthT
      cmp cx, 0
      jz skipLs2
      mov ax, x1
      mov bx, y1
      mov x, ax
      mov y, bx
      mov dx, lengthT
      mov lengthD, dx   
      call horizLineR
      mov ax, x
      mov bx, y
      mov x1, ax
      mov y1, bx
      mov ax, x2
      mov bx, y2
      mov x, ax
      mov y, bx
      call horizLineR
      mov ax, x
      mov bx, y
      mov x2, ax
      mov y2, bx
      skipLs2:
      mov ax, 2
      mov lastDirection, ax 
      
      
      ;;; test for line1, line2 ;;; fo2 3ayzeeeno line1
      mov ax, y2
      mov bx, y1
      cmp ax, bx
      ja exit2
      mov y1, ax ;; xchg
      mov y2, bx
      ;;; test for line1, line2
      exit2: 
      ret
trackRight endp 


trackLeft proc far
    
    
        
      ;;;; tkmlt track;;;;;

      mov ax, lastDirection
      cmp ax, 0 ;;; UP then left
      jz UL
      cmp ax, 1 ;;; down then left
      jz downLL
      cmp ax, 2 ;;; right then left (cancel)
      jnz escape_4
      jmp far ptr cs:exit3
      escape_4:
      cmp ax, 3 ;;; left then left  (skip)
      jz skip3
      UL: 
      mov ax, x2
      mov bx, y2
      mov x, ax
      mov y, bx
      mov dx, widthT
      mov lengthD, dx
      call verticalLineU
      call horizLineL
      mov ax, x
      mov bx, y
      mov x2, ax
      mov y2, bx
      jmp skip3
      downLL:
      mov ax, x2
      mov bx, y2
      mov x, ax
      mov y, bx
      mov dx, widthT
      mov lengthD, dx
      call verticalLineD
      call horizLineL
      mov ax, x
      mov bx, y
      mov x2, ax
      mov y2, bx
      jmp skip3
      skip3:
      ;;;; tkmlt track;;;;;
      mov cx, lengthT
      cmp cx, 0
      jz skipLs3
       mov ax, x1
      mov bx, y1
      mov x, ax
      mov y, bx
      mov dx, lengthT
      mov lengthD, dx 
      call horizLineL
      mov ax, x
      mov bx, y
      mov x1, ax
      mov y1, bx
       mov ax, x2
      mov bx, y2
      mov x, ax
      mov y, bx
      mov dx, lengthT
      mov lengthD, dx
      call horizLineL
      mov ax, x
      mov bx, y
      mov x2, ax
      mov y2, bx
      skipLs3:
      mov ax, 3
      mov lastDirection, ax 
      
      
      ;;; test for line1, line2 ;;; fo2 3ayzeeeno line1
      mov ax, y2
      mov bx, y1
      cmp ax, bx
      ja exit3
      mov y1, ax ;; xchg
      mov y2, bx
      ;;; test for line1, line2
      exit3: 
      ret
trackLeft endp


checkUP proc  
    ;;;; mmkn nhtag n shift el x 3la hasab howa gy mn ymen wla shmal fl second test  

    mov ax, y1
    cmp ax, 0
    jnz escape_5
    jmp far ptr dontU
    escape_5:
    ;;;;; first test
    mov ax, lengthT
    mov temporaryLength, ax

    mov ax, y1
    mov bx, lengthT
    add bx, widthT
    add bx, widthT
    cmp ax, bx
    jae skip1U
    mov ax, y1
    mov bx, widthT
    add bx, widthT
    cmp ax, bx
    jnb escape_6
    jmp far ptr cs:lowU
    escape_6:
    sub ax, bx
    mov temporaryLength, ax
    skip1U:          ;;;; check for lines in memory, ax = temporary length
    mov cx, temporaryLength
    add cx, widthT
    add cx, widthT
    mov ax, 320
    mov bx, y1
    sub bx, 1        ;;; 3shan abos 3l above pixel
    mul bx
    add ax, x1
    mov di, ax
    mov ah, 0;
    mov al, 03h ;;;;; color
    scan1U: ;;; hnscan shwya
    scasb
    jz exit1U
    sub di, 321 ;;; elly et7arakha w hnwdeha fo2
    loop scan1U
    exit1U:      ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
    mov dx, cx  ;;; allowed fl dx
    mov cx, temporaryLength
    mov bx, widthT
    add bx, widthT
    add cx, bx
    sub cx, dx
    cmp cx, bx
    jnb escape_7
    jmp far ptr cs:dontU
    escape_7:
    sub cx, bx ;;; allowed
    mov temporaryLength, cx ;;;; allowed mn first check 3ayzeen 3l tany mn gher mnghyr
    
    ;;;;; first test
    
    
    ;;;; second test
    mov ax, lengthT
    mov temporaryLength2, ax

    mov ax, y1
    mov bx, lengthT
    add bx, widthT
    add bx, widthT
    cmp ax, bx
    jae skip2U
    mov ax, y1
    mov bx, widthT
    add bx, widthT
    cmp ax, bx
    jb lowU
    sub ax, bx
    mov temporaryLength2, ax
    skip2U:          ;;;; check for lines in memory, ax = temporary length
    mov cx, temporaryLength2
    add cx, widthT
    add cx, widthT
    mov ax, 320
    mov bx, y1
    sub bx, 1
    mul bx
    add ax, x2
    ;;;; mmkn nhtag n shift el X 3la hasab howa gy mn ymen wla shmal

    mov dx, lastDirection
    cmp dx, 2
    jz rightU
    sub ax, widthT
    jmp leftU
    rightU:
    add ax, widthT
    leftU:
    ;;;;
    mov di, ax
    mov ah, 0;
    mov al, 03h ;;;;; color
    scan2U: ;;; hnscan shwya
    scasb
    jz exit2U
    sub di, 321 ;;; elly et7arakha w hnwdeha fo2
    loop scan2U
    exit2U:      ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
    mov dx, cx  ;;; allowed fl dx
    mov cx, temporaryLength2
    mov bx, widthT
    add bx, widthT
    add cx, bx
    sub cx, dx
    cmp cx, bx
    jb dontU
    sub cx, bx ;;; allowed
    mov temporaryLength2, cx ;;;; allowed mn second check 3l tany
    jmp exitAllU
    ;;;; second test   
    
    
    
    dontU:
    mov temporaryLength2, 0
    mov temporaryLength, 0
    mov dontDraw, 1
    
    lowU:
    mov temporaryLength2, 0
    mov temporaryLength, 0
    exitAllU:
    ret
checkUp endp 
 
 

checkDown proc   ;;;; still to be tested  dymn check bl Y2 3shan lower w ghyr X
    
    ;;;; mmkn nhtag n shift el x 3la hasab howa gy mn ymen wla shmal fl second test  
    mov ax, y2
    cmp ax, row
    jnz escape_8
    jmp far ptr cs:dontD
    escape_8:
    ;;;;; first test
    mov ax, lengthT
    mov temporaryLength, ax

    mov ax, row

    mov bx, y2
    add bx, lengthT
    add bx, widthT
    add bx, widthT 
    cmp ax, bx
    jae skip1D
    mov ax, row
    sub ax, widthT
    sub ax, widthT
    mov bx, ax
    mov ax, y2
    cmp bx, ax
    jnb escape_9
    jmp far ptr cs:low1D
    escape_9:
    
    sub bx, ax
    mov ax, bx
    mov temporaryLength, ax
    skip1D:          ;;;; check for lines in memory, ax = temporary length
    mov cx, temporaryLength
    add cx, widthT
    add cx, widthT
    mov ax, 320
    mov bx, y2
    add bx, 1       ;; nnzl taht pixel
    mul bx
    add ax, x1
    mov di, ax
    mov ah, 0;
    mov al, 03h ;;;;; color
    scan1D: ;;; hnscan shwya
    scasb
    jz exit1D
    add di, 319 ;;; elly et7arakha w hnwdeha fo2
    loop scan1D
    exit1D:      ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
    mov dx, cx  ;;; allowed fl dx
    mov cx, temporaryLength
    mov bx, widthT
    add bx, widthT
    add cx, bx
    sub cx, dx
    cmp cx, bx
    jnb escape_10
    jmp far ptr cs:dontD
    escape_10:
    sub cx, bx ;;; allowed
    mov temporaryLength, cx ;;;; allowed mn first check 3ayzeen 3l tany mn gher mnghyr
    
    ;;;;; first test
    
    
    ;;;; second test
    mov ax, lengthT
    mov temporaryLength2, ax

    mov ax, row
    mov bx, y2
    add bx, lengthT
    add bx, widthT
    add bx, widthT 
    cmp ax, bx

    jae skip2D
    mov ax, row
    sub ax, widthT
    sub ax, widthT
    mov bx, ax
    mov ax, y2
    cmp bx, ax
    jb low1D
    sub bx, ax
    mov ax, bx
    mov temporaryLength2, ax
    skip2D:          ;;;; check for lines in memory, ax = temporary length
    mov cx, temporaryLength2
    add cx, widthT
    add cx, widthT
    mov ax, 320
    mov bx, y2
    add bx, 1 ;;;; check pixel taht
    mul bx
    
    
    add ax, x2
    
    ;;;; mmkn nhtag n shift el X 3la hasab howa gy mn ymen wla shmal

    mov dx, lastDirection
    cmp dx, 2
    jz rightD
    sub ax, widthT
    jmp leftD
    rightD:
    add ax, widthT
    leftD:
    ;;;; 
    mov di, ax
    mov ah, 0;
    mov al, 03h ;;;;; color
    scan2D: ;;; hnscan shwya
    scasb
    jz exit2D
    add di, 319 ;;; elly et7arakha w hnwdeha taht
    loop scan2D
    exit2D:      ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
    mov dx, cx  ;;; allowed fl dx
    mov cx, temporaryLength2
    mov bx, widthT
    add bx, widthT
    add cx, bx
    sub cx, dx
    cmp cx, bx
    jb dontD
    sub cx, bx ;;; allowed
    mov temporaryLength2, cx ;;;; allowed mn second check 3l tany
    jmp exitAllD
    ;;;; second test   
    
    
    
    dontD:
    mov temporaryLength2, 0
    mov temporaryLength, 0
    mov dontDraw, 1
    low1D:
    mov temporaryLength2, 0
    mov temporaryLength, 0
    exitAllD:
    ret
checkDown endp



checkRight proc  ;;;y1 = y2, x2 3l ymen = use it
    
    mov ax, x2
    cmp ax, 319
    jnz escape_11
    jmp far ptr cs:dontR
    escape_11:
    ;;;;; first test
    mov ax, lengthT
    mov temporaryLength, ax

    mov ax, 319
    mov bx, x2
    add bx, lengthT
    add bx, widthT
    add bx, widthT
    cmp ax, bx
    jae skip1R
    mov ax, 319
    sub ax, widthT
    sub ax, widthT
    mov bx, ax
    mov ax, x2
    cmp bx, ax
    jnb escape_12
    jmp far ptr cs:lowR
    escape_12:
    sub bx, ax
    mov ax, bx
    mov temporaryLength, ax
    skip1R:          ;;;; check for lines in memory, ax = temporary length
    mov cx, temporaryLength
    add cx, widthT
    add cx, widthT
    mov ax, 320
    mov bx, y1
            
    mul bx
    add ax, x2
    add ax,1      ;;; 3shan abos 3l right pixel
    mov di, ax
    mov ah, 0;
    mov al, 03h ;;;;; color
    scan1R: ;;; hnscan shwya
    scasb
    jz exit1R
    loop scan1R
    exit1R:      ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
    mov dx, cx  ;;; allowed fl dx
    mov cx, temporaryLength
    mov bx, widthT
    add bx, widthT
    add cx, bx
    sub cx, dx
    cmp cx, bx
    jnb escape_13
    jmp far ptr cs:dontR
    escape_13:
    sub cx, bx ;;; allowed
    mov temporaryLength, cx ;;;; allowed mn first check 3ayzeen 3l tany mn gher mnghyr
    
    ;;;;; first test
    
    
    ;;;; second test
    mov ax, lengthT
    mov temporaryLength2, ax

    mov ax, 319
    mov bx, x2
    add bx, lengthT
    add bx, widthT
    add bx, widthT
    cmp ax, bx
    jae skip2R
    mov ax, 319
    sub ax, widthT
    sub ax, widthT
    mov bx, ax
    mov ax, x2
    cmp bx, ax
    jb lowR
    sub bx, ax
    mov ax, bx
    mov temporaryLength2, ax
    skip2R:          ;;;; check for lines in memory, ax = temporary length
    mov cx, temporaryLength2
    add cx, widthT
    add cx, widthT
    mov ax, 320
    mov bx, y1
    
    ;;;; mmkn nhtag n shift el height 3la hasab howa gy mn taht wla fo2

    mov dx, lastDirection
    cmp dx, 1        ;;; down is 1
    jz downR
    sub bx, widthT
    jmp upR
    downR:
    add bx, widthT
    upR:
    ;;;;          
    mul bx
    add ax, x2
    add ax,1      ;;; 3shan abos 3l right pixel
    mov di, ax
    mov ah, 0;
    mov al, 03h ;;;;; color
    scan2R: ;;; hnscan shwya
    scasb
    jz exit2R
    loop scan2R
    exit2R:      ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
    mov dx, cx  ;;; allowed fl dx
    mov cx, temporaryLength2
    mov bx, widthT
    add bx, widthT
    add cx, bx
    sub cx, dx
    cmp cx, bx
    jb dontR
    sub cx, bx ;;; allowed
    mov temporaryLength2, cx ;;;; allowed mn second check 3ayzeen 3l tany mn gher mnghyr
    jmp exitAllR
    ;;;; second test   
    
    
    
    dontR:
    mov temporaryLength2, 0
    mov temporaryLength, 0
    mov dontDraw, 1
    
    lowR:
    mov temporaryLength2, 0
    mov temporaryLength, 0
    exitAllR:
    ret
checkRight endp 


checkLeft proc       ;;;y1 = y2, x1 3l shmal = use it
    
    mov ax, x1
    cmp ax, 0
    jnz escape_14
    jmp far ptr cs:dontL
    escape_14:
    ;;;;; first test
    mov ax, lengthT
    mov temporaryLength, ax

    mov ax, x1
    mov bx, lengthT
    add bx, widthT
    add bx, widthT
    cmp ax, bx
    jae skip1L
    mov ax, x1
    mov bx, widthT
    add bx, widthT
    cmp ax, bx
    jnb escape_15
    jmp far ptr cs:lowL
    escape_15:
    sub ax, bx
    mov temporaryLength, ax
    skip1L:          ;;;; check for lines in memory, ax = temporary length
    mov cx, temporaryLength
    add cx, widthT
    add cx, widthT
    mov ax, 320
    mov bx, y1
            
    mul bx
    add ax, x1
    sub ax,1      ;;; 3shan abos 3l left pixel
    mov di, ax
    mov ah, 0;
    mov al, 03h ;;;;; color
    scan1L: ;;; hnscan shwya
    scasb
    jz exit1L
    sub di, 2 ;;;; 3shan amshy shmal
    loop scan1L
    exit1L:      ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
    mov dx, cx  ;;; allowed fl dx
    mov cx, temporaryLength
    mov bx, widthT
    add bx, widthT
    add cx, bx
    sub cx, dx
    cmp cx, bx
    jnb escape_16
    jmp far ptr cs:dontL
    escape_16:
    sub cx, bx ;;; allowed
    mov temporaryLength, cx ;;;; allowed mn first check 3ayzeen 3l tany mn gher mnghyr
    
    ;;;;; first test
    
    
    ;;;; second test
    mov ax, lengthT
    mov temporaryLength2, ax

    mov ax, x1
    mov bx, lengthT
    add bx, widthT
    add bx, widthT
    cmp ax, bx
    jae skip2L
    mov ax, x1
    mov bx, widthT
    add bx, widthT
    cmp ax, bx
    jb lowL
    sub ax, bx
    mov temporaryLength2, ax
    skip2L:          ;;;; check for lines in memory, ax = temporary length
    mov cx, temporaryLength2
    add cx, widthT
    add cx, widthT
    mov ax, 320
    mov bx, y1
    ;;;; mmkn nhtag n shift el height 3la hasab howa gy mn taht wla fo2

    mov dx, lastDirection
    cmp dx, 1           ;;; down is 1
    jz downL
    sub bx, widthT
    jmp upL
    downL:
    add bx, widthT
    upL:
    ;;;;    
    mul bx
    add ax, x1
    sub ax,1      ;;; 3shan abos 3l left pixel
    mov di, ax
    mov ah, 0;
    mov al, 03h ;;;;; color
    scan2L: ;;; hnscan shwya
    scasb
    jz exit2L
    sub di, 2 ;;;; 3shan amshy shmal
    loop scan2L
    exit2L:      ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
    mov dx, cx  ;;; allowed fl dx
    mov cx, temporaryLength2
    mov bx, widthT
    add bx, widthT
    add cx, bx
    sub cx, dx
    cmp cx, bx
    jb dontL
    sub cx, bx ;;; allowed
    mov temporaryLength2, cx ;;;; allowed mn first check 3ayzeen 3l tany mn gher mnghyr
    jmp exitAllL
    ;;;; second test   
    
    
    
    dontL:
    mov temporaryLength2, 0
    mov temporaryLength, 0
    mov dontDraw, 1
    
    lowL:
    mov temporaryLength2, 0
    mov temporaryLength, 0
    exitAllL:  
    ret
    
    
checkLeft endp 
 
 
 

drawUp proc far ;;; after checking 

  call checkUP
  cmp dontDraw, 1
  jz exitU
  mov ax, temporaryLength
  cmp ax, temporaryLength2
  jbe skipSwapU
  mov ax, temporaryLength2
  mov temporaryLength, ax
  
  skipSwapU:
     mov lengthT, ax
     call trackUp
     mov ax, lengthD
     mov lengthT, ax
     
  exitU:
    mov dontDraw, 0
    ret 
drawUp endP

drawRight proc far ;;; after checking 

  call checkRight
  cmp dontDraw, 1
  jnz escape_17
  jmp far ptr cs:exit
  escape_17:
  mov ax, temporaryLength
  cmp ax, temporaryLength2
  jbe skipSwapR
  mov ax, temporaryLength2
  mov temporaryLength, ax

  skipSwapR:
     mov lengthT, ax
     call trackRight
     mov ax, lengthD
     mov lengthT, ax
     
  exitR:
    mov dontDraw, 0
    ret 
drawRight endp

drawLeft proc far ;;; after checking 

  call checkLeft 
  cmp dontDraw, 1
  jz exitL
  mov ax, temporaryLength
  cmp ax, temporaryLength2
  jbe skipSwapL
  mov ax, temporaryLength2
  mov temporaryLength, ax

  skipSwapL:
     mov lengthT, ax
     call trackLeft
     mov ax, lengthD
     mov lengthT, ax
     
  exitL:
    mov dontDraw, 0
    ret 
drawLeft endp


drawDOWN proc far 

  call checkDown
  cmp dontDraw, 1
  jz exitD
  mov ax, temporaryLength
  cmp ax, temporaryLength2
  jbe skipSwapD
  mov ax, temporaryLength2
  mov temporaryLength, ax
  skipSwapD:
     mov lengthT, ax
     call trackDown
     mov ax, lengthD
     mov lengthT, ax 
     
  exitD:
    mov dontDraw, 0
    ret 
drawDOWN endp



drawTrack proc far 
   
        
        ;;;; call new proc
         call drawStartLine
        ;; test track up
        mov ax, widthT
        mov x2, ax
        call drawDOWN
        mov cx, 0FFh     ;;; 3dd el randoms  
        ;;; random
        rand:
        push cx
        mov ah, 2ch
        int 21h
        ;; test2
        mov ch,0
        mov cl, dh
        shl cl, 2
        loop22:
        push cx
        mov ah, 2ch
        int 21h
        pop cx
        loop loop22
        ;; test2
        mov ah, 0
        mov al, dl  ;;micro seconds?
        mov bl, 4
        
        div bl
        ;;; ah = rest
        cmp ah, 0
        jz U
        cmp ah, 2
        jz D
        cmp ah,3
        jz R
        cmp ah,1
        jz L
        U:
        call drawUP 
        jmp next
        D:
        call drawDOWN 
        jmp next
        R:
        mov ax, lengthT
        push ax
        add ax, lengthT
        mov lengthT, ax
        call drawRight
        pop ax
        mov lengthT, ax
        jmp next
        
        L:
        mov ax, lengthT
        push ax
        add ax, lengthT
        mov lengthT, ax
        call drawLeft
        pop ax
        mov lengthT, ax
        jmp next
        
        next:
        pop cx
        loop rand
        ;;;;; inline chat row
        mov ax, 320
        mov bx, word ptr row
        ;;;;;; draw the line taht b pixel
        inc bx
        mul bx
        mov di, ax
        mov al, 0eh
        mov cx, 320
        rep stosb
        
        ;;;;;inline chat row

        ;;;; call for new proc
        call drawEndLine
        ret
drawtrack endp
;;;;;;;;;;;;;;;;;;;;; Daowd 2 new procs

drawEndLine proc far
    mov ax, x1
    mov bx, x2
    cmp ax, bx
    jz vertical
    mov ax, 320
    mov bx, y1
    mul bx
    add ax, x1
    mov di, ax
    mov cx, x2
    sub cx, x1
    mov al, 04h
    rep stosb

    jmp endLine
    vertical:
    mov cx, y2
    sub cx, y1
    mov ax, 320
    mov bx, y1
    mul bx
    add ax, x1
    mov di, ax
    color:
    mov al, 04h
    stosb
    add di, 319
    loop color
    
    
    
    endLine:
ret
drawEndLine endp


drawStartLine proc far
    ;;start line
    mov ax, widthT
    mov lengthD, ax
    call horizLineR
    mov ax, lengthT
    mov lengthD, ax
    
    mov x, 0
    ;;start line
ret
drawStartLine endp



;;;;;;;;;;;;;;;;;;;;;; Daowd 2 new procs


gettime proc 


    mov ah, 2ch
    int 21h
    mov prevsec, dh

taketime:
mov bl,cursec
mov prevsec,bl
    mov ah, 2ch
    int 21h
    mov cursec, dh
    mov bh,prevsec
    ;sub cursec, bl ; Calculate the difference in seconds
    cmp cursec, bh 
    je taketime
    inc timer      ; Check if 10 seconds have passed
    cmp timer,5

    jge endofgame        ; If 10 seconds have passed, display the message
    jmp taketime
endofgame:
mov aX, 0600h ;bacground
      mov bh, 03h
      mov cx, 0603h
      mov dx, 1324h       
      int 10h 

    MOV AH,02  
    MOV BH,00  ;page    
    MOV DL,16 ;column  
    MOV DH,8  ;row 
    INT 10H 

    mov ah,9

        mov dx,offset gameovermsg
    int 21h
    ;;;;;;;;;;;;;;;;;;;;;;
    MOV AH,02  
    MOV BH,00  ;page    
    MOV DL,4 ;column  
    MOV DH,8  ;row 
    INT 10H 
    ;;;;;;;
    mov ah,9

        mov dx,offset firstPlayerName+2
    int 21h
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
     MOV AH,02  
    MOV BH,00  ;page    
    MOV DL,30 ;column  
    MOV DH,8  ;row 
    INT 10H 

    mov ah,9

        mov dx,offset secondPlayerName+2
    int 21h
    ;;;;;;;;;;;;;;;;;;;;;;;;;
   ; MOV AX,0A000h
    ;MOV ES,AX
    lea si,gameoverpic
    mov di,25728
     MOV DX,73

    REPEAT4:
    MOV CX,80
REP MOVSB
ADD DI,SCREEN_WIDTH-80
DEC DX
JNZ REPEAT4
;;;;;;;;;;;;;;;;;;;
lea si,blueover
 mov di,25632
     MOV DX,30

    REPEAT5:
    MOV CX,50
REP MOVSB
ADD DI,SCREEN_WIDTH-50
DEC DX
JNZ REPEAT5
;;;;;;;;;;;;;;;;;
lea si,redover
 mov di,25828
     MOV DX,30

    REPEAT6:
    MOV CX,55
REP MOVSB
ADD DI,SCREEN_WIDTH-55
DEC DX
JNZ REPEAT6


ret
gettime endp



