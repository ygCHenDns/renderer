// tinyRenderer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <graphics.h>
#include <iostream>
#include "image.h"
#include "geometry.h"
#include "camera.h"
#include "ObjParser.h"
#include "basicLogicStruct.h"

using namespace Renderer;

int main()
{

	ObjFileObject obj;
	char filePath[] = "D:\\tinyrenderer\\tinyRenderer\\simpleobj\\trunk.obj";
	obj.readFile(filePath);

	ImageBase image_base = ImageBase();
	image_base.Init();
	Vec3f cameraPosition(100.0, 100.0, 100.0), cameraFocus(0, 0, 0);
	Camera camera(cameraPosition, cameraFocus);
	camera.SetWidthAndHeight(800, 600);
	Vec4x4f viewMatrix = camera.DumpViewMatrix();
	Vec4x4f pm = camera.perspectiveMatrix(PI / 2.0f, 1.0f, 500.0f);
	std::cout << viewMatrix << std::endl;
	for (int i = 0; i < obj.face.get_size(); i++) {
		int start_index = 0;
		while (start_index <= obj.face[i].get_size() / 2) {
			int vertex_index_1 = obj.face[i][start_index % obj.face[i].get_size()][0] - 1;
			int vertex_index_2 = obj.face[i][(start_index + 1) % obj.face[i].get_size()][0] - 1;
			int vertex_index_3 = obj.face[i][(start_index + 2) % obj.face[i].get_size()][0] - 1;
			Vec3f v1(obj.vertex[vertex_index_1][0], obj.vertex[vertex_index_1][1], obj.vertex[vertex_index_1][2]);
			Vec3f v2(obj.vertex[vertex_index_2][0], obj.vertex[vertex_index_2][1], obj.vertex[vertex_index_2][2]);
			Vec3f v3(obj.vertex[vertex_index_3][0], obj.vertex[vertex_index_3][1], obj.vertex[vertex_index_3][2]);
			std::cout << v1 << v2 << v3 << std::endl;
			v1 = (v1.toPoint() * viewMatrix * pm).toVector3();
			v2 = (v2.toPoint() * viewMatrix * pm).toVector3();
			v3 = (v3.toPoint() * viewMatrix * pm).toVector3();
			std::cout << v1 << v2 << v3 << std::endl;
			image_base.triangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, COLOR::White, false);
			start_index += 2;
		}
		
	}


	// 右手坐标系
	/*ImageBase imageBase = ImageBase();
	imageBase.Init();
	
	Vec3f v1(-100.0,100.0,-100.0), v2(100.0,100.0,-100.0), v3(100.0,100.0,100.0), v4(-100.0,100.0,100.0);
	Vec3f v5(-100.0, -100.0, -100.0), v6(100.0, -100.0, -100.0), v7(100.0, -100.0, 100.0), v8(-100.0, -100.0, 100.0);

	Vec3f cameraPosition(300.0, 300.0, 300.0), cameraFocus(0,0,0);
	Camera camera(cameraPosition, cameraFocus);
	camera.SetWidthAndHeight(800, 600);
	Vec4x4f viewMatrix = camera.DumpViewMatrix();

	std::cout << viewMatrix;

	Vec4x4f pm = camera.perspectiveMatrix(PI / 2.0f, 1.0f, 500.0f);

	std::cout << pm;

	v1 = (v1.toPoint() * viewMatrix).toVector3();
	v2 = (v2.toPoint() * viewMatrix).toVector3();
	v3 = (v3.toPoint() * viewMatrix).toVector3();
	v4 = (v4.toPoint() * viewMatrix).toVector3();
	v5 = (v5.toPoint() * viewMatrix).toVector3();
	v6 = (v6.toPoint() * viewMatrix).toVector3();
	v7 = (v7.toPoint() * viewMatrix).toVector3();
	v8 = (v8.toPoint() * viewMatrix).toVector3();

	v1 = (v1.toPoint() * pm).toVector3();
	v2 = (v2.toPoint() * pm).toVector3();
	v3 = (v3.toPoint() * pm).toVector3();
	v4 = (v4.toPoint() * pm).toVector3();
	v5 = (v5.toPoint() * pm).toVector3();
	v6 = (v6.toPoint() * pm).toVector3();
	v7 = (v7.toPoint() * pm).toVector3();
	v8 = (v8.toPoint() * pm).toVector3();

	std::cout << v1 << v2 << v3 << v4 << v5<<v6<<v7<<v8<<std::endl;

	imageBase.triangle(-50, 30, -50, 30, 45, 250, Renderer::COLOR::White);*/

	/*imageBase.line(v1.x, v1.y, v2.x, v2.y, Renderer::COLOR::White);
	imageBase.line(v2.x, v2.y, v3.x, v3.y, Renderer::COLOR::White);
	imageBase.line(v3.x, v3.y, v4.x, v4.y, Renderer::COLOR::White);
	imageBase.line(v4.x, v4.y, v1.x, v1.y, Renderer::COLOR::White);

	imageBase.line(v5.x, v5.y, v6.x, v6.y, Renderer::COLOR::Green);
	imageBase.line(v6.x, v6.y, v7.x, v7.y, Renderer::COLOR::Green);
	imageBase.line(v7.x, v7.y, v8.x, v8.y, Renderer::COLOR::Green);
	imageBase.line(v8.x, v8.y, v5.x, v5.y, Renderer::COLOR::Green);

	imageBase.line(v1.x, v1.y, v5.x, v5.y, Renderer::COLOR::Blue);
	imageBase.line(v2.x, v2.y, v6.x, v6.y, Renderer::COLOR::Blue);
	imageBase.line(v3.x, v3.y, v7.x, v7.y, Renderer::COLOR::Blue);
	imageBase.line(v4.x, v4.y, v8.x, v8.y, Renderer::COLOR::Blue);

	imageBase.point(v1.x, v1.y, Renderer::COLOR::White);
	imageBase.point(v2.x, v2.y, Renderer::COLOR::White);
	imageBase.point(v3.x, v3.y, Renderer::COLOR::White);
	imageBase.point(v4.x, v4.y, Renderer::COLOR::White);
	imageBase.point(v5.x, v5.y, Renderer::COLOR::White);
	imageBase.point(v6.x, v6.y, Renderer::COLOR::White);
	imageBase.point(v7.x, v7.y, Renderer::COLOR::White);
	imageBase.point(v8.x, v8.y, Renderer::COLOR::White);*/

	std::cin.get();
	return 0;
}
