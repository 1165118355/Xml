#include <iostream>
#include "Xml.h"


using namespace WaterBox;
int main()
{

	SDL2_Xml *xml = SDL2_Xml::create();

	xml->setName("wawter");
	xml->setTag("type", "static");
	xml->setTag("six", "boy");
	xml->addChild(SDL2_Xml::create("uu"));
	xml->addChild(SDL2_Xml::create("oo"));
	xml->setData("2333");

	SDL2_Xml *childFire = SDL2_Xml::create("fire");
	childFire->setTag("type", "Dynamic");
	childFire->setTag("six", "girl");
	childFire->addChild(SDL2_Xml::create("123"));
	xml->addChild(childFire);
	childFire->setData("4567");

	xml->save("waterBOx.xml");

	SDL2_Xml *xml2 = SDL2_Xml::create();
	xml2->load("waterBOx.xml");
	while (1);
	return 0;
}



