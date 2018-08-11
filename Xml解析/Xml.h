#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

namespace WaterBox
{
	class SDL2_Xml
	{
	public:
		static SDL2_Xml *create();
		static SDL2_Xml *create(std::string name, int mode=0);
		~SDL2_Xml();

		/*
		*	��һ��Xml�ļ�
		*/
		int load(std::string path);

		/*
		*	����һ��Xml�ļ�
		*/
		int save(std::string path);

		/*
		*	���һ���ӽ��
		*/
		int addChild(SDL2_Xml *child);
		int removeChild(std::string name);

		/*
		*	��ȡ�ý����ӽ��
		*/
		SDL2_Xml *getChild(int num);

		/*
		*	��ȡ�ý����ӽ������
		*/
		int getNumChild();

		/*
		*	���øý�������
		*/
		void setName(std::string name);
		std::string getName();

		/*
		*	��ȡ�����
		*/
		SDL2_Xml *getParent();

		/*
		*	���øý���ǩ
		*/
		int setTag(std::string name, std::string data);
		std::string getTag(std::string name);
		void addTag(std::string name, std::string data);
		/*
		*	��ȡ��ǰ�ڵ�㼶
		*/
		int getHierarchy();
	private:
		/*
		*	���ŵĹ��캯��
		*/
		SDL2_Xml();

		
		//	д�� ��child�е���Ϣд��file
		void writeTraverseChild(std::fstream &file, SDL2_Xml *xmlNode);

		//	������file�е���Ϣ������child
		void readTraverseChild(std::fstream &file, SDL2_Xml *xmlNode);

		//	���ø����
		int setParent(SDL2_Xml *parent);

		//	���ò㼶
		void setHierarchy(int hierarchy);

		//	����㼶�ṹ
		void sortHierarchy();

		//	��ȡ���е�Tag
		std::map<std::string, std::string> *getAllTag();
	private:

		std::string m_Name;									//	��������
		std::map<std::string, std::string> m_Tag;			//	�����ǩ
		std::vector<SDL2_Xml *> m_Child;					//	���溢��
		std::string m_Buff;									//	���棨���ڴ�ӡ���ԣ�
		SDL2_Xml *m_Parent;									//	���游��
		int m_Hierarchy;									//	����㼶
	};
}