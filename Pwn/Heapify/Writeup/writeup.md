# PWN Challenge Writeup – "Heapify"

## Challenge Description
In this challenge, the BlackCell hackers have taken control of the event, and chaos reigns. Your mission is to retrieve the flag and stop them. The binary implements a heap-based storage system for "Chaos Chunks" with functions to create, edit, delete, and print these chunks. A heap buffer overflow vulnerability in the edit functionality allows an attacker to overwrite an encrypted function pointer stored in the chunk. When this pointer is later used, it may trigger a hidden win() function that reveals the flag. In addition, a format string vulnerability leaks an obfuscated global encryption key needed to correctly forge the pointer.

## Initial Analysis
- **Binary Protections:**
  - Partial RELRO, no stack canary, NX enabled, no PIE.
  - The absence of a stack protector and PIE simplifies address calculations.

- **Heap Structure:**
  - The binary maintains an array of 3 heap chunks.
  - Each chunk has a 64-byte buffer and an encrypted function pointer (`fp_enc`), which is stored as the function pointer XORed with a global key.

- **Global Key:**
  - A global key (`_FNGlobalKey`) is generated using `rand()` during initialization.
  - This key is used to encrypt and later decrypt the function pointer.

- **Vulnerabilities:**
  1. **Heap Buffer Overflow:**  
     The `edit_chunk()` function uses `gets()` to read input into the chunk's buffer without bounds checking, allowing an attacker to overflow the buffer and overwrite the adjacent `fp_enc` field.
  
  2. **Format String Vulnerability:**  
     The `vuln_format()` function prints two parameters—a constant (`0xdeadbeef`) and the global key—after applying XOR obfuscation (with fixed constants). This leak can be exploited to recover the true value of `_FNGlobalKey`.

## Exploitation Strategy
1. **Leak the Global Key:**
   - Exploit the format string vulnerability in `vuln_format()`.  
   - The function prints two values:
     - The first value is `0xdeadbeef ^ 0x12345678` (i.e. `0xcc99e897`).
     - The second is `_FNGlobalKey ^ 0x87654321`.
   - By capturing these values, you can confirm the first one and recover the real global key by XORing the second value with `0x87654321`.

2. **Overwrite the Function Pointer:**
   - Create a chunk using `create_chunk()`.
   - Use `edit_chunk()` to overflow the 64-byte buffer.  
   - Overwrite the encrypted function pointer (`fp_enc`) with the address of the win() function (`_FN11111111`), but encrypted as `win_address XOR _FNGlobalKey`.

3. **Trigger the Win Function:**
   - Invoke `print_chunk()` on the modified chunk.
   - The program decrypts the pointer by XORing it with the global key and calls the resulting function.
   - This transfers control to the win() function, which prints the flag.

## Exploit Outline (Pseudocode)
  # Leak the Global Key via the format string vulnerability
  # Overwrite function pointer in Chaos Chunk 0
  # Trigger the overwritten pointer

The provided solve.py script automates these steps.

## Conclusion
This challenge combines a heap overflow vulnerability with a format string leak to defeat a simple XOR-based pointer encryption mechanism. The attacker must first recover the global key, then use it to forge an encrypted pointer that, when decrypted during a chunk print, redirects execution to the win() function that prints the flag. Numerous dummy functions and obfuscated code are included to distract and confuse reverse engineers, fitting the theme of a chaotic takeover by BlackCell.

