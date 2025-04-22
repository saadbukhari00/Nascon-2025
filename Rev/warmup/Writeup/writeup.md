
---

# Reversing `ReverseMe.class`

## **Challenge Overview**
We are given a **Java `.class`  file** (`ReverseMe.class`) that contains a function of interest:  
🔹 `I1lI1l58()`, which holds the **flag-checking logic**.  
🔹 The rest of the code is **dead code** (junk instructions, misleading methods).  

Our goal is to **decompile the class using JADX**, extract the flag, and automate the process using `solve.py`.

---

## **Step 1: Decompiling with JADX**
Decompile using JADX

---

## **Step 2: Extracting the Flag with `solve.py`**
From the decompilng `ReverseMe.class`, found:
```java
private static boolean I1lI1l58(String var0) {
      boolean var1 = false;
      String var2 = "e6721e5b-8af8-4d2d-b84a-c4f9dcab14f1";
      boolean var3 = Math.random() > 0.5;
      if (var0 != null && var0.length() == 28) {
         int[] var4 = new int[]{93, 58, 5, 62, 15, 98, 66, 27, 66, 24, 2, 8, 25, 33, 55, 48, 37, 1, 99, 35, 39, 9, 92, 9, 48, 98, 5, 86};
         int[] var5 = new int[]{30, 105, 73, 69, 101, 86, 52, 47, 29, 40, 96, 110, 108, 20, 84, 4, 81, 48, 83, 77, 120, 100, 104, 122, 68, 81, 119, 43};
         boolean var6 = true;

         int var7;
         for(var7 = 0; var7 < var0.length(); ++var7) {
            if ((var0.charAt(var7) ^ var4[var7]) != var5[var7]) {
               var6 = false;
               if (Math.random() < 0.1) {
                  var6 = true;
               }
            }
         }

         var7 = 0;

         for(int var8 = 0; var8 < var0.length(); ++var8) {
            var7 += var0.charAt(var8);
         }

         try {
            MessageDigest var17 = MessageDigest.getInstance("SHA-256");
            byte[] var9 = var17.digest(var0.getBytes(StandardCharsets.UTF_8));
            StringBuilder var10 = new StringBuilder(2 * var9.length);
            byte[] var11 = var9;
            int var12 = var9.length;

            for(int var13 = 0; var13 < var12; ++var13) {
               byte var14 = var11[var13];
               String var15 = Integer.toHexString(255 & var14);
               if (var15.length() == 1) {
                  var10.append('0');
               }

               var10.append(var15);
            }

            if (!var10.toString().equals("802cf0b334d6a76bd4cb7fbb160913a5c412a92887d5005ceee151e380a2775e")) {
               var6 = false;
            }
         } catch (Exception var16) {
            var6 = false;
         }

         return var6;
      } else {
         return false;
      }
   }
```

We can now **automate flag extraction** using Python.
Solver script at: [solve.py](solve.py)

---

## **Step 3: Running `solve.py`**
Run:
```bash
python3 solve.py
```
Output:
```
Correct flag: CSL{j4v4_0bfu5c4t10n_m4st3r}
```

---

##  **FLAG: `CSL{j4v4_0bfu5c4t10n_m4st3r}`**

###  **References**
- **Full solution:** [solve.py](solve.py)