// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

// a = 6
// e = 3
// i = 1
// o = 0

int main(int argc, string argv[])
{
    printf("%i\n", argc);
    // Validate 1 word
    if (argc == 2)
    {
        printf("Okay!\n");
        int i;
        int length = 4;
        for (i = 0; i < length; i++)
            {
                char j = argv[1][i];
                if (j == 'a' || (j == 'e') || (j == 'i') || (j == 'o'))
                {
                    j = (j - 98);
                    printf("%i\n", j);
                }
                else
                {
                    printf("%c\n", argv[1][i]);
                }
            }



            //     else if (j == 'e')
            //     {
            //         j = 3;
            //     }
            //     else if (j == 'i')
            //     {
            //         j = 1;
            //     }
            //     else if (j == o)
            //     {
            //         j = 0;
            //     }
            //     printf("%s\n", argv[i]);
            // }
        // for (i = 0; i < argc; i++)
        // int replace(argv[i]);


    // }
    // else
    // {
    //     printf("Oopy doopsy!\n");
    // }
    return 0;
    }
}

// int replace(main)
// {
//     int argv = argv;
//     return argv;
// }