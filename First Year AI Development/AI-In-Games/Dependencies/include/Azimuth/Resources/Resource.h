#pragma once

#include <string>

using std::string;

template<typename T>
class Resource
{
public:
	T Get();
	void Dispose();


	operator T() { return Get(); }

protected:
	T* m_resource;

protected:
	Resource(T(*_load)(const char*), void(*_unload)(T), string _path);
	~Resource();

private:
	friend class Resources;

	string m_path;

	T(*m_load)(const char*);
	void(*m_unload)(T);

};

template<typename T>
inline T Resource<T>::Get()
{
	if (m_resource == nullptr)
	{
		m_resource = new T();
		*m_resource = m_load(m_path.c_str());
	}

	return *m_resource;
}

template<typename T>
inline void Resource<T>::Dispose()
{
	if (m_resource != nullptr)
	{
		m_unload(*m_resource);
		delete m_resource;
		m_resource = nullptr;
	}
}

template<typename T>
inline Resource<T>::Resource(T(*_load)(const char*), void(*_unload)(T), string _path)
	:m_resource(nullptr), m_path(std::move(_path)), m_load(_load), m_unload(_unload)
{

}

template<typename T>
inline Resource<T>::~Resource()
{
	Dispose();
}
