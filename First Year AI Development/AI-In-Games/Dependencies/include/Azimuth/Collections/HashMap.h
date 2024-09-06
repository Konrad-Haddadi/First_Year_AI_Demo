#pragma once

#include "Pair.h"

extern unsigned int DefaultHash(const char* _str);
extern unsigned int ELFHash(const char* _str);
extern unsigned int BKDRHash(const char* _str);

template<typename T, unsigned int (*HASH_FUNC)(const char*) = DefaultHash>
class HashMap
{
public:
	HashMap();
	~HashMap();

	const T* GetValue(char* _key);

	void AddValue(char* _key, T* _value);


private:
	const unsigned int MAP_SIZE = 256;
	Pair<T>** m_map;
};

template<typename T, unsigned int(*HASH_FUNC)(const char*)>
inline HashMap<T, HASH_FUNC>::HashMap()
{
	m_map = new Pair<T>*[MAP_SIZE];

	for (int i = 0; i < MAP_SIZE; i++)
		m_map[i] = nullptr;
}

template<typename T, unsigned int(*HASH_FUNC)(const char*)>
inline HashMap<T, HASH_FUNC>::~HashMap()
{
	for (int i = 0; i < m_map; i++)
	{
		if (m_map[i] != nullptr)
			delete m_map[i];
	}

	delete[] m_map;
	m_map = nullptr;
}

template<typename T, unsigned int(*HASH_FUNC)(const char*)>
inline const T* HashMap<T, HASH_FUNC>::GetValue(char* _key)
{
	unsigned int hash = HASH_FUNC(_key);
	unsigned int index = hash % MAP_SIZE;

	if (index > MAP_SIZE || m_map[index] == nullptr)
		return nullptr;

	return m_map[index]->GetValue();
}

template<typename T, unsigned int(*HASH_FUNC)(const char*)>
inline void HashMap<T, HASH_FUNC>::AddValue(char* _key, T* _value)
{
	unsigned int hash = HASH_FUNC(_key);
	unsigned int index = hash % MAP_SIZE;

	if (index > MAP_SIZE)
		return;

	if (m_map[index] != nullptr)
	{
		// We have a collision
		delete m_map[index];
	}

	m_map[index] = new Pair<T>(_key, _value);
	
}
