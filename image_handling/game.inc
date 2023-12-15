game proc far
mov ah,0    
    mov al,13h  ;GRAPHICS
    INT 10H  
     
      mov aX, 0600h ;bacground
     mov bh, 00h
    mov cx, 0000h
    mov dx, 184Fh       
    int 10h 
    MOV DI,6420 ;STARTING PIXEL
      ;;;;;;;;;;;;;;;;;

       MOV AX,0A000h
    MOV ES,AX

    MOV SI,offset beginpage
    
    MOV DX,160

    REPEATt:
    MOV CX,280
    REP MOVSB
    ADD DI,320-280
    DEC DX
    JNZ REPEATt 
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;done
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
mov bh,5eh  ;fore yellow/back blue 
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
      mov bh, 196
      mov cx, 0000h
      mov dx, 184Fh       
      int 10h 
      ;call game
      ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
      mov aX, 0600h ;bacground
      mov bh, 09h
      mov cx, 1200h
      mov dx, 154fh       
      int 10h 
      ;;;;;;;;;;;
      
      call displayInitialTime
      
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
    
    MOV DX,20

    REPEAT3:
    MOV CX,33
REP MOVSB
ADD DI,SCREEN_WIDTH-33
DEC DX
JNZ REPEAT3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
mov Di ,46675
MOV SI,offset rightcar
  MOV DX,20
    REPEAT2:
    MOV CX,37
REP MOVSB
ADD DI,SCREEN_WIDTH-37
DEC DX
JNZ REPEAT2


        mov pos_box1, 321
        mov pos_box2, 333
    
        
        call drawTrack
        call initialize_cars
        call set_interrupt
        ;;;;;;;;;;;;;;play
        call play
        call ret_interrupt    
        
  ;call getwinner
  
      ret
game endp

; ------------------------- Draw Cars ----------------------------------------- ;
set_interrupt proc
            
            push ax
            push es
            push bx
            mov ax, 3509h ; Get Interrupt Vector
            int  21h ; -> ES:BX
            mov old_int_offset, bx
            mov old_int_seg, es
            pop bx
            pop es
            cli
        ; replace the existing int09h handler with ours
            push DS
            mov dx, offset myint ; new offset 
            mov ax, seg myint ; new segment
            mov ds, ax 
            mov ax, 2509h
            int 21h
            pop ds  
            pop ax
            sti
            ret
set_interrupt endp
;-----------------------------------------------------;
ret_interrupt proc
              push ax
              push ds
              push dx
              mov dx,old_int_offset
              mov ds,old_int_seg
              mov ax, 2509h
              int 21h
              pop dx
              pop ds    
              pop ax
              ret
ret_interrupt endp
; ------------------ MY Own handler ------------------;
myint proc          ;  my keyboard interrupt handler 
    push bx
    in   al, 60h
    mov  ah, 0
    mov  bx, ax
    and  bx, 127           ; 7-bit scancode goes to BX
    shl  ax, 1             ; 1-bit pressed/released goes to AH
    xor  ah, 1             ; -> AH=1 Pressed, AH=0 Released
    mov  [KeyList + bx], ah
    mov  al, 20h           ; The non specific EOI (End Of Interrupt)
    out  20h, al
    pop  bx 
    iret
myint endp
; ----------------------- Initialize Car components --------------------------- ;
initialize_cars proc
                mov di,pos_box1
                mov si,offset redcar
                call draw_c
                mov di,pos_box2
                mov si,offset bluecar
                call draw_c
                ret
initialize_cars endp
; ------------------------------------------------------------------------------;
draw_c            proc
                push di
                pusha  ; for safety
                mov bl,pixel_size ; loop pixel size times
                my_draw_c:  mov cx,pixel_size ; for stosb 
                        rep movsb  ; draw horizontal line
                        sub di,pixel_size ; return to original position
                        add di,k ; new row
                        dec bl ; loop pixel size times
                        jnz my_draw_c
                popa
                pop di
                ret  
draw_c            endp
; ------------------------------- ;
rotate_left     proc
                pusha
                add di, pixel_size - 1
                mov bl,pixel_size
                mov cl,pixel_size
                outer:
                        mov bl,pixel_size
                        inner:
                                movsb 
                                dec di
                                add di,k
                                dec bl
                                jnz inner
                        
                        
                        dec di
                        sub di,k*(pixel_size)
                        dec cl
                        jnz outer
                popa
                ret
rotate_left     endp            
; ------------------------------- ;
; ------------------------------- ;
rotate_right    proc
                pusha
                add di, k * (pixel_size - 1)
                mov bl,pixel_size
                mov cl,pixel_size
                outer_r:
                        mov bl,pixel_size
                        inner_r:
                                movsb 
                                dec di
                                sub di,k
                                dec bl
                                jnz inner_r
                        
                        
                        inc di
                        add di,k*(pixel_size)
                        dec cl
                        jnz outer_r
                popa
                ret
rotate_right    endp            
; ------------------------------- ;
; - no rotate up just draw car --;
; ------------------------------- ;
rotate_up       proc
                pusha
                add di, (pixel_size - 1)*(k)
                mov bl,pixel_size
                mov cl,pixel_size
                outer_d:
                        mov bl,pixel_size
                        inner_d:
                                movsb 
                                dec bl
                                jnz inner_d
                        
                        
                        sub di,pixel_size
                        sub di,k
                        dec cl
                        jnz outer_d
                popa
                ret
rotate_up       endp            
; ------------------------------- ;
draw_l           proc
        ; ---- store changed vars ------------ ;
                push cx 
                push ax
                push di
                mov cx,pixel_size ; for stosb
                rep movsb
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
; --------------------------------------------- ;

; - --------------------Move the second box---------------------------- ;

; --------------------------------------------- ;
move_b1            proc
                pusha
                ; ----- Move box --------- ;
                cmp state_c1,0
                jz endmove
                move_box: 
                        push di ; store original value
                        cmp [KeyList + 48h] ,1
                        jnz down
                    ; ------- checks first  --------------;
                    ; ----- first check "track check top right corner"------;
                    push cx
                    push si
                    mov cx,pixel_size
                    mov di,pos_box1
                    sub di,k
                    mov si,offset color_path
                    obstacle_hit_u1:
                                    cmpsb 
                                    jnz temp_again_u1
                                    dec si
                                    dec cx
                                    jnz obstacle_hit_u1
                    
                    pop cx ; no pop si It will be popped later
                    ; ----- third check ------;
                    third_check_up1:
                    mov si, pos_box2
                    mov di,pos_box1
                    sub di,k
                    add si,k*(pixel_size - 1)
                    add si,pixel_size - 1
                    cmp di,si
                    ja all_good_up1
                    ; ----- fourth check -----;
                    fourth_check_up1:
                    mov di,pos_box1
                    mov si,pos_box2
                    add si,k*(pixel_size - 1)
                    sub di,k
                    add di,pixel_size - 1
                    cmp di,si
                    jb all_good_up1
                    pop si
                    jmp terminate1
                    ; ------------------------- ;
                    all_good_up1:
                        pop si
                        mov di, pos_box1
                        cmp last_mov_c1, 0
                        jz escape_up1

                        mov si,offset redcar ; red car
                        mov di, pos_box1 ; copy to position
                        call rotate_up ; rotate the car
                        mov last_mov_c1,0 ; update last move
                        jmp terminate1

                        escape_up1:
                        mov last_mov_c1 , 0
                        removelast:  
                                    add di, k*(pixel_size - 1) ; go to last row
                                    mov al,color_path ; "MAY BE CHANGED BASED ON BACKGROUND COLOR."
                                    mov cx,pixel_size ; 8 times size of row
                                    rep stosb
                                    
                        pop di
                        sub di,k   ; new  start position
                        push di ; save new start position
                        mov si,offset redcar
                        call rotate_up ; draw line at the beginning as if move up
                        pop di ; set new value of di
                        mov pos_box1,di
                        jmp endmove

                        down: 
                        cmp [KeyList + 50h] ,1
                        jnz right
                         ; ------- checks first  --------------;
                    ; ----- first check "track check top right corner"------;
                    push cx
                    push si
                    mov cx,pixel_size
                    mov di,pos_box1
                    add di,k*pixel_size
                    mov si,offset color_path
                    obstacle_hit_d1:
                                    cmpsb 
                                    jnz temp_again_d1
                                    dec si
                                    dec cx
                                    jnz obstacle_hit_d1
                    
                    pop cx ; no pop si It will be popped later
                    ; ----- third check ------;
                    third_check_down1:
                    mov si, pos_box2
                    mov di,pos_box1
                    add di,k*pixel_size
                    add si,pixel_size - 1
                    cmp di,si
                    ja all_good_down1
                    ; ----- fourth check -----;
                    fourth_check_down1:
                    mov di,pos_box1
                    mov si,pos_box2
                    add di,k*(pixel_size)
                    add di,pixel_size - 1
                    cmp di,si
                    jb all_good_down1
                    pop si
                    jmp terminate1
                    ; ------------------------- ;
                    all_good_down1:
                        pop si
                        mov di, pos_box1
                        
                        cmp last_mov_c1, 1
                        jz escape_down1 ; complete normally

                        mov si,offset redcar ; red car
                        mov di, pos_box1 ; copy to position
                        call draw_c ; flip the car
                        mov last_mov_c1,1 ; update last move
                        jmp terminate1

                        escape_down1:
                        mov last_mov_c1 , 1
                        removefirst:  
                                    mov al,color_path ; "TO BE REPLACED BY THE BACKGROUND COLOR"
                                    mov cx,pixel_size
                                    rep stosb
                                    
                        pop di 
                        add di,k ; set the new pos
                        push di 
                        mov si,offset redcar
                        call draw_c ; draw horizontal line at the end
                        pop di
                        mov pos_box1,di ; set the new position 
                        jmp endmove
                      ; --- right --- ;
                        right: 
                       cmp [KeyList + 4Dh] ,1
                        jnz temp_left 
                ; ------- checks first  --------------;
                ; ---- Track colors check ------------;
                    push cx
                    push si
                    mov cx,pixel_size
                    mov di,pos_box1
                    add di,pixel_size
                    mov si,offset color_path
                    obstacle_hit_r1:
                                    cmpsb 
                                    jnz temp_again_r1
                                    dec di
                                    dec si
                                    add di,k
                                    dec cx
                                    jnz obstacle_hit_r1
                    
                    pop si
                    pop cx
                ; -------------------------------------- ;
                    mov di,pos_box1
                    mov si,pos_box2
                    add di,pixel_size
                    cmp di,si
                    ja fourth_check_r1
                    sub si,di
                    mov ax,si
                    mov dx,0
                    mov cx,k
                    div cx
                    cmp dx,0 ; there is no remainder meaning on the same vertcal line
                    jne all_good_right1
                    cmp ax,pixel_size
                    ja  all_good_right1
                    jmp terminate1
                    temp_left: jmp left
                    
                    temp_again1:
                            pop si
                            pop cx
                            mov si,offset obstacle_color
                            mov powerupcar,1
                            call check_obstacle
                            cmp powerupchooser, 0
                            jz terminate1
                            pop di
                            call gotpowerup
                            jmp endmove
                    temp_again11:
                            pop si
                            pop cx
                            mov si,offset obstacle_color
                            mov powerupcar,1
                            call check_obstacle2
                            cmp powerupchooser, 0
                            jz terminate1
                            pop di
                            call gotpowerup
                            jmp endmove
                            jmp move_box
                    fourth_check_r1:
                    sub di,si
                    mov ax,di
                    mov dx,0
                    mov cx,k
                    div cx
                    cmp dx,0 ; there is no remainder meaning on the same vertcal line
                    jne all_good_right1
                    cmp ax,pixel_size ; not on the same horizontal line
                    ja  all_good_right1
                    jmp terminate1
                    ; --- all temp againssss -- ;
                    temp_again_u1 :
                            mov di,pos_box1
                            sub di,k
                            jmp temp_again1
                    
                    temp_again_d1 :
                            mov di,pos_box1
                            add di,k*pixel_size
                            jmp temp_again1
                    temp_again_r1 :
                            mov di,pos_box1
                            add di,pixel_size
                            jmp temp_again11
                    
                    temp_again_l1 :
                            mov di,pos_box1
                            dec di
                            jmp temp_again11
                    ; end temp agains  --- ;
                ; -------------------------------------- ;
                    all_good_right1:
                        mov di, pos_box1

                        cmp last_mov_c1,2 ; if it is the last move don't rotate
                        jz escape_rotr1 ; don't rotate gain
                        mov si,offset redcar ; red car
                        mov di, pos_box1 ; copy to position
                        call rotate_right ; rotate the car
                        mov last_mov_c1,2 ; update last move
                        jmp terminate1
                        escape_rotr1:

                        mov last_mov_c1 , 2
                        mov cx,pixel_size
                        removeleft:  
                                    mov al,color_path
                                    stosb
                                    dec di
                                    add di,k
                                    dec cx
                                    jnz removeleft
                                    
                        pop di 
                        inc di 
                        mov si,offset redcar
                        call rotate_right
                        mov pos_box1,di
                        jmp endmove
                    ; --- left --- ;
                        left: 
                        cmp [KeyList + 4Bh] ,1
                        jnz box2switchmid
                ; ---- Track colors check ------------;
                    push cx
                    push si
                    mov cx,pixel_size
                    mov di,pos_box1
                    dec di
                    mov si,offset color_path
                    obstacle_hit_l1:
                                    cmpsb 
                                    jnz temp_again_l1
                                    dec di
                                    dec si
                                    add di,k
                                    dec cx
                                    jnz obstacle_hit_l1
                    
                    pop si
                    pop cx
                ; -------------------------------------- ;
                ; ------------first car check--------------------- ;
                    mov di,pos_box2
                    mov si,pos_box1
                    add di,pixel_size
                    cmp di,si
                    ja fourth_check_l1
                    sub si,di
                    mov ax,si
                    mov dx,0
                    mov cx,k
                    div cx
                    cmp dx,0 ; there is no remainder meaning on the same vertcal line
                    jne all_good_left1
                    cmp ax,pixel_size
                    ja  all_good_left1
                    jmp terminate1
                    box2switchmid:jmp terminate1
                    fourth_check_l1:
                    sub di,si
                    mov ax,di
                    mov dx,0
                    mov cx,k
                    div cx
                    cmp dx,0 ; there is no remainder meaning on the same vertcal line
                    jne all_good_left1
                    cmp ax,pixel_size ; not on the same horizontal line
                    ja  all_good_left1
                    jmp terminate1
                    ;---- END of checks --------; 
                    all_good_left1:
                        mov di, pos_box1


                        cmp last_mov_c1,3 ; if it is the last move don't rotate
                        jz escape_rotl1 ; don't rotate gain
                        mov si,offset redcar ; red car
                        mov di, pos_box1 ; copy to position
                        call rotate_left ; rotate the car
                        mov last_mov_c1,3 ; update last move
                        jmp terminate1
                        escape_rotl1:
                        mov last_mov_c1 , 3
                        mov cx,pixel_size 
                        add di,pixel_size - 1
                        removeright:  
                                    mov al,color_path
                                    stosb
                                    dec di
                                    add di,k
                                    dec cx
                                    jnz removeright
                                    
                        pop di 
                        dec di 
                        mov si,offset redcar
                        call rotate_left
                        mov pos_box1,di
                        jmp endmove

                    terminate1:
                        pop di
                    endmove:
                popa
                ret
