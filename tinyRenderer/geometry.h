#pragma once
#ifndef GEO_H
#define GEO_H
#define PI 3.14159265359
namespace Renderer {
	template <class t> struct Vector2;
	template <class t> struct Vector3;
	template <class t> struct Vector3x3;
	template <class t> struct Vector4;
	template <class t> struct Vector4x4;
	float RadToAngle(float);
	float AngleToRad(float);

	template <class t> struct Vector2 {
		union {
			struct { t u, v; };
			struct { t x, y; };
			t data[2];
		};
		Vector2() : x(0), y(0) {}
		Vector2(t _x, t _y) :x(_x), y(_y) {}
		inline Vector2<t> operator +(const Vector2<t>& V2) const { return Vector2<t>(x + V2.x, y + V2.y); }
		inline Vector2<t> operator -(const Vector2<t>& V2) const { return Vector2<t>(x - V2.x, y - V2.y); }
		inline Vector2<t> operator *(float f) const { return Vector2<t>(x * f, y * f); }
		//dot product
		inline t operator *(const Vector2<t>& V2) const {
			t result = 0;
			for (int i = 0; i < 2; i++) {
				result += data[i] * V2.data[i];
			}
			return result;
		}
		//cross product
		inline t operator ^(const Vector2<t>& V2) const {
			return x * V2.y - V2.x * y;
		}
	};

	template <class t> struct Vector3 {
		union {
			struct { t x, y, z; };
			struct { t r, g, b; };
			t data[3];
		};
		Vector3() : x(0), y(0), z(0) {}
		Vector3(t _x, t _y, t _z) :x(_x), y(_y), z(_z) {}
		inline Vector3<t> operator +(const Vector3<t>& V3) const { return Vector3<t>(x + V3.x, y + V3.y, z + V3.z); }
		inline Vector3<t> operator -(const Vector3<t>& V3) const { return Vector3<t>(x - V3.x, y - V3.y, z - V3.z); }
		inline Vector3<t> operator *(float f) const { return Vector3<t>(x * f, y * f, z * f); }
		inline Vector3<t> operator /(float f) const { return Vector3<t>(x / f, y / f, z / f); }
		//dot product
		inline t operator *(const Vector3<t>& V3) const {
			t result = 0;
			for (int i = 0; i < 3; i++) {
				result += data[i] * V3.data[i];
			}
			return result;
		}
		//cross product
		inline Vector3<t> operator ^(const Vector3<t>& V3) const {
			return Vector3<t>(y * V3.z - z * V3.y, z * V3.x - x * V3.z, x * V3.y - y * V3.x);
		}
		inline float norm() const { return std::sqrt(x * x + y * y + z * z); }
		Vector3<t>& normalize(t l = 1) { *this = (*this) * (1 / norm()); return *this; }
		friend std::ostream& operator<<(std::ostream&, Vector3<t> &V3) { std::cout << V3.x << " " << V3.y << " " << V3.z << std::endl; return std::cout; }
		inline Vector4<t> toPoint() const { return Vector4<t>(x, y, z, 1); }
		inline Vector4<t> toVector() const { return Vector4<t>(x, y, z, 0); }
		inline t length() const { return sqrt(x * x + y * y + z * z); }
		inline Vector3<t> translate(t _x, t _y, t _z) {
			Vector4x4<t> translationMatrix(
				new t[4][4]{
					{1,		0,		0,		0},
					{0,		1,		0,		0},
					{0,		0,		1,		0},
					{_x,	_y,		_z,		1},
				}
			);

			*this = ((*this).toPoint() * translationMatrix).toVector3();
			return *this;
		}
		inline Vector3<t> rotate(t _x, t _y, t _z) {
			Vector4x4<t> rotateX(
				new t[4][4]{
					{				1,					0,						0,						0},
					{				0,					cos(AngleToRad(_x)),	sin(AngleToRad(_x)),	0},
					{				0,					-sin(AngleToRad(_x)),	cos(AngleToRad(_x)),	0},
					{				0,					0,						0,						1},
				}
			);
			Vector4x4<t> rotateY(
				new t[4][4]{
					{				cos(AngleToRad(_y)),				0,				-sin(AngleToRad(_y)),				0},
					{				0,									1,				0,									0},
					{				sin(AngleToRad(_y)),				0,				cos(AngleToRad(_y)),				0},
					{				0,									0,				0,									1},
				}
			);
			Vector4x4<t> rotateZ(
				new t[4][4]{
					{				cos(AngleToRad(_z)),				sin(AngleToRad(_z)),				0,				0},
					{				-sin(AngleToRad(_z)),				cos(AngleToRad(_z)),				0,				0},
					{				0,									0,									1,				0},
					{				0,									0,									0,				1},
				}
			);
			*this = ((*this).toPoint() * rotateX).toVector3();
			*this = ((*this).toPoint() * rotateY).toVector3();
			*this = ((*this).toPoint() * rotateZ).toVector3();
			return *this;
		}
		inline Vector3<t> scale(t _x, t _y, t _z) {
			Vector4x4<t> scaleMatrix(
				new t[4][4]{
					{_x,	0,		0,		0},
					{0,		_y,		0,		0},
					{0,		0,		_z,		0},
					{0,		0,		0,		1},
				}
			);

			*this = ((*this).toPoint() * scaleMatrix).toVector3();
			return *this;
		}
	};

