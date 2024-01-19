#include <stdio.h>
#include "../libspl.h"

int main()
{
	/**
	 * Problem:	Show that
	 *	
	 **/
	CTL P,Q,R;
	P = createVar(3);
	Q = createVar(2);
	R = createVar(1);

	CTL PQ = splOPT(ANDTL, P, Q);
	CTL nPQ = splNOT(PQ);
	CTL A = splOPT(ORTL, nPQ, R);
	CTL res = splOPT(IFTL, A, splNOT(P));

	int num_var = 7;
	char *names[] = {"P","Q","R","P&Q","!(P&Q)","!(P&Q)|R","(!(P&Q)|R)->!P"};
	char sep = ',';
	for(int i=0;i<num_var;i++) printf("%s%c",names[i],(i==num_var-1)?'\n':sep);

	CTL table[] = {P,Q,R,PQ,nPQ,A,res};
	drawTables(num_var,table,sep);

	return 0;
}
