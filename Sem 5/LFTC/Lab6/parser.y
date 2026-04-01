%{
#include <stdio.h> /* for (f)printf() */
#include <stdlib.h> /* for exit() */
#include <string.h>
#include <ctype.h>
#include "attrib.h"
#include "codeASM.h"

int  lineno = 1; /* number of current source line */
extern int yylex(); /* lexical analyzer generated from lex.l */
extern char *yytext; /* last token, defined in lex.l  */
FILE *output_ASM;

void
yyerror(char *s) {
  printf("\n \n \nMy error: \n");
  printf( "Syntax error on line #%d: %s\n", lineno, s);
  printf( "At token : \"%s\"\n", yytext);
  exit(1);
}

int isNumeric(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0; 
    }

    while (*str) {
        if (!isdigit((unsigned char)*str)) {
            return 0;
        }
        str++;
    }

    return 1;
}

int tempnr = 1;
void newTempName(char* s){
  sprintf(s,"[temp%d]",tempnr);
  tempnr++;
}

void addSquareBrackets(const char *input, char *output) {
    sprintf(output, "[%s]", input);
}


char tempbuffer[250];


%}


%union {
 char varname[10];
 attributes attrib;
 char strCode[512];
}


%token BEGINPAR
%token ENDPAR

%token LPAREN
%token RPAREN
%token ASSIGN
%token SEMICOLON
%token PLUS
%token MULTIPLY
%token MINUS
%token CITIRE
%token AFISARE 
%token OP_CITIRE
%token OP_AFISARE

%token <varname> IDENTIFIER
%token <varname> CONST 
%type <attrib> term
%type <attrib> expression
%type <attrib> factor



%%
program         : 	BEGINPAR 
				statement_list 
				ENDPAR   	
				;

				
statement_list  : statement_list statement 
                | statement
                ;
                                                                                   
statement       : assignment SEMICOLON
                | afisare SEMICOLON
                | citire SEMICOLON
                ;


citire:  CITIRE OP_CITIRE IDENTIFIER {
    output_ASM = fopen("output.asm", "a");
    fprintf(output_ASM, CITIRE_ASM_FORMAT, $3);
    fclose(output_ASM);
}
;


afisare: AFISARE OP_AFISARE expression {
  output_ASM = fopen("output.asm", "a");
  fprintf(output_ASM, AFISARE_ASM_FORMAT, $3.varn);
  fclose(output_ASM);
}
          ;
				
assignment      : IDENTIFIER ASSIGN expression
                  {
                    output_ASM = fopen("output.asm", "a");
                    fprintf(output_ASM, "%s\n",$3.cod);
                    fprintf(output_ASM, "mov ax, %s\n",$3.varn);
                    fprintf(output_ASM, "mov [%s],ax\n",$1);
                    fclose(output_ASM);
                   }
                ;
expression: term
          | expression PLUS term {
                newTempName($$.varn);
                sprintf($$.cod, "%s\n%s\n", $1.cod, $3.cod);
                sprintf(tempbuffer, ADD_ASM_FORMAT, $1.varn, $3.varn, $$.varn);
                strcat($$.cod, tempbuffer);
            }
          | expression MINUS term {
                newTempName($$.varn);
                sprintf($$.cod, "%s\n%s\n", $1.cod, $3.cod);
                sprintf(tempbuffer, MINUS_ASM_FORMAT, $1.varn, $3.varn, $$.varn);
                strcat($$.cod, tempbuffer);
            };

term: factor
    | term MULTIPLY factor {
          newTempName($$.varn);
          sprintf($$.cod, "%s\n%s\n", $1.cod, $3.cod);
          sprintf(tempbuffer, MULTIPLY_ASM_FORMAT, $1.varn, $3.varn, $$.varn);
          strcat($$.cod, tempbuffer);
      }

factor: CONST {
          strcpy($$.cod, "");
          strcpy($$.varn, $1);
      }
      | IDENTIFIER {
          strcpy($$.cod, "");
          char nume_cu_patrate[250];
          addSquareBrackets($1, nume_cu_patrate);
          strcpy($$.varn, nume_cu_patrate);
      }
      | LPAREN expression RPAREN {
          strcpy($$.cod, $2.cod);
          strcpy($$.varn, $2.varn);
      };

%%

int
main(int argc,char *argv[]) {
  output_ASM = fopen("output.asm", "a");
  fprintf(output_ASM, INIT_ASM);
  fclose(output_ASM);
  int parse_result = yyparse();
  if (parse_result != 0) {
      output_ASM = fopen("output.asm", "a");
        fprintf(stderr, "Parsing error detected at line %d.\n", lineno);
        fclose(output_ASM);
        return 1;
    }
  else {
    output_ASM = fopen("output.asm", "a");
    fprintf(stdout, "Parsing complete!\n");
    fprintf(output_ASM, END_ASM);
    fclose(output_ASM);
    return 0;
  }
} 
