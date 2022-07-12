

/*
 *
 * Font3x5
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : Font4X6.h
 * Date                : 17.02.2012
 * Font size in bytes  : 1472
 * Font width          : 3
 * Font height         : 5
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef FONT4x6_H
#define FONT4x6_H

#define FONT4x6_WIDTH 4
#define FONT4x6_HEIGHT 6

const static uint8_t Font4x6[] PROGMEM = {
    0x0, 0x0, //C0, // size
    0x04, // width
    0x07, // height
    0x20, // first char
    0x60, // char count
    
		0x00, 0x00, 0x00, 0x00,                  // Code for char  
        0x00, 0x5E, 0x00, 0x00,                  // Code for char !
        0x00, 0x06, 0x00, 0x06,                  // Code for char "
        0x00, 0x00, 0x00, 0x00,                  // Code for char #
        0x00, 0x00, 0x00, 0x00,                  // Code for char $
        0x00, 0x00, 0x00, 0x00,                  // Code for char %
        0x00, 0x00, 0x00, 0x00,                  // Code for char &
        0x00, 0x00, 0x00, 0x00,                  // Code for char '
        0x00, 0x3C, 0x42, 0x00,                  // Code for char (
        0x00, 0x42, 0x3C, 0x00,                  // Code for char )
        0x0A, 0x04, 0x0A, 0x00,                  // Code for char *
        0x08, 0x1C, 0x08, 0x00,                  // Code for char +
        0x40, 0x20, 0x00, 0x00,                  // Code for char ,
        0x08, 0x08, 0x08, 0x00,                  // Code for char -
        0x00, 0x60, 0x60, 0x00,                  // Code for char .
        0x20, 0x10, 0x08, 0x04,                  // Code for char /
        0x7E, 0x42, 0x42, 0x7E,                  // Code for char 0
        0x42, 0x7E, 0x40, 0x00,                  // Code for char 1
        0x72, 0x52, 0x52, 0x5E,                  // Code for char 2
        0x52, 0x52, 0x52, 0x7E,                  // Code for char 3
        0x1E, 0x10, 0x10, 0x7E,                  // Code for char 4
        0x5E, 0x52, 0x52, 0x72,                  // Code for char 5
        0x7E, 0x52, 0x52, 0x72,                  // Code for char 6
        0x02, 0x02, 0x02, 0x7E,                  // Code for char 7
        0x7E, 0x52, 0x52, 0x7E,                  // Code for char 8
        0x5E, 0x52, 0x52, 0x7E,                  // Code for char 9
        0x00, 0x24, 0x24, 0x00,                  // Code for char :
        0x00, 0x44, 0x24, 0x00,                  // Code for char ;
        0x00, 0x00, 0x00, 0x00,                  // Code for char <
        0x24, 0x24, 0x24, 0x24,                  // Code for char =
        0x00, 0x00, 0x00, 0x00,                  // Code for char >
        0x00, 0x00, 0x00, 0x00,                  // Code for char ?
        0x00, 0x00, 0x00, 0x00,                  // Code for char @
        0x7C, 0x12, 0x12, 0x7C,                  // Code for char A
        0x7E, 0x52, 0x52, 0x2C,                  // Code for char B
        0x3C, 0x42, 0x42, 0x24,                  // Code for char C
        0x7E, 0x42, 0x42, 0x3C,                  // Code for char D
        0x7E, 0x52, 0x52, 0x52,                  // Code for char E
        0x7E, 0x12, 0x12, 0x12,                  // Code for char F
        0x3C, 0x42, 0x52, 0x34,                  // Code for char G
        0x7E, 0x10, 0x10, 0x7E,                  // Code for char H
        0x42, 0x7E, 0x42, 0x00,                  // Code for char I
        0x20, 0x40, 0x42, 0x3E,                  // Code for char J
        0x7E, 0x18, 0x24, 0x42,                  // Code for char K
        0x7E, 0x40, 0x40, 0x40,                  // Code for char L
        0x7E, 0x0C, 0x0C, 0x7E,                  // Code for char M
        0x7E, 0x0C, 0x10, 0x7E,                  // Code for char N
        0x3C, 0x42, 0x42, 0x3C,                  // Code for char O
        0x7E, 0x12, 0x12, 0x0C,                  // Code for char P
        0x3C, 0x52, 0x22, 0x5C,                  // Code for char Q
        0x7E, 0x12, 0x32, 0x4C,                  // Code for char R
        0x4C, 0x52, 0x52, 0x22,                  // Code for char S
        0x02, 0x7E, 0x02, 0x00,                  // Code for char T
        0x3E, 0x40, 0x40, 0x3E,                  // Code for char U
        0x1E, 0x20, 0x40, 0x3E,                  // Code for char V
        0x7E, 0x30, 0x30, 0x7E,                  // Code for char W
        0x66, 0x18, 0x18, 0x66,                  // Code for char X
        0x26, 0x48, 0x48, 0x3E,                  // Code for char Y
        0x62, 0x52, 0x4A, 0x46,                  // Code for char Z
        0x00, 0x7E, 0x42, 0x00,                  // Code for char [
        0x04, 0x08, 0x10, 0x20,                  // Code for char BackSlash
        0x00, 0x42, 0x7E, 0x00,                  // Code for char ]
        0x08, 0x04, 0x02, 0x04,                  // Code for char ^
        0x40, 0x40, 0x40, 0x40,                  // Code for char _
        0x00, 0x02, 0x04, 0x00,                  // Code for char `
        0x20, 0x54, 0x54, 0x78,                  // Code for char a
        0x7E, 0x48, 0x48, 0x30,                  // Code for char b
        0x38, 0x44, 0x44, 0x28,                  // Code for char c
        0x30, 0x48, 0x48, 0x7E,                  // Code for char d
        0x38, 0x54, 0x54, 0x18,                  // Code for char e
        0x08, 0x7C, 0x0A, 0x0A,                  // Code for char f
        0x48, 0x94, 0x94, 0x7C,                  // Code for char g
        0x7E, 0x10, 0x08, 0x70,                  // Code for char h
        0x48, 0x7A, 0x40, 0x00,                  // Code for char i
        0x40, 0x80, 0x88, 0x7A,                  // Code for char j
        0x7E, 0x10, 0x28, 0x44,                  // Code for char k
        0x00, 0x3E, 0x40, 0x40,                  // Code for char l
        0x7C, 0x18, 0x18, 0x7C,                  // Code for char m
        0x7C, 0x08, 0x04, 0x78,                  // Code for char n
        0x38, 0x44, 0x44, 0x38,                  // Code for char o
        0x7C, 0x14, 0x14, 0x08,                  // Code for char p
        0x08, 0x14, 0x14, 0x7C,                  // Code for char q
        0x7C, 0x08, 0x04, 0x08,                  // Code for char r
        0x48, 0x54, 0x54, 0x24,                  // Code for char s
        0x04, 0x3E, 0x44, 0x44,                  // Code for char t
        0x3C, 0x40, 0x20, 0x7C,                  // Code for char u
        0x1C, 0x20, 0x40, 0x3C,                  // Code for char v
        0x7C, 0x30, 0x30, 0x7C,                  // Code for char w
        0x4C, 0x30, 0x30, 0x4C,                  // Code for char x
        0x4C, 0x90, 0x90, 0x7C,                  // Code for char y
        0x64, 0x54, 0x54, 0x4C,                  // Code for char z
        0x00, 0x00, 0x00, 0x00,                  // Code for char {
        0x00, 0x00, 0x00, 0x00,                  // Code for char |
        0x00, 0x00, 0x00, 0x00,                  // Code for char }
        0x00, 0x00, 0x00, 0x00                   // Code for char ~
};

#endif
