# Cracking `validator.exe` with Z3 Solver

## **Challenge Overview**
A **Windows binary** (`validator.exe`) that checks if an entered password is correct. Task is to:
1. **Reverse-engineer `validator.exe`** to analyze `passwordChecker` function.
2. Extract the **equations** used to validate the password.
3. **Use Z3 Solver** to compute the correct password.
4. Solve it using `solve.py`.

---

## **Step 1: Analyzing `validator.exe` in Ghidra**
1. Open **Ghidra** and load `validator.exe`.
2. Look at the `checkPassword` function:

## **Step 2: Writing the Z3 Solver Script**
Since we have **multiple equations**, we use **Z3 Solver** (a constraint solver) to find values for `v[0]` to `v[41]` that satisfy all constraints.

See full script in **[solve.py](solve.py)**.

---

## **Step 3: Running `solve.py`**
Execute:
```bash
python3 solve.py
```
Output:
```
Solved password: CSL{P4ssw0rd_Acc3pt3d!!_z3_s4v3d_y0ur_d4y}
```
---
