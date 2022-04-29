section .text ; code section
global fib ; linker needs to know about the symbol "fib", nm -a main.o

fib: ; fib logic section
        

returnOne:
    mov rax, 1
    ret

returnZero:
    mov rax, 0
    ret
