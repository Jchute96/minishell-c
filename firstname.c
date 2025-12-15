/*
Author: Jordan Chute
Program Description: This program takes a users first name as an argument and prints their first name to the screen
 */
#include <stdio.h>

int main(int argc, char **argv) {

    static char usage[] = "Usage: firstname yourfirstname\n";

    // Verify user only entered two arguments, program name and their first name
    if (argc != 2) {
        fprintf(stderr, "%s", usage);
        return 1;
    }

    // Print user entered argument for their first name
    printf("%s\n", argv[1]);

    return 0;
}