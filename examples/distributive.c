#include <stdio.h>
#include "../libspl.h"

int main()
{
	// This example is on the proof of Distributive Law
	CTL P = createVar(3), Q = createVar(2),
	    R = createVar(1);

	CTL A = splOPT(ANDTL, Q, R);//	Q & R = A
	CTL B = splOPT(ORTL,  P, A);//	P | A = B
	
	int num_var = 4;
	char *names[] = {"P","Q","R","P|(Q&R)"};
	char sep = ' ';
	for(int i=0;i<num_var;i++) printf("%s%c",names[i],(i==num_var-1)?'\n':sep);
	
	drawTable(B, sep);

	printf("------------------------------------------\n");

	CTL C = splOPT(ORTL,  P, Q);//	P | Q = C
	CTL D = splOPT(ORTL,  P, R);//	P | R = D
	CTL E = splOPT(ANDTL, C, D);//	C & D = E

	names[num_var-1] = "(P&Q)|(P&R)";
	for(int i=0;i<num_var;i++) printf("%s%c",names[i],(i==num_var-1)?'\n':sep);
	drawTable(E, sep);

	return 0;
}
