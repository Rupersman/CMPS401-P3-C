// Program-ID: P3.c
// Author: Paogrammers
// OS: Ubuntu 20
// Compiler: GNU C

/*
    This program makes a shell that loops reading a line from standard input and checks the first word of the input line.
    If the first word is one of the following internal commands (or aliases) perform the designated task.
    Otherwise use the standard ANSI C system function to execute the line through the default system shell.

    Commands:
        myclear
            Clear the screen using the system function clear: system("clear")
            The string “clear” is passed to the default command shell for execution.
        mydir <directory>
            List the directory contents (ls -al <directory>)
            You will need to provide some command line parsing capability to extract the target directory for listing.
            Once you have built the replacement command line, use the system function to execute it.
        myenviron
            List all the environment strings
            The environment strings can be accessed from within a program as a global variable.
                extern char **environ;
            The environ is an array of pointers to the environment strings terminated with a NULL pointer.
        myquit
            Quit from the program with a zero return value. Use the standard exit function.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024    // max line buffer
#define MAX_ARGS 64        // max # args
#define SEPARATORS " \t\n" // token sparators

extern char **environ; // environment array

void main()
{
    char user_command[MAX_BUFFER], user_command_to_tokenize[MAX_BUFFER], mydir_directory[MAX_BUFFER] = "";
    char *word;

    printf("Welcome to THE SHELL!\n");

    while (MAX_BUFFER == 1024)
    {
        printf("$ ");

        /*
            Source for %[^\n\r]:
            https://stackoverflow.com/questions/9459490/why-does-strtok-interact-like-this-with-scanf

            A space is added so that user_command isn't filled with "\n" on next iteration
            before the user can input a command
        */
        scanf(" %[^\n\r]", user_command);

        /* Copy inital string since strtok modifies the original variable */
        strcpy(user_command_to_tokenize, user_command);

        /* Read first word and determine if it is a command */
        word = strtok(user_command_to_tokenize, SEPARATORS);
        if (strcmp(word, "myclear") == 0)
        {
            /* If word is myclear: */
            system("clear");
        }
        else if (strcmp(word, "mydir") == 0)
        {
            /* 
                If word is mydir:

                This will extract the directory if it is within quotes.
                Note: quotes are not needed even if directory has spaces 
            */
            word = strtok(NULL, "\"");
            strcat(mydir_directory, "ls -al \""); //mydir_directory: ls -al "
            strcat(mydir_directory, word);        //mydir_directory: ls -al "<directory>
            strcat(mydir_directory, "\"");        //mydir_directory: ls -al "<directory>"
            system(mydir_directory);

            /* Empty the mydir_directory string for repeated use */
            memset(mydir_directory, 0, sizeof(mydir_directory));
        }
        else if (strcmp(word, "myenviron") == 0)
        {
            /* 
                If word is myenviron:

                Credit for below 3 lines: Dr. Kuo Pao Yang 
            */
            char **env = environ;
            while (*env)
                printf("%s\n", *env++); // step through environment
        }
        else if (strcmp(word, "myquit") == 0)
        {
            /* If word is myquit: */
            exit(0);
        }
        else
        {
            /* If command is not recognized, pass to system */
            system(user_command);
        }
    }
}