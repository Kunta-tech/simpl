#include <stdio.h>
#include "../libspl.h"

int main()
{
	CTL A = createVar(4), B = createVar(3),
	    C = createVar(2), C2= createVar(1);

	CTL D = splOPT(IFTL, A, B);//	A->B = D
	CTL G = splOPT(ORTL, C, C2);//	C|C2 = G
	CTL E = splOPT(ANDTL, D, G);//	D&G  = E
	
	char *names[] = {"A","B","C","C2","(A->B)&(C|C2)"};
	for(int i=0;i<5;i++) printf("%s%c",names[i],(i==4)?'\n':',');
	
	drawTable(E, ',');

	return 0;
}
