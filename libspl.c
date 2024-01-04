#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t	 lg8;	// 8  bit logic
typedef uint16_t lg16;	// 16 bit logic
typedef uint32_t lg32;	// 16 bit logic
typedef uint8_t  LTL;	// Logic Table

typedef struct ctl CTL; // Custom Table
struct ctl{
	lg32 lgTL;
	uint8_t TLlen;
};

char* splCTLtoString(CTL A){
	char *str;
	str = (char*)malloc(A.TLlen*sizeof(char));
	for(int i=0;i<A.TLlen;i++) str[i] = '0'+!!(A.lgTL&(1<<i));
	return str;
}

CTL splOPT(LTL TL, CTL obj1, CTL obj2){
	CTL newTL;
	newTL.lgTL = 0;
	newTL.TLlen = (obj1.TLlen>=obj2.TLlen)?obj1.TLlen:obj2.TLlen;
	newTL.TLlen <<= 1;

	int b1,b2;

	for (int i=0;i<obj1.TLlen;i++) {
		b1 = obj1.lgTL&(1<<i);
		b1 = !!b1;
		for (int j=0;j<obj2.TLlen;j++) {
			b2 = obj2.lgTL&(1<<j);
			b2 = !!b2;
			if(TL&((b1<<1)|b2)) newTL.lgTL |= 1<<((1<<j)<<i);
		}
	}
	return newTL;
}