move_b1             endp
; ------------------------------- ;
move_b2            proc
            ; --- push vlues that will be updated -- ;
                push di
                push ax
                push cx
                cmp state_c2,0
                jz endmove2
                mov di,pos_box2
                ; ----- Move box 2--------- ;
                move_box2: 
                    push di ; store original value
                    cmp [KeyList + 11h],1 ; up key
                    jnz down2
                ; ------- checks first  --------------;
                ; ----- first check "track check top right corner"------;
                    push cx
                    push si
                    mov cx,pixel_size
                    mov di,pos_box2
                    sub di,k
                    mov si,offset color_path
                    obstacle_hit_u2:
                                    cmpsb 
                                    jnz temp_again_u2
                                    dec si
                                    dec cx
                                    jnz obstacle_hit_u2
                    
                    pop cx ; no pop si It will be popped later
                    ; ----- third check ------;
                    third_check_up2:
                    mov si, pos_box1
                    mov di,pos_box2
                    sub di,k
                    add si,k*(pixel_size - 1)
                    add si,pixel_size - 1
                    cmp di,si
                    ja all_good_up2
                    ; ----- fourth check -----;
                    fourth_check_up2:
                    mov di,pos_box2
                    mov si,pos_box1
                    add si,k*(pixel_size - 1)
                    sub di,k
                    add di,pixel_size - 1
                    cmp di,si
                    jb all_good_up2
                    pop si
                    jmp terminate2
                    ; --- all temp againssss -- ;
                    temp_again_u2 :
                            mov di,pos_box2
                            sub di,k
                            jmp temp_again2
                    
                    temp_again_d2 :
                            mov di,pos_box2
                            add di,k*pixel_size
                            jmp temp_again2
                    temp_again_r2 :
                            mov di,pos_box2
                            add di,pixel_size
                            jmp temp_again22
                    
                    temp_again_l2 :
                            mov di,pos_box2
                            sub di, 1
                            jmp temp_again22
                    ; end temp agains  --- ;
                    ; ------------------------- ;
                    all_good_up2:
                        pop si
                        mov di, pos_box2
                        cmp last_mov_c2, 0
                        jz escape_up2

                        mov si,offset bluecar ; red car
                        mov di, pos_box2 ; copy to position
                        call rotate_up ; rotate the car
                        mov last_mov_c2,0 ; update last move
                        jmp terminate2

                        escape_up2:
                        mov last_mov_c2 , 0

                        removelast2:  
                                    add di, k*(pixel_size - 1) ; go to last row
                                    mov al,color_path ; "MAY BE CHANGED BASED ON BACKGROUND COLOR."
                                    mov cx,pixel_size ; 8 times size of row
                                    rep stosb
                                    
                        pop di
                        sub di,k   ; new  start position
                        push di ; save new start position
                        mov si,offset bluecar
                        call rotate_up ; draw line at the beginning as if move up
                        pop di ; set new value of di
                        mov pos_box2,di
                        jmp endmove2
            ; ---------- LET'S MOVE DOWN ------------------ ;
                    down2: 
                        cmp [KeyList + 1Fh],1 ; down key
                        jnz right2

                            ; ------- checks first  --------------;
                        ; ----- first check "track check top right corner"------;
                        push cx
                        push si
                        mov cx,pixel_size
                        mov di,pos_box2
                        add di,k*pixel_size
                        mov si,offset color_path
                        obstacle_hit_d2:
                                        cmpsb 
                                        jnz temp_again_d2
                                        dec si
                                        dec cx
                                        jnz obstacle_hit_d2
                        
                        pop cx ; no pop si It will be popped later
                        ; ----- third check ------;
                        third_check_down2:
                        mov si, pos_box1
                        mov di,pos_box2
                        add di,k*pixel_size
                        add si,pixel_size - 1
                        cmp di,si
                        ja all_good_down2
                        ; ----- fourth check -----;
                        fourth_check_down2:
                        mov di,pos_box2
                        mov si,pos_box1
                        add di,k*(pixel_size)
                        add di,pixel_size - 1
                        cmp di,si
                        jb all_good_down2
                        pop si
                        jmp terminate2
                        ; ------------------------- ;
                        all_good_down2:
                            pop si
                            mov di, pos_box2

                            cmp last_mov_c2, 1
                            jz escape_down2 ; complete normally

                            mov si,offset bluecar ; red car
                            mov di, pos_box2 ; copy to position
                            call draw_c ; flip the car
                            mov last_mov_c2,1 ; update last move
                            jmp terminate2

                            escape_down2:
                            mov last_mov_c2 , 1

                            removefirst2:  
                                        mov al,color_path ; "TO BE REPLACED BY THE BACKGROUND COLOR"
                                        mov cx,pixel_size
                                        rep stosb
                                        
                            pop di 
                            add di,k ; set the new pos
                            push di 
                            mov si,offset bluecar
                            call draw_c ; draw horizontal line at the end
                            pop di
                            mov pos_box2,di ; set the new position 
                            jmp endmove2
                ;---------------- LETS MOVE RIGHT   --- ;
                    right2: 
                        cmp [KeyList + 20h],1 ; right key
                        jnz temp_left2
                ; ---- Track colors check ------------;
                        push cx
                        push si
                        mov cx,pixel_size
                        mov di,pos_box2
                        add di,pixel_size
                        mov si,offset color_path
                        obstacle_hit_r2:
                                        cmpsb 
                                        jnz temp_again_r2
                                        dec di
                                        dec si
                                        add di,k
                                        dec cx
                                        jnz obstacle_hit_r2
                        
                        pop si
                        pop cx
                    ; -------------------------------------- ;
                    ; ------------first car check--------------------- ;
                        mov di,pos_box2
                        mov si,pos_box1
                        add di,pixel_size
                        cmp di,si
                        ja fourth_check_r2
                        sub si,di
                        mov ax,si
                        mov dx,0
                        mov cx,k
                        div cx
                        cmp dx,0 ; there is no remainder meaning on the same vertcal line
                        jne all_good_right2
                        cmp ax,pixel_size
                        ja  all_good_right2
                        jmp terminate2
                        temp_left2: jmp left2
                        temp_again2: 
                            pop si
                            pop cx
                            mov si,offset obstacle_color
                            mov powerupcar,2
                            call check_obstacle
                            cmp powerupchooser, 0
                            jz terminate2
                            pop di
                            call gotpowerup
                            jmp endmove2
                        temp_again22: 
                            pop si
                            pop cx
                            mov si,offset obstacle_color
                            mov powerupcar,2
                            call check_obstacle2
                            cmp powerupchooser, 0
                            jz terminate2
                            pop di
                            call gotpowerup
                            jmp endmove2
                        fourth_check_r2:
                        sub di,si
                        mov ax,di
                        mov dx,0
                        mov cx,k
                        div cx
                        cmp dx,0 ; there is no remainder meaning on the same vertcal line
                        jne all_good_right2
                        cmp ax,pixel_size ; not on the same horizontal line
                        ja  all_good_right2
                        jmp terminate2
                        ;---- END of checks --------;  
                        all_good_right2:
                            mov di, pos_box2

                            cmp last_mov_c2,2 ; if it is the last move don't rotate
                            jz escape_rotr2 ; don't rotate gain
                            mov si,offset bluecar ; red car
                            mov di, pos_box2 ; copy to position
                            call rotate_right ; rotate the car
                            mov last_mov_c2,2 ; update last move
                            jmp terminate2
                            escape_rotr2:

                            mov last_mov_c2 , 2

                            mov cx,pixel_size
                            removeleft2:   ; remove the line on the left
                                        mov al,color_path
                                        stosb
                                        dec di
                                        add di,k
                                        dec cx
                                        jnz removeleft2
                                        
                            pop di 
                            inc di 
                            push di 
                            mov si,offset bluecar
                            call rotate_right
                            pop di
                            mov pos_box2,di
                            jmp endmove2
                            tempppp3: jmp terminate2
                     ; --- left --- ;
                    left2: 
                    cmp [KeyList + 1Eh],1 ; left key
                    jnz tempppp3
                ; ---- Track colors check ------------;
                        push cx
                        push si
                        mov cx,pixel_size
                        mov di,pos_box2
                        dec di
                        mov si,offset color_path
                        obstacle_hit_l2:
                                        cmpsb 
                                        jnz temp_again_l2
                                        dec di
                                        dec si
                                        add di,k
                                        dec cx
                                        jnz obstacle_hit_l2
                        
                        pop si
                        pop cx
                    ; -------------------------------------- ;
                    ; -------------------------------------- ;
                        mov di,pos_box1
                        mov si,pos_box2
                        add di,pixel_size
                        cmp di,si
                        ja fourth_check_l2
                        sub si,di
                        mov ax,si
                        mov dx,0
                        mov cx,k
                        div cx
                        cmp dx,0 ; there is no remainder meaning on the same vertcal line
                        jne all_good_left2
                        cmp ax,pixel_size
                        ja  all_good_left2
                        jmp terminate2
                        fourth_check_l2:
                        sub di,si
                        mov ax,di
                        mov dx,0
                        mov cx,k
                        div cx
                        cmp dx,0 ; there is no remainder meaning on the same vertcal line
                        jne all_good_left2
                        cmp ax,pixel_size ; not on the same horizontal line
                        ja  all_good_left2
                        jmp terminate2
                    ; -------------------------------------- ;
                        all_good_left2:
                            mov di, pos_box2

                            cmp last_mov_c2,3 ; if it is the last move don't rotate
                            jz escape_rotl2 ; don't rotate gain
                            mov si,offset bluecar ; red car
                            mov di, pos_box2 ; copy to position
                            call rotate_left ; rotate the car
                            mov last_mov_c2,3 ; update last move
                            jmp terminate2
                            escape_rotl2:
                            mov last_mov_c2 , 3

                            mov cx,pixel_size 
                            add di,pixel_size - 1
                            removeright2:  
                                        mov al,color_path
                                        stosb
                                        dec di
                                        add di,k
                                        dec cx
                                        jnz removeright2
                                        
                            pop di 
                            dec di 
                            push di
                            mov si,offset bluecar
                            call rotate_left
                            pop di
                            mov pos_box2,di
                            jmp endmove2
                    terminate2:
                        pop di
                    endmove2:
                        pop cx
                        pop ax
                        pop di
                    ret
