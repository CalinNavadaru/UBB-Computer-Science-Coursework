%{
    #include <stdio.h>
    #include <string.h>
    int yylex(void);
    void yyerror(const char *s);
    extern int line_number;
    int palindrom(int a, int b);
%}

%token DOUA_PUNCTE
%union {
    int ora;
    int minut;
}
%token <ora> ORA
%token <minut> MINUT;
%%
input:
    expr
  | input expr 
  ;
expr: 
      ORA DOUA_PUNCTE MINUT { 
          if (!palindrom($1, $3)) {
              yyerror("Nu este palindroma ora!");
          }
      }
    | ORA DOUA_PUNCTE ORA {
          if (!palindrom($1, $3)) {
              yyerror("Nu este palindroma ora!");
          }
      }
;
%%
int main(void) {
    yyparse();
    return 0;
}

int palindrom(int a, int b) {
    char result[50];
    int t = a;
    int c_b = b;
    while(c_b) {
        t = t * 10;
        c_b/=10;
    }
    t+=b;
    printf("%d\n", t);
    sprintf(result, "%02d%d", a, b);
    printf("%s\n", result);
    int l = strlen(result);
    for (int i = 0; i < l / 2; i++) {
        if (result[i] != result[l - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

void yyerror(const char *s) {
    fprintf(stderr, "Eroare la linia %d: %s\n", line_number, s);
}