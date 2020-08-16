#include "ObjParser.h"
#include <iostream>
#include <string>
namespace Renderer {

	const char* ObjFileObject::VERTEX_PREFIX = "v ";
	const char* ObjFileObject::FACE_PREFIX = "f ";

	void ObjFileObject::readFile(char* filePath) {
		objFile.open(filePath);
		std::string output;
		int n;
		std::string temp = std::string(" ");
		while (std::getline(objFile, output))
		{
			//std::cout << output << std::endl;
			if ((n = output.find(VERTEX_PREFIX)) == 0) {
				BasicLogicStruct::Array<std::string> s;
				BasicLogicStruct::splitStr(output, temp, s);
				s.slice(1);
				BasicLogicStruct::Array<float> vertex_info;
				BasicLogicStruct::convert_str_array(vertex_info, s);
				this->vertex.append(vertex_info);
			}
			else if ((n = output.find(FACE_PREFIX)) == 0) {
				BasicLogicStruct::Array<std::string> s;
				BasicLogicStruct::splitStr(output, temp, s);
				s.slice(1);
				BasicLogicStruct::Array<BasicLogicStruct::Array<int>> single_face;
				for (int i = 0; i < s.get_size(); i++) {
					BasicLogicStruct::Array<std::string> face_info_s;
					BasicLogicStruct::splitStr(s.get(i), std::string("/"), face_info_s);
					BasicLogicStruct::Array<int> face_info_i;
					BasicLogicStruct::convert_str_array(face_info_i, face_info_s);
					single_face.append(face_info_i);
				}
				this->face.append(single_face);
			}
		}
		std::cout << this->vertex << std::endl;
		std::cout << this->face << std::endl;
	}

}