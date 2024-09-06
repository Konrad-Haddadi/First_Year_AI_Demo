#pragma once

#define PROGRAM_CATEGORY "Program"
#define WINDOW_CATEGORY "Window"
#define DEBUG_CATEGORY "Debug"


#include "Azimuth.h"
#include <map>
#include <iostream>
#include <string>
#include <raylib/raylib.h>
#include <glm/vec2.hpp>

using std::string;
using std::map;
using glm::vec2;

class Config
{
public:
	DLL Config(const string& _name);
	DLL Config(const string& _path, const string& _name);
	DLL ~Config();
	template<typename T>
	T* Get(string _category, string _key);

private:
	friend class Application;

	string m_path;

	map<string, map<string, int>> m_intValues;
	map<string, map<string, bool>> m_boolValues;
	map<string, map<string, float>> m_floatValues;
	map<string, map<string, vec2>> m_vectorValues;
	map<string, map<string, Color>> m_colorValues;
	map<string, map<string, string>> m_textValues;

private:

	DLL void Load();
	DLL string ProcessLine(string _line, string _category);
	DLL void ProcessValue(string _line, string _category);
	DLL void ProcessDecimal(string _varName, string _val, string _category);
	DLL bool IsDecimal(string _val);
	DLL string ProcessCategory(string _line, string _category);

	template<typename T>
	void InsertValue(string _varName, T _value, string _category, map<string, map<string, T>>& _values);

	template<typename T>
	void ValidateCategory(string _category, map<string, map<string, T>>& _values);

};

template<typename T>
inline T* Config::Get(string _category, string _key)
{
	if (typeid(T) == typeid(int))
	{
		return (T*)(&m_intValues[_category][_key]);
	}

	if (typeid(T) == typeid(bool))
	{
		return (T*)(&m_boolValues[_category][_key]);
	}

	if (typeid(T) == typeid(float))
	{
		return (T*)(&m_floatValues[_category][_key]);
	}

	if (typeid(T) == typeid(vec2))
	{
		return (T*)(&m_vectorValues[_category][_key]);
	}

	if (typeid(T) == typeid(Color))
	{
		return (T*)(&m_colorValues[_category][_key]);
	}

	if (typeid(T) == typeid(string))
	{
		return (T*)(&m_textValues[_category][_key]);
	}

	std::cout << "Value not found for type: " << typeid(T).name() << " in category: " <<
		_category << " with the key: " << _key << std::endl;

	return nullptr;
}

template<typename T>
inline void Config::InsertValue(string _varName, T _value, string _category, map<string, map<string, T>>& _values)
{
	ValidateCategory(_category, _values);
	_values[_category][_varName] = _value;
}

template<typename T>
inline void Config::ValidateCategory(string _category, map<string, map<string, T>>& _values)
{
	if (_values.find(_category) == _values.end())
		_values[_category] = map<string, T>();
}
