%{
    #include <stdio.h>
    int yylex(void);
    void yyerror(const char *s);
    extern int line_number;
%}

%token CIN IF WHILE STRUCT STR FOR INT FLOAT COUT
%token RSHIFT LSHIFT POWER INTEGER_DIV AND OR NOT_EQUAL EQUAL LESS_EQUAL GREATER_EQUAL
%token PLUS MINUS MODULO ASSIGN LESS GREATER MULTIPLY DIV

%left PLUS MINUS
%left MULTIPLY DIV INTEGER_DIV MODULO
%left POWER
%left AND OR
%left LESS GREATER EQUAL

%union {
    char* id;
    int num;
    char* str;
}
%token <id> IDENTIFICATOR
%token <num> NUMBER
%token <str> STRING

%%

program : 
        '{' struct_def list_instr '}'
        | '{' list_instr '}'
        | '{' struct_def '}'
        | '{' '}'
        ;
struct_def: 
        STRUCT IDENTIFICATOR '{' decl ';' '}'
        ;
list_instr:
        instr 
        | instr list_instr
        ;
instr: 
    atr ';' 
    | decl ';'
    | cond 
    | repr 
    | io
    ;
io: 
    CIN citire 
    | COUT scriere
    ;
citire: 
    RSHIFT IDENTIFICATOR ';' 
    | RSHIFT IDENTIFICATOR citire
    ;
scriere:
    LSHIFT IDENTIFICATOR scriere 
    | LSHIFT NUMBER scriere
    | LSHIFT STRING scriere  
    | LSHIFT IDENTIFICATOR ';' 
    | LSHIFT NUMBER ';'
    | LSHIFT STRING ';'   
    ;
decl: 
    tip IDENTIFICATOR
    | tip atr
    | decl ',' IDENTIFICATOR 
    | decl ',' atr
    ;
atr: 
    IDENTIFICATOR ASSIGN atr 
    | IDENTIFICATOR ASSIGN IDENTIFICATOR
    | IDENTIFICATOR ASSIGN NUMBER
    | IDENTIFICATOR ASSIGN STRING
    ;

op: math_op
    | comp_op
    | logic_op

math_op: 
    PLUS 
    | MINUS 
    | MULTIPLY 
    | DIV 
    | MODULO 
    ;

comp_op: 
    LESS 
    | LESS_EQUAL 
    | GREATER 
    | GREATER_EQUAL 
    | EQUAL 
    | NOT_EQUAL 
    ;

logic_op: 
    AND 
    | OR;

expr:
    IDENTIFICATOR
  | NUMBER
  | IDENTIFICATOR op expr
  | NUMBER op expr
  ;

repr: 
    while 
    | for
    ;
while: 
    WHILE expr '{' list_instr '}'
    ;
for: 
    FOR '(' atr ';' expr ';' expr ')' '{' list_instr '}'
    ;
cond:  
    IF '(' expr ')' '{' list_instr '}'
    ;
tip: 
    INT | FLOAT | STR | STRUCT IDENTIFICATOR
    ;

%%
int main(void) {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Eroare la linia %d: %s\n", line_number, s);
}