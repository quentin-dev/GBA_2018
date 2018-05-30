#include <stdio.h>
#include <stdlib.h>
#include "display.h"

volatile unsigned short* palette = (volatile unsigned short*) 0x5000000;
volatile unsigned short* front_buffer = (volatile unsigned short*) 0x6000000;
volatile unsigned short* back_buffer = (volatile unsigned short*) 0x600A000;
volatile unsigned long* display_control = (volatile unsigned long*) 0x4000000;
volatile unsigned short* scanline_counter = (volatile unsigned short*) 0x4000006;

int next_palette_index = 0;

void put_pixel(volatile unsigned short* buffer, int row, int col, unsigned char color)
{
    unsigned short offset = (row * WIDTH + col) >> 1;
    unsigned short pixel = buffer[offset];

    if(col & 1)
        buffer[offset] = (color << 8) | (pixel & 0x00ff);
    else
        buffer[offset] = (pixel & 0xff00) | color;
}

unsigned char add_color(unsigned char r, unsigned char g, unsigned char b)
{
    unsigned short color = b << 10;
    color += g << 5;
    color += r;

    palette[next_palette_index] = color;
    next_palette_index += 1;

    return next_palette_index - 1;
}

void draw_square(volatile unsigned short* buffer, struct square* s)
{
    short row, col;

    for(row = s->y; row < (s->y + s->size); row++){
        for(col = s->x; col < (s->x + s->size); col++)
            put_pixel(buffer, row, col, s->color);
    }
}

void clear_screen(volatile unsigned short* buffer, unsigned short color)
{
    unsigned short row, col;

    for(row = 0; row < HEIGHT; row++){
        for(col=0; col < WIDTH; col++)
            put_pixel(buffer, row, col, color);
    }
}

volatile unsigned short* flip_buffers(volatile unsigned short* buffer)
{
    if (buffer == front_buffer){
        *display_control &= ~SHOW_BACK;
        return back_buffer;
    } else {
        *display_control |= SHOW_BACK;
        return front_buffer;
    }
}

void wait_vblank()
{
    while(*scanline_counter < 160){}
}

void update_screen(volatile unsigned short* buffer, unsigned short color, struct square* s)
{
    short row, col;
    for(row = s->y - 3; row < (s->y + s->size + 3); row++){
        for(col = s->x - 3; col < (s->x + s->size + 3); col++)
            put_pixel(buffer, row, col, color);
    }
}
