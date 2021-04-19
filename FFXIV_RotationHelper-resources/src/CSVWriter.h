#pragma once

#include <string>
#include <fstream>
#include <vector>

namespace FFXIV_RotationHelper_resources
{
	class CSVWriter
	{
	public:
		CSVWriter(const std::string& fileName, const std::string& header);

		~CSVWriter();

		void Write(const std::string& str);

		void Write(const char c);

		void NewLine();

		void EraseTop();

		void Save();

	private:
		std::ofstream file;
		std::vector<std::string> lines;
		int lineIdx;
	};
}
