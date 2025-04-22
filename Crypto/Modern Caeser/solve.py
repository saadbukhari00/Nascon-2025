#!/usr/bin/env python3

def dynamic_caesar_decrypt(encrypted_message):
    decrypted_message = []
    
    for i, char in enumerate(encrypted_message):
        # Check if the character is a letter or digit
        if char.isalpha():
            if char.isupper():
                shifted_char = chr(((ord(char) - ord('A') - (i + 1)) % 26) + ord('A'))
            else:
                shifted_char = chr(((ord(char) - ord('a') - (i + 1)) % 26) + ord('a'))
        elif char.isdigit():
            shifted_char = chr(((ord(char) - ord('0') - (i + 1)) % 10) + ord('0'))
        elif char in '{}':
            shifted_char = char
        else:
            shifted_char = char
        
        decrypted_message.append(shifted_char)
    
    return ''.join(decrypted_message)

def get_encrypted_flag():
    with open('writeup.txt', 'r') as f:
        encrypted_flag = f.read().strip()
    return encrypted_flag

def solve_caesar_challenge():
    encrypted_flag = get_encrypted_flag()
    
    decrypted_flag = dynamic_caesar_decrypt(encrypted_flag)
    
    print(f"\nDecrypted Flag: {decrypted_flag}\n")
    
if __name__ == "__main__":
    solve_caesar_challenge()
