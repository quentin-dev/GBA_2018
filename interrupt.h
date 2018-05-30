#include <stdio.h>
#include <stdlib.h>

void interrupt_ignore();

typedef void (*intrp)();
extern const intrp IntrTable[13];
