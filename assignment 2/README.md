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
    The program should fully work as intended. To run the program with a file use "./main filename". The only problem our program might have is that our tokenarray has a maximum size of 5000 so if an expression is larger than 5000 tokens the program will most likely fail. This value can easily be changed in the token.h file. 

    A deviation from the assignment is that when replacing variables we add an exclamation mark after the variable so it will always be different. We thought that replacing them with standard letters such as 'w' or 'y' could create problems where these letters were already being used in the input. So instead we just do the exclamation mark.
    We also convert the expression to the prefix format and then build the tree instead of building the tree while parsing the expression.

Memory leaks:
    When testing we did not encounter any memory leaks except for still reachable leaks. These still reachable leaks are because we end the program with exit(0) and can be avoided by replacing exit(0) with return 0.

Reduction strategies:
    Our reduction strategy is as follows:
        First we check if there's a application lambda construction which shows if Beta-Reduction is possible. We always check for the first application lambda construction and try to reduce it. If this first construction cannot be reduced any other construction is also not reduced.
        Then we start performing Beta-Reductions and only performing Alpha-conversions when necessary. This will continue until it's either no longer possible or there have been over a 1000 reductions which will result in an error message. If a reduction doesn't change the abstract syntax tree the Beta-Reduction is stopped.
        Beta-Reduction is performed by copying the entire right subtree of the application into every bound variable occurence in the right side of the lambda where the variable is bound to the left child of the first lambda.
        Alpha conversion is performed by first finding all the variables in the right subtree of the application and then determening which of these variables are free. To all occurrences of these free variables in the right subtree of the lambda '!' is added if any of these free variables would otherwise become bound. Whether or not a free variale becomes bound or not is checked by looking for the "replace var" in the right subtree of the lambda. The "replace var" is the left child of the lambda. If the replace var becomes bound by a differnt lambda abstraction we don't look further down this part of the tree.

How the program works:
    The program reads from a file using getline().
    The first step in the program is creating a token array from the input expression. This is done by creating a token for each charachter in the input string, since variables are longer and need to satisfy certain condition we use a while loop and a large if statment. We also check if the amount of open and closing brackets is equal when creating the token array.
    
    After creating the token array we add applications to the array by checking where they need to be places. This function is quite complicated but is based on the amount of variables that are not part of a lambda abstraction.

    After this we pars the token array using a peek and consume function and a class counter j to remember the position in the token array. The array is parsed using the following LL grammar:
        <expr> = <lexpr><expr'>
        <expr'> = <lexpr><expr'> | empty
        <lexpr> = <pexpr> | λ <var> <lexpr>
        <pexpr> = <var> | (<expr>)
    The parser reports an error and exits the program with status 1 if the expression does not satisfy the LL grammar.

    After parsing the expression we want to build an abstract syntax tree from the token array so that we can use this tree to perform beta reduction on the expression. To build this tree we first create a postifx token array by using a algorithm to convert infix to prefix that uses a stack.
    After creating the tree we beta reduce the tree by the methods explained above.
    We then  want to output the expression in an unambiguous matter with the least amount of whitespace and parentheses.
    We create the output by walking through the tree inorder.
    
    hier nog uitleg hoe printinfix werkt en onze ouput format.
    
    After this we call the destructor for the tree to avoid memory leaks.