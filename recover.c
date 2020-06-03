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
    //allocate an array with 8 spaces for the name of the jpg. 3 for digis *** + 4 for .jpg + 1 for \0
    char jpegname[8];
    int count = 0;
    
    FILE *jpeg; 
    while(fread(buffer, 512, 1, file)==1)
    {
    
        if(buffer[0]== 0xff && buffer[1]==0xd8 && buffer[2]== 0xff)
            {
                if(count>0)
                { fclose(jpeg); 
                    
                }
                
            count++;
            sprintf(jpegname, "%03d.jpg", count-1);
            
           jpeg = fopen(jpegname, "w");
                    if(jpeg == NULL)
                        {
                        printf("Image cannot be opened.");
                        return 1;
                        }
            
            fwrite(buffer, 512, 1, jpeg);
            }
            else
            fwrite(buffer, 512, 1, jpeg);
            
           
        
    }

    
printf("%i",count);

}
