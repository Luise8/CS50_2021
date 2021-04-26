#include <stdio.h>
#include <cs50.h>
int main(void)
{
    //here ask your name, and save in the variable nombre
    string nombre = get_string("What is your name?\n");
    //now say hello + your name (variable nombre)
    printf("hello, %s\n", nombre);
}
