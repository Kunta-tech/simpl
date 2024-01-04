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
typedef uint32_t lg32;	// 16 bit logic
typedef uint8_t  LTL;	// Logic Table

typedef struct ctl CTL; // Custom Table
struct ctl{
	lg32 lgTL;
	uint8_t TLlen;
};

CTL createVar(){
	CTL newVar;
	newVar.lgTL = 2;
	newVar.TLlen = 2;
	return newVar;
}

void CTL_mirror(CTL *obj){
	obj->lgTL |= (obj->lgTL)<<(obj->TLlen);
	obj->TLlen <<=1;
}
void CTL_expand(CTL *obj){
	lg32 temp = 0;
	for(int i=0;i<obj->TLlen;i++){
		if((obj->lgTL)&(1<<i)){
			temp |= 1<<(i*2);
			temp |= 1<<(i*2 + 1);
		}
	}
	obj->lgTL = temp;
	obj->TLlen <<=1;
}

//	TT: Truth Table
/**	For anyone watching this code
 *	I know this sh*t is messed up
 *		So, please feel free to
 *	share a better code for this🥺
 **/
void printTT_CSV(int n, char *inst_set, CTL *Table, char **names){
	/* Checking the parameters */
	for(int i=0;i<n;i++){
		// inst_set has char from 0 to 9
		assert(inst_set[i]>='0' && inst_set[i]<='9');
		// Table[i].TLlen is a power of 2
		int temp = Table[i].TLlen;
		while (temp>0 && temp%2==0) temp >>= 1;
		assert(temp == 1);
	}

	/* Printing the headers */
	for(int i=0;i<n;i++) printf("%s,",names[i]);
	printf("\n");

	int maxlength = 0;
	for(int i=0;i<n;i++) maxlength = (Table[i].TLlen>maxlength)?Table[i].TLlen:maxlength;

	for(int i=0;i<n;i++){
		int cnt = inst_set[i]-'0';
		while (Table[i].TLlen<maxlength && cnt-->0) CTL_expand(&Table[i]);
		while (Table[i].TLlen<maxlength) CTL_mirror(&Table[i]);
	}

	for(int i=0;i<maxlength;i++){
		for(int j=0;j<n;j++){
			printf("%d,",!!(Table[j].lgTL&(1<<i)));
		}
		printf("\n");
	}
}

char* splCTLtoString(CTL A){
	char *str;
	str = (char*)malloc(A.TLlen*sizeof(char));
	for(int i=0;i<A.TLlen;i++) str[A.TLlen-1-i] = '0'+!!(A.lgTL&(1<<i));
	return str;
}

CTL splOPT(LTL TL, CTL obj1, CTL obj2){
	CTL newTL;
	if(obj2.TLlen>obj1.TLlen){
		CTL temp = obj2;
		obj2 = obj1;
		obj1 = temp;
	}

	newTL.lgTL = 0;
	newTL.TLlen = obj1.TLlen;
	newTL.TLlen = obj1.TLlen*obj2.TLlen;

	int b1,b2, szdiff = obj1.TLlen/obj2.TLlen;
	int cnt = 0;

	for (int i=0;i<obj1.TLlen;i++) {
		b1 = obj1.lgTL&(1<<i);
		b1 = !!b1;
		for (int j=0;j<obj2.TLlen;j++) {
			b2 = obj2.lgTL&(1<<j);
			b2 = !!b2;
			if(TL&(1<<((b1*2)+b2))){
				newTL.lgTL |= 1<<(cnt);
			}
			cnt++;
		}
	}
	return newTL;
}
