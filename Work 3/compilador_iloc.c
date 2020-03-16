#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

static int lbl;
static int reg;
int var=0;

int ex(nodeType *p) {
	int lbl1=0, lbl2=0, lbl3=0;
	int reg1, reg2;
	int	aux1=0, aux2=0, aux0=0;

	if (!p) return 0;
	switch(p->type) {
		case typeCon:
			printf("\tloadI %d, r%03d\n", p->con.value, reg1 = reg++);
			break;
		case typeId:
			printf("\tloadI @%c, r%03d\n", p->id.i + 'a', reg1 = reg++);
			int aux = (reg-1) < 0 ? reg:(reg-1);
			printf("\tload r%03d, r%03d\n", aux, reg1=reg++);
			break;
		case typeOpr:
			switch(p->opr.oper) {
				case WHILE:
					printf("L%03d:\n", lbl1 = lbl++);
					ex(p->opr.op[0]);
					aux0 = reg-1;
					lbl2 = lbl++;
					lbl3 = lbl++;
					printf("\tcbr r%03d, L%03d, L%03d\n", aux0, lbl2, lbl3);
					printf("L%03d:\n", lbl2);						
					ex(p->opr.op[1]);
					printf("\tjmpI L%03d\n", lbl1);
					printf("L%03d:\n", lbl3);
					break;
				case IF:
					ex(p->opr.op[0]);
					if (p->opr.nops > 2) {
						/* if else */
						aux0 = reg-1;
						lbl1 = lbl++;
						lbl2 = lbl++;
						printf("\tcbr r%03d, L%03d, L%03d\n", aux0, lbl1, lbl2);
						printf("L%03d:\n", lbl1);
						ex(p->opr.op[1]);
						printf("\tjmpI L%03d\n", lbl3 = lbl++);
						printf("L%03d:\n", lbl2);
						ex(p->opr.op[2]);
						printf("\tjmpI L%03d\n", lbl3);
						printf("L%03d:\n", lbl3);
					}else {
						/* if */
						aux0 = reg-1;
						lbl1 = lbl++;
						lbl2 = lbl++;	
						printf("\tcbr r%03d, L%03d, L%03d\n", aux0, lbl1, lbl2);
						printf("L%03d:\n", lbl1);
						ex(p->opr.op[1]);
						printf("\tjmpI L%03d\n", lbl2);
						printf("L%03d:\n", lbl2);
					}
					break;

				case PRINT:
					printf("\tloadI 1, rsys\n");					
					ex(p->opr.op[0]);
					aux0 = reg-1;
					printf("\tcall_sys r%03d\n", aux0);
					break;
				case '=':													
					ex(p->opr.op[1]);
					var = 0;
					printf("\tloadI @%c, r%03d\n", p->opr.op[0]->id.i + 'a', reg1 = reg++);									
					int aux = reg1-1;						
					printf("\tstore r%03d, r%03d\n", aux, reg1);
					break;
				default:
					ex(p->opr.op[0]);
					if(p->opr.op[1]->type == 1) var = 1;					
					ex(p->opr.op[1]);
					switch(p->opr.oper) {
						case '+':
							if(var) {
								aux1 = reg-1;
								aux2 = reg-3;
							}else {
								aux1 = reg-1;
								aux2 = reg-2;
							}
							printf("\tadd r%03d, r%03d, r%03d\n", aux1, aux2, reg1 = reg++); 
							break;
						case '-':
							if(var) {
								aux1 = reg-1;
								aux2 = reg-3;
							}else {
								aux1 = reg-1;
								aux2 = reg-2;
							}					
							printf("\tsub r%03d, r%03d, r%03d\n", aux1, aux2, reg1 = reg++); 
							break;
						case '*':
							if(var) {
								aux1 = reg-1;
								aux2 = reg-3;
							}else {
								aux1 = reg-1;
								aux2 = reg-2;
							}						
							printf("\tmult r%03d, r%03d, r%03d\n", aux1, aux2, reg1 = reg++);  
							break;
						case '/':
							if(var) {
								aux1 = reg-1;
								aux2 = reg-3;
							}else {
								aux1 = reg-1;
								aux2 = reg-2;
							}						
							printf("\tdiv r%03d, r%03d, r%03d\n", aux1, aux2, reg1 = reg++);  
							break;
						case '<':
							aux1 = reg-2;
							aux2 = reg-1;						
							printf("\tcmp_LT r%03d, r%03d, r%03d\n", aux1, aux2, reg1 = reg++);  
							break;
						case '>':
							aux1 = reg-2;
							aux2 = reg-1;						
							printf("\tcmp_GT r%03d, r%03d, r%03d\n", aux1, aux2, reg1 = reg++);  
							break;
						case GE:
							aux1 = reg-2;
							aux2 = reg-1;						
							printf("\tcmp_GE r%03d, r%03d, r%03d\n", aux1, aux2, reg1 = reg++);   
							break;
						case LE:
							aux1 = reg-2;
							aux2 = reg-1;						
							printf("\tcmp_LE r%03d, r%03d, r%03d\n", aux1, aux2, reg1 = reg++);   
							break;
						case NE:
							aux1 = reg-2;
							aux2 = reg-1;						
							printf("\tcmp_NE r%03d, r%03d, r%03d\n", aux1, aux2, reg1 = reg++);  
							break;
						case EQ:
							aux1 = reg-2;
							aux2 = reg-1;						
							printf("\tcmp_EQ r%03d, r%03d, r%03d\n", aux1, aux2, reg1 = reg++);   
							break;
					}
			}			
	}	
	return 0;
}
