/*
Author: Jordan Chute
Program Description: This program acts as a shell which allows the user to select certain programs from a menu to be run. Some of the options
                     available to the user include redirecting output of a program to a file and piping output from one program to another.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// Lets us use the creat() later in the program
#include <fcntl.h>

int main(int argc, char **argv) {

    int userInput = 0;
    
    char firstName[50];
    char input[10];

    // Variable used for the forks
    int pid;
    int pid1;
    int pid2;
    // Variable used for file descriptors
    int fd[2];
    // Variables used for file output
    int fileId;

    // Initialize arrays to hold the commands that will be used in the pipes
    char *lettersCmd[] = {"./letters", 0};
    char *userinputCmd[] = {"./userinput", 0};
    char *firstnameCmd[3];

    // Let user loop through menu options and running commands until the user enters 8 to exit
    while (userInput != 8) {
    
        // Display menu options to the user
        printf("\n");
        printf("1 letters\n");
        printf("2 numbers\n");
        printf("3 firstname\n");
        printf("4 userinput\n");
        printf("5 letters > outfile\n");
        printf("6 letters | userinput\n");
        printf("7 firstname | userinput\n");
        printf("8 exit\n");

        fgets(input, 10, stdin);
        userInput = atoi(input);
        printf("\n");
        
        switch (userInput) {

            // If user enters 1 run the letters program
            case 1:
                // Create child process
                pid = fork();
                if (pid == 0) {
                    // Replace child process with letters program
                    execlp("./letters", "letters", (char*) NULL);
                    // If execlp does not work print a message letting user know and exit program
                    fprintf(stderr, "execlp on letters failed\n");
                    exit(1);
                }
                // Wait for child process to finish before proceeding
                wait(NULL);
                break;

            // If user enters 2 run the numbers program
            case 2:
                // Create child process
                pid = fork();
                if (pid == 0) {
                    //Replace child process with numbers program
                    execlp("./numbers", "numbers", (char*) NULL);
                    // If execlp does not work print a message letting user know and exit program
                    fprintf(stderr, "execlp on numbers failed\n");
                    exit(1);
                }
                // Wait for child process to finish before proceeding
                wait(NULL);
                break;

            // If user enters 3 run the firstname program
            case 3:
                // Get user first name to use for argument for firstname program
                printf("Please enter your first name: ");
                fgets(firstName, 50, stdin);
                printf("\n");
                // Create child process
                pid = fork();
                if (pid == 0) {
                    // Replace child process with firstname program and use firstName variable as argument
                    execlp("./firstname", "firstname", firstName, (char*) NULL);
                    // If execlp does not work print a message letting user know and exit program
                    fprintf(stderr, "execlp on firstname failed\n");
                    exit(1);
                }
                // Wait for child process to finish before proceeding
                wait(NULL);
                break;

            // If user enters 4 run the userinput program
            case 4:
                // Create child process
                pid = fork();
                if (pid == 0) {
                    // Replace child process with userinput program
                    execlp("./userinput", "userinput", (char*) NULL);
                    // If execlp does not work print a message letting user know and exit program
                    fprintf(stderr, "execlp on userinput failed\n");
                    exit(1);
                }
                // Wait for child process to finish before proceeding
                wait(NULL);
                break;
            
            // If user enters 5 redirect output of letters to a file called outfile
            case 5:
                // Create child process
                pid = fork();
                if (pid == 0) {
                    
                    // Creates the outfile that will store the redirected output
                    fileId = creat("outfile", 0640);
                    
                    // Verify file has been created, if not print error message and exit
                    if (fileId < 0) { 
                    fprintf(stderr, "Error creating outfile\n");
                    exit(1);
                    }
                    
                    // Redirect the output of the program to our outfile
                    dup2(fileId, fileno(stdout));
                    close(fileId);

                    execlp("./letters", "letters", (char*) NULL);
                    // If execlp does not work print a message letting user know and exit
                    fprintf(stderr, "execlp on the redirection of letters failed\n");
                    exit(1);
                }
                // Wait for child process to finish before proceeding
                wait(NULL);
                break;
            
            // If a user enters 6 take the letters program and pipe it to the userinput program
            case 6:
                
                // Create the pipe that we will use
                pipe(fd);

                // Create first child process
                pid1 = fork();

                if (pid1 == 0) {
                    
                    // Sets fd[1] to write end of pipe receiving standard output from program
                    dup2(fd[1], 1);
                    
                    // Close both file descriptors for process
                    close(fd[0]);
                    close(fd[1]);

                    // Replace child process with program in lettersCmd
                    execvp(lettersCmd[0], lettersCmd);
                    
                    // Exit if command failed
                    fprintf(stderr, "%s failed\n", lettersCmd[0]);
                    exit(1);
                }

                // If fork failed exit the program
                else if (pid1 == -1) {
                    fprintf(stderr, "Fork failed\n");
                    exit(1);
                }

                // Create second child process
                pid2 = fork();

                if (pid2 == 0) {
                    // Sets fd[0] to read of the pipe receiving standard input
                    dup2(fd[0], 0);

                    // Close both file descriptors for process
                    close(fd[0]);
                    close(fd[1]);

                    // Replace child process with program in userinputCmd
                    execvp(userinputCmd[0], userinputCmd);

                    // Exit if command failed
                    fprintf(stderr, "%s failed\n", userinputCmd[0]);
                    exit(1);
                }

                // If fork failed exit the program
                else if (pid2 == -1) {
                    fprintf(stderr, "Fork failed\n");
                    exit(1);
                }

                // Close both file descriptors for the parents process pipe
                close(fd[0]);
                close(fd[1]);

                // Wait for child process to finish
                wait(NULL);
                wait(NULL);

                break;

            // If a user enters 7 take the firstname program and pipe it to the userinput program
            case 7:
                // Get user first name to use for argument for firstname program
                printf("Please enter your first name: ");
                fgets(firstName, 50, stdin);
                printf("\n");

                // Initialize the array used for the firstnameCmd
                firstnameCmd[0] ="./firstname";
                firstnameCmd[1] = firstName;
                firstnameCmd[2] = 0;

                // Create pipe
                pipe(fd);

                // Create first child process
                pid1 = fork();

                if (pid1 == 0) {
                    
                    // Sets fd[1] to write end of pipe receiving standard output from program
                    dup2(fd[1], 1);
                    
                    // Close both file descriptors for process
                    close(fd[0]);
                    close(fd[1]);

                    // Replace child process with program in firstnameCmd
                    execvp(firstnameCmd[0], firstnameCmd);
                    
                    // Exit if command failed
                    fprintf(stderr, "%s failed\n", firstnameCmd[0]);
                    exit(1);
                }

                // If fork failed exit the program
                else if (pid1 == -1) {
                    fprintf(stderr, "Fork failed\n");
                    exit(1);
                }

                // Create second child process
                pid2 = fork();

                if (pid2 == 0) {
                    // Sets fd[0] to read of the pipe receiving standard input
                    dup2(fd[0], 0);

                    // Close both file descriptors for process
                    close(fd[0]);
                    close(fd[1]);

                    // Replace child process with program in userinputCmd
                    execvp(userinputCmd[0], userinputCmd);

                    // Exit if command failed
                    fprintf(stderr, "%s failed\n", userinputCmd[0]);
                    exit(1);
                }

                // If fork failed exit the program
                else if (pid2 == -1) {
                    fprintf(stderr, "Fork failed\n");
                    exit(1);
                }

                // Close both file descriptors for the parents process pipe
                close(fd[0]);
                close(fd[1]);

                // Wait for child process to finish
                wait(NULL);
                wait(NULL);

                break;
            // If user enters 8 exit the program
            case 8:
                exit(0);
                break;
            
            default:
                printf("Invalid input. Please enter a number from 1 to 8.\n");
                break;
        }
    }
    return 0;
}