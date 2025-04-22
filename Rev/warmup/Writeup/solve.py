import hashlib

iArr = [93, 58, 5, 62, 15, 98, 66, 27, 66, 24, 2, 8, 25, 33, 55, 48, 37, 1, 99, 35, 39, 9, 92, 9, 48, 98, 5, 86]
iArr2 = [30, 105, 73, 69, 101, 86, 52, 47, 29, 40, 96, 110, 108, 20, 84, 4, 81, 48, 83, 77, 120, 100, 104, 122, 68, 81, 119, 43]

flag = "".join(chr(iArr[i] ^ iArr2[i]) for i in range(len(iArr)))

hash_object = hashlib.sha256(flag.encode())
flag_hash = hash_object.hexdigest()

if flag_hash == "802cf0b334d6a76bd4cb7fbb160913a5c412a92887d5005ceee151e380a2775e":
    print(f"Correct flag: {flag}")
else:
    print("Flag does not match hash.")
