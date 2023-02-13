#include "crunch.h"
#include <string.h>

/* This program randomly combines words contained in its input stream and sends them 
to the output stream. At program execution, the application shall read in the entire set of words 
to use during the combination process. After reaching the EOF symbol, the program shall then 
begin randomly selecting words and combining them into a concatenated output word. By 
default, the program produces only one combined output word for each execution, but users 
may change this behavior by providing an optional command line argument (through *argv). 
The words the program selects must meet minimum length criteria, and users may also 
change this value at program execution to meet their needs. The program must accept this.
 By default, the program squeezes the words together and omits any spacing between 
them (e.g., somewhatlikethisbutrandom), but users may override this behavior with a command 
line argument as well, and the program will produce output with the user specified parameter.
The command line arguments may appear in any order.

 When unable to construct strings meeting the minimum length from the input stream, 
the program shall alert the user to an error and suggest corrective action.
 There shall be no duplicate words in any single output combination, but the same word 
may appear twice in the total output when producing more than one string (i.e. -n specified >1)

Program Name: crunch
Command Line Args: -d <degree> Number of words from input stream to combine in each 
crunched output (default =4). 
-m <size> The minimum length of each word used (default =6). 
-n <count> Number of output strings to produce (default =1). 
-s Indicates to insert a space between the output words 
(default=none).
Program Input: stdin
Program Output: stdout
Return: 0 on completion
Allowed Imports: stdio.h stdlib.h time.h */

int strEqual(char* stringOne, char* stringTwo);

int main (int argc, char** argv)
{
    int degreeFlag = 4; // -d
    int sizeFlag = 6; // -m
    int countFlag = 1; // -n
    int spaceFlag = 0; // -s
    int commandStatus;

    for (int i = 0; i < argc; i++) 
    {
            if (strEqual(argv[i], "-d") == 1)
            {
                if (!((i + 1) > (argc - 1)))
                {
                    degreeFlag = atoi(argv[i+1]);
                }
                printf("degreeFlag = %d\n", degreeFlag); 
            }
            if (strEqual(argv[i], "-m") == 1)
            {
                if (!((i + 1) > (argc - 1)))
                {
                    sizeFlag = atoi(argv[i+1]);
                }
                printf("sizeFlag = %d\n", sizeFlag); 
            }
            if (strEqual(argv[i], "-n") == 1)
            {
                if (!((i + 1) > (argc - 1)))
                {
                    countFlag = atoi(argv[i+1]);
                }
                printf("countFlag = %d\n", countFlag); 
            }
            if (strEqual(argv[i], "-s") == 1)
            {
                spaceFlag == 1;
                printf("spaceFlag = %d\n", spaceFlag);
            }
    }

    return 0;

}

int strEqual(char* stringOne, char* stringTwo)
{
    int equal = 1;
    int i = 0;
    while (*stringOne)
    {
        // if characters differ, or end of the second string is reached
        if (*stringOne != *stringTwo) {
            equal = 0;
        }
 
        // move to the nestringOnet pair of characters
        stringOne++;
        stringTwo++;
    }
    return equal;
}