	template <class t> struct Vector4 {
		union {
			struct { t x, y, z, w; };
			struct { t r, g, b, a; };
			t data[4];
		};
		Vector4() : x(0), y(0), z(0), w(0) {}
		Vector4(t _x, t _y, t _z, t _w) :x(_x), y(_y), z(_z), w(_w) {}
		inline Vector4<t> operator +(const Vector4<t>& V4) const { return Vector4<t>(x + V4.x, y + V4.y, z + V4.z, w + V4.w); }
		inline Vector4<t> operator -(const Vector4<t>& V4) const { return Vector4<t>(x - V4.x, y - V4.y, z - V4.z, w - V4.w); }
		inline Vector4<t> operator *(float f) const { return Vector4<t>(x * f, y * f, z * f, w * f); }
		//dot product
		inline t operator *(const Vector4<t>& V4) const {
			t result = 0;
			for (int i = 0; i < 4; i++) {
				result += data[i] * V4.data[i];
			}
			return result;
		}
		Vector4<t> operator *(const Vector4x4<t>& V4x4) const {
			Vector4<t> result;
			for (int i = 0; i < 4; i++) {
				t sumRaw = 0;
				for (int j = 0; j < 4; j++) {
					sumRaw += data[j] * V4x4.data[j][i];
				}
				result.data[i] = sumRaw;
			}
			return result;
		}

		inline float norm() const { return std::sqrt(x * x + y * y + z * z + w * w); }
		Vector4<t>& normalize(t l = 1) { *this = (*this) * (1 / norm()); return *this; }
		Vector3<t> toVector3() const { return Vector3<t>(x, y, z); }
		friend std::ostream& operator<<(std::ostream&, Vector4<t>& V4) { std::cout << V4.x << " " << V4.y << " " << V4.z << " " << V4.w << std::endl; return std::cout; }

	};

	template <class t> struct Vector3x3 {
		union {
			struct { t m11, m12, m13, m21, m22, m23, m31, m32, m33; };
			t data[3][3];
			t raw[9];
		};

		Vector3x3() : raw{ 0 } {}
		Vector3x3(t _m) : raw{ _m } {}
		Vector3x3(t(*_data)[3]) { data = _data; }

		inline Vector3x3<t> operator +(const Vector3x3<t>& V3x3) const {
			Vector3x3<t> tv;
			for (int i = 0; i < 9; i++) {
				tv.raw[i] = raw[i] + V3x3.raw[i];
			}
			return tv;
		}

		inline Vector3x3<t> operator -(const Vector3x3<t>& V3x3) const {
			Vector3x3<t> tv;
			for (int i = 0; i < 9; i++) {
				tv.raw[i] = raw[i] - V3x3.raw[i];
			}
			return tv;
		}

		inline Vector3x3<t> operator *(float f) const {
			Vector3x3<t> tv;
			for (int i = 0; i < 9; i++) {
				tv.raw[i] = raw[i] * f;
			}
			return tv;
		}

		inline Vector3x3<t> operator *(const Vector3x3<t>& V3x3) const {
			Vector3x3<t> tv;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					float result = 0;
					for (int k = 0; k < 3; k++) {
						result += data[i][k] * V3x3.data[k][j];
					}
					tv.data[i][j] = result;
				}
			}
			return tv;
		}
	};

	template <class t> struct Vector4x4 {
		union {
			struct { t m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44; };
			t data[4][4];
			t raw[16];
		};

		Vector4x4() : raw{ 0 } {}
		Vector4x4(t _m) : raw{ _m } {}
		Vector4x4(t (*_data)[4]) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					data[i][j] = _data[i][j];
				}
			}
		}

		inline Vector4x4<t> operator +(const Vector4x4<t>& V4x4) const {
			Vector4x4<t> tv;
			for (int i = 0; i < 9; i++) {
				tv.raw[i] = raw[i] + V4x4.raw[i];
			}
			return tv;
		}

		inline Vector4x4<t> operator -(const Vector4x4<t>& V4x4) const {
			Vector4x4<t> tv;
			for (int i = 0; i < 9; i++) {
				tv.raw[i] = raw[i] - V4x4.raw[i];
			}
			return tv;
		}

		inline Vector4x4<t> operator *(float f) const {
			Vector4x4<t> tv;
			for (int i = 0; i < 9; i++) {
				tv.raw[i] = raw[i] * f;
			}
			return tv;
		}

		inline Vector4x4<t> operator *(const Vector4x4<t>& V4x4) const {
			Vector4x4<t> tv;
			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					float result = 0;
					for (int k = 0; k <= 3; k++) {
						result += data[i][k] * V4x4.data[k][j];
					}
					tv.data[i][j] = result;
				}
			}
			return tv;
		}

		Vector4<t> operator *(const Vector4<t>& V4) const {
			return V4 * (*this);
		}

		friend std::ostream& operator<<(std::ostream&, Vector4x4<t>& V4) {
			std::cout << std::endl;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					std::cout << V4.data[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			return std::cout;
		}


	};

	float RadToAngle(float rad) {
		return rad * 180.0 / PI;
	}
	float AngleToRad(float angle) {
		return angle * PI / 180.0;
	}

	typedef Vector2<float> Vec2f;
	typedef Vector2<int>   Vec2i;
	typedef Vector3<float> Vec3f;
	typedef Vector3<int>   Vec3i;
	typedef Vector4<float> Vec4f;
	typedef Vector4<int>   Vec4i;

	typedef Vector3x3<int> Vec3x3i;
	typedef Vector3x3<float> Vec3x3f;

	typedef Vector4x4<int> Vec4x4i;
	typedef Vector4x4<float> Vec4x4f;
}
#endif // !GEO_H