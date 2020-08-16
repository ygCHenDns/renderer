#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "geometry.h"
#include <iostream>
namespace Renderer {
	struct Camera {
		Vec3f Position, UpDirection, FocusPosition;

		float n = 0.1, f = 100.0, fov = 90.0, r;//近平面距离，远平面距离，中心垂直视野夹角，屏幕宽高比

		float beta;//中心水平夹角

		float d; //相机到投影屏幕的距离

		float viewH = 2.0, viewW; //投影屏幕宽高

		float screenWidth, screenHeight;

		Camera(Vec3f _p, Vec3f _f, Vec3f _up = Vec3f(0, 1, 0)) :Position(_p), UpDirection(_up), FocusPosition(_f) {}

		inline void SetWidthAndHeight(int width, int height) {
			r = float(width) / float(height);
			viewW = viewH * r;
			d = 1 / tan(AngleToRad(fov / 2)); //cot
			beta = 2.0 * atan(r * tan(AngleToRad(fov / 2)));
			screenWidth = width;
			screenHeight = height;
		}

		Vec4x4f DumpViewMatrix() {
			// 视野方向向量
			Vec3f w = (FocusPosition - Position) / (FocusPosition - Position).length();
			//std::cout << w;
			// 摄像机的右方向向量
			Vec3f u = w ^ UpDirection;
			//std::cout << u;
			//摄像机垂直向上向量
			Vec3f v = u ^ w;
			Vec4x4f viewM(
				new float[4][4]{
					{u.x, u.y, u.z, 0},
					{v.x,v.y,v.z,0},
					{w.x,w.y,w.z,0},
					{u * Position * -1,v * Position * -1,w * Position * -1,1},
				}
			);
			return viewM;
		}

		float w = 800, h = 600;

		Vec4x4f perspectiveMatrix(float fovy, float zn, float zf) {
			Vec4x4f pm;
			float fax = 1.0f / (float)tan(fovy * 0.5f);
			float aspect = (float)(screenWidth) / (float)(screenHeight);
			pm.data[0][0] = (float)(fax / aspect);
			pm.data[1][1] = (float)(fax);
			pm.data[2][2] = zf / (zf - zn);
			pm.data[3][2] = -zn * zf / (zf - zn);
			pm.data[2][3] = 1;
			return pm;
		}

	};
	Vec3f u/*右方向向量*/, v/*上方向向量*/, w/*观察方向向量*/;
}

#endif // !CAMERA_H
