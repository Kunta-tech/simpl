#include <asm-generic/errno.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*!
 * Copyright (c) 2024 Kunta-tech. All Rights Reserved.
 * Under GNU License
 */

typedef uint8_t	 lg8;	// 8  bit logic
typedef uint16_t lg16;	// 16 bit logic
typedef uint32_t lg32;	// 32 bit logic
typedef uint8_t  LTL;	// Logic Table

typedef struct ctl CTL; // Custom Table
struct ctl{
	lg32 lgTL;	// It is the state table of the expression
	uint8_t res;	// it stores the position of expression variables
};

uint8_t CTL_len(CTL obj){
	uint8_t cnt = 0;
	uint8_t n = obj.res;
	if(n==0) return 1;
	while (n>0) { n>>=1;cnt++; }
	cnt = 1<<cnt;
	return cnt;
}

void CTL_expand(CTL *obj,uint8_t tres){
	assert(tres>=1 && tres<=5);
	tres = 1<<(tres-1);
	lg32 temp = 0;
	int TLlen = 0;

	uint8_t n = obj->res;
	while (n>0) { n>>=1;TLlen++; }
	TLlen = 1<<TLlen;
	int cnt=0;
	for(int i=0;i<TLlen;i++){
		for(int j=0;j<tres;j++){
			temp |= (!!(obj->lgTL&(1<<i)))<<cnt;
			cnt++;
		}
	}

	obj->lgTL = temp;
	obj->res  = tres;
}

/* Creates A new State variable table */
CTL createVar(uint8_t res){
	if(!(res>=1 && res<=5)) res = 1;
	CTL newVar = {
		.lgTL = 2, /* There are only two states in a single variable 0 & 1 */
		.res  = 1
	};
	if(res>1) CTL_expand(&newVar, res);
	return newVar;
}

void drawTable(CTL obj,char sep){
	// drawTable() prints the boolean states of Inital Variables
	int TLlen = CTL_len(obj), rtemp;
	for(int i=0;i<TLlen;i++){
		rtemp = TLlen>>1;
		for(;rtemp>0;rtemp>>=1)	printf("%c%c",(i&rtemp)?'T':'F',sep);
		printf("%d\n",!!(obj.lgTL&(1<<i)));
	}
}

void drawTables(int n, CTL *table, char sep){
	// drawTables() does not prints the boolean states of Inital Variables
	// As it believes all the variables are present in the table[]
	int maxlen = 0,lens[n];
	for(int i=0;i<n;i++) {
		lens[i] = CTL_len(table[i]);
		maxlen = (lens[i]>maxlen)?lens[i]:maxlen;
	}
	for(int i=0;i<maxlen;i++){
		for(int j=0;j<n;j++)
			printf("%c%c",(table[j].lgTL&(1<<(i%lens[j])))?'T':'F',(j==n-1)?'\n':sep);
	}
}


char* splCTLtoString(CTL A){
	char *str;
	int len = CTL_len(A);
	str = (char*)malloc(len*sizeof(char));
	for(int i=0;i<len;i++) str[len-1-i] = '0'+!!(A.lgTL&(1<<i));
	return str;
}

CTL splNOT(CTL obj){
	CTL newobj = obj;
	int n = CTL_len(obj);
	for(int i=0;i<n;i++) newobj.lgTL ^= 1<<i;
	return newobj;
}

CTL splOPT(LTL TL, CTL obj1, CTL obj2){
	CTL newTL;
	//assert((obj1.res&obj2.res)==0);

	newTL.lgTL = 0;
	newTL.res  = obj1.res | obj2.res;
	uint8_t len1 = CTL_len(obj1),
		len2 = CTL_len(obj2), newlen;
	if(len1 >= len2) newlen = len1;
	else		 newlen = len2;
	
	int b1,b2;
	int cnt = 0;
	for(int i=0;i<newlen;i++){
		b1 = obj1.lgTL&(1<<(i%len1));
		b1 = !!b1;
		b2 = obj2.lgTL&(1<<(i%len2));
		b2 = !!b2;
		if(TL&(1<<((b1*2)+b2))) newTL.lgTL |= 1<<i;
	}
	return newTL;
}
