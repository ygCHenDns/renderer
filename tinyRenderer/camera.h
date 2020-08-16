#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "geometry.h"
#include <iostream>
namespace Renderer {
	struct Camera {
		Vec3f Position, UpDirection, FocusPosition;

		float n = 0.1, f = 100.0, fov = 90.0, r;//��ƽ����룬Զƽ����룬���Ĵ�ֱ��Ұ�нǣ���Ļ��߱�

		float beta;//����ˮƽ�н�

		float d; //�����ͶӰ��Ļ�ľ���

		float viewH = 2.0, viewW; //ͶӰ��Ļ���

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
			// ��Ұ��������
			Vec3f w = (FocusPosition - Position) / (FocusPosition - Position).length();
			//std::cout << w;
			// ��������ҷ�������
			Vec3f u = w ^ UpDirection;
			//std::cout << u;
			//�������ֱ��������
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
	Vec3f u/*�ҷ�������*/, v/*�Ϸ�������*/, w/*�۲췽������*/;
}

#endif // !CAMERA_H
