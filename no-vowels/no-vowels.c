// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

int replace(string argv[]);

int main(int argc, string argv[])
{
    // Validate 1 word
    if (argc == 2)
    {
        replace(argv);
    }
    else
    {
        return 1;
    }

    return 0;
}


int replace(string argv[])
{
    int i;
    int length = 0;
    for (length = 0; argv[1][length] != '\0'; length++);
    for (i = 0; i < length; i++)
        {
            char j = argv[1][i];
            if (j == 'a')
            {
                j = (j - 91);
                printf("%i", j);
            }
            else if (j == 'e')
            {
                j = (j - 98);
                printf("%i", j);
            }
            else if (j == 'i')
            {
                j = (j - 104);
                printf("%i", j);
            }
            else if (j == 'o')
            {
                j = (j - 111);
                printf("%i", j);
            }
            else
            {
                printf("%c", argv[1][i]);
            }
        }
    printf("\n");
    return 0;
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