move_b2             endp
; ------------------------------- ;

play            proc
                push di
                push ax
               
                check_move:
                        sti
                        mov cx,global_delay
                        call my_delay 
                        call freeze_2 ; the move and delay
                        call freeze_1
                        mov di,pos_box1 ; adjust pos for first car
                        call move_b1
                        mov di,pos_box2
                        call move_b2
                        call setcurrentsec
                        call check_poweractivation ; call to check if a car has activated its powers 
                        call markend ; time 
                        cmp flag,1
                        jz endr  
                        cmp powerupflag,1 
                        jz callpowers 
                        jmp check_move
                        callpowers:
                            call randompower
                            call choosewhichTorender
                            mov powerupflag,0
                        jmp check_move
                        endr:
                        pop ax
                        pop di
                        ;call ret_interrupt
                        call timeover
                          
                ret
play            endp

; ---------------- check obstacles --------------------------;
check_obstacle proc ; input di-> cars,  si -> color_obstacle
                pusha
                mov cx,pixel_size
                run_line:
                            cmpsb
                            jz Itisobstacle
                            dec si
                            dec cx
                            jnz run_line
                mov dx,powerupcar
                cmp dx, 1
                jnz itistwo
                mov powerupchooser , 1
                jmp endd
                itistwo :
                        mov powerupchooser, 2
                jmp endd
                Itisobstacle:
                            mov powerupchooser ,0
                endd:
                popa
                ret
check_obstacle endp
;------------------------------------------------------------;;
check_obstacle2 proc ; input di-> cars,  si -> color_obstacle
                pusha
                mov cx,pixel_size
                run_line2:
                            cmpsb
                            jz Itisobstacle2
                            dec si
                            dec di
                            add di,k
                            dec cx
                            jnz run_line2
                mov dx,powerupcar
                cmp dx, 1
                jnz itistwo2
                mov powerupchooser , 1
                jmp endd2
                itistwo2 :
                        mov powerupchooser, 2
                jmp endd2
                Itisobstacle2:
                            mov powerupchooser ,0
                endd2:
                popa
                ret
check_obstacle2 endp
;------------------------------------------------------------;;
speedup1 proc
        cmp di,pos_box1
        jnz twospeed
        mov sdelay_f_1, 1
        jmp endspeed
        twospeed:
        mov sdelay_f_2, 1
        endspeed:
         ret
speedup1 endp
;------------------------------------------------------------;;
speeddown1 proc
            cmp di,pos_box1
            jnz twospeed2
            mov sdelay_f_2, 3 ; If the first has speed down power up it means it slows the other
            jmp endspeed2
            twospeed2:
            mov sdelay_f_1, 3
            endspeed2:
           ret
speeddown1 endp
; ------------------------------------------------------------------ ;
check_poweractivation proc
                    push di
                    cmp [KeyList + 3],1 ; code for first car power activation
                    jnz check_other
                    mov di,pos_box1
                    call activate_powers
                    
                    check_other:
                                cmp [KeyList + 9],1 ; code for second car power activation
                                jnz end_check_powers
                                mov di,pos_box2
                                call activate_powers

                    end_check_powers:
                      pop di
                    ret
check_poweractivation endp
;---------------- deactivate power ups -----------------------------------;
releasepowerups proc
                pusha
                cmp di,pos_box1
                jnz relasecar2
                relasecar1:
                            cmp currentpoweractivatedrforCar1,1
                            jnz trysecond
                            mov sdelay_f_1, 2
                            jmp endrealeases1
                            trysecond:
                                        cmp currentpoweractivatedrforCar1,3
                                        jnz endrealeases
                                        mov sdelay_f_1, 2
                                        jmp endrealeases1
                relasecar2:
                            cmp currentpoweractivatedrforCar2,1
                            jnz trysecond2
                            mov sdelay_f_2, 2
                            jmp endrealeases2
                            trysecond2:
                                        cmp currentpoweractivatedrforCar2,3
                                        jnz endrealeases2
                                        mov sdelay_f_2, 2
                                        jmp endrealeases2
                endrealeases1:
                            mov currentpoweractivatedrforCar1, 4
                            mov time_powerc1,0
                            mov powerc1activated,0
                            jmp endrealeases
                endrealeases2:
                            mov currentpoweractivatedrforCar2, 4
                            mov time_powerc2,0
                            mov powerc2activated,0
                endrealeases:
                popa
                ret
releasepowerups endp
; ------------------------------------------------------------------------;
my_delay proc 
    
     delay_loop:
        dec cx          ; Decrement the delay count
        jnz delay_loop  ; Jump back to the loop if CX is not zero
    ret 
my_delay endp
;---------------------------------------------;
freeze_1 proc
        push cx
        cmp state_c1, 1 ; compare if move state
        jnz check_zero1 ; not move 
        dec delay_m_1 ; udate delay
        jnz end_freeze1 ; not ended
        mov state_c1,0 ; else: switch to freeze
        mov cx, sdelay_m_1 ; update variables
        mov delay_m_1, cx
        ;------------------------;
        check_zero1: ; means freeze state
        dec delay_f_1
        jnz end_freeze1
        mov state_c1,1
        mov cx, sdelay_f_1
        mov delay_f_1, cx
        ;------------------------;
        end_freeze1:
        pop cx
        ret
freeze_1 endp
;----------------------------------------------------;
freeze_2 proc
        push cx
        cmp state_c2, 1 ; compare if move state
        jnz check_zero2 ; not move 
        dec delay_m_2 ; udate delay
        jnz end_freeze2 ; not ended
        mov state_c2,0 ; else: switch to freeze
        mov cx, sdelay_m_2 ; update variables
        mov delay_m_2, cx
        ;------------------------;
        check_zero2: ; means freeze state
        dec delay_f_2
        jnz end_freeze2
        mov state_c2,1
        mov cx, sdelay_f_2
        mov delay_f_2, cx
        ;------------------------;
        end_freeze2:
        pop cx
        ret
freeze_2 endp
;---------------------------------------------------;
activate_powers proc
                push di
                cmp di,pos_box1 ; check if it is the first car
                jnz activatefor2 ; go to the second
                avtivatefor1:
                            cmp currentpowerforCar1, 4 ; if there is a power up to use
                            jz nochange ; else end it
                            mov di,pos_box1 ; adjust function parameters
                            call releasepowerups ;  
                            mov powerc1activated, 1
                            cmp currentpowerforCar1,1
                            jnz try1 
                            call speedup1
                            mov currentpowerforCar1,4
                            mov powerupcar1timer,0
                            mov currentpoweractivatedrforCar1,1
                            jmp endpowers
                            try1: ; three decrease other car speed ; 
                            cmp currentpowerforCar1, 3
                            jnz nochange
                            mov di,pos_box2
                            mov currentpoweractivatedrforCar1,3
                            call speeddown1
                            mov currentpowerforCar1,4
                            mov powerupcar1timer,0
                            jmp endpowers
                activatefor2:
                            cmp currentpowerforCar2, 4
                            jz nochange2
                            mov di,pos_box2
                            call releasepowerups
                            mov powerc2activated, 1
                            cmp currentpowerforCar2,1
                            jnz try11
                            mov currentpoweractivatedrforCar2,1
                            call speedup1
                            mov currentpowerforCar2,4
                            mov powerupcar2timer,0
                            jmp endpowers
                            try11:
                            cmp currentpowerforCar2, 3
                            jnz nochange
                            mov di,pos_box1
                            mov currentpoweractivatedrforCar2,3
                            call speeddown1
                            mov currentpowerforCar2,4
                            mov powerupcar2timer,0
                            jmp endpowers
                nochange1:
                    mov currentpowerforCar1, 4
                    jmp endpowers
                nochange2:
                    mov currentpowerforCar2, 4
                endpowers:
                pop di
                ret
activate_powers endp
; --------------------------------------------------;
obstacleDraw proc far

                          ;;; obstacle;;;
                    push bx
                    push cx
                    push dx
                    mov dx, cx
                    mov cx, widthT
                    
                    sub cx, dx
                    mov dx, cx
                    mov cx, ax ;;;; 3shan el color
                    cmp drawObstacle, 0
                    jz skipObstacleD
                    cmp addFill,1         ;; corners msh hytrsm feha
                    jz skipObstacleD
                    mov bx, lengthD
                    cmp bx, widthT
                    jb skipObstacleD


                    ;;; drawing
                    mov ax, obstacleLane
                    mov bx, lengthLane
                    push dx
                    mul bx
                    pop dx
                    cmp dx, ax
                    jbe skipObstacleD
                    add ax, lengthLane
                    cmp dx, ax
                    ja skipObstacleD
                                       
                    ;;;
                    mov al, obstacle_color
                    mov bx, lengthObstacle
                    
                    inc lengthDrawn 
                    sub bx, lengthDrawn
                    jz addWidthObstacleD
                    ;;;

                    
                    jmp noChangeD     ;;; draw obstacle
                    addWidthObstacleD:
                    inc widthDrawn
                    mov lengthDrawn, 0
                    mov ax, widthDrawn
                    cmp ax, lengthObstacle
                    jz obstacleDone
                    jmp skipObstacleD
                    obstacleDone:
                    mov drawObstacle,0
                    mov widthDrawn, 0
                    mov lengthDrawn, 0
                    skipObstacleD:
                    mov ax, cx
                    nochangeD:

                    pop dx
                    pop cx
                    pop bx
                    ret
                    ;;; obstacle;;;
obstacleDraw endp
verticalLineD proc far                              ;;;; ersm vertical line ta7t
      ;pusha        

                  


                    mov   ax, 320
                    mov   bx, y
                    mul   bx
                    add   ax, x
                    mov   di, ax
                    mov   cx, lengthD

      Line:         
    
                    mov   al, 03h
                    stosb
      ;;; filling
                    mov   dx, fill
                    cmp   dx, 0
                    jz    skipFillD
                    mov   si, di
                    mov   dx, cx
                    mov   al, 08h
                    mov   cx, widthT
                    add   cx, addFill
                    dec   cx
      fillDown:     
                    mov   al, 03h
                    scasb
                    jz    onceD

                    mov   al, 08h
                    call obstacleDraw
      onceD:        
                    
                    dec   di
                    stosb
                    loop  fillDown

                    mov   cx, dx
                    mov   di, si
                    mov   al, 03h
      skipFillD:    
      ;;;filling
                    add   di, 319                   ;;;;; 320 - 1 elly hwa katabo
                    loop  Line
                    mov   ax, y
                    add   ax, lengthD
                    mov   y, ax
    
      ;popa
                    ret
verticalLineD endp
 
verticalLineU proc far                              ;;;; ersm vertical line fo2
      ;pusha
                    mov   ax, 320
                    mov   bx, y
                    mul   bx
                    add   ax, x
                    mov   di, ax
                    mov   cx, lengthD
      Line1:        
    
                    mov   al, 03h
                    stosb
      ;;; filling
                    mov   dx, fill
                    cmp   dx, 0
                    jz    skipFillU
                    mov   si, di
                    sub   di, 2
                    mov   dx, cx
                    mov   al, 08h

                    mov   cx, widthT
                    add   cx, addFill
                    dec   cx
      fillU:        
                    mov   al, 03h
                    scasb
                    jz    onceU
                    mov   al, 08h
                    call obstacleDraw
      onceU:        
                    dec   di
                    stosb
                    sub   di, 2
                    loop  fillU
    
                    mov   cx, dx
                    mov   di, si
                    mov   al, 03h
      skipFillU:    
      ;;;filling
                    sub   di, 321                   ;;;;; 320 + 1 elly hwa katabo
                    loop  Line1
                    mov   ax, y
                    sub   ax, lengthD
                    mov   y, ax
    
      ;popa
                    ret
verticalLineU endp


