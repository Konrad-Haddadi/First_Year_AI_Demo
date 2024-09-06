#pragma once

#include <string>

template<typename T>
class Pair
{
public:
	Pair(char* _key, T* _value);
	~Pair();

	const char* GetKey() const;
	T* GetValue();

private:
	char* m_key;
	T* m_value;
};

template<typename T>
inline Pair<T>::Pair(char* _key, T* _value)
{
	int length = strlen(_key) + 1;
	m_key = new char[length];
	strncpy_s(m_key, length, _key, length);

	m_value = _value;
}

template<typename T>
inline Pair<T>::~Pair()
{
	if (m_key != nullptr)
	{
		delete m_key;
		m_key = nullptr;
	}

	if (m_value != nullptr)
	{
		delete m_value;
		m_value = nullptr;
	}
}

template<typename T>
inline const char* Pair<T>::GetKey() const
{
	return m_key;
}

template<typename T>
inline T* Pair<T>::GetValue()
{
	return m_value;
}
