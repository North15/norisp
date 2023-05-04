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
#include "mpc.h"

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
// Main 
//-----------------------------------------------------------------------
int main(int argc, char **argv) {
    // Create polish notaion parsers
    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Norisp   = mpc_new("norisp");

    // Define the parsers
    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                         \
            number   : /-?[0-9]+/ ;                               \
            operator : '+' | '-' | '*' | '/' ;                    \
            expr     : <number> | '(' <operator> <expr>+ ')' ;    \
            norisp   : /^/ <operator> <expr>+ /$/ ;               \
        ",
        Number, Operator, Expr, Norisp);

    // Print version and exit info
    puts("Norisp version 0.0.2");
    puts("Press Ctrl+C to Exit\n\n");

    //Infinte loop
    while(1){
        // Output promt and get user input
        char* input = readline("norisp> ");

        // add input to history
        add_history(input);

        // attempt to parse the user input
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Norisp, &r)) {
            // on success print the AST
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } 
        else {
            // otherwise print the error
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        // free user input from memory
        free(input);
    }

    // Deallocate created resources
    mpc_cleanup(4, Number, Operator, Expr, Norisp);

    return 0;
}

//-----------------------------------------------------------------------
// eval - Used to eval you the parser tree 
//-----------------------------------------------------------------------
long eval(mpc_ast_t* t) {
    //return items tagged as number
    if(strstr(t->tag, "number")) {
        return atoi(t->contents);
    }

    // The operator is always second
    char* operator = t->children[1]->contents;

    // Store the third child
    long x = eval (t->children[2]);

    // Iterate the remaining children
    int = 3;
    while(strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x,op, eval(t->children[i]));
        i++;
    }
    return x;
}

//-----------------------------------------------------------------------
// eval_op - Used to evaluate the operator in the parser tree 
//-----------------------------------------------------------------------
long eval_op(long x, char* op, long y) {
    if (strcmp(op, "+") == 0) {return x + y; }
    if (strcmp(op, "-") == 0) {return x - y; }
    if (strcmp(op, "*") == 0) {return x * y; }
    if (strcmp(op, "/") == 0) {return x / y; }
    return 0;
}