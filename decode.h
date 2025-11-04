#ifndef DECODE_H
#define DECODE_H

#include<stdio.h>

#include "types.h" // Contains user defined types

typedef struct decodeInfo
{
    char magic_string[3];   //to store decoded magic string
    int size_extn;          //to store size of extension
    char extn_ofile[5];     //to store entension of output file
    long size_ofile;        //to store output file size
    char *encode_fname;     //to store name of input file for decoding
    FILE *fptr_encode_image;//to store address of input file name 
    char output_fname[100];     //to store name of output file
    FILE *fptr_ofile;       //to store address of output file name
} DecodeInfo;

/* Decoding function prototype */

/* Read and validate Decode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Perform the decoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status open_dfiles(DecodeInfo *decInfo);

/* Store Magic String */
Status decode_magic_string(char *magic_string, DecodeInfo *decInfo);

/*Decode extension size*/
Status decode_secret_file_extn_size(int *size, DecodeInfo *decInfo);

/* Decode secret file extenstion */
Status decode_secret_file_extn(char *file_extn, DecodeInfo *decInfo);

/* Decode secret file size */
Status decode_secret_file_size(long *file_size, DecodeInfo *decInfo);

/* Decode secret file data*/
Status decode_secret_file_data(DecodeInfo *decInfo);

Status decode_size_to_lsb_long(char *image_buffer,long int *size);

/* Decode a byte into LSB of image data array */
Status decode_byte_to_lsb(char *image_buffer,char *data);

// Decode a size to lsb
Status decode_size_to_lsb(char *image_buffer,int *size);

#endif