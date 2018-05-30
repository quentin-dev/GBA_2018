#include <stdio.h>
#include <stdlib.h>
#include "buttons.h"
#include "interrupt.h"

#define WIDTH 240
#define HEIGHT 160

#define MODE3 0x0003
#define MODE4 0x004
#define BG2 0x0400

#define SHOW_BACK 0x10

const intrp IntrTable[13] = {interrupt_ignore};

volatile unsigned long* display_control = (volatile unsigned long*) 0x4000000;
volatile unsigned short* screen = (volatile unsigned short*) 0x6000000;

void put_pixel(int row, int col, unsigned short color);

void draw_square(struct square *s)
{
    for(unsigned short row = s->y; row < (s->y + s->size); row++){
        for(unsigned short col = s->x; col < (s->x + s->size); col++){
            put_pixel(row, col, s->color);
        }
    }
}

unsigned short make_color(unsigned char r, unsigned char g, unsigned char b) {
    unsigned short color = (b & 0x1f) << 10;
    color |= (g & 0x1f) << 5;
    color |= (r & 0x1f);
    return color;
}

void put_pixel(int row, int col, unsigned short color) {
    screen[row * WIDTH + col] = color;
}

void clear_screen()
{
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++)
            put_pixel(x, y, 0);
    }
}

int main() {
    *display_control = MODE3 | BG2;

    struct square s = {10, 10, 15, make_color(0, 20, 2)};

    while (1) {
        clear_screen();
        move_square(&s);
        draw_square(&s);
    }
}
