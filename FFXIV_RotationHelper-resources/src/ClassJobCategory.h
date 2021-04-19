#pragma once

#include <string>

namespace FFXIV_RotationHelper_resources
{
	class WebReader;

	class ClassJobCategory
	{
	public:
		ClassJobCategory(const int _count, const WebReader& webReader, const std::string fieldName);

		~ClassJobCategory();

		bool operator[](const int i) const;

	private:
		int count;
		bool* flags;
	};
}