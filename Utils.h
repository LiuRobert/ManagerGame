#pragma once
#include <vector>

class Utils
{
public:

	template<typename T>
	static void addUnique(std::vector<T>& v, const T& value)
	{
		if (!contains(v, value))
			v.push_back(value);
	}
	
	template<typename T, typename Y>
	static bool contains(const std::vector<T>& v, const Y& value)
	{
		return std::find(v.begin(), v.end(), value) != v.end();
	}

	template<typename T, typename Y>
	static void remove(std::vector<T>& v, const Y& value)
	{
		v.erase(std::remove(v.begin(), v.end(), value), v.end());
	}

private:
	Utils(const Utils&) = delete;
	Utils() {};
	~Utils() {};
};
