// Become familiar wih C syntax
// Learn to debug buggy code

#include <cs50.h>

int main(void)
{
    // Ask for your name and where live
    int name = get_string("What is your name? ");
    int location = get_string("Where do you live? ");

    // Say hello
    print("Hello, %i, from %i!", name, location)
}
