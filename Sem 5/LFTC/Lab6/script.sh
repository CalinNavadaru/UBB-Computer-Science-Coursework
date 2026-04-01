bison -d parser.y -Wcounterexamples
flex lexerl.lxi
gcc -c lex.yy.c -o lex.yy.o -lfl
gcc -o parser parser.tab.c lex.yy.c -lfl