import struct

def decrypt_hex(hex_values):
    hex_bytes = b''
    for hex_val in hex_values:
        hex_bytes += struct.pack('<Q', hex_val)
    
    decrypted = bytearray(hex_bytes)
    for i in range(len(decrypted)):
        decrypted[i] ^= 0xE
    
    return decrypted

def bytes_to_string(byte_data):
    try:
        return byte_data.decode('utf-8').rstrip('\x00')
    except UnicodeDecodeError:
        return str(byte_data)

def main():
    encrypted_hex = [
        0x3a60776a75425d4d,
        0x6d607b68516d3f63,
        0x603d695160613f7a,
        0x7360613f7a3a7c3d
    ]

    decrypted_data = decrypt_hex(encrypted_hex)
    
    decrypted_message = bytes_to_string(decrypted_data)
    print("Decrypted:", decrypted_message)
if __name__ == "__main__":
    main()
