#include <stdio.h>
#include "../libspl.h"

int main()
{
	/**
	 * Problem:	Show that
	 *	( P | Q ) & ( !P | R ) -> ( Q | R )
	 *	is Tautology
	 **/
	CTL P,Q,R;
	P = createVar(3);
	Q = createVar(2);
	R = createVar(1);

	CTL A = splOPT(ORTL, P, Q);
	CTL B = splOPT(ORTL, splNOT(P), R);
	CTL C = splOPT(ORTL, Q, R);

	CTL D = splOPT(ANDTL, A, B);
	CTL E = splOPT(IFTL, D, C);
	
	int num_var = 8;
	char *names[] = {"P","Q","R","P|Q","!P|R","Q|R","(P|Q)&(!P|R)","(P|Q)&(!P|R)->(Q|R)"};
	char sep = ',';
	for(int i=0;i<num_var;i++) printf("%s%c",names[i],(i==num_var-1)?'\n':sep);

	CTL table[] = {P,Q,R,A,B,C,D,E};
	drawTables(num_var,table,sep);

	return 0;
}
