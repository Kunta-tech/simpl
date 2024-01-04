#include <stdio.h>
#include <stdlib.h>
#include "libspl.h"

int main()
{
	CTL A = createVar(), B = createVar();

	CTL C = splOPT(ORTL, A, B);		// A OR B -> C
	char *str = splCTLtoString(C);
	printf("C: %s, len=%d\n",str,C.TLlen);
	free(str);
	A = splOPT(ANDTL, B, C);		// C AND D -> E
	str = splCTLtoString(A);
	printf("A: %s, len=%d\n",str,A.TLlen);
	free(str);

	CTL TABLE[5];
	TABLE[0] = B;
	TABLE[1] = B;
	TABLE[2] = B;
	TABLE[3] = C;
	TABLE[4] = A;

	char *names[] = {"A","B","C","A & B","(A & B) | C"};
	char *inset = "21010";

	printTT_CSV(5, inset, TABLE, names);

	return 0;
}
