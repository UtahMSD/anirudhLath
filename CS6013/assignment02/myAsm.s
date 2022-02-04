extern puts
section .text  ; this says that we're about to write code (as opposed to data)

global _sayHello ; this says that "sayHello" is a symbol that the linker needs to know about

myPuts:
	mov	rax, 1
	mov	rdi, 1
	mov	rsi, helloString
	mov 	rdx, 6

	syscall

	ret


sayHello:
	mov	rdi, helloString
	call	puts
	ret

_sayHello:      ;and here we go...
     mov    rax, 1         ; system call for write
     mov    rdi, 1         ; file handle 1 is stdout
     mov    rsi, helloString      ; address of string to output
     mov    rdx, 5         ; number of bytes
     syscall              ; invoke operating system to do the      mov    rax, 60         ; system call for exit
     xor    rdi, rdi        ; exit code 0
     syscall              ; invoke operating system to exit


section .rodata  ; this is the read only data (hello is a constant)

helloString: db "hello",0 ; hellostring is the name of our symbol

; db is the directive to put data in our object file
; the 0 is the null terminator that puts is expecting.
; nasm does NOT null terminate our string automatically
