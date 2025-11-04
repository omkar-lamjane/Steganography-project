#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"
#include "common.h"
#include <unistd.h>

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    //printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    //printf("height = %u\n", height);
    

    // Return image capacity
    return width * height * 3;
}

uint get_file_size(FILE *fptr)
{
    // Find the size of secret file data
    fseek(fptr,0,SEEK_END);
    return ftell(fptr);
}

/*
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    //check first character (content file name is there or not (before .))
    if((argv[2]-strstr(argv[2],".")) != 0)
    {
        //validate source file extention is having .bmp or not (with strstr)
        if(strstr(argv[2],".bmp") != NULL)
        {
            //encInfo -> src_image_fname = argv[2]
            encInfo->src_image_fname = argv[2];
            // return e_success;
        }
        else
        {
            //return e_failure
            printf(" ❌ Error : Source file should have .bmp extension\n");
            return e_failure;
        }
    }
    else
    {
        //return e_failure
        printf(" ❌ Error : Enter source file name\n");
        return e_failure;
    }
    
    //check first character (content file name is there or not (before .))
    if((argv[3]-strstr(argv[3],".")) != 0)
    {
        //validate source file extention is having (.txt or .c or .h or .sh)
        if(strstr(argv[3],".txt") || strstr(argv[3],".c") || strstr(argv[3],".h") || strstr(argv[3],".sh"))
        {
            //storing secret file name
            encInfo -> secret_fname = argv[3];

            //extracting the extension from content file
            char *add = strstr(encInfo->secret_fname,".");
            strcpy(encInfo->extn_secret_file,add);


            /*
            another method to copy secret file extension
            int i=0;
            while(add[i] != '\0')
            {
                encInfo->extn_secret_file[i] = add[i];
                i++;
            }
            encInfo->extn_secret_file[i] = '\0';
            return e_success;
            */

        }
        else
        {
            //return e_failure
            printf(" ❌ Error : extension should be (.txt or .c or .h or .sh)");
            return e_failure;
        }
    }
    else
    {
        //return e_failure
        printf(" ❌ Error : Content file name should not be empty\n");
        return e_failure;
    }
    
    //Check whether the argv[4] is having NULL or not 
    //if yes 
    if(argv[4] == NULL)
    {
        //encInfo-> stego_image_fname = "default.bmp";
        encInfo-> stego_image_fname = "default.bmp";
        return e_success;
    }
    //if no
    else
    {
        //check first character (content file name is there or not (before .))
        if((argv[4]-strstr(argv[4],".")) != 0)
        {
            //validate source file extention is having .bmp or not (with strstr)
            if(strstr(argv[4],".bmp"))
            {
                //encInfo -> stego_image_fname = argv[4]
                encInfo->stego_image_fname = argv[4];
            }
            else
            {
                //return e_failure
                printf(" ❌ Error : Encoding file should have .bmp extension\n");
                return e_failure;
            }
        }
    }
    return e_success;


}

Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, " ❌ Error : Unable to open file %s\n", encInfo->src_image_fname);

        return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, " ❌ Error : Unable to open file %s\n", encInfo->secret_fname);

        return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, " ❌ Error : Unable to open file %s\n", encInfo->stego_image_fname);

        return e_failure;
    }

    // No failure return e_success
    return e_success;
}