horizLineR proc far                                 ;;;; ersm Horizontal line ymen
      ;pusha
                    mov   ax, 320
                    mov   bx, y
                    mul   bx
                    add   ax, x
                    mov   di, ax
                    mov   cx, lengthD
                    mov   al, 03h
      storeR:       
                    stosb
      ;;; filling
                    mov   dx, fill
                    cmp   dx, 0
                    jz    skipFillR
                    mov   si, di
                    add   di, 319
                    mov   dx, cx
                    mov   al, 08h
                    
                    mov   cx, widthT
                    add   cx, addFill
                    dec   cx
      fillR:        
                    mov   al, 03h
                    scasb
                    jz    onceR
                    mov   al, 08h
                    call obstacleDraw
      onceR:        
                    dec   di
                    stosb
                    add   di, 319
                    loop  fillR
    
                    mov   cx, dx
                    mov   di, si
                    mov   al, 03h
      skipFillR:    
      ;;;filling
                    loop  storeR
                    mov   ax, x
                    add   ax, lengthD
                    mov   x, ax
    
      ;popa
                    ret
horizLineR endp

horizLineL proc far
      ;pusha
                    mov   ax, 320
                    mov   bx, y
                    mul   bx
                    add   ax, x
                    sub   ax, lengthD
                    mov   di, ax
                    mov   cx, lengthD
                    mov   al, 03h
      storeL:       
                    stosb
      ;;; filling
                    mov   dx, fill
                    cmp   dx, 0
                    jz    skipFillL
                    mov   si, di
                    sub   di,321
                    mov   dx, cx
                    mov   al, 08h
                    mov   cx, widthT
                    add   cx, addFill
                    dec   cx
      fillL:        
                    mov   al, 03h
                    scasb
                    jz    onceL
                    mov   al, 08h
                    call obstacleDraw
      onceL:        
                    dec   di
                    stosb
                    sub   di, 321
                    loop  fillL
    
                    mov   cx, dx
                    mov   di, si
                    mov   al, 03h
      skipFillL:    
      ;;;filling
                    loop  storeL
                    mov   ax, x
                    sub   ax, lengthD
                    mov   x, ax
    
      ;popa
                    ret
horizLineL endp

trackUp proc far
      ;;;; tkmlt track;;;;;

                    mov   ax, lastDirection
                    cmp   ax, 0                     ;;; same direction fo2
                    jz    skip1
                    cmp   ax, 1                     ;;; cancel aslan (up then down)
                    jz    exit1
                    cmp   ax, 2                     ;;; right then up
                    jz    RU
                    cmp   ax, 3                     ;;; left then up
                    jz    LU
      LU:           
                    mov   ax, x2
                    mov   bx, y2
                    mov   x, ax
                    mov   y, bx
                    mov   dx, widthT
                    mov   lengthD, dx
                    mov   fill,1
                    mov   addFill, 1
                    call  horizLineL
                    mov   addFill, 0
                    mov   fill,0
                    call  verticalLineU
                    mov   ax, x
                    mov   bx, y
                    mov   x2, ax
                    mov   y2, bx
                    jmp   skip1
      RU:           
                    mov   ax, x2
                    mov   bx, y2
                    mov   x, ax
                    mov   y, bx
                    mov   dx, widthT
                    mov   lengthD, dx
                    call  horizLineR
                    mov   fill,1
                    mov   addFill, 1
                    call  verticalLineU
                    mov   addFill, 0
                    mov   fill,0
                    mov   ax, x
                    mov   bx, y
                    mov   x2, ax
                    mov   y2, bx
                    jmp   skip1
      skip1:        
      ;;; test for line1, line2 ;;; shmal 3ayzeeeno line1
                    mov   ax, x2
                    mov   bx, x1
                    cmp   ax, bx
                    ja    skipSwapUP
                    mov   x1, ax                    ;; xchg
                    mov   x2, bx
      SkipSwapUP:   
      ;;; test for line1, line2

                    mov   cx, lengthT
                    cmp   cx, 0
                    jz    skipLs1
      ;;;; tkmlt track;;;;;

      
                    mov   ax, x1
                    mov   bx, y1
                    mov   x, ax
                    mov   y, bx
                    mov   dx, lengthT
                    mov   lengthD, dx
      
                    call  verticalLineU

                    mov   ax, x
                    mov   bx, y
                    mov   x1, ax
                    mov   y1, bx
                    mov   ax, x2
                    mov   bx, y2
                    mov   x, ax
                    mov   y, bx
                    mov   fill,1
                    call  verticalLineU
                    mov   fill,0
                    mov   ax, x
                    mov   bx, y
                    mov   x2, ax
                    mov   y2, bx
      skipLs1:      
                    mov   ax, 0
                    mov   lastDirection, ax
      
      exit1:        
                    ret
trackUp endp

trackDown proc far
      ;;;; tkmlt track;;;;;
                    mov   ax, lastDirection
                    cmp   ax, 1                     ;;; same direction ta7t
                    jz    skip
                    cmp   ax, 0                     ;;; cancel aslan (up then down)
                    jz    exit
                    cmp   ax, 2                     ;;; right then down
                    jz    RD
                    cmp   ax, 3                     ;;; left then down
                    jz    LD
      LD:           
                    mov   ax, x1
                    mov   bx, y1
                    mov   x, ax
                    mov   y, bx
                    mov   dx, widthT
                    mov   lengthD, dx
                    call  horizLineL
                    mov   fill,1
                    mov   addFill, 1
                    call  verticalLineD
                    mov   addFill, 0
                    mov   fill,0
                    mov   ax, x
                    mov   bx, y
                    mov   x1, ax
                    mov   y1, bx
                    jmp   skip
      RD:           
                    mov   ax, x1
                    mov   bx, y1
                    mov   x, ax
                    mov   y, bx
                    mov   dx, widthT
                    mov   lengthD, dx
                    mov   fill,1
                    mov   addFill, 1
                    call  horizLineR
                    mov   fill,0
                    mov   addFill, 0
                    call  verticalLineD
                    mov   ax, x
                    mov   bx, y
                    mov   x1, ax
                    mov   y1, bx
                    jmp   skip
      
      ;;;; tkmlt track;;;;;
      skip:         
      
      ;;; test for line1, line2 ;;; shmal 3ayzeeeno line1
                    mov   ax, x2
                    mov   bx, x1
                    cmp   ax, bx
                    ja    skipswapDown
                    mov   x1, ax                    ;; xchg
                    mov   x2, bx
      skipswapDown: 
      ;;; test for line1, line2
                    mov   cx, lengthT
                    cmp   cx, 0
                    jz    skipLs

                    jz    exit
                    mov   ax, x1
                    mov   bx, y1
                    mov   x, ax
                    mov   y, bx
                    mov   dx, lengthT
                    mov   lengthD, dx
                    mov   fill,1
                    call  verticalLineD
                    mov   fill,0
                    mov   ax, x
                    mov   bx, y
                    mov   x1, ax
                    mov   y1, bx
                    mov   ax, x2
                    mov   bx, y2
                    mov   x, ax
                    mov   y, bx
                    call  verticalLineD
                    mov   ax, x
                    mov   bx, y
                    mov   x2, ax
                    mov   y2, bx
      skipLs:       
                    mov   ax, 1
                    mov   lastDirection, ax
      
      
      exit:         
                    ret
trackDown endp


trackRight proc far
      ;;;; tkmlt track;;;;;

                    mov   ax, lastDirection
                    cmp   ax, 0                     ;;; UP then right
                    jz    UR
                    cmp   ax, 1                     ;;; down then right
                    jz    DR
                    cmp   ax, 2                     ;;; right then right (skip)
                    jz    skip2
                    cmp   ax, 3                     ;;; left then right  (cancel)
                    jz    exit2
      UR:           
                    mov   ax, x1
                    mov   bx, y1
                    mov   x, ax
                    mov   y, bx
                    mov   dx, widthT
                    mov   lengthD, dx
                    call  verticalLineU
                    mov   fill,1
                    mov   addFill, 1
                    call  horizLineR
                    mov   addFill, 0
                    mov   fill,0
                    mov   ax, x
                    mov   bx, y
                    mov   x1, ax
                    mov   y1, bx
                    jmp   skip2
      DR:           
                    mov   ax, x1
                    mov   bx, y1
                    mov   x, ax
                    mov   y, bx
                    mov   dx, widthT
                    mov   lengthD, dx
                    mov   fill,1
                    mov   addFill, 1
                    call  verticalLineD
                    mov   addFill, 0
                    mov   fill,0
                    call  horizLineR
                    mov   ax, x
                    mov   bx, y
                    mov   x1, ax
                    mov   y1, bx
                    jmp   skip2
      skip2:        
      ;;;; tkmlt track;;;;;
      ;;; test for line1, line2 ;;; fo2 3ayzeeeno line1
                    mov   ax, y2
                    mov   bx, y1
                    cmp   ax, bx
                    ja    skipswapRight
                    mov   y1, ax                    ;; xchg
                    mov   y2, bx
      skipswapRight:
      ;;; test for line1, line2
                    mov   cx, lengthT
                    cmp   cx, 0
                    jz    skipLs2
                    mov   ax, x1
                    mov   bx, y1
                    mov   x, ax
                    mov   y, bx
                    mov   dx, lengthT
                    mov   lengthD, dx
                    mov   fill,1
                    call  horizLineR
                    mov   fill,0
                    mov   ax, x
                    mov   bx, y
                    mov   x1, ax
                    mov   y1, bx
                    mov   ax, x2
                    mov   bx, y2
                    mov   x, ax
                    mov   y, bx
                    call  horizLineR

                    mov   ax, x
                    mov   bx, y
                    mov   x2, ax
                    mov   y2, bx
      skipLs2:      
                    mov   ax, 2
                    mov   lastDirection, ax
      
      
     
      exit2:        
                    ret
trackRight endp


trackLeft proc far
    
    
        
      ;;;; tkmlt track;;;;;

                    mov   ax, lastDirection
                    cmp   ax, 0                     ;;; UP then left
                    jz    UL
                    cmp   ax, 1                     ;;; down then left
                    jz    downLL
                    cmp   ax, 2                     ;;; right then left (cancel)
                    jz    exit3
                    cmp   ax, 3                     ;;; left then left  (skip)
                    jz    skip3
      UL:           
                    mov   ax, x2
                    mov   bx, y2
                    mov   x, ax
                    mov   y, bx
                    mov   dx, widthT
                    mov   lengthD, dx
                    mov   fill, 1
                    mov   addFill, 1
                    call  verticalLineU
                    mov   addFill, 0
                    mov   fill,0
                    call  horizLineL
                    mov   ax, x
                    mov   bx, y
                    mov   x2, ax
                    mov   y2, bx
                    jmp   skip3
      downLL:       
                    mov   ax, x2
                    mov   bx, y2
                    mov   x, ax
                    mov   y, bx
                    mov   dx, widthT
                    mov   lengthD, dx
                    call  verticalLineD
                    mov   fill,1
                    mov   addFill, 1
                    call  horizLineL
                    mov   addFill, 0
                    mov   fill,0
                    mov   ax, x
                    mov   bx, y
                    mov   x2, ax
                    mov   y2, bx
                    jmp   skip3
      skip3:        
      ;;;; tkmlt track;;;;;
      ;;; test for line1, line2 ;;; fo2 3ayzeeeno line1
                    mov   ax, y2
                    mov   bx, y1
                    cmp   ax, bx
                    ja    skipswapLeft
                    mov   y1, ax                    ;; xchg
                    mov   y2, bx
      skipswapLeft: 
      ;;; test for line1, line2
                    mov   cx, lengthT
                    cmp   cx, 0
                    jz    skipLs3
                    mov   ax, x1
                    mov   bx, y1
                    mov   x, ax
                    mov   y, bx
                    mov   dx, lengthT
                    mov   lengthD, dx

                    call  horizLineL

                    mov   ax, x
                    mov   bx, y
                    mov   x1, ax
                    mov   y1, bx
                    mov   ax, x2
                    mov   bx, y2
                    mov   x, ax
                    mov   y, bx
                    mov   dx, lengthT
                    mov   lengthD, dx
                    mov   fill,1
                    call  horizLineL
                    mov   fill,0
                    mov   ax, x
                    mov   bx, y
                    mov   x2, ax
                    mov   y2, bx
      skipLs3:      
                    mov   ax, 3
                    mov   lastDirection, ax
      
      
     
      exit3:        
                    ret
trackLeft endp


