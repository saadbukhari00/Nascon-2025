## **Challenge Overview**
A a binary (`challenge.exe`) that appears to be packed with **UPX**. Our goal is to:  
1. **Unpack** it using `upx`.  
2. **Analyze** it in **Ghidra**.  
3. Identify and reverse a **Custom encoding function which is base80**.  
4. **Write a script (`solve.py`)** to decode the output.
---

## **Step 1: Unpacking with UPX**
First, check if the binary is packed:  
```bash
file challenge.exe
```
Output:
```
challenge.exe: PE32 executable (console) Intel 80386, for MS Windows, UPX compressed, 3 sections
```

Unpack it using:
```bash
upx -d challenge.exe
```
Check again:
```bash
file challenge.exe
```
Now it should show a **normal PE32 executable**.

---

## **Step 2: Reverse Engineering with Ghidra**
1. Open **Ghidra** and load `challenge.exe`.  
2. Look for **suspicious functions** in the `Functions` window.  
3. Find encode function.

### **Key Findings**
The function takes an input string and applies **Base80 encoding** (similar to Base64 but using 80 unique characters).

Pseudo-code:
```c

/* Base80Encoder::encode[abi:cxx11](std::vector<unsigned char, std::allocator<unsigned char> >
   const&) */

Base80Encoder * __thiscall
Base80Encoder::encode[abi:cxx11](Base80Encoder *this,undefined4 param_1,vector<> *param_2)

{
  undefined uVar1;
  uint uVar2;
  uint uVar3;
  undefined *puVar4;
  char *pcVar5;
  byte *pbVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  vector<> local_28 [15];
  allocator local_19;
  byte local_18;
  byte local_17;
  byte local_16;
  byte local_15;
  byte local_14;
  byte local_13;
  ushort local_12;
  uint local_10;
  
  std::vector<>::vector(local_28);
  local_10 = 0;
  while( true ) {
    uVar2 = std::vector<>::size(param_2);
    if (uVar2 <= local_10) break;
    uVar2 = local_10 + 1;
    uVar3 = std::vector<>::size(param_2);
    if (uVar2 < uVar3) {
      puVar4 = (undefined *)std::vector<>::operator[](param_2,local_10);
      uVar1 = *puVar4;
      pcVar5 = (char *)std::vector<>::operator[](param_2,local_10 + 1);
      local_12 = CONCAT11(uVar1,*pcVar5);
      local_13 = *pcVar5 + (char)(local_12 / 0x50) * -0x50;
      local_12 = local_12 / 0x50;
      local_14 = (char)local_12 + (char)(local_12 / 0x50) * -0x50;
      local_12 = local_12 / 0x50;
      local_15 = (byte)local_12;
      std::vector<>::push_back
                (local_28,"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/=@#%&*[]{ }-_$!~`^"
                          + local_15);
      std::vector<>::push_back
                (local_28,"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/=@#%&*[]{ }-_$!~`^"
                          + local_14);
      std::vector<>::push_back
                (local_28,"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/=@#%&*[]{ }-_$!~`^"
                          + local_13);
      local_10 = local_10 + 2;
    }
    else {
      pbVar6 = (byte *)std::vector<>::operator[](param_2,local_10);
      local_16 = *pbVar6;
      local_17 = local_16 / 0x50;
      local_18 = local_16 + ((byte)((uint)local_16 * 0xcd >> 8) >> 6) * -0x50;
      std::vector<>::push_back
                (local_28,"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/=@#%&*[]{ }-_$!~`^"
                          + local_17);
      std::vector<>::push_back
                (local_28,"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/=@#%&*[]{ }-_$!~`^"
                          + local_18);
      local_10 = local_10 + 1;
    }
  }
  std::allocator<char>::allocator();
  uVar7 = std::vector<>::end(local_28);
  uVar8 = std::vector<>::begin(local_28);
  std::string::string<>((string *)this,uVar8,uVar7,&local_19);
  std::allocator<char>::~allocator((allocator<char> *)&local_19);
  std::vector<>::~vector(local_28);
  return this;
}


```

---

## **Step 3: Writing the Decoder (`solve.py`)**
Since we now understand the encoding, we can **reverse it** in Python.  
See [solve.py](solve.py) for the full solution.

---

## **Final Execution**
Now, we can pass the encoded string from the binary to `solve.py`:
```bash
python3 solve.py
```
Output:
```
Decoded: CSL{Cu5t0m_b4s3_80_1s_5un_h4h4!}
```

###  **FLAG: `CSL{Cu5t0m_b4s3_80_1s_5un_h4h4!}`**

---