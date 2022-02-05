extern puts


section .text  ; this says that we're about to write code (as opposed to data)

global sayHello ; this says that "sayHello" is a symbol that the linker needs to know about
global myPuts
global myGTOD


sayHello:
	mov	rdi, helloString
	call	puts
	ret

myPuts:
        mov     rax, 1
        mov     rdx, rsi
	mov	rsi, rdi
	mov	rdi, 1

        syscall

        ret

myGTOD:
	sub     rsp, 16
	mov	rax, 96
        mov     rdi, rsp
	mov	rsi, 0

	syscall

        mov     rax, [rsp]
        mov     rdx, [rsp+8]
        add     rsp, 16

        ret

section .rodata  ; this is the read only data (hello is a constant)

helloString: db "hello",0 ; hellostring is the name of our symbol

; db is the directive to put data in our object file
; the 0 is the null terminator that puts is expecting.
; nasm does NOT null terminate our string automatically
