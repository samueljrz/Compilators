%{

#include <stdio.h>

void yyerror(char *c);
int yylex(void);

%}

%token ZERO UM MAIS MENOS FIML


%%
NUMBER:
	SIGN LIST FIML {
                    $$ = $1 * $2;
                    printf("O binario equivale ao seguinte decimal: %d\n", $$);                
                    return 0;
                  }
    ;

SIGN:
	MAIS { $$ =  1; }
	| MENOS { $$ = -1; }
    | { $$ =  1; }
    ;

LIST:
	LIST BIT { $$ = 2*$1 + $2; }
	| BIT { $$ = $1; }
    ;

BIT:
	ZERO { $$ = $1; }
	| UM { $$ = $1; }
    ;
%%


void yyerror(char *c){
  printf("erro: %s\n", c);
}

int main(){
    while(1){
        yyparse();
    }
    return 0;
}
