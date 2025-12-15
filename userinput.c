/*
Author: Jordan Chute
Program Description: This program takes user input and changes all of the letters in it to capital letters
 */
#include <stdio.h>
#include <ctype.h>

int main() {

    char userInput[50];

    // Put user input into our userInput Variable 
    fgets(userInput, 50, stdin);
    printf("\n");

    // Parse through each character of the user input and change it to capital letter then print to screen
    for (int i = 0; userInput[i] != '\0'; i++) {
        printf("%c", toupper(userInput[i]));
    }

    printf("\n");

    return 0;

} 