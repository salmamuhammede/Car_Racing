.286
                    .MODEL SMALL;TINY   :data+code = 64KB    
                                
;------------------------------------------------------
                    .STACK 64   ;64 BYTES for stack      
;------------------------------------------------------                    
                    .DATA
k                   equ         320         
pixel_size          equ          10
pos_box1            dw          6450
pos_box2            dw          7568
color_box1          db          4
color_box2          db          7
; -----------------------------------------------------
                    .Code
Main                proc        far
                mov ax,@data
                mov ds,ax
            ; -- set video memory ----   ;
                mov ax,0A000h;
                mov es,ax
            ; -----set the box---------  ;
                mov ah,0
                mov al,13h
                int 10h
            ; -- draw square     -- ;
                mov di,pos_box1
                mov al,color_box1 
                mov bl,8
                call draw 
                mov di,pos_box2
                mov al,color_box2 
                mov bl,8
                call draw 
                call play
            
Main                Endp
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
                        removelast2:  
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
                        removefirst2:  
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
                        removelast:  
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
                        removefirst:  
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
                    endmove:
                        
                        pop cx
                        pop ax
                        pop di
                ret
move_b1             endp
; ------------------------------------------------------;


play            proc
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
                ret
play            endp
                    End Main