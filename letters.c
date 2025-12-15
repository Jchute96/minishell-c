/*
Author: Jordan Chute
Program Description: This program prints to the screen every letter of the alphabet in lowercase
 */
#include <stdio.h>

int main() {

    char letter = 'a';
    
    // Print every lowercase letter of the alphabet from a-z
    for (int i = 0; i < 26; i++) {
        printf("%c", letter);
        letter++;
    }

    printf("\n");

    return 0;
}