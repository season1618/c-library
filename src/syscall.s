.intel_syntax noprefix

.global read
read:
    mov rax, 0
    syscall
    ret
write:
    mov rax, 1
    syscall
    ret
