#include <stdio.h>
#include <stdlib.h>
#include "libspl.h"

int main()
{
	CTL A = createVar(), B = createVar(),
	    C = createVar();

	CTL D = splOPT(ORTL, A, B);		// A OR B -> D
	char *str = splCTLtoString(C);
	printf("C: %s, len=%d\n",str,C.TLlen);
	free(str);
	CTL E = splOPT(ANDTL, D, C);		// D AND C -> E
	str = splCTLtoString(E);
	printf("E: %s, len=%d\n",str,E.TLlen);
	free(str);

	CTL TABLE[5];
	TABLE[0] = A;
	TABLE[1] = B;
	TABLE[2] = C;
	TABLE[3] = D;
	TABLE[4] = E;

	char *names[] = {"A","B","C","A|B","(A|B)&C"};
	char *inset = "21010";

	printTT_CSV(5, inset, TABLE, names);

	return 0;
}
