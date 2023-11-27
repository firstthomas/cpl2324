# cpl2324

Class number: 2324-S1

Group number: ?

Students:
    Thomas Verwaal  s2615223
    Robert Salden   s3712478

Compiler version: 
    g++ 9.4.0
Operating system:
    Ubuntu 20.04.2

About the program:
    The program should fully work as intended.
    A deviation from the assignment is that when replacing variables we add an exclamation mark after the variable so it will always be different. We thought that replacing them with standard letters such as 'w' or 'y' could create problems where these letters were already being used in the input. So instead we just do the exclamation mark.

Reduction strategies:
    Our reduction strategy is as follows:
        First we check if there's a application lambda construction which shows if Beta-Conversion is possible. 
        Then we start performing Beta-Reductions and only performing Alpha-conversions when necessary. This will continue until it's either no longer possible or there have been over a 1000 reductions which will result in an error message.