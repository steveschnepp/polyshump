#include "p8sdl.h"

const SDL_Color VGA_COLORS[16] = {
	{0x00, 0x00, 0x00, 0xFF},	// Black
	{0x00, 0x00, 0xAA, 0xFF},	// Blue
	{0x00, 0xAA, 0x00, 0xFF},	// Green
	{0x00, 0xAA, 0xAA, 0xFF},	// Cyan
	{0xAA, 0x00, 0x00, 0xFF},	// Red
	{0xAA, 0x00, 0xAA, 0xFF},	// Magenta
	{0xAA, 0x55, 0x00, 0xFF},	// Brown
	{0xAA, 0xAA, 0xAA, 0xFF},	// Light Gray
	{0x55, 0x55, 0x55, 0xFF},	// Dark Gray
	{0x55, 0x55, 0xFF, 0xFF},	// Light Blue
	{0x55, 0xFF, 0x55, 0xFF},	// Light Green
	{0x55, 0xFF, 0xFF, 0xFF},	// Light Cyan
	{0xFF, 0x55, 0x55, 0xFF},	// Light Red
	{0xFF, 0x55, 0xFF, 0xFF},	// Light Magenta
	{0xFF, 0xFF, 0x55, 0xFF},	// Yellow
	{0xFF, 0xFF, 0xFF, 0xFF}	// White
};

