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

//declare a pointer 'file' to a file called whose name will be what human types in argv[1]. Open for reading.
    FILE *file = fopen(argv[1], "r");

//check if file opened successfully. if pointer was NULL then ERROR.
    if(file == NULL)
    {
        printf("Image cannot be opened.");
        return 1;
    }

//declaring and allocating a buffer for fread function to read into.
    unsigned char buffer[512];

    //allocate an array with 8 spaces for the name of the jpg. 3 for digis *** + 4 for .jpg + 1 for \0
    //for sprintf function
    char jpegname[8];

    int count = 0;

//declare pointer jpeg which later below I will point to
    FILE *jpeg;

    //fread - 'I will read from the file that pointer *file leads me to, in 512 chunks, and store each chuck in array called 'buffer'. Will read '1' at a time.
    //the output of read is whatever it reads. So i told it to read 1/time, so it returns 1. The condition checks when the end of the file will be reached. EOF will return 0.
    while(fread(buffer, 512, 1, file)==1)
    {

//testing two conditions. Is it a beginning of a JPEG? then do all those things. Otherwise keep going and write more 512Mb blocks in the currently open JPEG file
        if((buffer[0]== 0xff && buffer[1]==0xd8 && buffer[2]== 0xff) && ((buffer[3] & 0xf0) == 0xe0))
            {
                if(count>0)
                //if count>0 this means the picture from last loop hasn't been closed. need to close.
                {
                    fclose(jpeg);
                }

            count++;
            //if conditions are met and the file is JPEG, then i give it a name, same as the current count and store the name in 'jpegname' array (buffer)
            //sprintf, same as fread, uses a buffer array. so it prints a string into an array 'jpegname' that i had previously declared.
            sprintf(jpegname, "%03d.jpg", count-1);

//finally assigning the pointer to the file where i will write my photo. Open a file, with the name store in 'jpegname' array, for writing
           jpeg = fopen(jpegname, "w");
                    if(jpeg == NULL)
                        {
                        printf("Image cannot be opened.");
                        return 1;
                        }

//writing into the file. I am writing from 'buffer', 512Mb at a time (1) and all that is going to the file where the pointer jpeg leads me to
            fwrite(buffer, 512, 1, jpeg);
            }
            else
            fwrite(buffer, 512, 1, jpeg);

    }


printf("%i",count);

}
