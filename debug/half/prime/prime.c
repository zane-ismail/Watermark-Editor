#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // TODO
    if (number > 2)
        {
            if (number < 2)
            {
                return false;
            }
            else if (number == 2 || number == 3)
            {
                return true;
            for (int c = 2;c < number;c++)
            {
            if (number % c != 0)
            {
            return true;
            }
            }
            return false;
}

}
