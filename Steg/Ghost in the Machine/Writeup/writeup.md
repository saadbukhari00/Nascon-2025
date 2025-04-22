# 						Shadows Of NaSCon 2025

## 			Steganography Challenge "Ghost in the Machine" Writeup

#### Category: Easy

This challenge comes with an audio file `audio001.wav`

Upon listening to it seems like the dial tones you hear when dialing numbers on a phone. After a few searches on Google it looks like it could be a DTMF file. 

------

**DTMF**  **(Dual-Tone Multi-Frequency)** is the technology behind the tones you hear when you press  buttons on a telephone keypad. It uses pairs of audio tones to represent numbers, letters, and symbols. Here's how it works:

1. **Two Tones for Each Button:**
   Each button on the keypad corresponds to a unique pair of frequencies:
   - One frequency from a **low-frequency group** (697 Hz, 770 Hz, 852 Hz, 941 Hz).
   - One frequency from a **high-frequency group** (1209 Hz, 1336 Hz, 1477 Hz, 1633 Hz).
2. **Combination of Frequencies:**
   For example:
   - Pressing **1** sends a combination of **697 Hz** (low) and **1209 Hz** (high).
   - Pressing **5** sends **770 Hz** (low) and **1336 Hz** (high).
3. **16 Possible Signals:**
   The system can represent 16 different signals:
   - The numbers **0-9**.
   - The letters **A, B, C, D** (used for special purposes).
   - The symbols **#** and *****.
4. **Why It’s Useful:**
   - The tones are within the **voice frequency range**, so they can travel over phone lines, radio, and other communication systems.
   - They can pass through repeaters and amplifiers, making them reliable for long-distance communication.



------

This kind of file can be decoding using the Linux command line tool `multimon-ng` .

Lets decode it using the tool.

![image-20250309234635037](/home/abrar/.config/Typora/typora-user-images/image-20250309234635037.png)

> [!NOTE]
>
> `sudo apt install multimon-ng` to install the tool.

To decode use this command

```bash
multimon-ng -t wav -a DTMF audio001.wav
```

Decoding the DTMF audio file gives us this list of decoded numbers which look like ASCII text codes and the # symbol seems to separate them.

When we convert the ASCII text codes to text, it finally gives us the flag

`d......`

We put the flag inside the correct format

`CSL{d.......}` 

------