Status check_capacity(EncodeInfo *encInfo)
{
    encInfo -> image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);
    encInfo->size_secret_file = get_file_size(encInfo->fptr_secret);
    // char *extn = strstr(encInfo -> secret_fname, ".txt");
    int ext_size = strlen(encInfo->extn_secret_file);
    int total_bytes = 54 + (strlen(MAGIC_STRING) * 8) + 32 + (ext_size * 8) + 32 + (encInfo ->size_secret_file * 8);
    if(encInfo->image_capacity>total_bytes)
        return e_success;
    else
        return e_failure;


}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    //fread and fwrite upto 54 bytes for copy the header file
    char buffer[54];

    //rewind both file pointer in case if they are not at starting
    rewind(fptr_dest_image);
    rewind(fptr_src_image);
    fread(buffer,54,1,fptr_src_image);
    fwrite(buffer,54,1,fptr_dest_image);

    //validate both file pointer pointing to the same no. of byte
    if(ftell(fptr_src_image) == ftell(fptr_dest_image))
        return e_success;
    else
        return e_failure;
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    char buffer[8];
    //loop for encode magic string for strlen(magic_string) times
    for(int i=0; i<strlen(magic_string); i++)
    {
        fread(buffer,8,1,encInfo->fptr_src_image);
        encode_byte_to_lsb(magic_string[i],buffer);
        fwrite(buffer,8,1,encInfo->fptr_stego_image);
    }

    //validate both file pointer pointing to the same no. of byte
    if(ftell(encInfo->fptr_src_image)==ftell(encInfo->fptr_stego_image))
    return e_success;
    else
    return e_failure;
}
Status encode_secret_file_extn_size(int size, EncodeInfo *encInfo)
{
    char buffer[32];
    fread(buffer,32,1,encInfo->fptr_src_image);
    encode_size_to_lsb(size,buffer);
    fwrite(buffer,32,1,encInfo->fptr_stego_image);

    //validate both file pointer pointing to the same no. of byte
    if(ftell(encInfo->fptr_src_image)==ftell(encInfo->fptr_stego_image))
    return e_success;
    else
    return e_failure;
}

Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    char buffer[8];
    for(int i=0; i<strlen(file_extn); i++)
    {
        fread(buffer,8,1,encInfo->fptr_src_image);
        encode_byte_to_lsb(file_extn[i],buffer);
        fwrite(buffer,8,1,encInfo->fptr_stego_image); 
    }

    //validate both file pointer pointing to the same no. of byte
    if(ftell(encInfo->fptr_src_image)==ftell(encInfo->fptr_stego_image))
    return e_success;
    else
    return e_failure;
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char buffer[32];
    fread(buffer,32,1,encInfo->fptr_src_image);
    encode_size_to_lsb(file_size,buffer);
    fwrite(buffer,32,1,encInfo->fptr_stego_image);

    //validate both file pointer pointing to the same no. of byte
    if(ftell(encInfo->fptr_src_image)==ftell(encInfo->fptr_stego_image))
    return e_success;
    else
    return e_failure;
}

Status encode_secret_file_data(EncodeInfo *encInfo)
{
    //buffer size is of secret file 
    char buffer1[encInfo->size_secret_file];
    rewind(encInfo->fptr_secret);
    //to read and store data of secret onces in buffer
    fread(buffer1,encInfo->size_secret_file,1,encInfo->fptr_secret);
    
        char buffer[8];
        //loop for encoding byte by byte of secret file data upto size_secret_file
        for(int i=0; i<encInfo->size_secret_file; i++)
        {
            fread(buffer,8,1,encInfo->fptr_src_image);
            encode_byte_to_lsb(buffer1[i],buffer);
            fwrite(buffer,8,1,encInfo->fptr_stego_image);
        }
    //validate both file pointer pointing to the same no. of byte
    if(ftell(encInfo->fptr_src_image)==ftell(encInfo->fptr_stego_image))
    return e_success;
    else
    return e_failure;
    
}

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char buffer[1];
    //for copying remaining data from source file to dest file
    while(fread(buffer,1,1,fptr_src) == 1)
    {
        fwrite(buffer,1,1,fptr_dest);
    }
    //validate both file pointer pointing to the same no. of byte
    if(ftell(fptr_src) == ftell(fptr_dest))
        return e_success;
    return e_failure;
}

//encode byte of data to the lsb of imgae_buffer
Status encode_byte_to_lsb(char data, char *image_buffer)    
{
    for(int i=0; i<8; i++)
    {
        image_buffer[i] = ((image_buffer[i] & ~1) | ((data >> i) & 1));
    }
}

