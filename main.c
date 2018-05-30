#include <stdio.h>
#include <stdlib.h>
#include "buttons.h"
#include "interrupt.h"
#include "display.h"

const intrp IntrTable[13] = {interrupt_ignore};

int main() {
    *display_control = MODE4 | BG2;

    struct square s = {10, 10, 15, add_color(0, 20, 2)};
    volatile unsigned short* buffer = back_buffer;
    unsigned char blue = add_color(2,0,20); // blue = black + 2
    //unsigned char black = add_color(0,0,0);
    while (1) {
        clear_screen(buffer, blue);
        move_square(&s);
        draw_square(buffer, &s);
        buffer = flip_buffers(buffer);
    }
}
