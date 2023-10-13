#include <iostream>
#include <sstream>
#include <climits>
#include <string>
#include "parser.h"
using namespace std;

// (\x((a) (b)))

void arraycheck(Tokenizer token){
    for (int i = 0; i < token.array_size; i++){
        cout << "token_type" << token.tokenarray[i].x << endl;
    }
}

int main(){
    std::string input;
    std::string output;
    std::string output2; // For parsing own output
    cout << "Enter input expression, one per line" << endl;
    cout << "To stop the program enter 0" << endl;
	while (getline(cin, input)){
        if (input == "0"){
            break;
        }
        Tokenizer token(input);
        // arraycheck(token);
        Parser pars;
        pars.expr(token);
        token.create_output(output);
    }
    cout << output << endl;

    cout << "Parsing own output: " << endl;
    std::stringstream ss(output);
    while (getline(ss, input, '\n')){
        if (input == "0"){
            break;
        }
        Tokenizer token(input);
        // arraycheck(token);
        Parser pars;
        pars.expr(token);
        token.create_output(output2);
    }
    cout << output;
    // arraycheck(token);
    exit(0);
}

//Geeft nu output alleen nog niet UNAMBIGUOUS
//outputs a character string in a standard format to standard output
//this format may be explained in the README
//should use least amount of std library code

//README: student numbers, know defects or works correctly (defect is misschien dat er maximale grootte is ofzo)
//deviations from the assignment?
//may include explanation of how the programs work

//may include positive.zip and negative.zip file
//program may accept multiple expressions one per line(simpele while loop??)

//dit vindt ik teveel moeite:
//may support inernational variable names(unicode with lambda instead of \)


//eigen output parsen werkt alleen de output moet nog () teoevoegen als nodig
//zoals hieronder staat uitgelegd
//If parsing is succesful, the output of the program must be again acceptable
// by the program to parse: the program then succesfully parses its own output and
// should produce the exact same result. The output should be an UNAMBIGUOUS
// expression, i.e. with sufficiently many parentheses inserted so the parser never
// applies any of the precedence rules. The output may use the least amount of
// whitespace and parentheses in its output.
//dus x y z moet (x y) z als output en \x x y moet (\x x) y als output



// file als input
//A line is considered terminated by a newline character (\n),
//or a carriage return and newline character (\r\n).
//file als input

//should use least amount of std library code overal std neerzetten