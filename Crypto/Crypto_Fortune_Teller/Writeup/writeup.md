# **Crypto Fortune Teller**

### **Description:**
> "Randomness is an illusion.  
>  
> Random Numbers:  
> ```
> [  
>   0.4716964533196313,  
>   0.5456564973145532,  
>   0.20970818720192375,  
>   0.12428636932997339,  
>   0.9467983060151131,  
>   0.29346163876538855  
> ]  
> ```  
> Encrypted Flag:  
> `865d03009ac454c63ddbf270494702fd72432d0af00ee8a28b516dcbb0271e10`

---

## **Challenge Overview**

In this challenge:
- The encryption key for AES-256 is generated from a "random" number outputted by JavaScript’s **Math.random()** function.
- You are given **6 random numbers** (the first 6 outputs of `Math.random()`).
- The **7th output**, which is hidden, was used to derive the AES key.
- Your goal is to recover the hidden **7th random number**, recreate the AES key, and decrypt the encrypted flag.

---

## **Why is this solvable?**

Because **Math.random()** in JavaScript (V8 engine) is based on a **Xorshift128+ PRNG**, which is deterministic once you know its internal state. If we can recover the internal state from several consecutive outputs, we can predict future outputs.

In this case, since you’re given **6 consecutive outputs**, you can fully recover the PRNG’s state and predict the 7th number.



## **Solution Overview**

### Step 1️ — Recover Xorshift128+ internal state  
- JavaScript `Math.random()` produces a **double precision float** where the lower **52 bits** are derived from the PRNG's state (specifically the mantissa).
- You can **reverse-engineer** these mantissas back into the Xorshift internal state using symbolic execution (with Z3).
  
### Step 2️ — Predict the 7th random number  
- Once you recover the state, you simulate the PRNG **one more step** to get the hidden **7th random output**.

### Step 3️ — Derive AES key and decrypt  
- The **7th random number** is hashed with SHA-256 to create the AES key.
- Finally, decrypt the flag using **AES-256-ECB**.

---

## **Solve Script Explained**

```python
import z3
import struct
import hashlib
from Crypto.Cipher import AES
```

We will use z3, a powerful theorem prover and SMT (Satisfiability Modulo Theories) solver used to solve symbolic constraints.

---
```python
sequence = [
  0.4716964533196313,
  0.5456564973145532,
  0.20970818720192375,
  0.12428636932997339,
  0.9467983060151131,
  0.29346163876538855
]

sequence = sequence[::-1]
```
The `Xorshift128+` state is recovered in reverse (since the generator is forward-only, but we have to solve it backwards).

---
```python
solver = z3.Solver()
se_state0, se_state1 = z3.BitVecs("se_state0 se_state1", 64)
```
`se_state0` and `se_state1` are symbolic variables representing the internal state of the PRNG.

We create a symbolic model of **Xorshift128+** inside Z3 using bitwise operations.

---
```python
for i in range(len(sequence)):
    se_s1 = se_state0
    se_s0 = se_state1
    se_state0 = se_s0
    se_s1 ^= se_s1 << 23
    se_s1 ^= z3.LShR(se_s1, 17)  # Logical shift instead of Arthmetric shift
    se_s1 ^= se_s0
    se_s1 ^= z3.LShR(se_s0, 26)
    se_state1 = se_s1

    float_64 = struct.pack("d", sequence[i] + 1)
    u_long_long_64 = struct.unpack("<Q", float_64)[0]

    # Get the lower 52 bits (mantissa)
    mantissa = u_long_long_64 & ((1 << 52) - 1)

    # Compare Mantissas
    solver.add(int(mantissa) == z3.LShR(se_state0, 12))
```
Implementation of Javascript's V8 `Xorshift128+` PRNG.
- Floats from `Math.random()` are transformed back to their mantissas (lower 52 bits of state0 shifted right by 12).
- We constrain Z3 to find `se_state0` and `se_state1` that produce the observed mantissas.

---
```python
if solver.check() == z3.sat:
    model = solver.model()
    state0 = model[se_state0].as_long()

    # Predict next random number (7th)
    u_long_long_64 = (state0 >> 12) | 0x3FF0000000000000
    float_64 = struct.pack("<Q", u_long_long_64)
    next_sequence = struct.unpack("d", float_64)[0]
    next_sequence -= 1

    print(next_sequence)
```
After solving, you predict the 7th random number by simulating one more PRNG output.

---
```python
def decrypt_aes_ecb(encrypted_hex, random_number):
    key = hashlib.sha256(str(random_number).encode()).digest()
    cipher = AES.new(key, AES.MODE_ECB)
    decrypted = cipher.decrypt(bytes.fromhex(encrypted_hex))
    return decrypted.rstrip(b"\x00").decode()
```
Finally, you derive the AES key from the 7th random number, decrypt the flag, and remove padding.

