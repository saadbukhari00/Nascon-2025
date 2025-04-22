# Laboratory Challenge - Writeup

## Challenge Overview

This challenge presents a binary that allows users to submit shellcode in hex format, which the program then parses, loads into executable memory, and executes. The vulnerability is intentional: direct execution of user-provided code. Our goal is to exploit this to read the contents of `flag.txt` which is located in the same directory as the binary.

## Vulnerability Analysis

Let's start by examining the source code to understand how the program works and where the vulnerability lies.

### Key Components of the Program

The program's code is deliberately obfuscated with:
- Misleading function names like `_FN91028374`
- Random variables and operations
- Dummy code that doesn't contribute to the actual functionality
- Inconsistent naming conventions

Let's break down the actual functional parts:

1. **I/O Buffering Setup**:
   ```c
   static void _FN01234567() {
       setvbuf(stdout, NULL, _IONBF, 0);
       setvbuf(stderr, NULL, _IONBF, 0);
       setvbuf(stdin,  NULL, _IONBF, 0);
   }
   ```
   This disables buffering for stdin, stdout, and stderr, which is common in CTF challenges to prevent issues with pipe I/O.

2. **Banner Display**:
   ```c
   static void _FN77777777() {
       printf("Shadow Code's Lab\n");
       printf("Welcome to the secret testing node.\n");
       printf("Present your specialized shellcode, mortal.\n");
       printf("Use hex bytes like '\\x90\\x90\\x90' if you dare...\n");
   }
   ```
   This creates a thematic banner for the challenge.

3. **Shellcode Parsing**:
   ```c
   static int *FN33330000(char src, unsigned char dst, size*t lim) {
       size_t length = strlen(src);
       size_t out_len = 0;
       for (size_t i=0; i < length; i++) {
           if (src[i] == '\\' && src[i+1] == 'x' && (i+3 < length)) {
               char hh[3];
               hh[0] = src[i+2];
               hh[1] = src[i+3];
               hh[2] = '\0';
               unsigned int val;
               sscanf(hh, "%x", &val);
               if (out_len < lim) {
                   dst[out_len++] = (unsigned char)val;
               } else {
                   printf("** Shellcode too monstrous! Truncating.\n");
                   break;
               }
               i += 3;
           }
       }
       return out_len;
   }
   ```
   Despite the obfuscated name and some syntax errors in the shared code (which I'm treating as typos), this function parses the user's input from hex format (like `\x90\x90\x90`) into actual bytes that can be executed.

4. **Shellcode Execution**:
   ```c
   static void *FN19283746(unsigned char *sc, size*t sz) {
       void *exec_mem = mmap(NULL, sz, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
       if (exec_mem == MAP_FAILED) {
           perror("mmap");
           exit(1);
       }
       memcpy(exec_mem, sc, sz);
       printf("Invoking the haunted instructions...\n");
       ((void(*)(void))exec_mem)();
       munmap(exec_mem, sz);
   }
   ```
   This function is where the main vulnerability exists. It:
   - Uses `mmap` to allocate memory with execute permissions (`PROT_EXEC`)
   - Copies the user's shellcode into this executable region
   - Directly executes the shellcode by treating the memory as a function pointer and calling it
   - After execution, it cleans up by unmapping the memory

5. **Main Function**:
   ```c
   int main() {
       char    *local*input[_FNCNST001];
       unsigned char *shell*area[_FNCNST001];
       size_t  sc_size;
       _FN01234567();
       _FN45678901();
       _FN77777777();
       printf(">>> Offer your hex-coded incantations:\n");
       printf("> ");
       if (!fgets(_local_input, _FNCNST001, stdin)) {
           printf("~~ Cursed silence...no input found.\n");
           return 1;
       }
       *local*input[strcspn(_local_input, "\n")] = '\0';
       sc_size = *FN33330000(*local_input, *shell*area, _FNCNST001);
       printf("** Detected %zu bytes within your creation.\n", sc_size);
       if (sc_size < 10) {
           printf("** Too feeble. Minimum accepted size: 10 bytes.\n");
           return 1;
       }
       *FN19283746(*shell_area, sc_size);
       int obf_var = (int)sc_size;
       obf_var = *FNRNDMCRO(obf*var, 3);
       *FN98765432(obf*var);
       return 0;
   }
   ```
   The main function:
   - Sets up the environment
   - Displays the banner
   - Reads user input
   - Parses it into shellcode
   - Performs minimal validation (checking if the size is at least 10 bytes)
   - Executes the shellcode
   - Runs some meaningless operations afterward

### The Vulnerability

The vulnerability is straightforward despite the obfuscation: the program intentionally executes arbitrary user-provided code. While the thematic elements suggest a "controlled environment" with references to "haunted instructions," there are no actual restrictions on what the shellcode can do. Since the code runs with the same permissions as the program itself, the shellcode can access any files that the program can access, including `flag.txt`.

The obfuscation makes the program harder to read but doesn't add any actual security. In fact, the obfuscation might be intended to distract from the simple nature of the vulnerability.

## Exploit Development

To exploit this vulnerability, we need to craft shellcode that performs the following actions:

1. Opens the `flag.txt` file
2. Reads its contents
3. Writes the contents to stdout so we can see it

Let's break down the exploit step by step.

### Setting Up the Environment

First, we import the necessary modules and set up the context for our exploit:

```python
#!/usr/bin/env python3
from pwn import *
import re
context.arch = 'amd64'
context.os = 'linux'
context.log_level = 'info'
```

The `pwntools` library provides useful functions for CTF challenges, including shellcode generation. We specify that we're targeting a 64-bit Linux system and set the logging level to 'info' for better visibility.

### Developing the Shellcode

We need to create shellcode that:

1. Opens the file using the `open` syscall (syscall number 2)
2. Reads from the file using the `read` syscall (syscall number 0)
3. Writes to stdout using the `write` syscall (syscall number 1)
4. Exits cleanly using the `exit` syscall (syscall number 60)

```
The shell-code for the challenge is written in solve.py
```

### Sending the Exploit and Extracting the Flag

Now we need to:
1. Connect to the target program
2. Send our shellcode
3. Receive the output
4. Extract the flag

## Navigating the Obfuscation

One of the challenges in this exploitation task is navigating the code's obfuscation. The obfuscation techniques used include:

1. **Misleading function names**: Functions like `_FN91028374` give no indication of their purpose
2. **Dead code**: Functions like `_FN45678901` call other functions that don't do anything useful
3. **Syntax errors**: There are several apparent typos in the code (like `*local*input` instead of `local_input`), which might be deliberate to make the code harder to read
4. **Meaningless macros**: The `_FNRNDMCRO` macro performs a bit rotation operation but serves no real purpose
5. **Thematic text**: The program uses occult/magical terminology ("haunted instructions", "incantations") to create a theme and potentially distract from the technical analysis

Despite these obfuscation techniques, the core functionality remains simple: take user input, parse it into shellcode, and execute it.
