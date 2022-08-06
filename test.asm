;nasm -f elf64 hello.asm -o hello.o
;ld hello.o -o hello
;./hello
SECTION .data                     ; Section for variable definitions

; Variable containing a string that has a line break and is null-terminated
string:   DB "Hello\n",0ah

; Variable that calculates the value of an expression to determine the
; length, in bytes, of the variable "stringLiteral" by subtracting the
; starting memory address of the variable from the current memory address
lenString:        EQU ($ - string)

SECTION .text                     ; Section for instructions
global _start                      ; Make the label "_main"
                                  ; available to the linker as an
                                  ; entry point for the program
_start:                            ; Label for program entry

mov rax, 1
mov rdi, 1
lea rsi, [rel string]
mov rdx, lenString
syscall

mov rax, 60                       ; Set the system call for exit
xor rdi, rdi                      ; Set the return value in rdi (0)
syscall                           ; Issue the kernel interrupt
