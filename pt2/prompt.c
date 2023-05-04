/************************************************************************
Project: Norisp
Version: 0.0.1
Author: Norser
Date Created: 05/04/2023
************************************************************************/

//-----------------------------------------------------------------------
// Start preprocessor logic
//-----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------
// If we are compiling on a Windows machine compile these first
//-----------------------------------------------------------------------
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

// Fake readline function
char* readline(char* prompt) {
    //Outputs the parameter
    fputs(prompt, stdout);

    //Gets the users input and adds it to the charater buffer
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    
    return cpy
}

// Fake add_history function
void add_history(char* unused) {}

//-----------------------------------------------------------------------
// Otherwise include the editline headers
//-----------------------------------------------------------------------
#else 

#include <editline/readline.h>
#include <editline/history.h>

#endif 

//-----------------------------------------------------------------------
// Stop preprocessor logic
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
// Main code
//-----------------------------------------------------------------------

int main(int argc, char **argv) {
    // Print version and exit info
    puts("Norisp version 0.0.1");
    puts("Press Ctrl+C to Exit\n\n");

    //Infinte loop
    while(1){
        // Output promt and get user input
        char* input = readline("norisp> ");

        // add input to history
        add_history(input);

        // echo back user input
        printf("No you're a %s\n", input);

        // free user input from memory
        free(input);
    }
    return 0;
}