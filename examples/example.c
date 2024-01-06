#include <stdio.h>
#include "../libspl.h"

int main()
{
	CTL A = createVar(3), B = createVar(2),
	    C = createVar(1);

	CTL D = splOPT(ORTL, A, B);		// A OR B -> D
	CTL E = splOPT(ANDTL, D, C);		// D AND C -> E

	int num_var = 5;
	char sep = ',';
	char *names[] = {"A","B","C","A|B","(A|B)&C"};
	for(int i=0;i<num_var;i++) printf("%s%c",names[i],(i==num_var-1)?'\n':sep);
	CTL table[] = {A,B,C,D,E};

	drawTables(num_var,table,sep);
	return 0;
}
