LSB Image Steganography Project

Author: Omkar Lamjane
Guidance: Emertxe Institute, Guruvignesh Sir

1. Project Overview

This project implements LSB (Least Significant Bit) Image Steganography using the C programming language.

It allows hiding a secret text-based file inside a BMP image without affecting the visible appearance of the image.

Supported Operations

Encoding – Hide a secret file inside an image

Decoding – Extract the hidden file back from the image

2. What is Steganography?

Steganography is the technique of hiding data inside another file so that the existence of the data is concealed.

Why LSB Technique?

Uses the least significant bit of image pixels

Visual quality of image remains unchanged

Hidden data is difficult to detect

3. Encoding vs Decoding
Encoding

Converts secret file into binary

Embeds binary data into image LSBs

Decoding

Reads LSBs from encoded image

Reconstructs the original secret file

4. Encoding vs Encryption
Aspect	Encoding	Encryption
Purpose	Hide data	Secure data
Visibility	Data existence hidden	Data visible but unreadable
Key required	No	Yes
Used here	Yes	No

Remember:
Encoding hides data, encryption locks data.

5. Features

Supports .txt, .c, .h, .sh files

Uses LSB bit manipulation

Original image appearance preserved

Complete recovery of secret file

Command-line based execution

6. Encoding Process
1. Open source image and secret file
2. Check image capacity
3. Copy BMP header
4. Encode magic string
5. Encode secret file extension
6. Encode secret file size
7. Encode secret file data
8. Copy remaining image data


Result:
Secret file is successfully encoded into the image.

7. Decoding Process
1. Open encoded image
2. Decode magic string
3. Decode extension size
4. Decode extension
5. Decode secret file size
6. Extract secret file data


Result:
Secret file is successfully recovered.

8. Tools and Technologies

Language: C

Concepts: File handling, Bitwise operations

Compiler: GCC

Platform: Linux

9. How to Run
Encoding
./a.out -e beautiful.bmp secret.txt stego.bmp


Arguments:

-e → Encode mode

beautiful.bmp → Source image

secret.txt → File to hide

stego.bmp → Output image

Decoding
./a.out -d stego.bmp output.txt


Arguments:

-d → Decode mode

stego.bmp → Encoded image

output.txt → Recovered file

10. Learning Outcome

Learned LSB manipulation in images

Understood binary file handling

Improved bitwise programming skills

Gained practical steganography knowledge

11. Acknowledgment

Thanks to Emertxe Institute and Guruvignesh Sir
for guidance and support throughout this project.

12. Author

Omkar Lamjane
GitHub: https://github.com/omkar-lamjane
