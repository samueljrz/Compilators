#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
 int operando, cont = 0;
 char *pt;
 char op, *opc;
 char string[300];
 strncpy(string, opc, 5);
 printf("%s", string);
 printf("entre com uma expressao: ");
 scanf("%[^\n]",string);
 pt = strtok(string,",");
 pt = strtok(NULL,","); 
while(pt) //enquanto pt # NULL
 {
 cont++;
 printf("\n token %d: %s", cont, pt);
 pt = strtok(NULL,",");
 }

 printf("\n cont = %d \n \n", cont);
 system("pause");
 } 
