#include <stdio.h>
#include<string.h>
#include "decode.h"
#include "types.h"
#include<unistd.h>
#include "common.h"

/*Function definitions*/

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    //check first character (content file name is there or not (before .))
    if((argv[2][0] != '.' ))
    {
        //validate source file extention is having .bmp or not (with strstr)
        if(strstr(argv[2],".bmp") != NULL)
        {
            //store name of encoded file in encode fname
            decInfo->encode_fname = argv[2];
        }
        else
        {
            printf(" ❌ Error : .bmp encoded file is required ...!\n");
            return e_failure;
        }
    }
    else
    {
        printf(" ❌ Error : for decoding file name is must...!\n");
        return e_failure;
    }
    if(argv[3] == NULL)
    {
        //if user didn't give output file name then set name as default
        // decInfo->output_fname = "default";
        strcpy(decInfo->output_fname,"default");
        return e_success;
    }
    else
    {
        //check first character (content file name is there or not (before .))
        if(argv[3][0] != '.')
        {
            //if any extension is there then remove that extension
            if(strstr(argv[3],".") != NULL)
            {
                char *name = strstr(argv[3],".");
                *name = '\0';
            }
           
            //only store name of output file
            // decInfo->output_fname = argv[3];
            strcpy(decInfo->output_fname,argv[3]);
            
        }
        else
        {
            printf(" ❌ Error : output file should have name..!\n");
            return e_failure;
        }
    }
    return e_success;
}


Status open_dfiles(DecodeInfo *decInfo)
{
    //open encoded file in read mode
    decInfo->fptr_encode_image = fopen(decInfo->encode_fname,"r");
    if (decInfo->fptr_encode_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, " ❌ Error : Unable to open file %s\n", decInfo->encode_fname);

        return e_failure;
    }
    //skip the header part
    fseek(decInfo->fptr_encode_image,54,SEEK_CUR);
    return e_success;
}


/* Decode Magic String */
Status decode_magic_string(char *magic_string, DecodeInfo *decInfo)
{
    char buffer[8];
    int i;
    for( i=0; i<2; i++)
    {
        if(fread(buffer,8,1,decInfo->fptr_encode_image) != 1)
        {
            return e_failure;
        }
        decode_byte_to_lsb(buffer,&magic_string[i]);
    }
    magic_string[i] = '\0';
    //check magic string is same or not
    if(strcmp(magic_string,"#*")==0)
        return e_success;
    return e_failure;
}

/*Decode extension size*/
Status decode_secret_file_extn_size(int *size, DecodeInfo *decInfo)
{
    // printf("%ld\n",ftell(decInfo->fptr_encode_image));
    char buffer[32];
    //read 32 bytes of encoded image into buffer
    if (fread(buffer, 32, 1, decInfo->fptr_encode_image) != 1)
        return e_failure;
    //pass buffer to decode size from lsb bit from each byte
    decode_size_to_lsb(buffer,size);
    return e_success;
}

/* Decode secret file extenstion */
Status decode_secret_file_extn(char *file_extn, DecodeInfo *decInfo)
{
    char buffer[8];
    int i;
    //decode the extension using for loop upto extension size  
    for( i=0; i<decInfo->size_extn; i++)
    {
        if(fread(buffer,8,1,decInfo->fptr_encode_image)!=1)
        {
            return e_failure;
        }
        decode_byte_to_lsb(buffer,&file_extn[i]);
    }
    file_extn[i] = '\0';
    return e_success;
}

/* Decode secret file size */
Status decode_secret_file_size(long *file_size, DecodeInfo *decInfo)
{
    char buffer[32];
    if(fread(buffer,32,1,decInfo->fptr_encode_image) != 1)
    {
        return e_failure;
    }
    decode_size_to_lsb_long(buffer,file_size);
    return e_success;
}

