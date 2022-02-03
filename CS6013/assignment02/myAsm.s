section .text  ; this says that we're about to write code (as opposed to data)

global sayHello ; this says that "sayHello" is a symbol that the linker needs to know about

sayHello:           ;and here we go...

  ;;code goes here

  ret                 ; just return

section .rodata  ; this is the read only data (hello is a constant)

helloString: db "hello",0 ; hellostring is the name of our symbol

; db is the directive to put data in our object file
; the 0 is the null terminator that puts is expecting.
; nasm does NOT null terminate our string automatically
