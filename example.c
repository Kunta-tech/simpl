#include <stdio.h>
#include <stdlib.h>
#include "libspl.h"

int main()
{
	CTL A, B;
	A.lgTL = 2;
	A.TLlen = 2;
	B.lgTL = 2;
	B.TLlen = 2;

	CTL C = splOPT(ORTL, A, B);
	char *str = splCTLtoString(C);
	printf("C: %s, len=%d\n",str,C.TLlen);
	free(str);
	return 0;
}
