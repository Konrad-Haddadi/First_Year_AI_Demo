#pragma once

#include "Azimuth/Azimuth.h"

#include "Azimuth/Resources/Resource.h"

#include <map>
#include<stdexcept>
#include <string>

using std::map;
using std::runtime_error;
using std::string;

class Resources
{
public:
	template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
	static RESOURCE* Find(string _id);

private:
	friend class Application;

	DLL static Resources* m_instance;

	map<string, string> m_paths;
	map<string, void*> m_resources;

private:
	DLL static Resources* GetInstance();

	DLL void Load();
	DLL void Unload();

	DLL void LocateFiles(string _folder, string _extension);
	DLL bool HasResource(const string& _id) const;

	DLL string PathFromID(const string& _id);

	template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
	static RESOURCE* TryGetResource(const string& _id);
};

template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
inline RESOURCE* Resources::Find(string _id)
{
	return dynamic_cast<RESOURCE*>(TryGetResource<ASSET, RESOURCE>(_id));
}

template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
inline RESOURCE* Resources::TryGetResource(const string& _id)
{
	Resources* resources = GetInstance();

	string path = resources->PathFromID(_id);
	if (!path.empty())
	{
		if (!resources->HasResource(_id))
			resources->m_resources[_id] = new RESOURCE(path);

		return (RESOURCE*)resources->m_resources[_id];
	}

	throw runtime_error("No resource with id '" + _id + "' found!");
	return nullptr;
}
