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
