#pragma once

#ifdef DLL_EXPORT
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

#include <concepts>

// This allows us to specify that a template type MUST
// inherit another class type
template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;