printChar macro c
pusha
mov ah,2 
mov dl,c
int 21h
popa      
endm

printMsg macro message
pusha
mov ah,9
mov dx,offset message
int 21h
popa
endm
;movecursor macro x, y 
;mov ah,2
;mov bh,0
;mov dl,x
;mov dh,y
;int 10h
;endm
printNewLine macro
    mov ah, 02h    
    mov dl, 13d
    int 21h
    mov dl, 10d
    int 21h
endm, printNewLine
printWithNewLine macro msg
    printMsg msg
    printNewLine
endm