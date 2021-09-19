#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <iterator>
#include <regex>

namespace analyser
{

    class LexicalAnalyser
    {
    private:
        std::string source;
        std::vector<std::string> tokens;

        void generate_token()
        {
            std::cout << "[.] Generating tokens..." << std::endl;
            try
            {
                std::regex re("[\\ \\n\\t]");
                std::sregex_token_iterator first{source.begin(), source.end(), re, -1}, last;
                std::vector<std::string> _tokens{first, last};

                for (auto &token : _tokens)
                {
                    if (token == "")
                        continue;

                    tokens.push_back(token);
                    std::cout << token << std::endl;
                }

                std::cout << "[+] Tokens generated." << std::endl;
            }
            catch (...)
            {
                std::cout << "[-] Failed to generate token." << std::endl;
            }
        }

        bool is_keyword(std::string token)
        {
            std::string keywords[32] = {
                "auto", "double", "int", "struct", "break", "else", "long",
                "switch", "case", "enum", "register", "typedef", "char",
                "extern", "return", "union", "const", "float", "short",
                "unsigned", "continue", "for", "signed", "void", "default",
                "goto", "sizeof", "voltile", "do", "if", "static", "while"};
            if (std::find(std::begin(keywords), std::end(keywords), token) != std::end(keywords))
            {
                return true;
            }
            return false;
        }

        bool is_operator(std::string token)
        {
            std::vector<std::string> operators = 
            {
                "+", "-", "*", "/", "%", "++", "--",                    // arithmatic
                "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=",    // assignment
                "==", "!=", ">", "<", ">=", "<=",                       // comparison
                "&&", "||", "!",                                        // logical
                "&", "|", "!"                                           // boolean
            };
            if (std::find(std::begin(operators), std::end(operators), token) != std::end(operators))
            {
                return true;
            }
            return false;
        }

        bool is_symbol(std::string token)
        {
            std::string symbols = "(){}[];,";

            if (symbols.find(token) != std::string::npos)
            {
                return true;
            }
            return false;
        }

        bool is_identifier(std::string token)
        {
            return false;
        }

        bool is_function(std::string token)
        {

            int bracket_open_at = -1, bracket_close_at = -1;

            int i = 0;

            while (i < token.size())
            {
                char c = token[i];

                if (c == '(' && bracket_open_at == -1)
                {
                    bracket_open_at = i;
                }

                if (c == ')' && bracket_open_at != -1)
                {
                    bracket_close_at = i;
                }
                i++;
            }
            return (bracket_open_at != -1 && bracket_close_at != -1);
        }

        bool is_number(std::string token)
        {
            bool found_decimal = false;
            bool is_number = true;
            for(int i = 0; i < token.size(); ++i) {
                char c = token[i];
                is_number &= (c >= '0' && c <= '9') || (!found_decimal && c == '.');

                if(c == '.') {
                    found_decimal = true;
                }
            }

            return is_number;
        }

        std::string pretty_result(std::string token, std::string type)
        {
            return "<" + token + "," + type + ">";
        }

    public:
        // constructor
        LexicalAnalyser() {}

        // sets source code
        // generates tokens
        void set_souce(std::string _source)
        {
            std::cout << "[.] Setting source code..." << std::endl;
            source = _source;

            // generate_token();
        }

        void analyse()
        {
            std::cout << "[.] Analysing tokens..." << std::endl;

            std::vector<std::string> identified_tokens;
            std::vector<std::string> symbol_table;

            std::string last_identifier;
            std::string last_operator;
            bool assign_next = false;

            int i = 0;
            std::string buffer = "";

            while (i < source.size())
            {
                char c = source[i];
                std::string c_string = std::string(1, c);

                // check if current buffer has reached an end
                if (c == '\n' || c == '\t' || c == ' ' || c == ',' || c == ';')
                {
                    if (buffer == " ")
                    {
                        buffer.clear();
                        i++;
                        continue;
                    }
                    if (is_keyword(buffer))
                    {
                        identified_tokens.push_back(pretty_result(buffer, "keyword"));
                    }
                    else if (is_function(buffer))
                    {
                        identified_tokens.push_back(pretty_result(buffer, "function"));
                    }
                    else
                    {
                        if (!buffer.empty())
                        {
                            if(is_number(buffer)) {
                                identified_tokens.push_back(pretty_result(buffer, "number"));
                                if(assign_next) {
                                    symbol_table.push_back(pretty_result(buffer, last_identifier));
                                    assign_next = false;
                                }
                            } else {
                                identified_tokens.push_back(pretty_result(buffer, "identifier"));
                                last_identifier = buffer;
                            }
                        }
                    }

                    if (c == ',' || c == ';')
                    {
                        buffer = c;
                        identified_tokens.push_back(pretty_result(buffer, "symbol"));
                    }
                    buffer.clear();
                    i++;
                    continue;
                }

                if (is_operator(c_string))
                {
                    identified_tokens.push_back(pretty_result(buffer, "identifier"));
                    last_identifier = buffer;
                    buffer.clear();

                    std::string forwardBuffer = std::string(1,source[i]);
                    forwardBuffer += source[i+1];

                    // check if a two character operator
                    if(is_operator(forwardBuffer)) {
                        // add to result if yes
                        identified_tokens.push_back(pretty_result(forwardBuffer, "operator"));
                        i++;
                    } else {
                        // only one character operator
                        identified_tokens.push_back(pretty_result(c_string, "operator"));

                        if(c_string == "=") {
                            assign_next = true;
                        }
                    }
                    i++;
                    buffer.clear();
                    continue;
                }

                buffer += c;

                // std::cout << "current buffer: " << buffer << std::endl;
                if (is_symbol(buffer))
                {
                    identified_tokens.push_back(pretty_result(buffer, "symbol"));
                    buffer.clear();
                }
                ++i;
            }
            std::cout << "\n\n\n";
            for (auto &token : identified_tokens)
            {
                std::cout << token << std::endl;
            }

            std::cout << "\n\nSymbol table:" << std::endl;
            for(auto& item : symbol_table) 
            {
                std::cout << item << std::endl;
            }
        }
    };

}