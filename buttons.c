#include <stdio.h>
#include <stdlib.h>
#include "buttons.h"

volatile unsigned short* KEY_INPUT = (volatile unsigned short*) 0x04000130;

unsigned char key_pressed(unsigned short key)
{
    unsigned short pressed = *KEY_INPUT & key;
    if(pressed == 0)
        return 1;
    else
        return 0;
}

void move_square(struct square* s)
{
    if (key_pressed(KEY_DOWN))
        s->y += 3;
    if (key_pressed(KEY_UP))
        s->y -= 3;
    if (key_pressed(KEY_RIGHT))
        s->x += 3;
    if (key_pressed(KEY_LEFT))
        s->x -= 3;
}
