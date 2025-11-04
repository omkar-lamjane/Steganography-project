#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"
#include "decode.h"
OperationType check_operation_type(char *);

int main(int argc, char *argv[])
{
    

    // Step 1 : Check the argc >= 4 true - > // Step 2 : Call the check_operation_type(argv[1]) == e_encode ))
    if(argc >= 4 && (check_operation_type(argv[1]) == e_encode))
    {
            // Step 3 : Declare structure variable EncodeInfo enc_info
            EncodeInfo enc_info;
            // Step 4 : Call the read_and_validate_encode_args(argv,&enc_info)== e_success)
            if((read_and_validate_encode_args(argv,&enc_info) == e_success))
            {
                printf("\n===========================================\n");
                printf("       🔐 Steganography Encoding\n");
                printf("===========================================\n\n");
                // Step 5 : Call the do_encoding (&encInfo);
                if (do_encoding(&enc_info) == e_success)
                {
                    printf("\n-----------------------------------------------------------------------------------------\n");
                    printf("\t\t🔒 %s is encoded successfully into %s file ✅\n",enc_info.secret_fname,enc_info.stego_image_fname);
                    printf("-----------------------------------------------------------------------------------------\n");
                }
                
            }
            
    }
    // Step 1 : Check the argc >= 2 true - > // Step 2 : Call the check_operation_type(argv[1]) == e_decode ))
    else if(argc >= 2 && (check_operation_type(argv[1]) == e_decode))
    {
            // Step 3 : Declare structure variable DecodeInfo dec_info
            DecodeInfo dec_info;

            printf("\n===========================================\n");
            printf("        🕵‍♂ Steganography Decoding\n");
            printf("===========================================\n\n");

            // Step 4 : Call the read_and_validate_decode_args(argv,&dec_info)== e_success)
            if((read_and_validate_decode_args(argv,&dec_info)==e_success))
            {
                // Step 5 : Call the do_decoding (&dec_Info);
                do_decoding(&dec_info);
            }

    }
    else 
    {
        //for error handling
        if (argc < 2)
        {
            printf("\n👉 Enter ( ./a.out -h ) for usage information\n\n");
            return 0;
        }
        //for usage information
        if (strcmp(argv[1],"-h")==0)
        {
            printf(" 🔒 For Encoding file -\nUsage message - ./a.out <source_file.bmp> <secret_file_name> <optional>\nOptional - <encode_file_name.bmp>\n\n");
            printf(" 🔓 For Decoding file -\nUsage message - ./a.out <encode_file_name.bmp> <optional>\nOptional - <output_file>\n");
        }
    }
    
  
}

OperationType check_operation_type(char *symbol)
{
    // Step 1 : Check whether the symbol is -e or not true - > return e_encode false -> Step 2
    if(strcmp(symbol, "-e") == 0)
        return e_encode;
    // Step 2 : Check whether the symbol is -d or not true - > return e_decode false -> return e_unsupported
    else if(strcmp(symbol, "-d") == 0)
        return e_decode;
    else
        printf("\n👉 Enter ( ./a.out -h ) for usage information\n\n");
        return e_unsupported;
    
}
