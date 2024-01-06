#include <stdio.h>
#include "../libspl.h"

int main()
{
	// This example is on the proof of De Morgan's Law
	CTL P = createVar(2), Q = createVar(1);

	CTL A = splOPT(ORTL, P, Q);//	P OR Q = A
	A = splNOT(A);
	CTL B = splOPT(ANDTL, splNOT(P), splNOT(Q));// !P AND !Q = B
	
	int num_var = 4;
	char *names[] = {"P","Q","!(P|Q)","(!P)&(!Q)"};
	char sep = ' ';
	for(int i=0;i<num_var;i++) printf("%s%c",names[i],(i==num_var-1)?'\n':sep);

	CTL table[] = {P,Q,A,B};
	drawTables(num_var, table, sep);

	return 0;
}
