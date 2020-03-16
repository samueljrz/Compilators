digit  [0-9]
letter [A-Za-z]

%{

#include <string.h>

int intf=0, floatf=0, floatv=0, intv=0, aux1=0;
char vint[100][100], vfloat[100][100], fint[100][100], ffloat[100][100];
char aux[1000];
char *aux2, *aux3;

%}

%%

int(" "|\t)+{letter}({letter}|{digit}|" ")*"(" {	
	sscanf(yytext, "%s %s", fint[0], aux);
	intf++;
	aux1 = strlen(aux);
	strncpy(fint[intf], aux, (aux1-1));
}

float(" "|\t)+{letter}({letter}|{digit})*"(" {
	sscanf(yytext, "%s %s", ffloat[0], aux);
	floatf++;
	aux1 = strlen(aux);
	strncpy(ffloat[floatf], aux, (aux1-1));
}

int" "{letter}({letter}|{digit}|","|" "|";")* {
	sscanf(yytext, "%s %s", vint[0], aux);
	intv++;
	aux1 = strlen(aux);
	aux2 = strpbrk(aux, ",");
	aux3 = strpbrk(aux, ";");
	if(aux2 || aux3) {
		strncpy(vint[intv], aux, (aux1-1));
	}else {
		strncpy(vint[intv], aux, aux1);
	}		
	aux2 = strtok(yytext, ",");
	aux2 = strtok(NULL, ",");
	while(aux2) {
		intv++;		
		aux3 = strpbrk(aux2, ";");
		if(aux3) {
			aux1 = strlen(aux2);			
			strncpy(vint[intv], aux2, (aux1-1));	
		}else {	
			strcpy(vint[intv], aux2);	
		}		
		aux2 = strtok(NULL, ",");		
	}
}

float" "{letter}({letter}|{digit}|","|" "|";")* {	
	sscanf(yytext, "%s %s", vfloat[0], aux);
	floatv++;
	aux1 = strlen(aux);
	aux2 = strpbrk(aux, ",");
	aux3 = strpbrk(aux, ";");
	if(aux2 || aux3) {
		strncpy(vfloat[floatv], aux, (aux1-1));
	}else {
		strncpy(vfloat[floatv], aux, aux1);
	}	
	aux2 = strtok(yytext, ",");
	aux2 = strtok(NULL, ",");	
	while(aux2) {
		floatv++;
		aux3 = strpbrk(aux2, ";");
		if(aux3) {
			aux1 = strlen(aux2);			
			strncpy(vfloat[floatv], aux2, (aux1-1));	
		}else {	
			strcpy(vfloat[floatv], aux2);	
		}	
		aux2 = strtok(NULL, ",");		
	}
}

. ;
\n ;

%%

#include <string.h>

int main(int argc, char *argv[]) {	
	int i;
	yyin = fopen(argv[1], "r");		
	yylex();
	
	printf("Variaveis Inteiras: \n");
	for(i=0; i<intv; i++) {
		printf("%s ", vint[i+1]);
	}
	printf("\nTotal de Variaveis Inteiras: %d", intv);	
	/////////////////////////////////////////////////////////
	printf("\nVariaveis Ponto Flutuante: \n");
	for(i=0; i<floatv; i++) {
		printf("%s ", vfloat[i+1]);
	}
	printf("\nTotal de Variaveis Ponto Flutuante: %d", floatv);	
	/////////////////////////////////////////////////////////
	printf("\nFunções Inteiras: \n");
	for(i=0; i<intf; i++) {
		printf("%s ", fint[i+1]);
	}
	printf("\nTotal de Funções Inteiras: %d", intf);
	/////////////////////////////////////////////////////////
	printf("\nFunções Ponto Flutuante: \n");
	for(i=0; i<floatf; i++) {
		printf("%s ", ffloat[i+1]);
	}
	printf("\nTotal de Funções Ponto Flutuante: %d\n", floatf);
	fclose(yyin);
	return 0;
}
