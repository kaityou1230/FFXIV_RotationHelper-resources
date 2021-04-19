#pragma once

#include <string>

namespace FFXIV_RotationHelper_resources
{
	class SplitedString;

	class WebReader
	{
	public:
		WebReader(const std::wstring& url);

		~WebReader();

		const SplitedString& Get(const int idx) const;

		int GetCount() const;

	private:
		int getLineCount(const std::string& str) const;

	private:
		SplitedString* split;
		int count;
	};
}
