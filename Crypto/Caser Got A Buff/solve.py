import string

def decrypt_caesar_buff(encrypted_message, start_key):
    decrypted_message = []
    key = start_key
    i = 0

    while i < len(encrypted_message):
        char = encrypted_message[i]

        # Check if the character is a letter or digit
        if char.isalpha():
            if char.isupper():
                shifted_char = chr(((ord(char) - ord('A') - key) % 26) + ord('A'))
            else:
                shifted_char = chr(((ord(char) - ord('a') - key) % 26) + ord('a'))
        elif char.isdigit():
            shifted_char = chr(((ord(char) - ord('0') - key) % 10) + ord('0'))
        else:
            shifted_char = char

        # Append the decrypted character
        decrypted_message.append(shifted_char)

        # Skip the random characters after the shifted character
        i += 1 + key
        key += 1

    return ''.join(decrypted_message)

# Test the decryption function by brute-forcing the starting key
encrypted_message = "GY1nWXJoEuBRvOyGNg{Fn7gAq0BMOUY1WlbQ46lFWR7AP1nMIod8LeMv$XVlr50yR22v_WK3lDl75C1e0OEzRW10lXRHck7iPEAcmBtRFzbwtkuCJsMsS6NJeGfdPLVxg5iU4lyGyDC7dw6_FEJghFjYXfMJVNzSH9JcpaBCIfFtHJrPMR05$Wp3HitKaYZON7hEDSwp_gUSz61CSZZd63RpHek4eBcB9IR989qQIrVEwYziB8YnOtsDrocPUQ0UE4dG97wsN86J3KsAQfCJUjhzvhKcdtLCxp8h9Gp1bRHepYjpaZPHyY440B2Su7CIskDZnAUxqkkyqZBmr0M8g_tWgAfzu8k8UYZvZgUyOB2ZkCD46Vf27xsgCzG7ZvsBVaZCTdqzcp57ccaZecHvwqtkXDIqc1Z6zCtmIKqrZ9EVVJQUlsxe4xvRr1MlekcqnBEqvGT3fk3FGIrkHBdHAgGfMvg9pRmXAtVZpB97islEvs7NC4K9vriGKuRF6zau4zCnBH24JIR15x4aUxQaXRShqJbn2N7wVAyWIgj2hLCdQhdkCJIuxz4MoL0Xg9SXvC1eDhkid4BTq9gGW2jqTxCCCh2U7w2JywaqrB6uNhgy4pPmJQSkNgCcGP4NTVIPGDBCwgS8tnCxzasr6j7Ga5RqLlYvwVjdMC9EuNl3S9o7wbwsUVzi50ypqnYVC2ySpbv92jFIhbcbf76YBfmqFvIr9Hw0RaK8JOCWJgOQLUfm5EQvJE5AryQwsI7rqxEkCZppCK2pKixi2htn6mUGKwRzBFJzGgT88lX7EO2OQX8cgoAByAEAAADfAKXYbgfAsUuTf6Ip2tcCWy5RFt59jPJW1upHJNUvskl0mc0nk9mgk2CmWjv0LgQWvqleJ1qrswmDNegZGp4dAAgzH2Lx4X7F2MbXD5LUXKc0DonM0jU6O2M1G2jZ3ooM65inQ3nWODvb0JCKKkyoVAVleN1N47lYg9ifbJNKFTsSZmB6M6eNeIadAZrZTPJRiUb3gULfd0eqBKFFo6dYKkPPLXNrZd1HzRbqh9jS3jS2vnSGhxrODfeuUAccyE7xScTGYIEZIB22e2thLIcqsrQsEYmuyRIPIWpvgx61O3yeFb71ZEaMWMM9aKlR0DblN7tMNzPPVBHF2xsSMOzXpG0RUeyd8nZkZ2nrapNlXEPP4C3WDFxXpxQoFuoQhINsa4WZaFL0U9es7cFS8cBLNGZ3qdm7dboxTEa6UMvwxNPIS7YeMjolld41OzZ0WApg4zFz66b1BIgBAm9cNtFcex6OGkPlaKlwewRdB7xQ1wVY6c4Nr63zgu4ujpRICUL6huiGtKsdLtDnK8zoss028rcTSrdzt8v3a8ZReJ2l9sPQEaIzoucr4cQdXNAZzaLyssahiFHcCXR2MaOQaQEJLdZbXYyargjIaXXbEA1aMLxydFWqW9FpShYlQkBlTZJLxUgOWXSEQ4E7kKrQZNbWXPrAIKWERgYBYg9ft9W4Xbtok2eht3EwaEj1OhYr7XSjWH5yn7EWjIanqhdpgpNTS9qVV2WBLZ8vOFG0eQkQX1upwEw2pi0jHuJLEX9n1OoPbMRqlB1rZabfvEbGwAGMhPpJJcItEgR9xsEhbMGiC2bP4nsdm5i3HYKsCIJwmPEbwzs18SVtx0VhIzqulvtWiBZbCsysUDTm7a97a6lIvrIw60m53RbysM7nyF9SYQXTvR0E37CYE927wQBk8vhSjDY792QVU0dsobOvghtBmRIWGQI7RtRWBzzA9F0ugFP7NSDNIGQJLxEYPrFMR2w2fES7REx0TstmwTnJlff0QAMQnMd9r5yfSxSZmQlKBH3snepQL7wlYfLBmAdJV12A9CuZv9dokaD0Y2tJAcPJY3JawfjpFViHaDs4twFVXzMIMS6356gAg5IhRvQvi44qukm7RdzB8cSosF2B029P9cbVyzIaX2npoTtygvDBauUmfc1vTlh0Fe9vSuT4K5aiBmSXZ9giU5pUugcydUqcJdjwOOOljgFLGxHKNjb4Y5QrK7oS6jjOTtIL37Ts33QJjbLowmNEUt7mxNGAD318nFP3l8iFJiDbfBq40bVdXvcz0xBZt58zJMJgP5tdXeZKcfU2C5uLc895EhgpIKPXoendgxKXdUSUsGJLvtkzXKfUnpA6RJpPDzRV6eQUHa8Iz0InfU7b26ek15UQo2TObhXQRuqQvC5zl6kBpBHogmpYnYdf8PX1o7sjrMH8PewfwUClK8vBR2cjtejA_sR8plNK7WYX5gGJDJZukFQ1jwqWXyHaN4uRSV7XbGdtMDgfEjWixdBbRYaBEw19Z8yd1F04UvyoFr6PNxjWh3nEUUR2cioyF8daWVngSlAUyrsCvehlDPKaDPN3fuyQijg5JXwCY}LRM2jd2r0Ae1IfbKqyCeKTzjHHDqHF30aeZ6OsdXYpr1AhSq3TRExPd6o8GqbHjeR2H4M"
# Attempt decryption with starting keys from 1 to 3
for starting_key in range(1, 10):
    decrypted_flag = decrypt_caesar_buff(encrypted_message, starting_key)
    print(f"Starting Key {starting_key}: {decrypted_flag}")
