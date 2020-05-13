#pragma once
#include <memory>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>

using namespace rapidxml;

/*
	A wrapper of rapidxml, made for the aim of reducing repetition.
*/

class XML {
public:
	static void loadXML(xml_document<>** document, file<>** fileData, const char* fileName);
	static char* getAttribute(xml_node<>* node, std::string attribute);
	static xml_node<>* getFirstNode(xml_document<>* document, std::string name);
	static std::string getName(xml_node<>* node);

	template<class T>
	static void linkValues(T& variable, char* value) {
		if (value) {
			variable = static_cast<T>(atof(value));
		}
	}

	template<class T>
	static T getValue(char* value) {
		return static_cast<T>(atof(value));
	}
};