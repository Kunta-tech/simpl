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
	lg32 lgTL;
	uint8_t TLlen;
};

typedef struct ctl CTL; // Custom Table

#define ANDTL (LTL)8	// 1000
#define ORTL  (LTL)14	// 1110

CTL createVar();

void printTT_CSV(int, char*, CTL*, char**);

char* splCTLtoString(CTL);

CTL splOPT(LTL ,CTL ,CTL);

#endif // !LIBSPL_H
