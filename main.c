#include <stdio.h>
#include <stdlib.h>
#include "buttons.h"

/* the width and height of the screen */
#define WIDTH 240
#define HEIGHT 160

/* these identifiers define different bit positions of the display control */
#define MODE3 0x0003
#define MODE4 0x004
#define BG2 0x0400

#define SHOW_BACK 0x10

volatile unsigned long* display_control = (volatile unsigned long*) 0x4000000;
volatile unsigned short* screen = (volatile unsigned short*) 0x6000000;

/*volatile unsigned short* KEY_INPUT = (volatile unsigned short*) 0x04000130;

#define KEY_UP 0x0040 // 0000 0000 0100 0000
#define KEY_DOWN 0x0080
#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_ANY 0x03FF // 0000 0011 1111 1111
*/

void put_pixel(int row, int col, unsigned short color);

/*struct square {
    unsigned short x, y, size, color;
};*/

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
    /* we set the mode to mode 3 with background 2 on */
    *display_control = MODE3 | BG2;

    struct square s = {10, 10, 15, make_color(0, 20, 2)};

    while (1) {
        clear_screen();
        move_square(&s);
        draw_square(&s);
    }
}

/* the game boy advance uses "interrupts" to handle certain situations
 * for now we will ignore these */
void interrupt_ignore() {
}

/* this table specifies which interrupts we handle which way
 * for now, we ignore all of them */
typedef void (*intrp)();
const intrp IntrTable[13] = {
    interrupt_ignore,   /* V Blank interrupt */
    interrupt_ignore,   /* H Blank interrupt */
    interrupt_ignore,   /* V Counter interrupt */
    interrupt_ignore,   /* Timer 0 interrupt */
    interrupt_ignore,   /* Timer 1 interrupt */
    interrupt_ignore,   /* Timer 2 interrupt */
    interrupt_ignore,   /* Timer 3 interrupt */
    interrupt_ignore,   /* Serial communication interrupt */
    interrupt_ignore,   /* DMA 0 interrupt */
    interrupt_ignore,   /* DMA 1 interrupt */
    interrupt_ignore,   /* DMA 2 interrupt */
    interrupt_ignore,   /* DMA 3 interrupt */
    interrupt_ignore,   /* Key interrupt */
};
