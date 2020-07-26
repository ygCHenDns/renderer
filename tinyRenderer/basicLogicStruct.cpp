#include "basicLogicStruct.h"
namespace BasicLogicStruct {
	Array<std::string> splitStr(const std::string oriStr, const std::string seperator) {
		Array<std::string> splitRes;

		size_t posBegin = 0;
		size_t posSeperator = oriStr.find(seperator);
		std::string temp;
		while (posSeperator != oriStr.npos)
		{
			temp = oriStr.substr(posBegin, posSeperator - posBegin);
			splitRes.append(temp);
			std::cout << splitRes << std::endl;
			posBegin = posSeperator + seperator.size();
			posSeperator = oriStr.find(seperator, posBegin);
		}
		if (posBegin != oriStr.length()) {
			temp = oriStr.substr(posBegin);
			splitRes.append(temp);
		}

		return splitRes;
	}
}