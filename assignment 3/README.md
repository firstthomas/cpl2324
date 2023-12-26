# cpl2324

Class number: 2324-S1

Group number: Robert+Thomas

Students:
    Thomas Verwaal  s2615223
    Robert Salden   s3712478

Compiler version: 
    g++ 9.4.0
Operating system:
    Ubuntu 20.04.2

About the program:
    The program should fully work as intended. To run the program with a file use "./main < filename". The only problem our program might have is that our tokenarray has a maximum size of 5000 so if an expression is larger than 5000 tokens the program will most likely fail. This value can easily be changed in the token.h file. 

Memory leaks:
    When testing we did not encounter any memory leaks except for still reachable leaks. These still reachable leaks are because we end the program with exit(0) and can be avoided by replacing exit(0) with return 0.

How the program works:
    The program reads from a file using getline() and can have multiple expression as input because we use a while loop.
    The first step in the program is creating a token array from the input expression. This is done by creating a token for each charachter in the input string, since variables are longer and need to satisfy certain condition we use a while loop and a large if statment. We also check if the amount of open and closing brackets is equal when creating the token array.

    After creating the token array we add applications to the array by checking where they need to be places. This function is quite complicated but is based on the amount of variables that are not part of a lambda abstraction.
    
    After this we pars the token array using a peek and consume function and a class counter j to remember the position in the token array. The array is parsed using the following LL grammar:
        <expr> = <lexpr><expr'>
        <expr'> = <lexpr><expr'> | empty
        <lexpr> = <pexpr> | λ <var> ^ <type> <lexpr'>
        <pexpr> = <var> | (<expr>)
        <type> = <ptype> <type'>
        <type'> = -> <type> | empty
        ptype = uvar | (type)
    Where uvar is variable that starts with a uppercase letter and lvar with a lowercase letter. The parser reports an error and exits the program with status 1 if the expression does not satisfy the LL grammar.

    After parsing the expression we want to typeDerivCheck the expression.
    output the expression unambiguous with the least amount of whitespace and parentheses.
    To do this we build a tree. To build this tree we first create a postifx token array by using a algorithm to convert infix to prefix that uses a stack.
    Because our typeChecking changes the tree we first create the output by walking through the tree inorder.
    
    hier nog uitleg hoe printinfix werkt en onze ouput format. deze is anders voor assignment 3
    
    After creating the output we first typeDerivCheck the tree. Our 
    typeDerivCheck() function is based on the three rules from the lectures. We apply these rules to the left child of our root and then check if the left and right side are equal.
    
    For \y^B(y \x^B y) : B -> B as input, type checking cannot be fully apllied and we give an error but still print the output.
    According to the teacher this expression could still have correct types but because we cannot apply the rules any further we cannot check if the types are correct.

    After this we call the destructor for the tree to avoid memory leaks.