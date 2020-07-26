#include "ObjParser.h"
#include <iostream>
#include <string>
namespace Renderer {

	const char* ObjFileObject::VERTEX_PREFIX = "v ";

	void ObjFileObject::readFile(char* filePath) {
		objFile.open(filePath);
		std::string output;
		int n;
		std::string temp = std::string(" ");
		while (std::getline(objFile, output))
		{
			std::cout << output << std::endl;
			if ((n = output.find(VERTEX_PREFIX)) == 0) {
				BasicLogicStruct::Array<std::string> a = BasicLogicStruct::splitStr(output, temp);
				std::cout << a << std::endl;
			}

		}
	}
}