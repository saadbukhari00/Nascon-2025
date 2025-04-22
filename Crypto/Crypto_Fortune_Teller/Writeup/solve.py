#!/usr/bin/python3
import z3
import struct
import hashlib
from Crypto.Cipher import AES



encrypted_hex = "865d03009ac454c63ddbf270494702fd72432d0af00ee8a28b516dcbb0271e10"
sequence = [
    0.4716964533196313,  
    0.5456564973145532,  
    0.20970818720192375,  
    0.12428636932997339,  
    0.9467983060151131,  
    0.29346163876538855
]


sequence = sequence[::-1]

solver = z3.Solver()


se_state0, se_state1 = z3.BitVecs("se_state0 se_state1", 64)

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


if solver.check() == z3.sat:
    model = solver.model()

    states = {}
    for state in model.decls():
        states[state.__str__()] = model[state]

    state0 = states["se_state0"].as_long()


    u_long_long_64 = (state0 >> 12) | 0x3FF0000000000000
    float_64 = struct.pack("<Q", u_long_long_64)
    next_sequence = struct.unpack("d", float_64)[0]
    next_sequence -= 1

    print(next_sequence)

def decrypt_aes_ecb(encrypted_hex, random_number):
    # Convert the random number into a 256-bit key
    key = hashlib.sha256(str(random_number).encode()).digest()

    # Decrypt using AES-256-ECB
    cipher = AES.new(key, AES.MODE_ECB)
    decrypted = cipher.decrypt(bytes.fromhex(encrypted_hex))

    # Remove potential padding (AES uses PKCS7 padding)
    return decrypted.rstrip(b"\x00").decode()

# Example usage
random_number = next_sequence

decrypted_flag = decrypt_aes_ecb(encrypted_hex, random_number)
print("Decrypted Flag:", decrypted_flag)
