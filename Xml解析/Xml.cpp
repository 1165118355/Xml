#include "Xml.h"

WaterBox::Xml::Xml(std::string name)
{
}

int WaterBox::Xml::load(std::string path)
{
	std::string temp;
	std::fstream file(path, std::ios::in);
	if (!file.is_open())						//	判断文件是否被打开
	{
		std::cout << "path error";
		file.close();
		return -1;
	}
	while (!file.eof())							//	判断文件是否被完全读取完成
	{
		file >> temp;
		int y=temp.length();
		if (temp[temp.length()-1] == '>')		//	读取到>说明到了行尾
		{
			temp += '\n';
		}
		else
		{
			temp += ' ';
		}
		buff += temp;
	}
	file.close();
	return 0;
}

int WaterBox::Xml::save(std::string path)
{
	return 0;
}

int WaterBox::Xml::getNumChild()
{
	
	return 0;
}

int WaterBox::Xml::checkNumChild(std::string str, int pos)
{
	int i = pos;
	while (buff[i])
	return 0;
}
