#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <raylib.h>

enum TextAlignment
{
	CENTER,
	LEFT,
	RIGHT
};

inline void DrawAlignedText(const char* text, int x, int y, int font, Color c, TextAlignment alignment = TextAlignment::CENTER)
{
	int textWidth = MeasureText(text, font);
	int posX = 0;
	switch (alignment)
	{
		case CENTER:
			posX = x - (textWidth / 2);
			break;
		case LEFT:
			posX = x - textWidth;
			break;
		case RIGHT:
			posX = x;
			break;
	}

	DrawText(text, posX, y, font, c);
}

#endif // !UI_UTILS_H
