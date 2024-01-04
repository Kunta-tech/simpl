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

void swap(void *A,void *B){
	void *C = A;
	A = B;
	B = C;
}

char* splCTLtoString(CTL A){
	char *str;
	str = (char*)malloc(A.TLlen*sizeof(char));
	for(int i=0;i<A.TLlen;i++) str[A.TLlen-1-i] = '0'+!!(A.lgTL&(1<<i));
	return str;
}

CTL splOPT(LTL TL, CTL obj1, CTL obj2){
	CTL newTL;
	if(obj2.TLlen>obj1.TLlen)	swap(&obj1,&obj2);

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
