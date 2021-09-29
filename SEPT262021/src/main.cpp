/**
 * @author:                     Syed Tajir Hasnain
 * @date:                       15/09/2021
 * @assignment_no:              6
 * @assignment_title:           Predictive Parser
 * 
*/

#include <iostream>
#include "predictive_parser.h"

int main(int argc, char **argv) {
#ifdef tajir
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    parser::PredictiveParser parser = parser::PredictiveParser();

    parser.get_productions();

    parser.parse("+ii+i*$");

    return 0;
}