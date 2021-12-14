#include "ClassJob.h"

#include <cassert>

#include "SplitedString.h"
#include "WebReader.h"

using namespace FFXIV_RotationHelper_resources;

ClassJob::ClassJob(ClassJobColumn column, const std::string& _fullName, const WebReader& webReader)
	: classJobType(column)
	, fullName(_fullName)
{
	categoryCount = stoi(webReader.Get(webReader.GetCount() - 1)[0]) + 1;
	category = new bool[categoryCount] { false, };

	const SplitedString& row = webReader.Get(1);
	int col = static_cast<int>(column);

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

ClassJobColumn ClassJob::GetClassJobType() const
{
	return classJobType;
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
