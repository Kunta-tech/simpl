#ifndef LIBSPL_H
#define LIBSPL_H

/*!
 * Copyright (c) 2024 Kunta-tech. All Rights Reserved.
 * Under GNU License
 */

#include <stdint.h>
typedef uint8_t	 lg8;	// 8  bit logic
typedef uint16_t lg16;	// 16 bit logic
typedef uint32_t lg32;	// 16 bit logic
typedef uint8_t  LTL;	// Logic Table

struct ctl{
	lg32 lgTL;	// It is the state table of the expression
	uint8_t res;	// it stores the position of expression variables
};

typedef struct ctl CTL; // Custom Table

#define ANDTL (LTL)0x8	// 1000
#define ORTL  (LTL)0xE	// 1110
#define IFTL  (LTL)0xB	// 1011
#define NIFTL (LTL)0xD	// 1101
#define XORTL (LTL)0x6	// 0110
#define EQTL  (LTL)0x9	// 1001

const CTL SPL_TRUE = { .lgTL=1, .res=0 };
const CTL SPL_FALSE= { .lgTL=0, .res=0 };

CTL createVar(lg8);

void drawTable(CTL ,char);
void drawTables(int ,CTL* ,char);

char* splCTLtoString(CTL);

CTL splNOT(CTL);
CTL splOPT(LTL ,CTL ,CTL);

#endif // !LIBSPL_H
