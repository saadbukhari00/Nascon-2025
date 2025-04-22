import hashlib
import time

SECRET = "two_genders_only"
with open("flag.txt", "r") as f:
    FLAG = f.read().strip()

def check_password(user_input):
    fake_hash = hashlib.sha256(user_input.encode()).hexdigest()
    print(f"[!] Hashing {user_input} with SHA-256... {fake_hash}")

    for i in range(len(user_input)):
        if i >= len(SECRET) or user_input[i] != SECRET[i]:
            return False
        
        time.sleep(0.1)

    return user_input == SECRET

while True:
    guess = input("\n[?] Enter password: ")
    
    if check_password(guess):
        print(f"[+] Correct! Here is your flag: {FLAG}")
        break
    else:
        print("[-] Wrong! Try again.")
