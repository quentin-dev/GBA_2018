#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdio.h>
#include <stdlib.h>

#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_SELECT 0x0004
#define KEY_START 0x0008
#define KEY_RIGHT 0x0010
#define KEY_LEFT 0x0020
#define KEY_UP 0x0040
#define KEY_DOWN 0x0080
#define KEY_SR 0x0100
#define KEY_SL 0x0200

extern volatile unsigned short* KEY_INPUT;

typedef struct square square;
struct square {
    unsigned short x, y, size, color;
};

unsigned char key_pressed(unsigned short key);

void move_square(square* s);

#endif
