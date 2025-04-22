# 						Shadows Of NaSCon 2025

## 			Steganography Challenge "Inaudible Ink" Writeup

#### Category: Easy

The challenge comes with a file `s3cr3t.wav`

<img src="/home/abrar/.config/Typora/typora-user-images/image-20250309144043408.png" alt="image-20250309144043408" style="zoom:45%;" />

`s3cr3t.wav`is a WAVE audio file. After analyzing, it sounds like Morse code so let's use an online Morse code audio decoder.

<img src="/home/abrar/Pictures/Screenshots/Screenshot From 2025-03-09 03-56-47.png" style="zoom:30%;" />

Upon decoding the audio file, we obtain the following string.

`THREE MAY KEEP A SECRET, IF TWO OF THEM ARE DEAD.`

So looks like this isn't the flag, lets have another look at the description of the challenge.

```
During a raid on a BlackCell APT group's hideout, investigators recovered an oLd radio transmitter.
Among the debriS was an audio file laBeled 'Inaudible Ink'. The ....
```

Hmm..., for some reason the letters L,S and B are capitalized where they shouldn't be, is this a hint towards "LSB"? It could be that the flag is hidden in the least significant bits of the WAVE audio file. But before we proceed further, lets understand quickly how LSB steganography works in audio files.

- In a `.wav` file, the audio is represented as a series of **samples**.
- Each sample is a numerical value that represents the amplitude (loudness) of the audio at a specific point in time.
- The **sample rate** (e.g., 11.050 kHz) determines how many samples are taken per second.
- The **bit depth** (e.g., 8-bit) determines the precision of each sample. For example, in a 8-bit audio file, each sample is represented as a 8-bit (1 byte) integer.

```bash
>> file s3cr3t.wav
s3cr3t.wav: RIFF (little-endian) data, WAVE audio, Microsoft PCM, 8 bit, mono 11050 Hz
```

Our `s3cr3t.wav` has a bit depth of 8 bits so each sample is 1 bytes, so our flag could be hidden in the LSBs of the samples of our `s3cr3t.wav` audio file.

To extract the LSBs from our audio file we will use a python tool called Stegolsb, you can read more about it [here](https://github.com/ragibson/Steganography).

We will extract the LSBs using this command and output them into `extracted_flag.txt`.

```bash
>> stegolsb wavsteg -r -i s3cr3t.wav -n 2 -o extracted_flag.txt -b 50
Files read                     in 0.00s
Recovered 50 bytes             in 0.00s
Written output file            in 0.00s
```

> [!NOTE]
>
> To use this tool, `pip install stegolsb` in a python virtual environment

```bash
>> cat extracted_flag.txt 
UT......
```

Lets put this encoded string on [cyberchef](https://gchq.github.io/CyberChef/).

It was base64 encoded two times and after decoding it we got the flag.