/* Decode secret file data*/
Status decode_secret_file_data(DecodeInfo *decInfo)
{
    decInfo->fptr_ofile = fopen(decInfo->output_fname,"w");
    if(decInfo->fptr_ofile == NULL)
    {
        printf("\n ❌ Error : while opening the output file for write\n");
        return e_failure;
    }
    char buffer[8];
    char data;
    //get 8 byte once from encoded image in buffer 
    for(int i=0;i<decInfo->size_ofile;i++)
    {
        if(fread(buffer,8,1,decInfo->fptr_encode_image) != 1)
        {
            return e_failure;
        }
        //decode 8 bits from lsb of 8 bytes and store in data
        decode_byte_to_lsb(buffer,&data);
        //write that 1 byte of data in output file
        fwrite(&data,1,1,decInfo->fptr_ofile);
    }
    return e_success;
}

/* Decode image data array's lsb into data */
Status decode_byte_to_lsb(char *image_buffer,char *data)
{
    *data = 0;
    for(int i=0; i<8; i++)
    {
        *data = *data | ((image_buffer[i] & 1) << i);
    }
}

/* Decode image data array's lsb into size */
Status decode_size_to_lsb_long(char *image_buffer,long int *size)
{
    *size = 0;
    for(int i=0; i<32; i++)
    {
        *size = *size | ((image_buffer[i] & 1) << i);
    }
    return e_success;
}

/* Decode image buffer array's lsb into size */
Status decode_size_to_lsb(char *image_buffer,int *size)
{
    *size = 0;
    for(int i=0; i<32; i++)
    {
        *size = *size | ((image_buffer[i] & 1) << i);
    }
    return e_success;
}


/* Perform the decoding */

/* Call functions one by one */
/*  1) open files
    2) decode magic string
    3) decode secret file extension size
    4) decode secret file extension
    5) decode secret file size
    6) decode secret file data
*/

Status do_decoding(DecodeInfo *decInfo)
{
    if(open_dfiles(decInfo)==e_success)
    {
        usleep(1000000);
        printf("\n-> %-30s : %-15s ✅\n", "File opened", decInfo->encode_fname);
        usleep(1000000);
        if((decode_magic_string(decInfo->magic_string,decInfo))==e_success)
        {
            printf("-> %-30s : %-15s ✅\n", "Decoded Magic string", decInfo->magic_string);
            usleep(1000000);
            if((decode_secret_file_extn_size(&decInfo->size_extn,decInfo))==e_success)
            {
                printf("-> %-30s : %-15d ✅\n","Decoded Size of Extension",decInfo->size_extn);
                usleep(1000000);
                if(decode_secret_file_extn(decInfo->extn_ofile,decInfo)==e_success)
                {
                    printf("-> %-30s : %-15s ✅\n","Decoded Extension",decInfo->extn_ofile);
                    usleep(1000000);

                    //after getting the extension name concatinating it to the file name
                    strcat(decInfo->output_fname, decInfo->extn_ofile);

                    printf("-> %-30s : %-15s ✅\n","Decoded Output File Name",decInfo->output_fname);
                    usleep(1000000);

                    if(decode_secret_file_size(&decInfo->size_ofile,decInfo)==e_success)
                    {
                        printf("-> %-30s : %-15ld ✅\n","Decoded Size of secret file",decInfo->size_ofile);
                        usleep(1000000);
                        if(decode_secret_file_data(decInfo)==e_success)
                        {
                            printf("\n-----------------------------------------------------------------------------------------\n");
                            printf("\t\t 🔓 %s is decoded Successfully into %s file ✅\n",decInfo->encode_fname,decInfo->output_fname);
                            printf("-----------------------------------------------------------------------------------------\n");
                            return e_success;
                        }
                        else
                        {
                            printf(" ❌ Error : while decoding secret file data\n");
                            return e_failure;
                        }
                    }
                    else
                    {
                        printf(" ❌ Error : while decoding secret file size\n");
                        return e_failure;
                    }
                }
                else
                {
                    printf(" ❌ Error : while decoding secret file extension\n");
                    return e_failure;
                }
            }
            else
            {
                printf(" ❌ Error : while decoding size of secret file extension\n");
                return e_failure;
            }
        }
        else
        {
            printf(" ❌ Error : while decoding magic string\n");
            return e_failure;
        }
    }
    else
    {
        printf(" ❌ Error : while opening the file\n");
        return e_failure;
    }
}