//encode size (4 bytes) to the lsb of imagebuffer
Status encode_size_to_lsb(int size, char *imageBuffer)      
{
    for(int i=0; i<32; i++)
    {
        imageBuffer[i] = ((imageBuffer[i] & ~1) | ((size >> i) & 1));
    }
}

/* Perform encoding operation */

/*  1) open files
 *  2) check capacity
 *  3) copy bmp header
 *  4) encode magic string
 *  5) encode secret file extension size
 *  6) encode secret file extension
 *  7) encode secret file size
 *  8) encode secret file data 
 *  9) copy remaining image data 
 */

Status do_encoding(EncodeInfo *encInfo)
{
    // call open_files(encInfo);
    if(open_files(encInfo) == e_success)
    {
        usleep(1000000);
        printf("\n%-40s %2s","-> Files opened","✅\n");
        usleep(1000000);
        //call check capacity(encInfo)
        if(check_capacity(encInfo) == e_success)
        {
            printf("%-40s %2s","-> Capacity checked", "✅\n");
            usleep(1000000);
            //call copy_bmp_header(src file , dest file)
            if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_success)
            {
                printf("%-40s %2s","-> Header file copied", "✅\n");
                usleep(1000000);
                //call encode_magic_string
                if(encode_magic_string(MAGIC_STRING,encInfo)==e_success)
                {
                    printf("%-40s %2s","-> Encoded Magic String", "✅\n");
                    usleep(1000000);
                    //call secret file extn size
                    if(encode_secret_file_extn_size(strlen(encInfo->extn_secret_file),encInfo)==e_success)
                    {
                        printf("%-40s %2s","-> Encoded secret file extension size" ,"✅\n");
                        usleep(1000000);
                        //call secret file ext
                        if(encode_secret_file_extn(encInfo->extn_secret_file,encInfo)==e_success)
                        {
                            printf("%-40s %2s","-> Encoded secret file extension" ,"✅\n");
                            usleep(1000000);
                            //call secret file size
                            if(encode_secret_file_size(encInfo->size_secret_file,encInfo)==e_success)
                            {
                                printf("%-40s %2s","-> Encoded secret file size","✅\n");
                                usleep(1000000);
                                //call secret file data
                                if(encode_secret_file_data(encInfo)==e_success)
                                {
                                    printf("%-40s %2s","-> Encoded secret file data", "✅\n");
                                    usleep(1000000);
                                    //call cpoy remaining date
                                    if(copy_remaining_img_data(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_success)
                                    {
                                        printf("%-40s %2s","-> Copied remaining image data" ,"✅\n");
                                        usleep(1000000);
                                        //return success
                                        return e_success;
                                    }
                                    else
                                    {
                                        printf(" ❌ Error : occurred while copying remaining data...!\n");
                                        return e_failure; 
                                    }
                                        
                                }
                                else
                                {
                                    printf(" ❌ Error : occurred while encoding secret file data...!\n");
                                    return e_failure;   
                                }   
                            }
                            else
                            {
                                printf(" ❌ Error : occurred while encoding secret file size...!\n");
                                return e_failure;   
                            }
                                
                        }
                        else
                        {
                            printf(" ❌ Error : occurred while encoding secret file extension...!\n");
                            return e_failure;
                        }
                            
                    }
                    else
                    {
                        printf(" ❌ Error : occurred while encoding secret file extention size...!\n");
                        return e_failure;
                    }
                }
                else
                {
                    printf(" ❌ Error : occurred while encoding magic string..!\n");
                    return e_failure;
                }
                    
            }
            else
            {
                printf(" ❌ Error : occurred while copying header file...!\n");
                return e_failure;
            }
                
        }
        else
        {
            printf(" ❌ Error : %s file don't have enough size to encode..!\n",(encInfo->src_image_fname));
            return e_failure;
        }
    }
    else
    {
        printf(" ❌ Error : occurred while opening the file !\n");
        return e_failure;
    }
        
}
