
%{
#include <stdio.h>

int yylex();
int yyerror(char *s);

%}

%token STRING OTHER WHITESPACE SEMICOLON UNARY_OPERATOR ARITHMETIC_OPERATOR ASSIGNMENT_OPERATOR RELATIONAL_OPERATOR LOGICAL_OPERATOR KEYWORD FUNCTION SYMBOL IDENTIFIER NUMBER COMMENT SPECIAL_CHARACTER PRE_PROCESSOR

%type <identifier> STRING
%type <operator> UNARY_OPERATOR
%type <operator> ARITHMETIC_OPERATOR
%type <operator> ASSIGNMENT_OPERATOR
%type <operator> RELATIONAL_OPERATOR
%type <operator> LOGICAL_OPERATOR
%type <identifier> KEYWORD
%type <identifier> FUNCTION
%type <symbol> SYMBOL
%type <identifier> IDENTIFIER
%type <number> NUMBER
%type <comment> COMMENT
%type <character> SPECIAL_CHARACTER
%type <identifier> PRE_PROCESSOR
%type <identifier> WHITESPACE
%type <character> SEMICOLON

%union{
	char identifier[20];
    int number;
	char operator[3];
	char symbol[1];
	char comment[1000];
	char character[1];
}

%%

prog:
  stmts
;

stmts:
		| stmt stmts

stmt:
		STRING {
				printf("%s is a string\n", $1);
		}
		| NUMBER {
				printf("%d is a number\n", $1);
		}
		| UNARY_OPERATOR {
				printf("%s is a unary operator\n", $1);
		}
		| ARITHMETIC_OPERATOR {
			printf("%s is an arithmatic operator\n", $1);
		}
		| ASSIGNMENT_OPERATOR {
			printf("%s is an assignment operator\n", $1);
		}
		| RELATIONAL_OPERATOR {
			printf("%s is a relational operator\n", $1);
		}
		| LOGICAL_OPERATOR {
			printf("%s is a logical operator\n", $1);
		}
		| KEYWORD {
			printf("%s is a keyword\n", $1);
		}
		| FUNCTION {
			printf("%s is a function\n", $1);
		}
		| SYMBOL {
			printf("%s is a symbol\n", $1);
		}
		| IDENTIFIER {
			printf("%s is an identifier\n", $1);
		}
		| COMMENT {
			printf("%s is a comment\n", $1);
		}
		| SPECIAL_CHARACTER {
			printf("%s is a special character\n", $1);
		}
		| PRE_PROCESSOR {
			printf("%s is a pre-processor\n", $1);
		}
		| WHITESPACE {
			// avoid
		}
		| OTHER
;

%%

int yyerror(char *s)
{
	printf("Syntax Error on line %s\n", s);
	return 0;
}

int main()
{
	freopen("input.c", "r", stdin);
	freopen("output.txt", "w", stdout);
    yyparse();
    return 0;
}
