#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace WaterBox
{

	struct
	{
		std::string name;
		std::vector<std::string> tag;
	};
	class Xml
	{
	public :
		enum OpenType
		{
			READ=0,
			WRITE
		};
	public:
		Xml(std::string name);

		/*
		*	打开一个Xml文件
		*/
		int load(std::string path);

		/*
		*	保存一个Xml文件
		*/
		int save(std::string path);

		/*
		*	获取该结点的子结点数量
		*/
		int getNumChild();

		/*
		*	获取该结点的
		*/
		int getChild(int id);


	private:
		int checkNumChild(std::string str, int pos);
		std::string buff;
		std::fstream file;
	};
}