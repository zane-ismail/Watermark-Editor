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
    for (i = 0; password[i] != '\0'; i++)
    printf("%i\n", password[i]);
// Validate upper case
    if (password[i] >= 65 && password[i] <= 90)
    {
        return true;
    }
// Validate lower case
    else if (password[i] >= 97 && password[i] <= 122)
    {
        return true;
    }
// Validate number
    else if (password[i] >= 48 && password[i] <= 57)
    {
        return true;
    }
// Validate symbol
    else if (password[i] >= 32 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 126)
    {
        return true;
    }
    return false;
}
