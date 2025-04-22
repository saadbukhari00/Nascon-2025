def reverse_in_chunks(s):
    chunk_size = 11
    num_chunks = 4  
    
    total_length = chunk_size * num_chunks
    s = s[:total_length]  
    
    chunks = [list(s[i:i+chunk_size]) for i in range(0, total_length, chunk_size)]
    reversed_chunks = [chunk[::-1] for chunk in chunks]  

    return ''.join([''.join(chunk) for chunk in reversed_chunks])

s = "si_tahw{LSCcneics_eht_i_ecneics_e}nam_eht_s"
reversed_s = reverse_in_chunks(s)
print(reversed_s)