#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <iterator>
#include <regex>
#include <stack>

namespace parser
{
    class PredictiveParser
    {
        std::string productions[5][6];
        std::string cols[6] = {"i", "+", "*", "(", ")", "$"}, rows[5] = {"E", "e", "T", "t", "F"};

    public:
        void get_productions()
        {
            productions[0][0] = "Te";
            productions[0][3] = "Te";
            productions[1][1] = "+Te";
            productions[1][4] = "x";
            productions[1][5] = "x";
            productions[2][0] = "Ft";
            productions[2][3] = "Ft";
            productions[3][1] = "x";
            productions[3][2] = "*Ft";
            productions[3][4] = "x";
            productions[3][5] = "x";
            productions[4][0] = "i";
            productions[4][3] = "(E)";
        }

        void parse(std::string input)
        {
            std::string temp_row, temp_col;
            std::string input;
            //cin>>input;
            int length = input.length();
            int done;
            std::string check[100] = {"null"};
            std::string st = "+iE$";
            std::stack<std::string> stk;
            
            std::cout << "stack = " << st << "\tinput = " << input << endl;
            while (1) //&& input[0] != '$')
            {
                done = 0;
                if (st[0] == '$' && input[0] != '$')
                {
                    std::cout << "wrong" << endl;
                    break;
                }
                if (st[0] == '$' && input[0] == '$')
                {
                    std::cout << "parse successful" << endl;
                    break;
                }
                temp_row = st[0];
                temp_col = input[0];
                std::cout << st[0] << "\t" << input[0] << endl;
                std::cout << "stack = " << st << "\tinput = " << input << endl;
                if (temp_row == temp_col)
                {
                    input.erase(input.begin() + 0);
                    st.erase(st.begin() + 0);
                    std::cout << "stack = " << st << "\tinput = " << input << endl;
                    continue;
                }
                for (int i = 0; i < 5; i++)
                {
                    if (done == 1)
                        break;
                    if (rows[i] == temp_row)
                        for (int j = 0; j < 6; j++)
                        {
                            if (cols[j] == temp_col)
                            {
                                if (table[i][j] == "null")
                                {
                                    std::cout << "wrong" << endl;
                                    done = 1;
                                    exit(0);
                                    break;
                                }
                                std::string temp_str;
                                temp_str = table[i][j];
                                if (temp_str == "x")
                                {
                                    st.erase(0, 1);
                                    done = 1;
                                    break;
                                }
                                else
                                {
                                    st.replace(0, 1, temp_str);
                                    done = 1;
                                    break;
                                }
                            }
                        }
                }
            }
        }
    };
}