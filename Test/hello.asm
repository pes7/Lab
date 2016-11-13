.686
.MODEL FLAT, C
.STACK

.DATA
    helloFormat BYTE "Hello %s!",10,13,0
    
.CODE
readName PROTO C
printf PROTO arg1:Ptr Byte, printlist: VARARG
sayHello PROC
    invoke readName
    invoke printf, ADDR helloFormat, eax
    ret
sayHello ENDP
END