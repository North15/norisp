#include "mpc.h"

int main(int argc, char** argv){
    // Build adjective parser 
    mpc_parser_t* Adjective = mpc_or(4,
        mpc_sym("wow"), mpc_sym("many"),
        mpc_sym("so"), mpc_sym("such")
    );

    // Build noun parser 
    mpc_parser_t* Noun = mpc_or(5,
        mpc_sym("norisp"), mpc_sym("language"),
        mpc_sym("book"), mpc_sym("build"),
        mpc_sym("c")
    );

    // Build phrase parser
    mpc_parser_t* Phrase = mpc_and(2, mpcf_strfold, Adjective, Noun, free);

    //Build doge parser
    mpc_parser_t* Doge = mpc_many(mpcf_strfold, Phrase);

    // Prase some stuff here

    // Free allocated memory
    mpc_delete(Doge);

    return 0;
}