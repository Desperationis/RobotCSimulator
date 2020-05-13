#include "XML.h"
#include <Debug/Log.h>

void XML::loadXML(xml_document<>** document, file<>** fileData, const char* fileName) {
	*fileData = new file<>(fileName);
	*document = new xml_document<>();
	try {
		(*document)->parse<0>((*fileData)->data());
	}
	catch (parse_error& error) {
		Log::assertionLog(error.what(), false);
	}
}

char* XML::getAttribute(xml_node<>* node, std::string attribute) {
	if (node->first_attribute(attribute.c_str(), 0, false) == 0) {
		return nullptr;
	}
	return node->first_attribute(attribute.c_str(), 0, false)->value();
}

xml_node<>* XML::getFirstNode(xml_document<>* document, std::string name) {
	xml_node<>* node = document->first_node(name.c_str());

	std::string error = "\"" + name + "\"" + " was not found on a xml document";
	Log::assertionLog(error, node);

	return node;
};

std::string XML::getName(xml_node<>* node) {
	std::string name = node->name();
	return name;
}