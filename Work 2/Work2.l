
/*
bison -dy binary.y
flex binary.l
gcc -o binary lex.yy.c y.tab.c -ll
./binary
*/
%{
    #include <stdio.h>
    #include "y.tab.h"
    
    void yyerror(char *c);
%}

%%


[+] { return MAIS; }

[-] { return MENOS; }

[1] {
        yylval = 1;
        return UM;
    }

[0] {
        yylval = 0;
        return ZERO;
    }

[\n] { return FIML; }

[ \t] ;

. ;

%%

int yywrap(){
    return 1;
}
