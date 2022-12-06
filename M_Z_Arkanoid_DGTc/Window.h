#pragma once
#include "Types.h"

#define framerate 1000.f/240.f

struct Window 
{
	Window(int width = 0, int height = 0, int mousex = 0, int mousey = 0)
		:width_(width), height_(height), mouseX_(mousex), mouseY_(mousey) {}

	void PreInit(int w, int h)
	{
		width_ = w;
		height_ = h;

		const int WINDOW_BASE_WIDTH = 1920;
		const int WINDOW_BASE_HEIGHT = 1080;

		float xUnit = (float)((float)width_ / (float)WINDOW_BASE_WIDTH);
		float yUnit = (float)((float)height_ / (float)WINDOW_BASE_HEIGHT);

		ScreenUnits.SetValue(xUnit, yUnit);
	}

	const int2& GetXYBorders() { return int2(width_, height_); };

	const vec2& GetScreenUnits() { return ScreenUnits; }

	const int& GetHeight() { return height_; }
	const int& GetWidth() { return width_; }

	const int& GetMouseX() { return mouseX_; }
	const int& GetMouseY() { return mouseY_; }

	void OnMouseMove(int x, int y, int xrelative, int yrelative)
	{
		mouseX_ = x + xrelative;
		mouseY_ = y + yrelative;
	}

private:
	int width_, height_, mouseX_, mouseY_;

	vec2 ScreenUnits;
};

