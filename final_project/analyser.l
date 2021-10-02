%{

#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
void showError();
%}

%%

"++"|"--"                                               {sscanf(yytext, "%s", yylval.operator); return (UNARY_OPERATOR);}

"+"|"-"|"*"|"/"                                         {sscanf(yytext, "%s", yylval.operator); return (ARITHMETIC_OPERATOR);}

["]([^"\\\n]|\\.|\\\n)*["]                              {sscanf(yytext, "%s", yylval.identifier); return (STRING);}

"="|"+="|"-="|"*="|"/="|"%="|"<<="|">>="|"&="|"^="|"|=" {sscanf(yytext, "%s", yylval.operator); return (ASSIGNMENT_OPERATOR);}

"=="|">="|"<="|"!="|">"|"<"                             {sscanf(yytext, "%s", yylval.operator); return (RELATIONAL_OPERATOR);}

"&&"|"||"|"!"                                           {sscanf(yytext, "%s", yylval.operator); return (LOGICAL_OPERATOR);}

if|else|then|int|switch|for|char|return|main|string|while|do|break|continue|double|float|EOF|case|long|short|sizeof|void|static|goto|struct|unsigned {sscanf(yytext, "%s", yylval.identifier); return (KEYWORD);}

[a-zA-Z_]([a-zA-Z_]|[0-9])*[(][a-zA-Z0-9," "]*[)]       {sscanf(yytext, "%s", yylval.identifier); return (FUNCTION);}

"{"|"}"|"["|"]"|","|";"|"("|")"                         {sscanf(yytext, "%s", yylval.symbol); return (SYMBOL);}

[a-zA-Z_][a-zA-Z_0-9]*                                  {sscanf(yytext, "%s", yylval.identifier); return (IDENTIFIER);}

[0-9]+[.0-9]*                                           {yylval.number = atof(yytext); return (NUMBER);}

"//".*" "*                                              {sscanf(yytext, "%s", yylval.comment); return (COMMENT);}

\/\*(.*\n)*.*\*\/                                       {sscanf(yytext, "%s", yylval.comment); return (COMMENT);}

"#"|"@"|"$"|"^"|"%"|"^"|"&"                             {sscanf(yytext, "%s", yylval.character); return (SPECIAL_CHARACTER);}

#.*                                                     {sscanf(yytext, "%s", yylval.identifier); return (PRE_PROCESSOR);}

[ \t\n]+                                                {return (WHITESPACE);}
.      		                                            {showError(yytext); return(OTHER);}

%%


void showError(char input[]) {
    printf("%s Other input\n", input);
}
