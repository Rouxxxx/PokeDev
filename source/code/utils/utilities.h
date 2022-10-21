#pragma once

#include <string>

class Utilities {
public:
	static inline bool IsInteger(const std::string& s) {
		if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
			return false;

		char* p;
		auto tmp = strtol(s.c_str(), &p, 10);
		return (*p == 0);
	}
};