checkUP proc far
      ;;;; mmkn nhtag n shift el x 3la hasab howa gy mn ymen wla shmal fl second test

                    mov   ax, y1
                    cmp   ax, 0
                    jz    dontU
      ;;;;; first test
                    mov   ax, lengthT
                    mov   temporaryLength, ax

                    mov   ax, y1
                    mov   bx, lengthT
                    add   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx
                    jae   skip1U
                    mov   ax, y1
                    mov   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx
                    jb    lowU
                    sub   ax, bx
                    mov   temporaryLength, ax
      skip1U:                                       ;;;; check for lines in memory, ax = temporary length
                    mov   cx, temporaryLength
                    add   cx, widthT
                    add   cx, widthT
                    mov   ax, 320
                    mov   bx, y1
                    sub   bx, 1                     ;;; 3shan abos 3l above pixel
                    mul   bx
                    add   ax, x1
                    mov   di, ax
                    mov   ah, 0                     ;
                    mov   al, 03h                   ;;;;; color
      scan1U:                                       ;;; hnscan shwya
                    scasb
                    jz    exit1U
                    sub   di, 321                   ;;; elly et7arakha w hnwdeha fo2
                    loop  scan1U
      exit1U:                                       ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
                    mov   dx, cx                    ;;; allowed fl dx
                    mov   cx, temporaryLength
                    mov   bx, widthT
                    add   bx, widthT
                    add   cx, bx
                    sub   cx, dx
                    cmp   cx, bx
                    jb    dontU
                    sub   cx, bx                    ;;; allowed
                    mov   temporaryLength, cx       ;;;; allowed mn first check 3ayzeen 3l tany mn gher mnghyr
    
      ;;;;; first test
    
    
      ;;;; second test
                    mov   ax, lengthT
                    mov   temporaryLength2, ax

                    mov   ax, y1
                    mov   bx, lengthT
                    add   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx
                    jae   skip2U
                    mov   ax, y1
                    mov   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx
                    jb    lowU
                    sub   ax, bx
                    mov   temporaryLength2, ax
      skip2U:                                       ;;;; check for lines in memory, ax = temporary length
                    mov   cx, temporaryLength2
                    add   cx, widthT
                    add   cx, widthT
                    mov   ax, 320
                    mov   bx, y1
                    sub   bx, 1
                    mul   bx
                    add   ax, x2
      ;;;; mmkn nhtag n shift el X 3la hasab howa gy mn ymen wla shmal

                    mov   dx, lastDirection
                    cmp   dx, 0                     ;;; cancel
                    jz    leftU                     ;;;;;; cancel
                    cmp   dx, 2
                    jz    rightU
                    mov   dx, x1                    ;;;;;; added to not exit bounds
                    cmp   dx, widthT                ;;;;;; added to not exit bounds
                    jb    dontD                     ;;;;;; added to not exit bounds
                    sub   ax, widthT
                    jmp   leftU
      rightU:       
                    add   ax, widthT
                    mov   dx, x2                    ;;;;;; added to not exit bounds
                    add   dx, widthT                ;;;;;; added to not exit bounds
                    cmp   dx, 319                   ;;;;;; added to not exit bounds
                    ja    dontD                     ;;;;;; added to not exit bounds
      leftU:        
      ;;;;
                    mov   di, ax
                    mov   ah, 0                     ;
                    mov   al, 03h                   ;;;;; color
      scan2U:                                       ;;; hnscan shwya
                    scasb
                    jz    exit2U
                    sub   di, 321                   ;;; elly et7arakha w hnwdeha fo2
                    loop  scan2U
      exit2U:                                       ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
                    mov   dx, cx                    ;;; allowed fl dx
                    mov   cx, temporaryLength2
                    mov   bx, widthT
                    add   bx, widthT
                    add   cx, bx
                    sub   cx, dx
                    cmp   cx, bx
                    jb    dontU
                    sub   cx, bx                    ;;; allowed
                    mov   temporaryLength2, cx      ;;;; allowed mn second check 3l tany
                    jmp   exitAllU
      ;;;; second test
    
    
    
      dontU:        
                    mov   temporaryLength2, 0
                    mov   temporaryLength, 0
                    mov   dontDraw, 1
                    ret
    
      lowU:         
                    mov   temporaryLength2, 0
                    mov   temporaryLength, 0
                          ;;;; mmkn nhtag n shift el X 3la hasab howa gy mn ymen wla shmal

                    mov   dx, lastDirection
                    cmp   dx, 0                     ;;; cancel
                    jz    leftU2                     ;;;;;; cancel
                    cmp   dx, 2
                    jz    rightU2
                    mov   dx, x1                    ;;;;;; added to not exit bounds
                    cmp   dx, widthT                ;;;;;; added to not exit bounds
                    jb    dontD                     ;;;;;; added to not exit bounds
                    sub   ax, widthT
                    jmp   leftU2
      rightU2:       
                    add   ax, widthT
                    mov   dx, x2                    ;;;;;; added to not exit bounds
                    add   dx, widthT                ;;;;;; added to not exit bounds
                    cmp   dx, 319                   ;;;;;; added to not exit bounds
                    ja    dontD                     ;;;;;; added to not exit bounds
      leftU2:        
      ;;;;
      exitAllU:     
                    ret
checkUp endp
 
 

checkDown proc far                                  ;;;; still to be tested  dymn check bl Y2 3shan lower w ghyr X
    
      ;;;; mmkn nhtag n shift el x 3la hasab howa gy mn ymen wla shmal fl second test
                    mov   ax, y2
                    cmp   ax, row
                    jz    dontD
      ;;;;; first test
                    mov   ax, lengthT
                    mov   temporaryLength, ax

                    mov   ax, row

                    mov   bx, y2
                    add   bx, lengthT
                    add   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx
                    jae   skip1D
                    mov   ax, row
                    sub   ax, widthT
                    sub   ax, widthT
                    mov   bx, ax
                    mov   ax, y2
                    cmp   bx, ax
                    jb    low1D
    
                    sub   bx, ax
                    mov   ax, bx
                    mov   temporaryLength, ax
      skip1D:                                       ;;;; check for lines in memory, ax = temporary length
                    mov   cx, temporaryLength
                    add   cx, widthT
                    add   cx, widthT
                    mov   ax, 320
                    mov   bx, y2
                    add   bx, 1                     ;; nnzl taht pixel
                    mul   bx
                    add   ax, x1
                    mov   di, ax
                    mov   ah, 0                     ;
                    mov   al, 03h                   ;;;;; color
      scan1D:                                       ;;; hnscan shwya
                    scasb
                    jz    exit1D
                    add   di, 319                   ;;; elly et7arakha w hnwdeha fo2
                    loop  scan1D
      exit1D:                                       ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
                    mov   dx, cx                    ;;; allowed fl dx
                    mov   cx, temporaryLength
                    mov   bx, widthT
                    add   bx, widthT
                    add   cx, bx
                    sub   cx, dx
                    cmp   cx, bx
                    jb    dontD
                    sub   cx, bx                    ;;; allowed
                    mov   temporaryLength, cx       ;;;; allowed mn first check 3ayzeen 3l tany mn gher mnghyr
    
      ;;;;; first test
    
    
      ;;;; second test
                    mov   ax, lengthT
                    mov   temporaryLength2, ax

                    mov   ax, row
                    mov   bx, y2
                    add   bx, lengthT
                    add   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx

                    jae   skip2D
                    mov   ax, row
                    sub   ax, widthT
                    sub   ax, widthT
                    mov   bx, ax
                    mov   ax, y2
                    cmp   bx, ax
                    jb    low1D
                    sub   bx, ax
                    mov   ax, bx
                    mov   temporaryLength2, ax
      skip2D:                                       ;;;; check for lines in memory, ax = temporary length
                    mov   cx, temporaryLength2
                    add   cx, widthT
                    add   cx, widthT
                    mov   ax, 320
                    mov   bx, y2
                    add   bx, 1                     ;;;; check pixel taht
                    mul   bx
    
    
                    add   ax, x2
    
      ;;;; mmkn nhtag n shift el X 3la hasab howa gy mn ymen wla shmal

                    mov   dx, lastDirection
                    cmp   dx, 1                     ;;; cancel
                    jz    leftD                     ;;;;;; cancel
                    cmp   dx, 2
                    jz    rightD
                    mov   dx, x1                    ;;;;;; added to not exit bounds

                    cmp   dx, widthT                ;;;;;; added to not exit bounds
                    jb    dontD                     ;;;;;; added to not exit bounds
                    sub   ax, widthT
                    jmp   leftD
      rightD:       
                    add   ax, widthT
                    mov   dx, x2                    ;;;;;; added to not exit bounds
                    add   dx, widthT                ;;;;;; added to not exit bounds
                    cmp   dx, 319                   ;;;;;; added to not exit bounds
                    ja    dontD                     ;;;;;; added to not exit bounds
    
      leftD:        
      ;;;;
                    mov   di, ax
                    mov   ah, 0                     ;
                    mov   al, 03h                   ;;;;; color
      scan2D:                                       ;;; hnscan shwya
                    scasb
                    jz    exit2D
                    add   di, 319                   ;;; elly et7arakha w hnwdeha taht
                    loop  scan2D
      exit2D:                                       ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
                    mov   dx, cx                    ;;; allowed fl dx
                    mov   cx, temporaryLength2
                    mov   bx, widthT
                    add   bx, widthT
                    add   cx, bx
                    sub   cx, dx
                    cmp   cx, bx
                    jb    dontD
                    sub   cx, bx                    ;;; allowed
                    mov   temporaryLength2, cx      ;;;; allowed mn second check 3l tany
                    jmp   exitAllD
      ;;;; second test
    
    
    
      dontD:        
                    mov   temporaryLength2, 0
                    mov   temporaryLength, 0
                    mov   dontDraw, 1
                    ret
      low1D:        
                    mov   temporaryLength2, 0
                    mov   temporaryLength, 0
                       add   ax, x2
    
      ;;;; mmkn nhtag n shift el X 3la hasab howa gy mn ymen wla shmal

                    mov   dx, lastDirection
                    cmp   dx, 1                     ;;; cancel
                    jz    leftD2                    ;;;;;; cancel
                    cmp   dx, 2
                    jz    rightD2
                    mov   dx, x1                    ;;;;;; added to not exit bounds

                    cmp   dx, widthT                ;;;;;; added to not exit bounds
                    jb    dontD                     ;;;;;; added to not exit bounds
                    sub   ax, widthT
                    jmp   leftD2
      rightD2:       
                    add   ax, widthT
                    mov   dx, x2                    ;;;;;; added to not exit bounds
                    add   dx, widthT                ;;;;;; added to not exit bounds
                    cmp   dx, 319                   ;;;;;; added to not exit bounds
                    ja    dontD                     ;;;;;; added to not exit bounds
    
      leftD2:        
      ;;;;
      exitAllD:     
                    ret
checkDown endp



