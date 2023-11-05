#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <string>
#include "parser.h"
// #include "tree.h"
using namespace std;

void arraycheck(Token tokenArray[], int array_size){
    for (int i = 0; i < array_size; i++){
        if(tokenArray[i].x == SLASH){
            cout << "/";
        }
        else if(tokenArray[i].x == BRACKET_OPEN){
            cout << "(";
        }
        else if(tokenArray[i].x == BRACKET_CLOSE){
            cout << ")";
        }
        else if(tokenArray[i].x == VARIABLE){
            cout << tokenArray[i].y;
        }
        else if(tokenArray[i].x == APP){
            cout << "@";
        }
        else if(tokenArray[i].x == END){
            cout << "   END" << endl;
        }
    }
}


// Asks the user for 1 or more input expressions and reads it into a
// a string of tokens. Then parses the token string and returns output to 
// the standard output. It then repeats these steps on its own output.
int main(){
    std::string input;
    std::string output;
    std::string filenaam;
    std::string output2; // For parsing own output
    cout << "Enter file name." << endl;
    cout << "To stop the program enter 0" << endl;
    cin >> filenaam;
    ifstream myFile (filenaam);
    while (getline(myFile, input)){
        if (input == "0"){
            break;
        }
        Tokenizer token(input, true);
        Parser pars;
        pars.expr(token);
        token.create_output(output);
        // token.add_application();
        // arraycheck(token.tokenarray, token.array_size);
        // tree* tree1;
        // tree1 = new tree(token.tokenarray, token.array_size);
        // token.create_output(output);
    }
    myFile.close();

	// while (getline(cin, input)){
    //     if (input == "0"){
    //         break;
    //     }
    //     Tokenizer token(input);
    //     Parser pars;
    //     pars.expr(token);
    //     token.create_output(output);
    // }
    cout << output << endl;;

    cout << "Parsing own output: " << endl;
    std::stringstream ss(output);
    while (getline(ss, input)){
        if (input == "0"){
            break;
        }
        Tokenizer token(input, false);
        Parser pars;
        pars.expr(token);
        token.create_output(output2);
        token.add_application();
        arraycheck(token.tokenarray, token.array_size);
    }
    cout << output;
    exit(0);
}



//README: student numbers, know defects or works correctly (defect is misschien dat er maximale grootte is ofzo)
//deviations from the assignment?
//may include explanation of how the programs work

//may include positive.zip and negative.zip file

//should use least amount of std library code overal std neerzetten



//tijd over:

//eigen output parsen werkt alleen de output moet nog () teoevoegen als nodig
//zoals hieronder staat uitgelegd
//If parsing is succesful, the output of the program must be again acceptable
// by the program to parse: the program then succesfully parses its own output and
// should produce the exact same result. The output should be an UNAMBIGUOUS
// expression, i.e. with sufficiently many parentheses inserted so the parser never
// applies any of the precedence rules. The output may use the least amount of
// whitespace and parentheses in its output.
// Geeft nu output alleen nog niet UNAMBIGUOUS
// outputs a character string in a standard format to standard output
// this format may be explained in the README
// dus x y z moet (x y) z als output en \x x y moet (\x x) y als output

//dit vindt ik teveel moeite:
//may support inernational variable names(unicode with lambda instead of \)


// void arraycheck(Tokenizer token){
//     for (int i = 0; i < token.array_size; i++){
//         cout << "token_type" << token.tokenarray[i].x << endl;
//     }
// }