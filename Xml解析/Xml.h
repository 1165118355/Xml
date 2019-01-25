///////////////////////////////
//	this class is a Xml in c++.
//	xml�࣬�����������������ǽ���xml�ļ�
//	��xml�ࡷ
//	2018��8��13�� 20:13:28
//	by	ˮ������
#ifndef _SDL2_XML_H_BOX
#define _SDL2_XML_H_BOX

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
		///	\breif	����һ���յ�xml�ڵ�
		static SDL2_Xml *create();

		///	\breif	����һ��xml�ڵ�(���mode=0 name���Ǵ���һ��xml�ڵ㣬���mode=1, name���Ǽ���һ��xml�ڵ�)
		static SDL2_Xml *create(std::string name);

		///	\brief	����һ��Xml�ڵ㲢�������ĸ��ڵ�
		static SDL2_Xml *create(std::string name, SDL2_Xml *parent);

		///	\brief	ɾ���ý�㣨����ɾ������ڵ������е��ӽ�㣩
		~SDL2_Xml();

		///	\brief	����һ��xml�ļ���path��ʾ·��������
		int load(std::string path);

		///	\brief	����һ��xml�ļ���path��ʾ·��������
		int save(std::string path);

		///	\brief	��ӻ�ɾ���ӽ��
		int addChild(SDL2_Xml *child);
		int removeChild(std::string name);

		///	\brief	��ȡ�ӽ��(����index)
		SDL2_Xml *getChild(int num);

		///	\breif	��ȡ��ǰ�ڵ��ܹ����ӽڵ�����
		int getNumChild();

		///	\brief	���õ�ǰ�ڵ������
		void setName(std::string name);
		std::string getName();

		///	\brief	��ȡ��ǰ�ڵ�ĸ���
		SDL2_Xml *getParent();

		///	\brief	���õ�ǰ�ڵ�ı�ǩ�����û���ҵ��ñ�ǩ���Զ���Ӹñ�ǩ����������
		int setTag(std::string name, std::string data);
		int setTag(std::string name, int data);
		int setTag(std::string name, float data);
		int setTag(std::string name, double data);
		std::string getTag(std::string name);
		void addTag(std::string name, std::string data);

		///	\brief	���øýڵ�����ݣ�����һ���ַ�����
		void setData(std::string data);
		std::string getData();

		///	\brief	��һ���ַ���������xmlʵ��
		void parse(std::string parseStr);
		std::string getTree();

		///	\brief	��ȡ��ǰ�ڵ�Ĳ㼶
		int getHierarchy();

		///	\brief	����ý�����Ϣ
		void clear(int child = 0);


	private:
		enum
		{
			NONE,
			INPUT_OTHER,
			INPUT_NAME,
			INPUT_TAG_NAME,
			INPUT_TAG_DATA,
			INPUT_DATA
		};

		//	���ŵĹ��캯��
		SDL2_Xml();

		///	\brief	��һ���ַ���������xmlʵ�� (�����������ݹ��)
		bool parse(std::string parseStr, int &nowSub, SDL2_Xml *xmlNode);

		//	д�� ��child�е���Ϣд��file
		void writeTraverseChild(std::string &file, SDL2_Xml *xmlNode);

		//	���ø����
		int setParent(SDL2_Xml *parent);

		//	���ò㼶
		void setHierarchy(int hierarchy);

		//	����㼶�ṹ
		void sortHierarchy();

		//	��ȡ���е�Tag
		std::map<std::string, std::string> *getAllTag();
	private:
		std::string							m_Name;				//	��������
		std::map<std::string, std::string>	m_Tag;				//	�����ǩ
		std::string							m_Data;				//	��������
		std::vector<SDL2_Xml *>				m_Child;			//	���溢��
		std::string							m_Buffer;			//	���棨���ڴ�ӡ���ԣ�
		SDL2_Xml*							m_Parent;			//	���游��
		int									m_Hierarchy;		//	����㼶
		SDL2_Xml*							m_Self;				//	�����Լ�
	};
}
#endif // !_SDL2_XML_H_BOX
