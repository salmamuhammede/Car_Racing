extern beginpage:far
extern leftcaringame:far
extern SCREEN_HEIGHT:far
extern SCREEN_WIDTH:far
extern pixel_size:far
extern rightcar:far


extern clearfromstatus:far
extern aggreedsize:far
extern aggreedsizefrostausbar:far
extern createob:far
extern flyob:far
extern decreseimg:far
extern flyinten:far
extern bomb:far
extern fire:far
extern beatme:far
extern floorpic:far
extern floor:far
extern blueover:far
extern redover:far
extern celebratemonkey:far
extern gameoverpic:far 

public drawbeginpage
public drawleftcarinstatus
public drawrightcarinstatus


.MODEL small


.code

draws PROC
 ret   
draws ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;beginning page
drawbeginpage proc

    MOV SI,offset beginpage
    
    MOV DX,160

    REPEATt:
    MOV CX,280
    REP MOVSB
    ADD DI,320-280
    DEC DX
    JNZ REPEATt 
    ret
 drawbeginpage endp
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; statuse bar cars
 drawleftcarinstatus proc
 MOV SI,offset leftcaringame
 MOV DX,20

REPEAT3:
MOV CX,33
REP MOVSB
ADD DI,SCREEN_WIDTH-33
DEC DX
JNZ REPEAT3
ret
 drawleftcarinstatus endp
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 drawrightcarinstatus proc
 MOV SI,offset rightcar
  MOV DX,20
    REPEAT2:
    MOV CX,37
REP MOVSB
ADD DI,SCREEN_WIDTH-37
DEC DX
JNZ REPEAT2
ret
drawrightcarinstatus endp


end draws
