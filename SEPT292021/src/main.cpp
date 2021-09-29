/**
 * @author:                     Syed Tajir Hasnain
 * @date:                       29/09/2021
 * @assignment_no:              7
 * @assignment_title:           Operator Precedence Parsing 
 * 
*/

#include <iostream>
#include <string>
#include <stack>
#include "./operator_precendence.h"

int main(int argc, char **argv)
{
#ifdef tajir
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    std::string input;

    while (std::getline(std::cin, input))
    {

        std::cout << "Result: " << oprecedence::calculate(input) << std::endl; 
    }

    return 0;
}