checkRight proc far                                 ;;;y1 = y2, x2 3l ymen = use it
    
                    mov   ax, x2
                    cmp   ax, 319
                    jz    dontR
      ;;;;; first test
                    mov   ax, lengthT
                    mov   temporaryLength, ax

                    mov   ax, 319
                    mov   bx, x2
                    add   bx, lengthT
                    add   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx
                    jae   skip1R
                    mov   ax, 319                   ;;;;; test
                    sub   ax, widthT
                    sub   ax, widthT
                    mov   bx, ax
                    mov   ax, x2
                    cmp   bx, ax
                    jb    lowR
                    sub   bx, ax
                    mov   ax, bx
                    mov   temporaryLength, ax
      skip1R:                                       ;;;; check for lines in memory, ax = temporary length
                    mov   cx, temporaryLength
                    add   cx, widthT
                    add   cx, widthT
                    mov   ax, 320
                    mov   bx, y1
            
                    mul   bx
                    add   ax, x2
                    add   ax,1                      ;;; 3shan abos 3l right pixel
                    mov   di, ax
                    mov   ah, 0                     ;
                    mov   al, 03h                   ;;;;; color
      scan1R:                                       ;;; hnscan shwya
                    scasb
                    jz    exit1R
                    loop  scan1R
      exit1R:                                       ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
                    mov   dx, cx                    ;;; allowed fl dx
                    mov   cx, temporaryLength
                    mov   bx, widthT
                    add   bx, widthT
                    add   cx, bx
                    sub   cx, dx
                    cmp   cx, bx
                    jb    dontR
                    sub   cx, bx                    ;;; allowed
                    mov   temporaryLength, cx       ;;;; allowed mn first check 3ayzeen 3l tany mn gher mnghyr
    
      ;;;;; first test
    
    
      ;;;; second test
                    mov   ax, lengthT
                    mov   temporaryLength2, ax

                    mov   ax, 319
                    mov   bx, x2
                    add   bx, lengthT
                    add   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx
                    jae   skip2R
                    mov   ax, 319
                    sub   ax, widthT
                    sub   ax, widthT
                    mov   bx, ax
                    mov   ax, x2
                    cmp   bx, ax
                    jb    lowR
                    sub   bx, ax
                    mov   ax, bx
                    mov   temporaryLength2, ax
      skip2R:                                       ;;;; check for lines in memory, ax = temporary length
                    mov   cx, temporaryLength2
                    add   cx, widthT
                    add   cx, widthT
                    mov   ax, 320
                    mov   bx, y2                    ;;;; changed to y2
    
      ;;;; mmkn nhtag n shift el height 3la hasab howa gy mn taht wla fo2

                    mov   dx, lastDirection
                    cmp   dx, 2                     ;;; cancel
                    jz    upR                       ;;;;;; cancel
                    cmp   dx, 1
                    jz    downR
                    sub   bx, widthT
                    mov   dx, y1                    ;;;;;; added to not exit bounds
                    cmp   dx, widthT                ;;;;;; added to not exit bounds
                    jb    dontR                     ;;;;;; added to not exit bounds
                    jmp   upR
      downR:        
                    add   bx, widthT
                    mov   dx, y2                    ;;;;;; added to not exit bounds
                    add   dx, widthT                ;;;;;; added to not exit bounds
                    cmp   dx, row                   ;;;;;; added to not exit bounds
                    jae   dontR                     ;;;;;; added to not exit bounds
      upR:          
      ;;;;
                    mul   bx
                    add   ax, x2
                    add   ax,1                      ;;; 3shan abos 3l right pixel
                    mov   di, ax
                    mov   ah, 0                     ;
                    mov   al, 03h                   ;;;;; color
      scan2R:                                       ;;; hnscan shwya
                    scasb
                    jz    exit2R
                    loop  scan2R
      exit2R:                                       ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
                    mov   dx, cx                    ;;; allowed fl dx
                    mov   cx, temporaryLength2
                    mov   bx, widthT
                    add   bx, widthT
                    add   cx, bx
                    sub   cx, dx
                    cmp   cx, bx
                    jb    dontR
                    sub   cx, bx                    ;;; allowed
                    mov   temporaryLength2, cx      ;;;; allowed mn second check 3ayzeen 3l tany mn gher mnghyr
                    jmp   exitAllR
      ;;;; second test
    
    
    
      dontR:        
                    mov   temporaryLength2, 0
                    mov   temporaryLength, 0
                    mov   dontDraw, 1
                    ret
    
      lowR:         
                    mov   temporaryLength2, 0
                    mov   temporaryLength, 0
                     mov   bx, y2                    ;;;; changed to y2
    
      ;;;; mmkn nhtag n shift el height 3la hasab howa gy mn taht wla fo2

                    mov   dx, lastDirection
                    cmp   dx, 2                     ;;; cancel
                    jz    upR2                      ;;;;;; cancel
                    cmp   dx, 1
                    jz    downR2
                    sub   bx, widthT
                    mov   dx, y1                    ;;;;;; added to not exit bounds
                    cmp   dx, widthT                ;;;;;; added to not exit bounds
                    jb    dontR                     ;;;;;; added to not exit bounds
                    jmp   upR2
      downR2:        
                    add   bx, widthT
                    mov   dx, y2                    ;;;;;; added to not exit bounds
                    add   dx, widthT                ;;;;;; added to not exit bounds
                    cmp   dx, row                   ;;;;;; added to not exit bounds
                    jae   dontR                     ;;;;;; added to not exit bounds
      upR2:          
      ;;;;
                    
      exitAllR:     
                    ret
checkRight endp


checkLeft proc far                                  ;;;y1 = y2, x1 3l shmal = use it
    
                    mov   ax, x1
                    cmp   ax, 0
                    jz    dontL
      ;;;;; first test
                    mov   ax, lengthT
                    mov   temporaryLength, ax

                    mov   ax, x1
                    mov   bx, lengthT
                    add   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx
                    jae   skip1L
                    mov   ax, x1
                    mov   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx
                    jb    lowL
                    sub   ax, bx
                    mov   temporaryLength, ax
      skip1L:                                       ;;;; check for lines in memory, ax = temporary length
                    mov   cx, temporaryLength
                    add   cx, widthT
                    add   cx, widthT
                    mov   ax, 320
                    mov   bx, y1
            
                    mul   bx
                    add   ax, x1
                    sub   ax,1                      ;;; 3shan abos 3l left pixel
                    mov   di, ax
                    mov   ah, 0                     ;
                    mov   al, 03h                   ;;;;; color
      scan1L:                                       ;;; hnscan shwya
                    scasb
                    jz    exit1L
                    sub   di, 2                     ;;;; 3shan amshy shmal
                    loop  scan1L
      exit1L:                                       ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
                    mov   dx, cx                    ;;; allowed fl dx
                    mov   cx, temporaryLength
                    mov   bx, widthT
                    add   bx, widthT
                    add   cx, bx
                    sub   cx, dx
                    cmp   cx, bx
                    jb    dontL
                    sub   cx, bx                    ;;; allowed
                    mov   temporaryLength, cx       ;;;; allowed mn first check 3ayzeen 3l tany mn gher mnghyr
    
      ;;;;; first test
    
    
      ;;;; second test
                    mov   ax, lengthT
                    mov   temporaryLength2, ax

                    mov   ax, x1
                    mov   bx, lengthT
                    add   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx
                    jae   skip2L
                    mov   ax, x1
                    mov   bx, widthT
                    add   bx, widthT
                    cmp   ax, bx
                    jb    lowL
                    sub   ax, bx
                    mov   temporaryLength2, ax
      skip2L:                                       ;;;; check for lines in memory, ax = temporary length
                    mov   cx, temporaryLength2
                    add   cx, widthT
                    add   cx, widthT
                    mov   ax, 320
                    mov   bx, y2                    ;;;  change to y2 test
      ;;;; mmkn nhtag n shift el height 3la hasab howa gy mn taht wla fo2

                    mov   dx, lastDirection
                    cmp   dx, 3                     ;;; cancel
                    jz    upL                       ;;;;;; cancel
                    cmp   dx, 1
                    jz    downL
                    sub   bx, widthT
                    mov   dx, y1                    ;;;;;; added to not exit bounds
                    cmp   dx, widthT                ;;;;;; added to not exit bounds
                    jb    dontL                     ;;;;;; added to not exit bounds
                    jmp   upL
      downL:        
                    add   bx, widthT
                    mov   dx, y2                    ;;;;;; added to not exit bounds
                    add   dx, widthT                ;;;;;; added to not exit bounds
                    cmp   dx, row                   ;;;;;; added to not exit bounds
                    jae   dontL                     ;;;;;; added to not exit bounds
      upL:          
      ;;;;
                    mul   bx
                    add   ax, x1
                    sub   ax,1                      ;;; 3shan abos 3l left pixel
                    mov   di, ax
                    mov   ah, 0                     ;
                    mov   al, 03h                   ;;;;; color
      scan2L:                                       ;;; hnscan shwya
                    scasb
                    jz    exit2L
                    sub   di, 2                     ;;;; 3shan amshy shmal
                    loop  scan2L
      exit2L:                                       ;;; hndraw el allowed - 2* width lw mfesh 2*width yb2a don't draw asln
                    mov   dx, cx                    ;;; allowed fl dx
                    mov   cx, temporaryLength2
                    mov   bx, widthT
                    add   bx, widthT
                    add   cx, bx
                    sub   cx, dx
                    cmp   cx, bx
                    jb    dontL
                    sub   cx, bx                    ;;; allowed
                    mov   temporaryLength2, cx      ;;;; allowed mn first check 3ayzeen 3l tany mn gher mnghyr
                    jmp   exitAllL
      ;;;; second test
    
    
    
      dontL:        
                    mov   temporaryLength2, 0
                    mov   temporaryLength, 0
                    mov   dontDraw, 1
                    ret
    
      lowL:         
                    mov   temporaryLength2, 0
                    mov   temporaryLength, 0
                       mov   bx, y2                    ;;;  change to y2 test
      ;;;; mmkn nhtag n shift el height 3la hasab howa gy mn taht wla fo2

                    mov   dx, lastDirection
                    cmp   dx, 3                     ;;; cancel
                    jz    upL2                       ;;;;;; cancel
                    cmp   dx, 1
                    jz    downL2
                    sub   bx, widthT
                    mov   dx, y1                    ;;;;;; added to not exit bounds
                    cmp   dx, widthT                ;;;;;; added to not exit bounds
                    jb    dontL                     ;;;;;; added to not exit bounds
                    jmp   upL2
      downL2:        
                    add   bx, widthT
                    mov   dx, y2                    ;;;;;; added to not exit bounds
                    add   dx, widthT                ;;;;;; added to not exit bounds
                    cmp   dx, row                   ;;;;;; added to not exit bounds
                    jae   dontL                     ;;;;;; added to not exit bounds
      upL2:          
      ;;;;
                    
                    
      exitAllL:     
                    ret
    
    
checkLeft endp
 
 
 

drawUp proc far                                     ;;; after checking

                    call  checkUP
                    cmp   dontDraw, 1
                    jz    exitU
                    mov   ax, temporaryLength
                    cmp   ax, temporaryLength2
                    jbe   skipSwapU
                    mov   ax, temporaryLength2
                    mov   temporaryLength, ax
  
      skipSwapU:    
                    mov   lengthT, ax
                    call  trackUp
                    mov   ax, lengthD
                    mov   lengthT, ax
     
      exitU:        
                    mov   dontDraw, 0
                    ret
drawUp endP

drawRight proc far                                  ;;; after checking

                    call  checkRight
                    cmp   dontDraw, 1
                    jz    exit
                    mov   ax, temporaryLength
                    cmp   ax, temporaryLength2
                    jbe   skipSwapR
                    mov   ax, temporaryLength2
                    mov   temporaryLength, ax

      skipSwapR:    
                    mov   lengthT, ax
                    call  trackRight
                    mov   ax, lengthD
                    mov   lengthT, ax
     
      exitR:        
                    mov   dontDraw, 0
                    ret
drawRight endp

drawLeft proc far                                   ;;; after checking

                    call  checkLeft
                    cmp   dontDraw, 1
                    jz    exitL
                    mov   ax, temporaryLength
                    cmp   ax, temporaryLength2
                    jbe   skipSwapL
                    mov   ax, temporaryLength2
                    mov   temporaryLength, ax

      skipSwapL:    
                    mov   lengthT, ax
                    call  trackLeft
                    mov   ax, lengthD
                    mov   lengthT, ax
     
      exitL:        
                    mov   dontDraw, 0
                    ret
drawLeft endp


drawDOWN proc far

                    call  checkDown
                    cmp   dontDraw, 1
                    jz    exitD
                    mov   ax, temporaryLength
                    cmp   ax, temporaryLength2
                    jbe   skipSwapD
                    mov   ax, temporaryLength2
                    mov   temporaryLength, ax
      skipSwapD:    
                    mov   lengthT, ax
                    call  trackDown
                    mov   ax, lengthD
                    mov   lengthT, ax
     
      exitD:        
                    mov   dontDraw, 0
                    ret
drawDOWN endp


drawTrack proc far
   
        

                    call  drawStartLine

                    mov   ax, widthT
                    mov   x2, ax

                    call  drawDown

                    mov   cx, 00ffh                 ;;; 3dd el randoms
      ;;; random
      rand:         
        
                    push  cx
                    mov   ah, 2ch
                    int   21h

      ;; test2
                    mov   ch,0
                    mov   cl, dh
                    add cl, 10
                    shl   cl, 2
      loop22:       
                    push  cx
                    mov   ah, 2ch
                    int   21h
                    pop   cx
                    loop  loop22
      ;; test2
                    mov   ah, 0
                    mov   al, dl                    ;;micro seconds?
                    mov   bl, 4
        
                    div   bl
      ;;; ah = rest 
                    
                    jz next

                    call RandObst

                    cmp   ah, 0
                    jz    U
                    cmp   ah, 3
                    jz    D
                    cmp   ah,1
                    jz    R
                    cmp   ah,2
                    jz    L
      U:            
                    call  drawUP
                    jmp   next
      D:            
                    call  drawDOWN
                    jmp   next
      R:            
                    mov   ax, lengthT
                    push  ax
                    add   ax, lengthT
                    mov   lengthT, ax
                    call  drawRight
                    pop   ax
                    mov   lengthT, ax
                    jmp   next
        
      L:            
                    mov   ax, lengthT
                    push  ax
                    add   ax, lengthT
                    mov   lengthT, ax
                    call  drawLeft
                    pop   ax
                    mov   lengthT, ax
                    jmp   next
        
      next:         
                    pop   cx
                    loop  rand
                    call  drawEndLine
      ;;;;; inline chat row
                    mov   ax, 320
                    mov   bx, word ptr row
                    inc   bx
                    mul   bx
                    mov   di, ax
                    mov   al, 0eh
                    mov   cx, 320
                    rep   stosb
        
      ;;;;;inline chat row

                    ret
