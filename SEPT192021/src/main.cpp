/**
 * @author:                     Syed Tajir Hasnain
 * @date:                       15/09/2021
 * @assignment_no:              5
 * @assignment_title:           Try to write a program that takes input a C Code. Then ignoring all tabs, white space &
 *                              new line, identify the following tokens:
 *                              1. Keywords = int, main, return, char, if, else………………………………….
 *                              2. Operators = +, -, * , &&, ||,>,<,=……………
 *                              3. Symbols = (,{,],;,),},]………………
 *                              4. Identifier = my_name, LengthCount, ans123,…..
 *                              5. Function name = main(), myFun(),……………….
 *                              6. Numbers = 1,2,12.44, 43.50,………………………………..
 * 
*/

#include <iostream>
#include "analyser.h"

int main(int argc, char **argv) {
#ifdef tajir
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    analyser::LexicalAnalyser analyser = analyser::LexicalAnalyser();
    std::string s;
    std::string source;

    while(std::getline(std::cin, s)) {
        source += s;
    }

    analyser.set_souce(source);

    analyser.analyse();

    return 0;
}