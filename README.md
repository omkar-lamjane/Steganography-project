# 🖼️ LSB Image Steganography Project

### 🔹 Author: Omkar Lamjane  
### 🔹 Under the guidance of Emertxe Institute and Guruvignesh Sir

---

## 📘 Project Overview

This project is based on **LSB (Least Significant Bit) Image Steganography**.  
It allows us to **hide a secret file (like .txt, .c, .h, .sh)** inside a **.bmp image file** without changing the way the image looks.

It has two main operations:

- **Encoding** – Hiding the secret file inside a BMP image.  
- **Decoding** – Extracting the hidden file back from the image.

---

## 🧠 What is Steganography?

**Steganography** is the technique of hiding one file inside another in such a way that others cannot detect it.  
For example, you can hide a secret text file inside an image file — and the image will still look the same.

In this project, I used the **LSB technique** — which means data is hidden in the **least significant bit** of each pixel in the image.

We use LSB because changing the last bit of a pixel **does not visibly affect the image**,  
so the hidden message remains secret without anyone noticing.

---

## 🧩 What is Encoding and Decoding?

- **Encoding** means **hiding** the secret file inside the image using bits.
- **Decoding** means **retrieving** that hidden file back from the image.

---

## 🔐 Encoding vs Encryption

| Feature | Encoding | Encryption |
|----------|-----------|-------------|
| **Purpose** | To hide or represent data in another form. | To secure data so only authorized users can read it. |
| **Goal** | Make data hidden or less noticeable. | Make data unreadable without a key. |
| **Focus** | Hiding the *existence* of data. | Protecting the *contents* of data. |
| **Example in this project** | Hiding secret.txt inside image.bmp | Locking secret.txt using a password |

🧠 **Simple way to remember:**  
> Encoding hides the message,  
> Encryption locks the message.

---

## ⚙️ Features

✅ Hide any text-based file (.txt, .c, .h, .sh) inside a BMP image  
✅ Decode and recover the exact same secret file  
✅ Works using LSB bit manipulation  
✅ Maintains the original appearance of the image  
✅ Step-by-step process shown on terminal

---

## 🧾 Encoding Flow

-> Files opened ✅
-> Capacity checked ✅
-> Header file copied ✅
-> Encoded Magic String ✅
-> Encoded secret file extension size ✅
-> Encoded secret file extension ✅
-> Encoded secret file size ✅
-> Encoded secret file data ✅
-> Copied remaining image data ✅

🔒 secret.txt is encoded successfully into navin.bmp ✅
yaml
Copy code

---

## 🧾 Decoding Flow

-> File opened : navin.bmp ✅
-> Decoded Magic string : #* ✅
-> Decoded Size of Extension : 4 ✅
-> Decoded Extension : .txt ✅
-> Decoded Output File Name : default.txt ✅
-> Decoded Size of secret file : 36 ✅

🔓 navin.bmp is decoded successfully into default.txt ✅
yaml
Copy code

---

## 🧰 Tools and Technologies Used

- **Language:** C  
- **Concepts:** File Handling, Bitwise Operations, Command-Line Arguments  
- **Compiler:** GCC  
- **Platform:** Linux

---

## ▶️ How to Run

### **Encoding**
$ ./a.out -e beautiful.bmp secret.txt stego.bmp

markdown
Copy code
- `-e` → Encode mode  
- `beautiful.bmp` → Source image  
- `secret.txt` → File to hide  
- `stego.bmp` → Output encoded image

### **Decoding**
$ ./a.out -d stego.bmp output.txt

yaml
Copy code
- `-d` → Decode mode  
- `stego.bmp` → Encoded image  
- `output.txt` → Recovered file

---

## 🎯 Learning Outcome

- Understood how LSB bits work in pixel data  
- Learned bitwise and file handling operations in C  
- Gained a better understanding of how data hiding and extraction work

---

## 💬 Acknowledgment

I would like to thank **Emertxe Institute** and **Guruvignesh Sir**  
for their continuous guidance and support throughout this project.

---

## 📎 Related Projects

- [📇 Address Book Project] (https://github.com/omkar-lamjane/AddressBook-project)

---

## 📌 Author

**Omkar Lamjane**  
👨‍💻 GitHub: [omkar-lamjane](https://github.com/omkar-lamjane)
