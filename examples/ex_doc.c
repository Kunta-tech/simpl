#include <stdio.h>
#include "../libspl.h"

int main(){
	/**
	[ This is an example problem from the paper, page no. 7 ]
	Let’s assume:
P: Jasmine is invited.
Q: Kanti is invited.
R: Samir is invited.
The following three conditions should be met:
a) P → ¬R: If Jasmine is invited, Samir will not be invited.
b) R → Q: If Samir is invited, Kanti will also be invited.
c) Q → P: If Kanti is invited, Jasmine will also be invited.
The compound proposition for the puzzle is:
	(P → ¬R) ∧ (R → Q) ∧ (Q → P)

	THE OUTPUT:	Table of P, Q, R, ANS
	Truth Cases:
		1)  !P & !Q & !R
		2)   P & !Q & !R
		3)   P &  Q & !R
	*/
	
	CTL P,Q,R;

	P = createVar(3);
	Q = createVar(2);
	R = createVar(1);

	CTL a = splOPT(IFTL, P, splNOT(R));
	CTL b = splOPT(IFTL, R, Q);
	CTL c = splOPT(IFTL, Q, P);

	CTL ANS = splOPT(ANDTL, splOPT(ANDTL, a, b), c);

	int num_var = 4;
	char sep = ',';
	char *names[] = {"P","Q","R","ANS"};
	for(int i=0;i<num_var;i++) printf("%s%c",names[i],(i==num_var-1)?'\n':sep);
	drawTable(ANS, sep);
}