drawtrack endp

drawEndLine proc far
                    mov   ax, x1
                    mov   bx, x2
                    cmp   ax, bx
                    jz    vertical
                    mov   ax, 320
                    mov   bx, y1
                    mul   bx
                    add   ax, x1
                    mov   di, ax
                    mov   cx, x2
                    sub   cx, x1

                    mov   al, 04h
                    rep   stosb

                    jmp   endLine
      vertical:     
                    mov   cx, y2
                    sub   cx, y1
                    mov   ax, 320
                    mov   bx, y1
                    mul   bx
                    add   ax, x1
                    mov   di, ax
      color:        
                    mov   al, 04h
                    stosb
                    add   di, 319
                    loop  color
    
    
    
      endLine:      
                    ret
drawEndLine endp


drawStartLine proc far
      ;;start line
                    mov   ax, widthT
                    mov   lengthD, ax
                    call  horizLineR
                    mov   ax, lengthT
                    mov   lengthD, ax
    
                    mov   x, 0
      ;;start line
                    ret
drawStartLine endp

RandObst proc far

                    mov bx, ax            
                    mov al, ah            ;; random 0 to 3 fl al wl ah
                    
                    and ah, 1
                    
                    jz noObst

                    mov drawObstacle,1

                    mov ah,0
                    mov cl,3
                    div cl
                  ;; result in al, ah = rem
                    mov al, ah
                    mov ah,0
                    mov obstacleLane, ax
                    
                    noObst:
                    mov ax, bx
                    ret
RandObst endp

;;;;;;;;;;;;;;;;;;;;;; Daowd 2 new procs
starttime proc
   mov ah, 2ch
   int 21h
   mov prevsec, dh
   ret
starttime endp
; set current second ;
setcurrentsec proc
                push dx
                taketimess:
                    mov ah, 2ch
                    int 21h
                    mov cursec, dh
                pop dx
                ret
setcurrentsec endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;initilize time
markend proc 
push ax
push bx
push dx
push di
    mov bh,prevsec    
    cmp cursec, bh 
    je nochange
    inc timer      ; Check if 10 seconds have passed
    inc poweruptimer
    ; First power up timer ;
    cmp powerc1activated,1 ; if a power is currently activated
    jnz completerest ; not activated
    inc time_powerc1 ; else increment time in use
    cmp time_powerc1, 5 ; if reached zero
    jnz completerest ; else complete
    mov di,pos_box1 ; car 1
    call releasepowerups ; function that release power ups activated
    completerest:
    ; second power up timer ;
    cmp powerc2activated,1 ; if a power is currently activated
    jnz completerest2 ; not activated
    inc time_powerc2 ; else increment time in use
    cmp time_powerc2, 5 ; if reached zero
    jnz completerest2 ; else complete
    mov di,pos_box2  ; car 2 
    call releasepowerups ; function that release power ups activated
    completerest2:
    cmp poweruptimer,10
    jnz rest
    mov powerupflag,1
    mov  poweruptimer,0  
    rest:
    cmp timer, 120
    jnz updateparams
    mov flag,1
    updateparams:
    mov bl,cursec
    mov prevsec,bl
   nochange:
        pop di 
        pop DX
        pop bx
        pop ax
    ret
markend endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;time is overrrrrrrrrr
timeover proc     
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
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;; secondplayer
    MOV AH,02  
    MOV BH,00  ;page    
    MOV DL,30 ;column  
    MOV DH,8  ;row 
    INT 10H 
    mov ah,9
    mov dx,offset secondPlayerName+2
    int 21h
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;score1    
    ;;;;;;;;;;;;;;;;;;;;;;;;;monkey photo
   
    lea si,gameoverpic
    mov di,25728
     MOV DX,73

    REPEAT4:
    MOV CX,80
REP MOVSB
ADD DI,SCREEN_WIDTH-80
DEC DX
JNZ REPEAT4
;;;;;;;;;;;;;;;;;;; bluecar over
lea si,blueover
 mov di,25632
     MOV DX,30

    REPEAT5:
    MOV CX,50
REP MOVSB
ADD DI,SCREEN_WIDTH-50
DEC DX
JNZ REPEAT5
;;;;;;;;;;;;;;;;; redcarin over
lea si,redover
 mov di,25828
     MOV DX,30

    REPEAT6:
    MOV CX,55
REP MOVSB
ADD DI,SCREEN_WIDTH-55
DEC DX
JNZ REPEAT6
;;;;;;;;;;;;;;;;;;;;;;;;;;;;; return to main
mov timer,0
 mov ah, 2ch
    int 21h
    mov prevsec, dh

taketime2:
mov bl,cursec
mov prevsec,bl
    mov ah, 2ch
    int 21h
    mov cursec, dh
    mov bh,prevsec
    ;sub cursec, bl ; Calculate the difference in seconds
    cmp cursec, bh 
    je taketime2
    inc timer2      ; Check if 10 seconds have passed
    cmp timer2,5

    jge returnz      ; If 10 seconds have passed, display the message
    jmp taketime2
    returnz:
     mov ah,00h 
mov al,03h 
int 10h
jmp lopp

ret
timeover endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;winerrrrrrrrrrrrrrrrrrr
getwinner proc 
    mov ah, 2ch
    int 21h
    mov prevsec, dh
taketimeE:
mov bl,cursec
mov prevsec,bl
    mov ah, 2ch
    int 21h
    mov cursec, dh
    mov bh,prevsec
    ;sub cursec, bl ; Calculate the difference in seconds
    cmp cursec, bh 
    je taketimeE
    inc timer      ; Check if 10 seconds have passed
    cmp timer,10

    jge endofgame2        ; If 10 seconds have passed, display the message
    jmp taketimeE
endofgame2:
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

        mov dx,offset winningmsg
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
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;; secondplayer
    MOV AH,02  
    MOV BH,00  ;page    
    MOV DL,30 ;column  
    MOV DH,8  ;row 
    INT 10H 
    mov ah,9
    mov dx,offset secondPlayerName+2
    int 21h
    
    ;;;;;;;;;;;;;;;;;;;;;;;;winner
    mov winer,2
    MOV AH,02  
    MOV BH,00  ;page    
    MOV DL,17;column  
    MOV DH,18  ;row 
    INT 10H 
    cmp winer,1
    je one

    mov dx,offset secondPlayerName+2
    jmp enr
    one:
    mov dx,offset firstPlayerName+2
    enr:
    mov ah,9
    int 21h;
     ;;;;;;;;;;;;;;;;;;;;;;;;;monkey photo
   
    lea si,celebratemonkey
    mov di,25728
     MOV DX,60
    REPEATT4:
    MOV CX,45
REP MOVSB
ADD DI,SCREEN_WIDTH-45
DEC DX
JNZ REPEATT4
;;;;;;;;;;;;;;;;;;; bluecar over
lea si,blueover
 mov di,25632
     MOV DX,30

    REPEATT5:
    MOV CX,50
REP MOVSB
ADD DI,SCREEN_WIDTH-50
DEC DX
JNZ REPEATT5
;;;;;;;;;;;;;;;;; redcarin over
lea si,redover
 mov di,25828
     MOV DX,30

    REPEATT6:
    MOV CX,55
REP MOVSB
ADD DI,SCREEN_WIDTH-55
DEC DX
JNZ REPEATT6
ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;; return to main
mov timer,0
 mov ah, 2ch
    int 21h
    mov prevsec, dh

taketimeE2:
mov bl,cursec
mov prevsec,bl
    mov ah, 2ch
    int 21h
    mov cursec, dh
    mov bh,prevsec
    ;sub cursec, bl ; Calculate the difference in seconds
    cmp cursec, bh 
    je taketimeE2
    inc timer      ; Check if 10 seconds have passed
    cmp timer,5

    jge returnn     ; If 10 seconds have passed, display the message
    jmp taketimeE2
    returnn:
    mov ah,00h 
mov al,03h 
int 10h
jmp lopp

ret
getwinner endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;powerups section
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;first in statusbar
drawIncresespeed proc
lea si,increseimg ;left di for power ups 46120-----------right 46328
;mov di,46120
MOV DX,20

    REPEATincrese2:
    MOV CX,20
REP MOVSB
ADD DI,300
DEC DX
JNZ REPEATincrese2

ret
drawIncresespeed endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
drawcreateob proc
lea si,createob ;left di for power ups 46120-----------right 46328
;mov di,48888
MOV DX,20

    REPEATob2:
    MOV CX,20
REP MOVSB
ADD DI,300
DEC DX
JNZ REPEATob2

ret
drawcreateob endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
drawflyobstacle proc
lea si,flyob ;left di for power ups 46120-----------right 46328 update ll 48680  rr 48888
;mov di,48888
MOV DX,20

    REPEATfly2:
    MOV CX,20
REP MOVSB
ADD DI,300
DEC DX
JNZ REPEATfly2
ret
drawflyobstacle endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
drawdecresesofanother proc
lea si,decreseimg; left di for power ups 46120-----------right 46328
;mov di,46328
MOV DX,20

    REPEATincrese:
    MOV CX,20
REP MOVSB
ADD DI,300
DEC DX
JNZ REPEATincrese

ret
drawdecresesofanother endp 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; clearscreen of obstacle
Noobstacleleft proc
;mov aX, 0600h ;bacground
 ;     mov bh, 09h
  ;    mov cx, 1305h
   ;   mov dx, 1407h       
    ;  int 10h 
    ;mov di,48,680
    mov si,offset clearfromstatus
    MOV DX,20

    clearstatus:
    MOV CX,20
REP MOVSB
ADD DI,300
DEC DX
JNZ clearstatus
      ret
Noobstacleleft endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;for status
changeTimer proc
mov ah, 2ch
    int 21h
    mov prevsec, dh

taketimeE3:
mov bl,cursec
mov prevsec,bl
    mov ah, 2ch
    int 21h
    mov cursec, dh
    mov bh,prevsec
    ;sub cursec, bl ; Calculate the difference in seconds
    cmp cursec, bh 
    je taketimeE3
    mov al,secondsss
    ;call printseconds
    dec secondsss
    inc timer      ; Check if 10 seconds have passed
    cmp timer,60

    jge endofgame23        ; If 10 seconds have passed, display the message
    jmp taketimeE3
endofgame23:
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

        mov dx,offset winningmsg
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
ret
changeTimer endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;obstacles in track
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;fly for 222222
drawflyinten proc
;mov di,4824
mov si,offset flyinten
MOV DX,10
flyu:
MOV CX,10
REP MOVSB
ADD DI,310
DEC DX
JNZ flyu
ret
drawflyinten endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; bomb for 4444444444
drawbomb proc
;mov di,8644
mov si,offset bomb
MOV DX,10
bomb8:
MOV CX,10
REP MOVSB
ADD DI,310
DEC DX
JNZ bomb8
ret
drawbomb endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; fire for 11111111111111111
drawfire proc
;mov di,8664
mov si,offset fire
MOV DX,10
fire8:
MOV CX,10
REP MOVSB
ADD DI,310
DEC DX
JNZ fire8
ret
drawfire endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; decrese enemy for 333333333333333333
drawbeatme proc
;mov di,12484
mov si,offset beatme
MOV DX,10
beatme8:
MOV CX,10
REP MOVSB
ADD DI,310
DEC DX
JNZ beatme8
ret
drawbeatme endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; randoization of power
randompower proc
;call ret_interrupt
 mov ah, 2ch
 int 21h    
tracktime:    
    mov randomNum,dl;    
    mov ah,0
    mov al,randomNum
    mov bl,4;
    div bl;sub cursec, bl ; Calculate the difference in seconds
    mov reminder4,ah;    
    mov bl,2
    mov ah,0
    mov al,randomNum
    div bl;;sub cursec, bl ; Calculate the difference in seconds
    mov reminder2,ah;     
    cmp reminder2,0;
    je car1
    mov bh,reminder4
    mov car2power,bh;sub cursec, bl ; Calculate the difference in seconds
    ret
    car1:
    mov bh,reminder4
    mov car1power,bh;
    call set_interrupt
    ret
