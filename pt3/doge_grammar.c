#include "mpc.c"

int main (int argc, char** argv) {
    // Build parser rule sets
    mpc_parser_t* Adjective = mpc_new("adjective");
    mpc_parser_t* Noun      = mpc_new("noun");
    mpc_parser_t* Phrase    = mpc_new("phrase");
    mpc_parser_t* Doge      = mpc_new("doge");

    // Populate parser rules
    mpca_lang(MPCA_LANG_DEFAULT,
        "
            adjective : \"wow"\| \"many\
                      | \"so\" | \"such\";
            noun      : \"lisp\" | \"langauage\"
                      | \"book\" | \"build\" | \"c\";
            phrase    : <adjective> <noun>;
            doge      : <phrase>*;
        ",
        Adjective, Noun, Phrase, Doge);

    // Parse some stuff here

    // Free allocated resources
    mpc_cleanup(4, Adjective, Noun, Phrase, Doge);

    return 0;
}