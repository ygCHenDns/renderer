#pragma once
#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H
#include <fstream>
#include "basicLogicStruct.h"
namespace Renderer {


	class ObjFileObject {
	private:
		static const char* VERTEX_PREFIX;
		static const char* FACE_PREFIX;
		std::ifstream objFile;
	public:
		BasicLogicStruct::Array<BasicLogicStruct::Array<float>> vertex;
		BasicLogicStruct::Array<BasicLogicStruct::Array<BasicLogicStruct::Array<int>>> face;
		void readFile(char* filePath);
		
	};
}


#endif // !OBJ_PARSER_H