randompower endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
choosewhichTorender proc
mov dx,0A000h
mov es,dx
cmp car1power,4
je dontcare
call checkavailblecar1
cmp canpower,1
jz finallycan 
ret
finallycan:
mov canpower,0
mov di,newcar1
mov prevdicar1,di
cmp car1power,0
je bombp
cmp car1power,3
je decrp
cmp car1power,2
je flyp
cmp car1power,1
je firep
bombp:
mov car1power,4
call drawbomb
ret
decrp:
mov car1power,4
call drawbeatme
ret
firep:
mov car1power,4
call drawfire
ret
flyp:
mov car1power,4
call drawflyinten
ret
dontcare:
cmp car2power,4
jne another
mov car2power,4
ret
another:
call checkavailblecar2
cmp canpower,1
jz finallycan2
ret
finallycan2:
mov canpower,0
mov di,newcar2
mov prevdicar2,di
cmp car2power,0
je bombp2
cmp car2power,3
je decrp2
cmp car2power,2
je flyp2
cmp car2power,1
je firep2
bombp2:
mov car2power,4
call drawbomb
ret
decrp2:
mov car2power,4
call drawbeatme
ret
firep2:
mov car2power,4
call drawfire
ret
flyp2:
mov car2power,4
call drawflyinten
ret
choosewhichTorender endp 

gotpowerup proc
cmp prevdicar1,0
jz tryanother
 mov di,prevdicar1
 lea si,Flyfloor
 cmpsb
 je handlefly
 lea si,bombfloor
 cmpsb
 je handlebomb
 lea si,beatmefloor
 cmpsb
 je handlebeatme
 lea si,firefloor
 cmpsb
 je handlefire
 handlefly:
 
 cmp powerupchooser,1
 jnz a
 mov di,48680
 mov powerupcar1timer,0
 call drawflyobstacle
 mov currentpowerforCar1,2
 jmp cl1
 a:
 mov di,48888
 mov powerupcar2timer,0
 call drawflyobstacle
 mov currentpowerforCar2,2
 cl1:
 jmp clean
 handlebomb:
  
 cmp powerupchooser,1
 jnz a2
 mov di,48680
 mov powerupcar1timer,0
 call drawcreateob
 mov currentpowerforCar1,0
 jmp cl2
 a2:
 mov di,48888
 mov powerupcar2timer,0
 call drawcreateob
 mov currentpowerforCar2,0
 cl2:
 jmp clean
 handlebeatme:
 cmp powerupchooser,1
 jnz a3
 mov di,48680
 mov powerupcar1timer,0
 call drawdecresesofanother
 mov currentpowerforCar1,3
 jmp cl3
 a3:
 mov di,48888
 mov powerupcar2timer,0
 call drawdecresesofanother
 mov currentpowerforCar2,3
 cl3:
 jmp clean
 handlefire:
 cmp powerupchooser,1
 jnz a4
 mov di,48680
 mov powerupcar1timer,0
 call drawIncresespeed
 mov currentpowerforCar1,1
 jmp cl4
 a4:
 mov di,48888
 mov powerupcar2timer,0
 call drawIncresespeed
 mov currentpowerforCar2,1
 cl4:
 jmp clean
 clean:
 mov di,prevdicar1
 call drawcleaning;
 mov prevdicar1,0
 
 jmp endboth

tryanother:
cmp prevdicar2,0
jz endboth

 mov di,prevdicar2
 lea si,Flyfloor
 cmpsb
 je handlefly2
 lea si,bombfloor
 cmpsb
 je handlebomb2
 lea si,beatmefloor
 cmpsb
 je handlebeatme2
 lea si,firefloor
 cmpsb
 je handlefire2
 handlefly2:
 cmp powerupchooser,1
 jnz a5
 mov di,48680
 mov powerupcar1timer,0
 call drawflyobstacle
 mov currentpowerforCar1,2
 jmp cl5
 a5:
 mov di,48888
 mov powerupcar2timer,0
 call drawflyobstacle
 mov currentpowerforCar2,2
 cl5:
 jmp clean2
 handlebomb2:
cmp powerupchooser,1
 jnz a6
 mov di,48680
 mov powerupcar1timer,0
 call drawcreateob
 mov currentpowerforCar1,0
 jmp cl6
 a6:
 mov di,48888
 mov powerupcar2timer,0
 call drawcreateob
 mov currentpowerforCar2,0
 cl6:
 jmp clean2
 handlebeatme2:
 cmp powerupchooser,1
 jnz a7
 mov di,48680
 mov powerupcar1timer,0
 call drawdecresesofanother
 mov currentpowerforCar1,3
 jmp cl7
 a7:
 mov di,48888
 mov powerupcar2timer,0
 call drawdecresesofanother
 mov currentpowerforCar2,3
 cl7:
 jmp clean2
 handlefire2:
 cmp powerupchooser,1
 jnz a8
 mov di,48680
 mov powerupcar1timer,0
 call drawIncresespeed
 mov currentpowerforCar1,1
 jmp cl8
 a8:
 mov di,48888
 mov powerupcar2timer,0
 call drawIncresespeed
 mov currentpowerforCar2,1
 cl8:
 jmp clean2
 clean2:
 mov di,prevdicar2
 call drawcleaning;
 mov prevdicar2,0
 endboth:
    mov powerupchooser,0
 ret
gotpowerup endp

drawcleaning proc
mov si,offset floorpic
MOV DX,10
darkgrey:
MOV CX,10
REP MOVSB
ADD DI,310
DEC DX
JNZ darkgrey
ret
drawcleaning endp
checkforboth proc
cmp currentpowerforCar1,4
jz shofsecond
cmp powerupcar1timer,5
jnz incrementtimer
mov di,48680
call Noobstacleleft
mov currentpowerforCar1,4
mov powerupcar1timer,0
jmp shofsecond
incrementtimer:
inc powerupcar1timer
shofsecond:
cmp currentpowerforCar2,4
jz shofsecond2
cmp powerupcar2timer,5
jnz incrementtimer2
mov di,48888
call Noobstacleleft
mov currentpowerforCar2,4
mov powerupcar2timer,0
jmp shofsecond2
incrementtimer2:
inc powerupcar2timer
shofsecond2:
ret
checkforboth endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 checkavailblecar1 proc
 mov bx,pos_box1
 mov di,bx 
 sub di,k
 lea si,floor
 mov dx,pixel_size
 beginup:
  mov cx,pixel_size
                tryup:
                            cmpsb
                            jnz generaltrydown
                            dec si                            
                            dec cx
                            jnz tryup
                            lea si,floor
                            dec di
                            sub di,330
                            dec dx
                            jnz beginup
                            mov currentpoerdirection,0
                            jmp cancreateup
                            ;;;;;;;;;;;;;;;;;;;;;;;;;;;downpower
                            generaltrydown:
                            mov dx,pixel_size
                            mov bx,pos_box1
                            lea si,floor
                            mov di,bx
                            add di,3520
                            begindown:
                            mov cx,pixel_size
                            trydown:
                            cmpsb
                            jnz generaltryleft
                            dec si                            
                            dec cx
                            jnz trydown
                            dec di
                            lea si,floor
                            add di,310
                            dec dx
                            jnz begindown
                            mov currentpoerdirection,2
                            jmp cancreateup
                            ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;powerleft
                            generaltryleft:
                            lea si,floor
                            mov dx,pixel_size
                             mov bx,pos_box1
                            mov di,bx
                            dec di
                            beginleft:
                            mov cx,pixel_size
                            tryleft:
                            cmpsb
                            jnz generaltryright
                            dec si
                            dec di
                            add di,k
                            dec cx
                            jnz tryleft
                            lea si,floor
                            dec di
                            sub di,3200
                            dec dx
                            jnz beginleft
                             mov currentpoerdirection,3
                            jmp cancreateup
                            ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;powerright
                              generaltryright:
                             lea si,floor
                             mov dx,pixel_size
                             mov bx,pos_box1
                            mov di,bx
                            add di,11
                            beginright:
                            mov cx,pixel_size
                            tryright:
                            cmpsb
                            jnz cantcreate
                            dec si
                            dec di
                            add di,k
                            dec cx
                            jnz tryright
                            lea si,floor                         
                            sub di,3200
                            inc di
                            dec dx
                            jnz beginright
                             mov currentpoerdirection,1
                            jmp cancreateup
                            cancreateup:
                            cmp currentpoerdirection,0
                            jnz setdown
                            mov bx,pos_box1
                            mov newcar1,bx
                            sub newcar1,canup
                            jmp endsetting
                            setdown:
                            cmp currentpoerdirection,2
                            jnz setleft
                             mov bx,pos_box1
                            mov newcar1,bx
                            add newcar1,canup
                            jmp endsetting
                            setleft:
                             cmp currentpoerdirection,3
                            jnz setright
                              mov bx,pos_box1
                            mov newcar1,bx
                            sub newcar1,canleft
                            jmp endsetting
                            setright:
                            cmp currentpoerdirection,1
                            jnz cantcreate
                              mov bx,pos_box1
                            mov newcar1,bx
                            add newcar1,canleft
                            jmp endsetting
                            endsetting:
                            mov canpower,1
                            ret
                            cantcreate:
                            mov canpower,0
                            mov currentpoerdirection,4
                            ret          
 checkavailblecar1 endp
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
checkavailblecar2 proc
  mov bx,pos_box2
 mov di,bx 
 sub di,k
 lea si,floor
 mov dx,pixel_size
 beginup2:
  mov cx,pixel_size
                tryup2:
                            cmpsb
                            jnz generaltrydown2
                            dec si                            
                            dec cx
                            jnz tryup2
                            lea si,floor
                            dec di
                            sub di,330
                            dec dx
                            jnz beginup2
                            mov currentpoerdirection,0
                            jmp cancreateup2
                            ;;;;;;;;;;;;;;;;;;;;;;;;;;;downpower
                            generaltrydown2:
                            mov dx,pixel_size
                            mov bx,pos_box1
                            lea si,floor
                            mov di,bx
                            add di,3520
                            begindown2:
                            mov cx,pixel_size
                            trydown2:
                            cmpsb
                            jnz generaltryleft2
                            dec si                            
                            dec cx
                            jnz trydown2
                            dec di
                            lea si,floor
                            add di,310
                            dec dx
                            jnz begindown2
                            mov currentpoerdirection,2
                            jmp cancreateup2
                            ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;powerleft
                            generaltryleft2:
                            lea si,floor
                            mov dx,pixel_size
                             mov bx,pos_box1
                            mov di,bx
                            dec di
                            beginleft2:
                            mov cx,pixel_size
                            tryleft2:
                            cmpsb
                            jnz generaltryright2
                            dec si
                            dec di
                            add di,k
                            dec cx
                            jnz tryleft2
                            lea si,floor
                            dec di
                            sub di,3200
                            dec dx
                            jnz beginleft2
                             mov currentpoerdirection,3
                            jmp cancreateup2
                            ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;powerright
                            generaltryright2:
                             lea si,floor
                             mov dx,pixel_size
                             mov bx,pos_box2
                            mov di,bx
                            add di,11
                            beginright2:
                            mov cx,pixel_size
                            tryright2:
                            cmpsb
                            jnz cantcreate2
                            dec si
                            dec di
                            add di,k
                            dec cx
                            jnz tryright2
                            lea si,floor                         
                            sub di,3200
                            inc di
                            dec dx
                            jnz beginright2
                             mov currentpoerdirection,1
                            jmp cancreateup2
                            cancreateup2:
                            cmp currentpoerdirection,0
                            jnz setdown2
                            mov bx,pos_box2
                            mov newcar2,bx
                            sub newcar2,canup
                            jmp endsetting2
                            setdown2:
                            cmp currentpoerdirection,2
                            jnz setleft2
                             mov bx,pos_box2
                            mov newcar2,bx
                            add newcar2,canup
                            jmp endsetting2
                            setleft2:
                             cmp currentpoerdirection,3
                            jnz setright2
                              mov bx,pos_box2
                            mov newcar2,bx
                            sub newcar2,canleft
                            jmp endsetting2
                            setright2:
                            cmp currentpoerdirection,1
                            jnz cantcreate2
                              mov bx,pos_box2
                            mov newcar2,bx
                            add newcar2,canleft
                            jmp endsetting2
                            endsetting2:
                            mov canpower,1
                            ret
                            cantcreate2:
                            mov canpower,0
                            mov currentpoerdirection,4
                            ret            
 checkavailblecar2 endp
 