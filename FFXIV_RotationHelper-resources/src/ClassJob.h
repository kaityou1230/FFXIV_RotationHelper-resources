#pragma once

#include <string>

namespace FFXIV_RotationHelper_resources
{
	class WebReader;

	class ClassJob
	{
	public:
		ClassJob(const std::string& _shortName, const std::string& _fullName, const WebReader& webReader);

		~ClassJob();

		const std::string& GetShortName() const;
		
		const std::string& GetFullName() const;

		bool IsClassJobCategory(int field) const;

	private:
		std::string shortName;
		std::string fullName;
		int categoryCount;
		bool* category;
	};
}