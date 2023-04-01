#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
         start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("End size ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    int current_population = start_size;
    int years = 0;

    while (current_population < end_size)
    {
        current_population = (current_population + (current_population / 3) - (current_population / 4));
        years ++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);
}
