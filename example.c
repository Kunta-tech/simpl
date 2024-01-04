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
	A = splOPT(ANDTL, C, B);		// C AND D -> E
	str = splCTLtoString(A);
	printf("A: %s, len=%d\n",str,A.TLlen);
	free(str);

	return 0;
}
