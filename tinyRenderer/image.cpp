#include "image.h"
namespace Renderer {
		ImageBase::ImageBase() {
			this->w = defaultW;
			this->h = defaultH;
		}

		ImageBase::ImageBase(int w, int h) {
			this->w = w;
			this->h = h;
		}

		int ImageBase::Init() {
			ImageBase::window = initgraph(this->w, this->h, SHOWCONSOLE);
			setorigin(w / 2,h / 2);
			std::cout << "Window Init Success!" << std::endl;
			return CODE_SUCCESS;
		}

		void ImageBase::point(int x, int y, int color) {
			putpixel(x, y, color);
		}

		void ImageBase::point(float x, float y, int color) {
			this->point((int)x, (int)y, color);
		}

		void ImageBase::line(int x1, int y1, int x2, int y2, int color) {
			bool reverse = false;
			if (abs(x1 - x2) < abs(y1 - y2)) {
				// 避免x1-x2为0的情况
				reverse = true;
				std::swap(x1, y1);
				std::swap(x2, y2);
			}

			if (x1 > x2) {
				std::swap(x1, x2);
				std::swap(y1, y2);
			}
			
			float k = y2 - y1?(x2 - x1) / (float)(y2 - y1):0;
			float b = reverse?x1 - k * y1:y1 - k * x1;

			for (int x = x1; x < x2; x++) {
				//int y = b + k * x;

				float t = (x - x1) / (float)(x2 - x1);
				int y = y1 * (1.0 - t) + y2 * t;

				if (reverse){
					this->point(y, x, color);
				}
				else {
					this->point(x, y, color);
				}
			}
		}

		void ImageBase::triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, bool fill) {
			if (!fill) {
				line(x1, y1, x2, y2);
				line(x2, y2, x3, y3);
				line(x3, y3, x1, y1);
			}
			else {
				// draw fill triangle here
				// bubble sort by y
				if (y1 > y2) {
					std::swap(x1, x2);
					std::swap(y1, y2);
				}
				if (y1 > y3) {
					std::swap(x1, x3);
					std::swap(y1, y3);
				}
				if (y2 > y3) {
					std::swap(x2, x3);
					std::swap(y2, y3);
				}

				int max_height = y3 - y1;

				for (int y = y1; y <= y2; y++) {
					int segment_height = y2 - y1 + 1;
					float alpha = (float)(y - y1) / max_height;
					float beta = (float)(y - y1) / segment_height;
					int tx1 = x1 + (x3 - x1) * alpha;
					int ty1 = y1 + (y3 - y1) * alpha;
					int tx2 = x1 + (x2 - x1) * beta;
					int ty2 = y1 + (y2 - y1) * beta;

					std::cout << "1" << std::endl;

					this->point(tx1, ty1);
					this->point(tx2, ty2);
				}

			}
		}
}