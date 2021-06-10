#pragma once

#include <string>
#include <vector>

namespace FFXIV_RotationHelper_resources
{
	class SplitedString
	{
	public:
		SplitedString() = default;

		void Initialize(const std::string& str, int strSize);

		const std::string& operator[](int i) const;

		int GetCount() const;

		int Find(const std::string& str) const;

	private:
		std::vector<std::string> s;
	};
}