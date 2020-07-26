#pragma once
#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H
#include <fstream>
#include "basicLogicStruct.h"
namespace Renderer {


	class ObjFileObject {
	private:
		static const char* VERTEX_PREFIX;
		std::ifstream objFile;
		BasicLogicStruct::Array<BasicLogicStruct::Array<float>> vertex;

	public:
		void readFile(char* filePath);
		
	};
}


#endif // !OBJ_PARSER_H
