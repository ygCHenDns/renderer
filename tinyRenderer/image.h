#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#define CODE_SUCCESS 1
#define CODE_FAIL 0
#include <graphics.h>
#include <iostream>
namespace Renderer {
	enum COLOR {
		White = BGR(0xFFFFFF),
		Red = BGR(0xFF0000),
		Green = BGR(0x00FF00),
		Blue = BGR(0x0000FF),
	};

	

	class ImageBase {
	private:
		HWND window = nullptr;
		int defaultW = 800, defaultH = 600;
		int w, h;
	public:
		ImageBase(int w, int h);
		ImageBase();
		int Init();
		void point(int x, int y, int color = COLOR::White);
		void point(float x, float y, int color = COLOR::White);
		void line(int x1, int y1, int x2, int y2, int color = COLOR::White);
		void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color = COLOR::White, bool use_point = true);
		//void triangle(Vec3f p1, Vec3f p2, Vec3f p3, int color = COLOR::White,  bool fill = true);
	};
}
#endif // !IMAGE_H


