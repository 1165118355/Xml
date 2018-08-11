#include "Xml.h"

using namespace WaterBox;

WaterBox::SDL2_Xml::SDL2_Xml()
{
	m_Name = "";
	m_Hierarchy=0;
}

WaterBox::SDL2_Xml::~SDL2_Xml()
{
	for (int i=0; i<m_Child.size(); ++i)
	{
		delete m_Child[i];
	}
}

void WaterBox::SDL2_Xml::writeTraverseChild(std::fstream & file, SDL2_Xml * xmlNode)
{
	for (int i=0; i<xmlNode->getHierarchy(); ++i)
	{
		file << "\t";
	}
	//	��ʼ
	file << "<" << xmlNode->getName();

	//	��ӱ�ǩ
	std::map<std::string, std::string> *nowTag = xmlNode->getAllTag();
	for (std::map<std::string, std::string>::iterator it= nowTag->begin(); it != nowTag->end(); ++it)
	{
		file << " " << it->first << "=" << "\"" << it->second << "\"" ;
	}
	file << ">\n";

	//	�ӽ���������
	for (int i = 0; i<xmlNode->getNumChild(); ++i)
	{
		SDL2_Xml *childXml = xmlNode->getChild(i);
		if (!childXml)
		{	
			continue;
		}
		writeTraverseChild(file, childXml);
	}

	for (int i = 0; i<xmlNode->getHierarchy(); ++i)
	{
		file << "\t";
	}
	//	����
	file << "</" << xmlNode->getName() << ">\n";
}

SDL2_Xml * WaterBox::SDL2_Xml::create()
{
	SDL2_Xml *xml = new SDL2_Xml();
	return xml;
}

SDL2_Xml * WaterBox::SDL2_Xml::create(std::string name, int mode/*=0*/)
{
	SDL2_Xml *xml = new SDL2_Xml();
	switch (mode)
	{
	case 0:
		xml->setName(name);
		break;
	case 1:
		xml->load(name);
		break;
	}
	return xml;
}

int WaterBox::SDL2_Xml::load(std::string path)
{
	std::fstream file(path, std::ios::in);
	if (!file.is_open())						//	�ж��ļ��Ƿ񱻴�
	{
		std::cout << "path error\n";
		file.close();
		return -1;
	}
	readTraverseChild(file, this);
	save("tempCheck.xml");
	return 0;
}

int WaterBox::SDL2_Xml::save(std::string path)
{
	std::fstream file(path, std::ios::out);

	//	ͨ���ݹ�ķ�ʽ�������еĽڵ㣬�����ڵ� ����Ϣд��file
	writeTraverseChild(file, this);

	file.close();
	return 0;
}

int WaterBox::SDL2_Xml::addChild(SDL2_Xml * child)
{
	if (child == NULL)
	{
		return -1;
	}
	child->setParent(this);
	child->sortHierarchy();
	m_Child.push_back(child);
	return 0;
}

int WaterBox::SDL2_Xml::removeChild(std::string name)
{
	for (int i=0; i<m_Child.size(); ++i)
	{
		if (!strcmp(name.c_str(), m_Child[i]->getName().c_str()))
		{
			m_Child.erase(m_Child.begin()+i);
		}
	}
	return 0;
}

SDL2_Xml *WaterBox::SDL2_Xml::getChild(int num)
{
	if (m_Child.size() > num)
	{
		return m_Child[num];
	}
	return nullptr;
}

int WaterBox::SDL2_Xml::getNumChild()
{
	return m_Child.size();
}

void WaterBox::SDL2_Xml::setName(std::string name)
{
	m_Name = name;
}

std::string WaterBox::SDL2_Xml::getName()
{
	return m_Name;
}

SDL2_Xml * WaterBox::SDL2_Xml::getParent()
{
	return m_Parent;
}

int WaterBox::SDL2_Xml::setTag(std::string name, std::string data)
{
	std::map<std::string, std::string>::iterator it = m_Tag.find(name);
	if (it == m_Tag.end())
	{
		addTag(name, data);
		return -1;
	}
	it->second = data;
	return 1;
}

std::string WaterBox::SDL2_Xml::getTag(std::string name)
{
	std::map<std::string, std::string>::iterator it = m_Tag.find(name);
	if (it == m_Tag.end())
	{
		return NULL;
	}
	return it->second;
}

void WaterBox::SDL2_Xml::addTag(std::string name, std::string data)
{
	std::pair<std::string, std::string> pa(name, data);
	m_Tag.insert(pa);
}

int WaterBox::SDL2_Xml::getHierarchy()
{
	return m_Hierarchy;
}

std::map<std::string, std::string> *WaterBox::SDL2_Xml::getAllTag()
{
	return &m_Tag;
}

int WaterBox::SDL2_Xml::setParent(SDL2_Xml * parent)
{
	if (parent != NULL)
	{
		m_Parent = parent;
	}
	else
	{
		return -1;
	}
	return 0;
}

void WaterBox::SDL2_Xml::setHierarchy(int hierarchy)
{
	m_Hierarchy = hierarchy;
}

void WaterBox::SDL2_Xml::sortHierarchy()
{
	if (m_Parent != NULL)
	{
		m_Hierarchy = m_Parent->getHierarchy() + 1;
	}
	for (int i=0; i<m_Child.size(); ++i)
	{
		m_Child[i]->sortHierarchy();
	}
}

void WaterBox::SDL2_Xml::readTraverseChild(std::fstream & file, SDL2_Xml * xmlNode)
{
	//	�ж�����
	//	ȡ��tag
	//	����ӽڵ�
	std::string tBuffer;
	do
	{
		//	���ļ�ȡ��һ���ַ���
		file >> tBuffer;

		//	�����һ���쳣�ͽ�����һ�еļ���
		if (tBuffer.size() < 3)
		{
			break;
		}

		//	�ж���һ���Ƿ��ǽ������
		if (tBuffer[0] == '<' && tBuffer[1] == '/')
		{
			delete xmlNode;
			return;
		}

		//	��ȡ�ڵ�����
		if (tBuffer[0] == '<' && tBuffer[1] != '/' && tBuffer[tBuffer.size()-1] == '>')
		{
			xmlNode->setName(tBuffer.substr(1, tBuffer.size()-2));
		}
		else if (tBuffer[0] == '<' && tBuffer[1] != '/')
		{
			xmlNode->setName(tBuffer.substr(1, tBuffer.size()-1));
		}

		//	��ȡ���Tag
		if (tBuffer[0] != '<')
		{
			std::string paName = tBuffer.substr(0, tBuffer.find('=')-0);
			std::string paData="";
			if (tBuffer[tBuffer.size()-1] == '>')
			{
				paData = tBuffer.substr(tBuffer.find('=') + 2, tBuffer.size() - (tBuffer.find('=') +2)-2);
			}
			else
			{
				paData = tBuffer.substr(tBuffer.find('=') + 2, tBuffer.size() - (tBuffer.find('=') + 2)-1);
			}
			xmlNode->addTag(paName, paData);
		}
	}while (!file.eof() && tBuffer[tBuffer.size() - 1] != '>');

	
	//	�ݹ�����ӽڵ�
	while (!file.eof())
	{
		file >> tBuffer;
		if (tBuffer[0] == '<' && tBuffer[1] == '/')
		{
			return;
		}
		else
		{
			file.seekg(0-tBuffer.size(), std::ios::cur);
			SDL2_Xml *xmlChild = SDL2_Xml::create();
			xmlNode->addChild(xmlChild);
			readTraverseChild(file, xmlChild);
		}
	}
}
