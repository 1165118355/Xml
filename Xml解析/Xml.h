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
		*	打开一个Xml文件
		*/
		int load(std::string path);

		/*
		*	保存一个Xml文件
		*/
		int save(std::string path);

		/*
		*	添加一个子结点
		*/
		int addChild(SDL2_Xml *child);
		int removeChild(std::string name);

		/*
		*	获取该结点的子结点
		*/
		SDL2_Xml *getChild(int num);

		/*
		*	获取该结点的子结点数量
		*/
		int getNumChild();

		/*
		*	设置该结点的名字
		*/
		void setName(std::string name);
		std::string getName();

		/*
		*	获取父结点
		*/
		SDL2_Xml *getParent();

		/*
		*	设置该结点标签
		*/
		int setTag(std::string name, std::string data);
		std::string getTag(std::string name);
		void addTag(std::string name, std::string data);
		/*
		*	获取当前节点层级
		*/
		int getHierarchy();
	private:
		/*
		*	优雅的构造函数
		*/
		SDL2_Xml();

		
		//	写， 将child中的信息写入file
		void writeTraverseChild(std::fstream &file, SDL2_Xml *xmlNode);

		//	读，将file中的信息读出到child
		void readTraverseChild(std::fstream &file, SDL2_Xml *xmlNode);

		//	设置父结点
		int setParent(SDL2_Xml *parent);

		//	设置层级
		void setHierarchy(int hierarchy);

		//	排序层级结构
		void sortHierarchy();

		//	获取所有的Tag
		std::map<std::string, std::string> *getAllTag();
	private:

		std::string m_Name;									//	保存名字
		std::map<std::string, std::string> m_Tag;			//	保存标签
		std::vector<SDL2_Xml *> m_Child;					//	保存孩子
		std::string m_Buff;									//	缓存（用于打印调试）
		SDL2_Xml *m_Parent;									//	保存父亲
		int m_Hierarchy;									//	保存层级
	};
}