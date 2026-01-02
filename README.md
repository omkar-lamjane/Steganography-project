LSB Image Steganography Project
Author: Omkar Lamjane
Under the guidance of Emertxe Institute and Guruvignesh Sir
Project Overview

This project is based on LSB (Least Significant Bit) Image Steganography.
It allows us to hide a secret file (such as .txt, .c, .h, .sh) inside a .bmp image file without changing the visible appearance of the image.

The project supports two main operations:

Encoding – Hiding the secret file inside a BMP image

Decoding – Extracting the hidden file back from the image

What is Steganography?

Steganography is a technique used to hide one file inside another in such a way that its existence is not noticeable.
For example, a secret text file can be hidden inside an image file while the image continues to look the same.

In this project, the LSB technique is used, where data is hidden in the least significant bit of each pixel in the image.

LSB is chosen because modifying the least significant bit does not cause a visible change in the image, making the hidden data difficult to detect.

What is Encoding and Decoding?

Encoding refers to the process of hiding the secret file inside the image using bit-level manipulation.

Decoding refers to extracting the hidden secret file back from the encoded image.

Encoding vs Encryption
Feature	Encoding	Encryption
Purpose	To hide or represent data in another form	To secure data so only authorized users can read it
Goal	Hide the existence of data	Make data unreadable without a key
Focus	Concealment of data	Protection of data
Example in this project	Hiding secret.txt inside image.bmp	Locking secret.txt using a password

Simple way to remember:
Encoding hides the message, while encryption locks the message.

Features

Supports hiding any text-based file (.txt, .c, .h, .sh) inside a BMP image

Allows decoding and recovery of the original secret file

Uses LSB-based bit manipulation

Maintains the original appearance of the image

Displays a clear step-by-step process on the terminal

Encoding Flow

-> Files opened successfully
-> Image capacity checked
-> BMP header copied
-> Magic string encoded
-> Secret file extension size encoded
-> Secret file extension encoded
-> Secret file size encoded
-> Secret file data encoded
-> Remaining image data copied

Secret file is encoded successfully into the output image.

Decoding Flow

-> Encoded image file opened
-> Magic string decoded
-> Secret file extension size decoded
-> Secret file extension decoded
-> Output file name generated
-> Secret file size decoded
-> Secret file data extracted

Encoded image is decoded successfully and the secret file is recovered.

Tools and Technologies Used

Programming Language: C

Concepts Used: File Handling, Bitwise Operations, Command-Line Arguments

Compiler: GCC

Operating System: Linux

How to Run
Encoding
./a.out -e beautiful.bmp secret.txt stego.bmp


-e indicates encode mode

beautiful.bmp is the source image

secret.txt is the file to be hidden

stego.bmp is the output encoded image

Decoding
./a.out -d stego.bmp output.txt


-d indicates decode mode

stego.bmp is the encoded image

output.txt is the recovered secret file

Learning Outcome

Gained understanding of how LSB manipulation works in pixel data

Learned practical usage of bitwise operations in C

Improved knowledge of file handling and binary file processing

Understood the working of data hiding and extraction techniques

Acknowledgment

I would like to sincerely thank Emertxe Institute and Guruvignesh Sir
for their continuous guidance and support throughout this project.

Related Projects

Address Book Project
https://github.com/omkar-lamjane/AddressBook-project

Author

Omkar Lamjane
GitHub: https://github.com/omkar-lamjane
