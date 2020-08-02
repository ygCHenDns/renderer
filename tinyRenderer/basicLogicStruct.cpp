#include "basicLogicStruct.h"
namespace BasicLogicStruct {
	void splitStr(const std::string oriStr, const std::string seperator, Array<std::string> & splitRes) {
		size_t posBegin = 0;
		size_t posSeperator = oriStr.find(seperator);
		std::string temp;
		while (posSeperator != oriStr.npos)
		{
			temp = oriStr.substr(posBegin, posSeperator - posBegin);
			splitRes.append(temp);
			posBegin = posSeperator + seperator.size();
			posSeperator = oriStr.find(seperator, posBegin);
		}
		if (posBegin != oriStr.length()) {
			temp = oriStr.substr(posBegin);
			splitRes.append(temp);
		}
	}

	void convert_str_array(Array<int>& int_array, Array<std::string>& str_array) {
		for (int i = 0; i < str_array.get_size(); i++) {
			int_array.append(atoi(str_array.get_data()[i].c_str()));
		}
	}

	void convert_str_array(Array<float>& f_array, Array<std::string>& str_array) {
		for (int i = 0; i < str_array.get_size(); i++) {
			f_array.append(atof(str_array.get_data()[i].c_str()));
		}
	}
}