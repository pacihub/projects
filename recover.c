#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

//ensure the human to type a file name
if(argc != 2)
    {
        printf("Use only one name.");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    
//check if file opened successfully. if pointer was NULL then ERROR.
    if(file == NULL)
    {
        printf("Image cannot be opened.");
        return 1;
    }
    
    
    unsigned char buffer[512];
    char jpegname[8];
    int count = 0;
    
    while (fread(buffer, 512, 1, file) ==1)
    {
    
    
    
    
        for(int i=0; i< 512; i++)
        {   
    
        if(buffer[i]== 0xff && buffer[i+1]==0xd8 && buffer[i+2]== 0xff)
            {
            count++;
            sprintf(jpegname, "%03d.jpg", count);
            
            FILE *jpeg = fopen(jpegname, "w");
                    if(jpeg == NULL)
                        {
                        printf("Image cannot be opened.");
                        return 1;
                        }
            
            fwrite(buffer, 512, 1, jpeg);
            
                    
            }
            
        }
        
    }
    
printf("%i",count);

}
