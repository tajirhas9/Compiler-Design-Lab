#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <cmath>
using namespace std;

const int inf = 2000000000;
    bool is_operator(char token)
    {
        std::string symbols = "()*/%+-=";

        if (symbols.find(token) != std::string::npos)
        {
            return true;
        }
        return false;
    }

    bool is_operator(std::string token)
    {
        return (
            token == "(" || token == ")" || 
            token == "*" || token == "/" || token == "%" || 
            token == "+" || token == "-" || 
            token == "="
            );
    }

    int operator_weight(std::string op)
    {
        if (op == "^")
            return 3;
        if (op == "*" || op == "/" || op == "%")
            return 2;
        if (op == "+" || op == "-")
            return 1;
        return -1;
    }

    double operate(double a, double b, std::string op)
    {
        int x = a;
        int y = b;
        //Perform operation
        if (op == "+")
            return b + a;
        else if (op == "-")
            return b - a;
        else if (op == "*")
            return b * a;
        else if (op == "/")
            return b / a;
        else if (op == "^")
            return pow(b, a); //find b^a
        else if(op == "%") {
            int res = y % x;
            return res*1.0;
        }
        else
            return -inf*1.0; //return negative infinity
    }

    /**
     *  parses string that contains a mathematical expression
     *  @returns a vector with the values
     **/
    std::vector<std::string> parse(std::string expression)
    {
        std::vector<std::string> values; // for storing values
        std::string buffer;              // buffer, for storing current stream
        int i = 0;                       // for iterating over expression

        while (i < expression.size())
        {
            char c = expression[i];
            std::string c_string = std::string(1, c);

            // check if the current character is an operator
            if (is_operator(c))
            {
                // if yes
                // the current buffer is a number if not empty
                if (!buffer.empty())
                {
                    // push the number to result
                    values.push_back(buffer);
                    buffer.clear();
                }
                // push the operator to result
                values.push_back(c_string);
                ++i;
                continue;
            }
            else
            {
                buffer += c_string;
                ++i;
            }
        }

        // last number
        if (!buffer.empty())
        {
            values.push_back(buffer);
        }

        // print
        std::cout << "Expression: ";
        for (auto &exp : values)
        {
            std::cout << exp << " , ";
        }

        std::cout << std::endl;

        return values;
    }

    std::vector<std::string> to_postfix(std::vector<std::string> values)
    {
        std::vector<std::string> postfix;
        std::string buffer;
        std::stack<std::string> Stack;

        for (int i = 0; i < values.size(); ++i)
        {
            std::string token = values[i];

            if (token.size() > 1 || !is_operator(token))
            {
                // token is a number
                postfix.push_back(token);
            }
            else if (token == "(")
            {
                Stack.push(token);
            }
            else if (token == ")")
            {
                while (!Stack.empty() && Stack.top() != "(")
                {
                    std::string top = Stack.top();
                    Stack.pop();
                    postfix.push_back(top);
                }
                Stack.pop();
            }
            else
            {
                while (!Stack.empty() && operator_weight(token) <= operator_weight(Stack.top()))
                {
                    std::string top = Stack.top();
                    Stack.pop();
                    if (top != "(" && top != ")")
                    {
                        postfix.push_back(top);
                    }
                }
                Stack.push(token);
            }
        }

        while (!Stack.empty())
        {
            if (Stack.top() != "(" && Stack.top() != ")")
            {
                postfix.push_back(Stack.top());
            }
            Stack.pop();
        }

        // print
        std::cout << "Postfix Expression: ";
        for (auto &exp : postfix)
        {
            std::cout << exp << " , ";
        }

        std::cout << std::endl;

        return postfix;
    }

    double calculate_postfix(std::vector<std::string> expression)
    {
        std::stack<double> Stack;

        for (int i = 0; i < expression.size(); ++i)
        {
            std::string token = expression[i];

            if (is_operator(token))
            {
                std::cout << "operator: " << token << std::endl;
                double num1 = Stack.top();
                Stack.pop();
                double num2 = Stack.top();
                Stack.pop();

                std::cout << "popping: " << num1 << ", " << num2 << std::endl;
                std::cout << "result: " << operate(num1, num2, token) << std::endl;
                Stack.push(operate(num1, num2, token));

                std::cout << "pushing: " << operate(num1, num2, token) << std::endl;
            }
            else
            {
                Stack.push(std::stod(token));
                std::cout << "pushing: " << std::stod(token) << std::endl;
            }
        }

        return Stack.top();
    }

    double calculate(std::string expression) 
    {

        std::vector<std::string> postfix = to_postfix(parse(expression));

        return calculate_postfix(postfix);

    }

int main(int argc, char **argv)
{
    std::string input;

    while (std::getline(std::cin, input))
    {

        std::cout << "Result: " << calculate(input) << std::endl; 
    }

    return 0;
}