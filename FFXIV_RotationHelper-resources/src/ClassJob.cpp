#include "ClassJob.h"

#include <cassert>

#include "SplitedString.h"
#include "WebReader.h"

using namespace FFXIV_RotationHelper_resources;

ClassJob::ClassJob(const std::string& _shortName, const std::string& _fullName, const WebReader& webReader)
	: shortName(_shortName)
	, fullName(_fullName)
{
	categoryCount = stoi(webReader.Get(webReader.GetCount() - 1)[0]) + 1;
	category = new bool[categoryCount] { false, };

	const SplitedString& row = webReader.Get(1);
	int col = row.Find(shortName);

	int rowCount = webReader.GetCount();
	for (int i = 2; i < rowCount; i++)
	{
		const SplitedString& row = webReader.Get(i);
		if (row[col] == "True")
		{
			int idx = std::stoi(row[0]);
			category[idx] = true;
		}
	}
}

ClassJob::~ClassJob()
{
	if (category)
	{
		delete[] category;
	}
}

const std::string& ClassJob::GetShortName() const
{
	return shortName;
}

const std::string& ClassJob::GetFullName() const
{
	return fullName;
}

bool ClassJob::IsClassJobCategory(int field) const
{
	assert(field >= 0 && field < categoryCount);

	return category[field];
}
