# PWN Challenge Writeup – "Race against time"

## Challenge Description
This challenge features a file manager that’s been co-opted by the *Shadows of NasCon*. Your task is to navigate its functions, bypass privilege checks, and ultimately read a protected flag. Despite its seemingly normal options (like reading files, creating symlinks, and updating notes), a subtle vulnerability allows clever attackers to race the system into revealing secrets.

## Initial Analysis
First, inspect the binary’s security features:

```bash
checksec --file=./chall
RELRO:          Partial RELRO
Stack Canary:   No canary found
NX:             NX enabled
PIE:            No PIE
```

Partial RELRO: Some relocation sections are protected, but not fully.

No Stack Canary: Classic buffer overflows remain viable.

NX Enabled: The stack is non-executable, preventing direct shellcode injection.

No PIE: The binary is loaded at a fixed base address, simplifying return-oriented programming (ROP).

However, the real focus is on a time-of-check to time-of-use (TOCTOU) vulnerability.

Identifying the Vulnerability
A closer look at the source code (or disassembly) reveals a routine for reading files:
FILE *file = fopen(filename, "r");
// ...
fread(buffer, 1, BUFFER_SIZE * 2, file);

Before the file is opened, the program checks whether the user has permissions to read it. It then sleeps for a short time, creating a race condition window. During this interval, you can swap a symlink from a harmless file to the protected flag file.

Finding the Exploit Path
Privilege Escalation:
The binary includes a feature to increase your privilege level step-by-step. Reaching the top privilege level (SYSTEM) often lets you read restricted files directly, though there’s a secondary check preventing low-level users from reading flag.txt.

Symlink Trick:

Create a symlink pointing to a dummy file that passes the initial permission check.

Immediately after the permission check (but before the file is opened), delete the symlink and recreate it to point at flag.txt.

The program then opens the symlink—which now leads to the flag.

Exploiting the Vulnerability
A high-level overview:

Launch the Program:
Run ./chall and observe the menu options.

Escalate Privileges:
Use the menu option (often #7) to increase your privilege level repeatedly until you’re at the highest level (if necessary).

Create Symlink:
Choose the option to create a symlink (#3). First, point it to some dummy file.

Read File:
Immediately select the option to read a file (#1). Provide the symlink’s name (e.g., tmp_link).

Perform the Race Swap:
The program will check permission, then pause. During that pause, remove tmp_link and recreate it pointing to the flag. If timed correctly, you’ll bypass the permission check.

Flag Retrieval:
Once the file is actually read, it should reveal the flag contents.

Getting the Flag
When the race condition is exploited successfully, the program displays the contents of flag.txt. For instance:

File contents:
CSL{************}

