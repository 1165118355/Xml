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
		*	��һ��Xml�ļ�
		*/
		int load(std::string path);

		/*
		*	����һ��Xml�ļ�
		*/
		int save(std::string path);

		/*
		*	��ȡ�ý����ӽ������
		*/
		int getNumChild();

		/*
		*	��ȡ�ý���
		*/
		int getChild(int id);


	private:
		int checkNumChild(std::string str, int pos);
		std::string buff;
		std::fstream file;
	};
}