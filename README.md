LSB Image Steganography Project
Author: Omkar Lamjane
Under the guidance of Emertxe Institute and Guruvignesh Sir
Project Overview

This project is based on LSB (Least Significant Bit) Image Steganography.
It allows hiding a secret file (such as .txt, .c, .h, .sh) inside a BMP image file without altering the visible appearance of the image.

The project supports two main operations:

Encoding – Hiding the secret file inside a BMP image

Decoding – Extracting the hidden secret file back from the image

What is Steganography?

Steganography is a technique used to hide one file inside another in such a way that the existence of the hidden file is not noticeable.

In this project, the LSB technique is used, where secret data is embedded into the least significant bit of each pixel in the image.

Since changing the least significant bit does not create a visible difference in the image, the hidden data remains undetectable to the human eye.

Encoding and Decoding

Encoding refers to hiding the secret file inside an image using bit-level manipulation.

Decoding refers to extracting the hidden secret file back from the encoded image.

Encoding vs Encryption
Feature	Encoding	Encryption
Purpose	Hide data inside another medium	Secure data using a key
Goal	Conceal the existence of data	Prevent unauthorized access
Focus	Data hiding	Data protection
Example	Hiding secret.txt inside image.bmp	Locking secret.txt with a password

Simple rule:
Encoding hides the message, while encryption locks the message.

Features

Supports hiding text-based files (.txt, .c, .h, .sh)

Allows complete recovery of the original secret file

Uses LSB-based bitwise manipulation

Preserves the original image appearance

Displays step-by-step execution on the terminal

Encoding Flow

-> Files opened successfully
-> Image capacity verified
-> BMP header copied
-> Magic string encoded
-> Secret file extension size encoded
-> Secret file extension encoded
-> Secret file size encoded
-> Secret file data encoded
-> Remaining image data copied

The secret file is successfully embedded into the output image.

Decoding Flow

-> Encoded image file opened
-> Magic string decoded
-> Secret file extension size decoded
-> Secret file extension decoded
-> Output file name generated
-> Secret file size decoded
-> Secret file data extracted

The encoded image is successfully decoded and the secret file is recovered.

Tools and Technologies Used

Programming Language: C

Concepts Used: File Handling, Bitwise Operations, Command-Line Arguments

Compiler: GCC

Operating System: Linux

How to Run
Encoding
./a.out -e beautiful.bmp secret.txt stego.bmp


-e specifies encode mode

beautiful.bmp is the source image

secret.txt is the file to be hidden

stego.bmp is the output encoded image

Decoding
./a.out -d stego.bmp output.txt


-d specifies decode mode

stego.bmp is the encoded image

output.txt is the recovered secret file

Learning Outcome

Understood LSB manipulation in image pixel data

Gained hands-on experience with bitwise operations in C

Improved knowledge of binary file handling

Learned practical data hiding and extraction techniques

Acknowledgment

I would like to sincerely thank Emertxe Institute and Guruvignesh Sir
for their continuous guidance and support throughout this project.

Related Projects

Address Book Project
https://github.com/omkar-lamjane/AddressBook-project

Author

Omkar Lamjane
GitHub: https://github.com/omkar-lamjane
