#include <stdio.h>
#include <stdlib.h>
#include "buttons.h"
#include "interrupt.h"
#include "display.h"

const intrp IntrTable[13] = {interrupt_ignore};

int main() {
    *display_control = MODE4 | BG2;

    struct square s = {10, 10, 15, add_color(0, 20, 2)};
    volatile unsigned short* buffer = front_buffer;
    unsigned char black = add_color(0,0,0);

    clear_screen(front_buffer, black);
    clear_screen(back_buffer, black);

    while (1) {
        update_screen(buffer, black, &s);
        draw_square(buffer, &s);
        move_square(&s);
        wait_vblank();
        buffer = flip_buffers(buffer);
    }
}
