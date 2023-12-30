extern x:word
extern y:word
extern lengthD:word
extern addFill:word
extern fill:word
extern skipFill:byte
extern widthT:word
extern color_track:byte
extern lastObstacle:word
extern lengthObstacle:word
extern widthDrawn:word
extern lengthLane:word
extern obstacle_color:word
extern lengthD:word
extern obstacleLane:word
extern lengthDrawn:word
extern lastDirection:word
extern x1:word
extern x2:word
extern y1:word
extern y2:word
extern lengthT:word
extern temporaryLength:word
extern temporaryLength2:word
extern dontDraw:word
extern drawn:word
extern prev_rand:byte
extern endLineStart:word
extern endLineEnd:word
extern changesLeft:word
extern row:word
extern drawObstacle:word
public drawtrack

.MODEL small



.code
drawtrack proc far
   


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
                    mov  ah, 0
                    mov  al, dl                       ;;micro seconds
                    add al, prev_rand
                    mov cl, dh
                    ror al, cl
                    mov prev_rand, al
                    mov cx, dx
                    mov bl, 4
                    div  bl
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
 ;--------------------------------------------------;
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
                    
                     mov al, 09h
                    
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
                    inc ax
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
                    mov ax, lastDirection
                    cmp ax,3
                    jz dontAddL
                    inc changesLeft
                    dontAddL:
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

randFunc proc far
                      mov dx, cx
                        mov  ah, 2ch
                        int  21h
                        mov  ah, 0
                        mov  al, dl                       ;;micro seconds
                        add al, prev_rand
                        mov cl, dh
                        ror al, cl
                        mov prev_rand, al
                        mov cx, dx
                        mov bl, 4
                        div  bl

ret
randFunc endp


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
                    mov endLineStart, di

                    rep   stosb
                    mov endLineEnd, di
                    dec endLineEnd

                    jmp   endLine
      vertical:     
                    mov   cx, y2
                    sub   cx, y1
                    mov   ax, 320
                    mov   bx, y1
                    mul   bx
                    add   ax, x1
                    mov   di, ax
                    mov endLineStart, di
      color:        
                    mov   al, 04h
                    stosb
                    add   di, 319
                    loop  color

                    mov endLineEnd, di
                    dec endLineEnd
    
    
    
      endLine:      
                    ret
drawEndLine endp


drawStartLine proc far
        mov changesLeft, 0
        mov x1,0
        mov x2,0
        mov y1,0
        mov y2,0
        mov lastDirection,1
        mov ax, widthT
        mov lengthT, ax
        mov lengthD, ax
        mov dontDraw,0
        mov drawObstacle,0
        mov x,0
        mov y,0
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
end drawtrack