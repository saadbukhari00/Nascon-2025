def base80_decode(encoded_str):
    base80_alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/=@#%&*[]{}-_$!~`^"
    base80_reverse = {c: i for i, c in enumerate(base80_alphabet)}
    
    encoded_len = len(encoded_str)
    if encoded_len % 3 not in (0, 2):
        raise ValueError("Invalid encoded string length")
    
    decoded = bytearray()
    i = 0
    while i + 3 <= encoded_len:
        triplet = encoded_str[i:i+3]
        try:
            d2 = base80_reverse[triplet[0]]
            d1 = base80_reverse[triplet[1]]
            d0 = base80_reverse[triplet[2]]
        except KeyError as e:
            raise ValueError(f"Invalid character in triplet: {e}")
        
        num = d2 * (80 ** 2) + d1 * 80 + d0
        decoded.append((num >> 8) & 0xFF)
        decoded.append(num & 0xFF)
        i += 3
    
    if i < encoded_len:
        remaining = encoded_str[i:i+2]
        if len(remaining) != 2:
            raise ValueError("Invalid remaining characters")
        try:
            d0 = base80_reverse[remaining[0]]
            d1 = base80_reverse[remaining[1]]
        except KeyError as e:
            raise ValueError(f"Invalid character in remaining: {e}")
        
        decoded.append(d0 * 80 + d1)
    
    return bytes(decoded)


encoded_str = "2tZ34x2t*2B41-!3@I27%24V2J=3=n4nF2B54XF4Da4Da1RD"
decoded_data = base80_decode(encoded_str)
print("Decoded:", decoded_data.decode('utf-8'))
