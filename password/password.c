// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int i;
    bool upper = 0;
    bool lower = 0;
    bool number = 0;
    bool symbol = 0;
    for (i = 0; password[i] != '\0'; i++)
    {
// Validate upper case
        if (password[i] >= 65 && password[i] <= 90)
        {
            upper = 1;
        }
// Validate lower case
        else if (password[i] >= 97 && password[i] <= 122)
        {
            lower = 1;
        }
// Validate number
        else if (password[i] >= 48 && password[i] <= 57)
        {
            number = 1;
        }
// Validate symbol
        else if (password[i] >= 32 && password[i] <= 47)
        {
            symbol = 1;
        }
        else if (password[i] >= 58 && password[i] <= 126)
        {
            symbol = 1;
        }
    }
    if (upper == 1 && lower == 1 && number == 1 && symbol == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
