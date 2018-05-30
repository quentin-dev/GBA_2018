#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <stdio.h>
#include <stdlib.h>

void interrupt_ignore();

typedef void (*intrp)();
extern const intrp IntrTable[13];

#endif
