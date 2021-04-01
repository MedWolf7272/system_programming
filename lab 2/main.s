extern printf
section .text
global main
main:
    push rbp

    mov rcx, 10
    mov rsi, array
    mov rax, 0
    mov rbx, 0

    for_loop:
        lodsw
        xor ax, 0b1111111100000000
        test rcx, 1
        jnz end_of_loop
        add rbx, rax
        end_of_loop:
    loop for_loop

    mov rdi, fmt
    mov rsi, rbx
    mov rax, 0           
    call    printf
    pop rbp

    mov rax, 0
    ret

section .data
    array dw 111, 222, 333, 444, 555, 666, 777, 888, 999, 1111 
    fmt db "Сумма четных элементов: %d", 10, 0
  