#include "SplitedString.h"

#include <cassert>

using namespace FFXIV_RotationHelper_resources;

void SplitedString::Initialize(const std::string& str, int strSize)
{
	assert(str.size());

	bool bQuote = false;

	int offset = 0;
	int i = 0;
	for (; i < strSize; i++)
	{
		if (bQuote && str[i] == '\"')
		{
			bQuote = false;

			std::string substr;
			substr.assign(str.begin() + offset, str.begin() + i);
			s.push_back(substr);

			i++;
			offset = i + 1;
		}
		else if (!bQuote && str[i] == '\"')
		{
			bQuote = true;

			offset = i + 1;
		}
		else if (!bQuote && str[i] == ',')
		{
			std::string substr;
			substr.assign(str.begin() + offset, str.begin() + i);
			s.push_back(substr);
			
			offset = i + 1;
		}
	}

	if (offset < i)
	{
		std::string substr;
		substr.assign(str.begin() + offset, str.begin() + i);
		s.push_back(substr);
	}
}

std::string SplitedString::operator[](int i) const
{
	assert((size_t)i >= 0 && (size_t)i < s.size());

	return s[i];
}

int SplitedString::GetCount() const
{
	return (int)s.size();
}

int SplitedString::Find(const std::string& str) const
{
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == str)
		{
			return (int)i;
		}
	}

	return -1;
}
