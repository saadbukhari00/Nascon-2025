# Teleword Puzzle Challenge

## Challenge Overview

In this challenge, you are tasked with connecting to a remote service using **Netcat**. The service continuously sent **teleword puzzles**  that needed to be solved. The puzzles kept coming with random grid size each time until all were correctly solved. Approximately 150.

---

##  Connection Setup

Use the following command to connect to the server:

```bash
nc <IP_ADDRESS> <PORT>
```

Once connected, the server sends grids along with a list of target words. The task was to locate these words in the grid and send back the teleword which is the word made using unused letters.

---

## Automation with `solve.py`


The script handles:

- Reading the puzzle grid and word list from the server.
- Programmatically searching for words in all directions.
- Submitting the correct answers back to the server.
- Repeating this until the flag was received.

You can view the script here:  
👉 [`solve.py`](solve.py)

---

##  Usage 



```bash
python3 solve.py 
```


---


Once all puzzles were solved correctly, the server responded with:
```
Congratulations! You've solved all puzzles
CSL{H3r3_1s_y0ur_r3w4rd_TH3_FLAG_3nj0y!!_9dc9a1e16229676c65a5c2f242477c6964181f2a_6}
```
---
