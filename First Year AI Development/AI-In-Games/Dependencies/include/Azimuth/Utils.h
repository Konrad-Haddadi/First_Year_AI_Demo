#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Utils
{
	static bool Any(string _string, bool(*_predicate)(char));

	static bool All(string _string, bool(*_predicate)(char));

	static vector<string> Split(string _string, char _delim, int& _count);

	static bool TryParse(string _string, bool& _val);

	static bool TryParse(string _string, int& _val);
};