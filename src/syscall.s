.intel_syntax noprefix

.global read
read:
    mov rax, 0
    syscall
    ret
.global write
write:
    mov rax, 1
    syscall
    ret
.global brk
brk:
    mov rax, 12
    syscall
    ret
.global clock_gettime
clock_gettime:
    mov rax, 228
    syscall
    ret
.global getrandom
getrandom:
    mov rax, 318
    syscall
    ret
