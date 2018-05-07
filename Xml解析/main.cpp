#include <iostream>
#include "Xml.h"
int main()
{

	WaterBox::Xml *xml = new WaterBox::Xml("");
	xml->open("XMLFile.xml");
	while (1);
	return 0;
}
