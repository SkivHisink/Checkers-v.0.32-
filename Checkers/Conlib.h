#pragma once
//extern "C" {

/*////////////////////////////////////////////////////////////////////////////
// Output functions
////////////////////////////////////////////////////////////////////////////*/

/*////////////////////////////////////////////////////////////////////////////
// 6 functions below
// If the function succeeds, the return value is nonzero.
// If the function fails, the return value is zero.
// To get extended error information, call GetLastError()
////////////////////////////////////////////////////////////////////////////*/

int	GotoXY(int x, int y);		/* moves cursor to given position (x,y) */
int	GetXY(int *px, int *py);	/* retrieves current cursor position */
int	MaxXY(int *px, int *py);	/* retrieves current maximal window coordinates */
int	ClearConsole();					/* clears console window */

/* controls the cursor visibility (depends on bVisible value) */
int	ConShowCursor(int bVisible);

/* prints formatted string at current cursor position */
int	OutTxt(const char *, ...);
void frame(int maxX, int maxY, int foregroung);
/*////////////////////////////////////////////////////////////////////////////
// Input functions
////////////////////////////////////////////////////////////////////////////*/

int KeyPressed();	/* non zero if key was pressed */
int GetKey();		/* returns key code, positive means regular character,
					   negative means extended character */

/*////////////////////////////////////////////////////////////////////////////
// Special characters codes
////////////////////////////////////////////////////////////////////////////*/

#define KEY_ESC		27
#define KEY_ENTER	13
#define KEY_SPACE	32

/*////////////////////////////////////////////////////////////////////////////
// Extended characters codes
////////////////////////////////////////////////////////////////////////////*/

#define KEY_UP		-72		/* Up arrow */
#define KEY_LEFT	-75		/* Left arrow */
#define KEY_RIGHT	-77		/* Right arrow */
#define KEY_DOWN	-80		/* Down arrow */

/*////////////////////////////////////////////////////////////////////////////
// Text atrributes
////////////////////////////////////////////////////////////////////////////*/

#ifndef FOREGROUND_BLUE

#define FOREGROUND_BLUE      0x0001 /* text color contains blue. */
#define FOREGROUND_GREEN     0x0002 /* text color contains green. */
#define FOREGROUND_RED       0x0004 /* text color contains red. */
#define FOREGROUND_INTENSITY 0x0008 /* text color is intensified. */
#define BACKGROUND_BLACK	 0x0000 /* 1)background color contains black. */
#define BACKGROUND_BLUE      0x0010 /* 2)background color contains blue. */
#define BACKGROUND_GREEN     0x0020 /* 3)background color contains green. */
#define BACKGROUND_TURQUOISE 0x0030 /* 4)background color contains turquoise. */
#define BACKGROUND_RED       0x0040 /* 5)background color contains red. */
#define BACKGROUND_PURPLE	 0x0050 /* 6)background color contains purple. */
#define BACKGROUND_ORANGE	 0x0060 /* 7)background color contains orange. */
#define BACKGROUNG_WHITE	 0x0070 /* 8)background color contains white. */
#define BACKGROUND_INTENSITY 0x0080 /* 9)background color is intensified. */
#define BACKGROUND_UNKNOWN1 0x0090 /* 10)background color is intensified. */
#define BACKGROUND_UNKNOWN2 0x0100 /* 11)background color is intensified. */
#define BACKGROUND_UNKNOWN3 0x0110 /* 12)background color is intensified. */
#define BACKGROUND_UNKNOWN4 0x0120 /* 13)background color is intensified. */
#define BACKGROUND_UNKNOWN5 0x0130 /* 14)background color is intensified. */
#define BACKGROUND_UNKNOWN6 0x0140 /* 15)background color is intensified. */
#define BACKGROUND_UNKNOWN7 0x0150 /* 16)background color is intensified. */
#endif /* FOREGROUND_BLUE */

enum ConsoleColors
{
	BlackFore = 0,
	MaroonFore = FOREGROUND_RED,
	GreenFore = FOREGROUND_GREEN,
	NavyFore = FOREGROUND_BLUE,
	TealFore = FOREGROUND_GREEN | FOREGROUND_BLUE,
	OliveFore = FOREGROUND_RED | FOREGROUND_GREEN,
	PurpleFore = FOREGROUND_RED | FOREGROUND_BLUE,
	GrayFore = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	SilverFore = FOREGROUND_INTENSITY,
	RedFore = FOREGROUND_INTENSITY | FOREGROUND_RED,
	LimeFore = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	BlueFore = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	AquaFore = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	YellowFore = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	FuchsiaFore = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	WhiteFore = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,

	BlackBack = 0,
	MaroonBack = BACKGROUND_RED,
	GreenBack = BACKGROUND_GREEN,
	NavyBack = BACKGROUND_BLUE,
	TealBack = BACKGROUND_GREEN | BACKGROUND_BLUE,
	OliveBack = BACKGROUND_RED | BACKGROUND_GREEN,
	PurpleBack = BACKGROUND_RED | BACKGROUND_BLUE,
	GrayBack = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	SilverBack = BACKGROUND_INTENSITY,
	RedBack = BACKGROUND_INTENSITY | BACKGROUND_RED,
	LimeBack = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
	BlueBack = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
	AquaBack = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
	YellowBack = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
	FuchsiaBack = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
	WhiteBack = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
};

/* sets current text (foreground&background) attribute */
int SetColor(short color);

/* retrievess current text (foreground&background) attribute */
short GetColor();

/*////////////////////////////////////////////////////////////////////////////
// Block output
////////////////////////////////////////////////////////////////////////////*/

/* rectangular image descriptor */
typedef struct _IMG IMG;

/* allocates image of the given size */
IMG *	ImgAlloc(int width, int height);

/* deletes the given image */
void	ImgFree(IMG * pImg);

/* fills all image with given char and attribute */
int	ImgFill(IMG * pImg, char ch, short attr);

/* puts char into image to given position */
int	ImgPutChar(IMG * pImg, int x, int y, char ch, short attr);

/* writes image to console. left & top - window coords of upper-left cell of image */
int	ImgPut(const IMG * pImg, int left, int top);

//}
