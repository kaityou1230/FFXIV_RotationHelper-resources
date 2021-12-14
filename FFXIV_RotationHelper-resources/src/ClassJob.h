#pragma once

#include <string>

#include "ClassJobColumn.h"

namespace FFXIV_RotationHelper_resources
{
	class WebReader;

	class ClassJob
	{
	public:
		ClassJob(ClassJobColumn column, const std::string& _fullName, const WebReader& webReader);

		~ClassJob();

		ClassJobColumn GetClassJobType() const;

		const std::string& GetFullName() const;

		bool IsClassJobCategory(int field) const;

	private:
		ClassJobColumn classJobType;
		std::string fullName;
		int categoryCount;
		bool* category;
	};
}