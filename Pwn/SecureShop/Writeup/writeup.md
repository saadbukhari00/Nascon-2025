# SecureShop Challenge Writeup

## Introduction

The SecureShop Challenge is a multi-stage binary exploitation challenge that blends reverse engineering with an obfuscated integer overflow vulnerability. Solvers must first bypass a login portal by leaking a global username and reverse-engineering a custom password obfuscation algorithm. After authentication, they must trigger a hidden integer overflow in the shop interface to unlock the secure vault and retrieve the flag.

## Challenge Overview

The binary (`chall.c`) consists of two main stages:

1. **Authentication Portal:**
   - **Global Username:** Stored as a string in the binary.
   - **Obfuscated Password:** The actual password is transformed using a custom shifting algorithm.

2. **SecureShop Purchase Interface:**
   - Once authenticated, the user accesses a purchase system with an obfuscated integer overflow vulnerability hidden within a cost computation function.

Several dummy functions and obfuscation routines are included to mislead reverse engineers.

## Detailed Breakdown

### 1. Authentication Portal

#### Global Credentials
- **Username:** Stored in plaintext in the binary (easily leakable via static analysis).
- **Password:** The real password (e.g., `"P@55w0rd"`) is stored in an encoded form.

#### Custom Password Shifting Algorithm

- **Encoding Transformation (compile-time):**

  ```c
  encoded[i] = (((original[i] - 32) + (i + 3) + ((i % 3) * 4)) % 95) + 32;
  ```

  The encoded password stored in the binary is, for example, `"SHB;#@{r"`.

- **Decoding Transformation (during execution):**

  ```c
  decoded[i] = (((encoded_pass[i] - 32) - (i + 3) - ((i % 3) * 4) + 95) % 95) + 32;
  ```

  Applying this operation to each character of `"SHB;#@{r"` recovers the actual password.

#### Reverse Engineering Notes
- **Leak the Username:** Use `strings` or inspect global variables in a disassembler.
- **Recover the Password:** Reverse the shifting logic by analyzing the decryption loop in `auth_portal()`.

### 2. SecureShop Purchase Interface

#### The Vulnerable Computation

- The function `compute_cost(int price, int quantity)` calculates the total cost:
  
  ```c
  int modifier = ((price & 0xFF) % 7) - ((quantity & 0xFF) % 5);
  int total = price * quantity - modifier;
  ```
  
- **Vulnerability:** The multiplication `price * quantity` can overflow, causing `total` to become negative.

#### Exploitation Strategy

1. **Reverse Engineer the Binary:**
   - Identify `global_username` and `encoded_pass` in the binary.
   - Analyze the decoding logic in `auth_portal()`.
   
2. **Recover the Password:**
   - Reverse the custom shifting algorithm to recover `"P@55w0rd"` from `"SHB;#@{r"`.

3. **Bypass Authentication:**
   - Use the leaked username and recovered password to log in.

4. **Trigger the Integer Overflow:**
   - Find values of `price` and `quantity` that cause overflow.
   - Once overflowed, the program calls `secure_unlock()` and reveals the flag.

## Final Remarks

The SecureShop Challenge tests both reverse engineering and binary exploitation skills. The multi-stage nature—requiring password de-obfuscation and integer overflow exploitation—demands careful analysis and creative input crafting.

Happy hacking, and best of luck solving SecureShop!

