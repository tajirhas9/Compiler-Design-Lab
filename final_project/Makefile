default:
	clear
	flex -l analyser.l
	bison -dv parser.y 
	gcc -o parser parser.tab.c lex.yy.c -lfl
	./parser
