section .text  ; this says that we're about to write code (as opposed to data)

global _sayHello ; this says that "sayHello" is a symbol that the linker needs to know about

_sayHello:           ;and here we go...

  ;;code goes here

  ret                 ; just return