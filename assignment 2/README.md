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
    The program should fully work as intended and can be stopped




    
    A deviation from the assignment is that when replacing variables we add an exclamation mark after the variable so it will always be different. We thought that replacing them with standard letters such as 'w' or 'y' could create problems where these letters were already being used in the input. So instead we just do the exclamation mark.
    We also convert the expression to the prefix format and then build the tree instead of building the tree while parsing the expression.

Reduction strategies:
    Our reduction strategy is as follows:
        First we check if there's a application lambda construction which shows if Beta-Reduction is possible. We always check for the first application lambda construction and try to reduce it. If this first construction cannot be reduced any other construction is also not reduced.
        Then we start performing Beta-Reductions and only performing Alpha-conversions when necessary. This will continue until it's either no longer possible or there have been over a 1000 reductions which will result in an error message. If a reduction doesn't change the abstract syntax tree the Beta-Reduction is stopped.
        Beta-Reduction is performed by copying the entire right subtree of the application into every variable occurence in the right side of the lambda where the variable is equal to the left child of the lambda.
        Alpha conversion is performed by first finding all the variables in the right subtree of the application and then determening which of these variables are free. To all occurrences of these free variables in the right subtree of the lambda '!' is added if any of these free variables would otherwise become bound. Whether or not a free variale becomes bound or not is checked by looking for the "replace var" in the right subtree of the lambda. The "replace var" is the left child of the lambda. 