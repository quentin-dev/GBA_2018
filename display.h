#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdio.h>
#include <stdlib.h>
#include "buttons.h"

#define WIDTH 240
#define HEIGHT 160

#define MODE3 0x0003
#define MODE4 0x0004
#define BG2 0x0400

#define SHOW_BACK 0x10

void draw_square(volatile unsigned short* buffer, struct square* s);
void clear_screen(volatile unsigned short* buffer, unsigned short color);

volatile unsigned short* flip_buffers(volatile unsigned short* buffer);
void put_pixel(volatile unsigned short* buffer, int row, int col, unsigned char color);

//extern int next_palette_index;
extern volatile unsigned short* front_buffer;
extern volatile unsigned short* back_buffer;
extern volatile unsigned short* palette;
extern volatile unsigned long* display_control;
unsigned char add_color(unsigned char r, unsigned char g, unsigned char b);

#endif
