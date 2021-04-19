#include "ClassJobCategory.h"

#include <cassert>
#include <string>

#include "SplitedString.h"
#include "WebReader.h"

using namespace FFXIV_RotationHelper_resources;

ClassJobCategory::ClassJobCategory(const int _count, const WebReader& webReader, const std::string fieldName)
	: count(_count + 1)
{
	flags = new bool[count] { false, };

	const SplitedString& category = webReader.Get(1);
	int col = category.Find(fieldName);

	int rowCount = webReader.GetCount();
	for (int i = 2; i < rowCount; i++)
	{
		const SplitedString& row = webReader.Get(i);
		if (row[col] == "True")
		{
			int idx = std::stoi(row[0]);
			flags[idx] = true;
		}
	}
}

ClassJobCategory::~ClassJobCategory()
{
	if (flags)
	{
		delete[] flags;
	}
}

bool ClassJobCategory::operator[](const int i) const
{
	assert(i >= 0 && i < count);

	return flags[i];
}
